#include "Common.h"
/*#############################################################

						   プレーヤー自機

##############################################################*/
/*=============================================================
自弾実態
=============================================================*/
//初期化
void PBullet::Init(){
	for(int i=0;i<MBCAP;i++){
		pbNo[i]=0;
		My::Bullet::flg[i]=0;
	}
}

//画像セット
int PBullet::imgset(int bimage){
	mkImg=bimage;
	return mkImg;
}

//弾の作成
void PBullet::create(int x, int y, double Deg, double scalar,int idx){
	mkflg=1;
	mkx=x;
	mky=y;
	mkDeg=Deg;
	mkScl=scalar;
	mkidx=idx;
}

//移動、及び描画
void PBullet::move(){
	int i = 0;
	while(i++<Cap){
		if(pbNo[i]==0){ //弾のフラグがなかったら
			if(mkflg==1){//弾を作成する必要があったら
				pbNo[i]=1;
				pbx[i]=(float)mkx;
				pby[i]=(float)mky;
				math m;
				double r = m.ToRadian(mkDeg);
				double r2=m.ToRadian(180-mkDeg);
				pbvx[i]=(float)(mysin(r2)*mkScl);
				pbvy[i]=(float)(mycos(r2)*mkScl);
				pbrad[i]=(float)r;
				pbImg[i]=mkImg;
				pbIdx[i]=mkidx*50+i;
				My::Bullet::flg[pbIdx[i]]=true;
				My::Bullet::IsHit[pbIdx[i]]=false;
				mkflg=0;
				//発射エフェクト
				//DrawRotaGraph(pbx[i]+pbvx[i]+PjSys::Scr::MoveX,pby[i]+pbvy[i]+PjSys::Scr::MoveY,1.0,r,My::Bullet::pbFire[0][i%8],TRUE);

				i--;
			}
		}else{//弾のフラグがあったら
			if(My::Bullet::IsHit[pbIdx[i]]==true){
				My::Bullet::flg[pbIdx[i]]=false;
			}
			pbx[i]+=pbvx[i];//加算
			pby[i]+=pbvy[i];
			if ((pbx[i]<120)||(pbx[i]>520)||(pby[i]<0)||(pby[i]>480)){ //はみ出したらフラグ消去
				pbNo[i]=0;My::Bullet::flg[pbIdx[i]]=false;
			}else{
				My::Bullet::x[pbIdx[i]]=(int)pbx[i];
				My::Bullet::y[pbIdx[i]]=(int)pby[i];
				if(My::Bullet::flg[pbIdx[i]]){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,32+i);
					if(My::DefFrame>0){
						SetDrawBright(255,255,255);
						DrawRotaGraph((int)pbx[i]+PjSys::Scr::MoveX , (int)pby[i]+PjSys::Scr::MoveY  , 1.0f , pbrad[i] , pbImg[i] , TRUE); //描画
					}else{
						DrawRotaGraph((int)pbx[i]+PjSys::Scr::MoveX , (int)pby[i]+PjSys::Scr::MoveY  , 1.0f , pbrad[i] , pbImg[i] , TRUE); //描画
					}
						/*
					SetUseZBuffer3D( TRUE ) ;
					SetWriteZBuffer3D( TRUE ) ;
					DxLib::VECTOR pLoc={(float)(pbx[i]+PjSys::Scr::MoveX),(float)(pby[i]+PjSys::Scr::MoveY),0.4f};
					DrawBillboard3D( ConvScreenPosToWorldPos( pLoc ), 0.5f, 0.5f, 5.0f, pbrad[i], pbImg[i], TRUE ) ;
					SetUseZBuffer3D( FALSE ) ;
					SetWriteZBuffer3D( FALSE ) ;
					*/
					if(My::DefFrame>0){
						SetDrawBright(255,255,255);
					}
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
					PjSys::DrawGuide( (int)pbx[i]-My::Bullet::region/2, (int)pby[i]-My::Bullet::region/2,(int)pbx[i]+My::Bullet::region/2 ,(int)pby[i]+My::Bullet::region/2);
				}
			}
		}
	}
}
/************************************************************
自機実態
****************************************************************/

int Player::Pause(int& img){
	static const int U = PAD_INPUT_UP;
	static const int D = PAD_INPUT_DOWN;
	static const int L = PAD_INPUT_LEFT;
	static const int R = PAD_INPUT_RIGHT;
	static const int A = PjSys::key::shot_p;
	static const int B = PjSys::key::sub_p;
	static const int C = PjSys::key::bomb_p;

	//コナミコマンド(自爆する)
	static int KC[10] = {U,U,D,D,L,R,L,R,B,A};
	static CommandInput KonantokaCommand(KC,10);

	//無敵コマンド(↓↓→→↑↑B↑↑←←↓↓A)
	static int IC[14] = {D,D,R,R,U,U,B,U,U,L,L,D,D,A};
	static CommandInput InvCommand(IC,14);

	//レベル最大コマンド(CCCCCCCCCA)
	static int LMC[10] = {C,C,C,C,C,C,C,C,C,A};
	static CommandInput LvMaxCommand(LMC,10);

	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::pause_p ) != 0){
	//if(CheckHitKey(KEY_INPUT_P)==1){
		if(PauseKey==0){
				if(!NowPause){
					NowPause=true;
					My::Pause=true;
					IsBGMPaused=false;
					IsBossBGMPaused=false;
					if(CheckSoundMem(PjSys::bgm)==1){
						IsBGMPaused=true;
						StopSoundMem(PjSys::bgm);
					}
					if(CheckSoundMem(PjSys::bossbgm)==1){
						IsBossBGMPaused=true;
						StopSoundMem(PjSys::bossbgm);
					}
				//	PjSys::Scr::ImgScrShot = MakeGraph( 640 , 480 ) ;
					// 画面データの取りこみ
				//	GetDrawScreenGraph( 0 , 0 , 640 , 480 , PjSys::Scr::ImgScrShot ) ;

					PausePhase=0;
				}else{
					NowPause=false;
					My::Pause=false;
					if(IsBGMPaused==true){
						PlaySoundMem( PjSys::bgm , DX_PLAYTYPE_LOOP , FALSE ) ;
					}
					if(IsBossBGMPaused==true){
						PlaySoundMem( PjSys::bossbgm , DX_PLAYTYPE_LOOP , FALSE ) ;
					}
				//	DeleteGraph(PjSys::Scr::ImgScrShot);
					PausePhase=0;
				}
		}
		PauseKey=1;
	}else{PauseKey=0;}
	if(GetActiveFlag()==FALSE){NowPause=true;} //非アクティブだったらポーズ有効
	if(NowPause){
		//メニューに戻る
		if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p) !=0 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::sub_p) !=0 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::bomb_p) !=0) {
				NowPause=false;
				My::Pause=false;
				PausePhase=0;
				InitSoundMem() ;
				InitGraph();
				stage.setstage(0);
		}

		//隠しコマンド
		if(KonantokaCommand.Check() == true){
			PlaySoundMem(SndBorn,DX_PLAYTYPE_BACK);
			My::IsHit=true;
		}
			if(InvCommand.Check() == true){
				PlaySoundMem(SndBorn,DX_PLAYTYPE_BACK);
				if(PjSys::cheat::Inv){PjSys::cheat::Inv=false;}else{PjSys::cheat::Inv=true;}
			}
			if(LvMaxCommand.Check() == true){
				PlaySoundMem(My::sw::sndLv[4],DX_PLAYTYPE_BACK);
				My::SubLevel=5;
			}

		if(PausePhase<=80){
			int line=DerivationGraph( PausePhase*5, 0, 1, 64, img ) ;
			DrawModiGraph(PausePhase*5+120,208 ,520,208,520,272,PausePhase*5+120,272,line,true);
			DrawRectGraph(120 ,208 ,0,0,PausePhase*5 , 64,img,true ,false ) ;
			PausePhase++;
			return 1;
		}else if(PausePhase<161){
			int line=DerivationGraph( (PausePhase-80)*5, 0, 1, 64, img ) ;
			DrawModiGraph(120,208 ,120+(PausePhase-80)*5,208,120+(PausePhase-80)*5,272,120,272,line,true);
			DrawRectGraph(120+(PausePhase-80)*5 ,208 ,(PausePhase-80)*5,0,400-(PausePhase-80)*5,64,img,true ,false ) ;

			PausePhase++;
			return 1;
		}else if(PausePhase==161){
			PausePhase=0;
			return 1;
		}

		PausePhase++;

		return 1;
	}else{return 0;}
}

int Player::GameOver(int& img){ //ゲームオーバー
	PjSys::Scr::DrawNoise();

	if(pPhase==0){
		InitSoundMem() ;

		My::NowInv=true;
		My::Move=false;
		px[0]=120;
		py[0]=240-32;
		PjSys::Scr::AddLog(" - GAME OVER -",0,GetColor(255,0,0));
		PjSys::Scr::IsNoise=240;
		PjSys::Scr::NoiseAlpha=255;
	}else if(pPhase==240){
		My::GOver=false;
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0 );
		InitGraph() ;
		stage.setstage(0);
		pPhase=0;
		return 1;
	}else{
		for(int i=1;i<5;i++){ //エフェクトループ
			SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(16*pow(2.0,5-i)-1));
			DrawRotaGraph((int)(320 - 50*(i-1) + (pPhase-40)*(1.0*(i-1))),240,0.8+0.2*i,0,img,true);
			//SetDrawBright(255,(int)(16*pow(2.0,i)-1),(int)(16*pow(2.0,i)-1));
		}

		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0 );
	}
	pPhase++;
	return 0;
}

void Player::Draw(int* img,int* inv){//描画
	if(My::Invincible>0 || PjSys::cheat::Inv){ //無敵判定
		My::Invincible--;
		My::NowInv=true;
		if(My::Invincible<=30){
			SetDrawBright(135+My::Invincible*4,135+My::Invincible*4,135+My::Invincible*4);
		}
		DrawRotaGraph((int)getX()+PjSys::Scr::MoveX , (int)getY()+PjSys::Scr::MoveY  , 1.0f , 0 , *inv , TRUE) ;

		if(My::Invincible<=30){SetDrawBright(255,255,255);}
	}else{
		My::NowInv=false;
	}
	if(My::DefFrame>0){
		if(--My::DefFrame>SUBINVFRAME){//ディフェンダー判定
			SetDrawBright(255,255-50*My::SubLevel,255-50*My::SubLevel);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
			SetDrawMode(1);
			DrawRotaGraph((int)getX()+PjSys::Scr::MoveX , (int)getY()+PjSys::Scr::MoveY  , 2.0f , 0 , *inv , TRUE) ;
			SetDrawMode(0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			SetDrawBright(255,255,255);
			//PjSys::Scr::BGWire=true;
			if(SUBFRAMECNT*My::SubLevel-My::DefFrame<=30){
				//SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
				//DrawCircle((int)getX(),(int)getY(),(SUBFRAMECNT*(My::SubLevel-2)-My::DefFrame)*10,GetColor(255,0,0),0);
				//SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
		}else if(My::DefFrame<=1){
				My::SubLevel=0;
				My::SubEnergy=0;
				My::DefFrame=0;
				My::Laser::RefCounterMax=0;
				My::Laser::RefCounterMin=8;
		}else if(My::DefFrame>1 && My::DefFrame<=SUBINVFRAME){
			if(My::DefFrame==SUBINVFRAME&&CheckSoundMem(SndDefE)!=1){PlaySoundMem(SndDefE,DX_PLAYTYPE_BACK,true);} //ディフェンダー終了音
			SetDrawBright(My::DefFrame*255/SUBINVFRAME,0,0);
			SetDrawBlendMode(DX_BLENDMODE_ADD,My::DefFrame*127/SUBINVFRAME);
			DrawRotaGraph((int)getX()+PjSys::Scr::MoveX , (int)getY()+PjSys::Scr::MoveY  , 2.0f , 0 , *inv , TRUE) ;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			SetDrawBright(255,255,255);
			//PjSys::cheat::Inv=true;
			My::Invincible=My::DefFrame;
			PjSys::Scr::BGWire=false;
		}
	}
	double d;
	math m;
	switch(imgNo){
		case 0:
			d=m.ToRadian(-10.0);
			break;
		case 1:
			d=0;
			break;
		case 2:
			d=m.ToRadian(10.0);
			break;
	}
//	MV1SetDifColorScale( My::Model, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
	//ベイパー
	Vapor::Move();

	//自機モデルの描画
	SetCameraPositionAndAngle( PjSys::CameraPos, DX_PI_F/-2.0f, 0, 0 ) ;
	DxLib::VECTOR pLoc={(float)getX()+PjSys::Scr::MoveX-1,(float)getY()+PjSys::Scr::MoveY,0.4f};
	MV1SetPosition( My::Model, ConvScreenPosToWorldPos( pLoc ) ) ;
	MV1SetScale( My::Model, VGet(My::Exp,My::Exp,My::Exp )) ;
	MV1SetRotationXYZ(My::Model, VGet(My::fLoop,0,DX_PI_F/60*My::Rot)) ;
	MV1DrawModel( My::Model ) ;
	//PjSys::NumDraw(PjSys::SmallNum,My::NowBuzz,My::x,My::y,16);
	if(My::IsBurner){
		DxLib::VECTOR ab={(float)getX()+PjSys::Scr::MoveX-1,(float)getY()+PjSys::Scr::MoveY,0.4f};
		//MV1SetOpacityRate( My::burner, 0.5f ) ;
		MV1SetRotationXYZ(My::burner, VGet(My::fLoop,0,DX_PI_F/60*My::Rot)) ;
		MV1SetPosition( My::burner, ConvScreenPosToWorldPos( ab ) ) ;
		MV1SetScale( My::burner, VGet(My::Exp,My::Exp*2,My::Exp )) ;
		MV1DrawModel(My::burner) ;
	}
	//DrawRotaGraph((int)getX()+PjSys::Scr::MoveX , (int)getY()+PjSys::Scr::MoveY  , 1.0f , d , img[imgNo] , TRUE) ;//自機の描画
	SetDrawBright(255,255,255);
	if(My::BuzzLvFrame>0 && My::BuzzLv>0){
		//バズ描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(My::NowBuzz>0)?255:My::BuzzLvFrame*6);
		SetDrawBright(255, (int)(255/My::BuzzLv), (int)(255/My::BuzzLv));
		DrawRotaGraph((int)getX()+PjSys::Scr::MoveX-1,(int)getY()+PjSys::Scr::MoveY,1.0f,PI/60*My::BuzzLvFrame,My::imgBuzz,true);
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	if(My::NowBuzz>0){ //バズスコア加算
		My::AddScore((int)(pow((float)BUZZSCORE,My::BuzzLv)));
	}

	if(My::ctphase>0){
		int i;
		if(My::ctphase>=48){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(64-My::ctphase)*16-1);
			i=48-My::ctphase;
			DrawModiGraph((int)getX()+i+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY, (int)getX()+64+i+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY,(int)getX()+64+i+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY, (int)getX()+i+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY,PjSys::SmallChar[My::chartip] , TRUE );
		}else if(My::ctphase>16){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,224);
			i=0;
			DrawModiGraph((int)getX()+i+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY, (int)getX()+64+i+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY,(int)getX()+64+i+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY, (int)getX()+i+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY,PjSys::SmallChar[My::chartip] , TRUE );
		}else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,My::ctphase*16-1);
			i=My::ctphase*-1+16;
			DrawModiGraph((int)getX()+i+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY, (int)getX()+64+i*10+PjSys::Scr::MoveX, (int)getY()-40-i+PjSys::Scr::MoveY,(int)getX()+64+i*10+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY, (int)getX()+i+PjSys::Scr::MoveX, (int)getY()-24-i+PjSys::Scr::MoveY,PjSys::SmallChar[My::chartip] , TRUE );
		}
		//DrawRotaGraph((int)getX()+32+i+PjSys::Scr::MoveX , (int)getY()-32-i+PjSys::Scr::MoveY  , 1.0f , 0 , PjSys::SmallChar[My::chartip] , TRUE) ;//情報チップの描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		My::ctphase--;
	}
	if(My::ntphase>0){
		int i;
		if(My::ntphase>=48){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(64-My::ntphase)*8-1);
			i=48-My::ntphase;
		}else if(My::ntphase>16){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
			i=0;
		}else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,My::ntphase*8-1);
			i=My::ntphase*-1+16;
		}
		PjSys::NumDraw(PjSys::SmallNum,My::numtip,(int)getX()+24+i,(int)getY()-24-i,8);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		My::ntphase--;
	}
	if(My::Invincible<=32 && My::Invincible>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
		//DrawBox((int)My::x-15,(int)My::y+32,(int)My::x-15+My::Invincible,(int)My::y+40,GetColor(255,0,0),true);
		SetDrawBright(255,0,0);
		DrawRectGraph( (int)My::x-16, (int)My::y+32, 0, 0, My::Invincible, 8, My::imgLeftTimeGaze, FALSE, FALSE ) ;
		SetDrawBright(255,255,255);
		DrawBox((int)My::x-16,(int)My::y+32,(int)My::x+16,(int)My::y+40,GetColor(255,255,255),false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	if(My::DefFrame>1 && My::DefFrame<=SUBINVFRAME+32 && My::DefFrame>=SUBINVFRAME){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
//			DrawBox((int)My::x-15,(int)My::y+40,(int)My::x-15+My::DefFrame-SUBINVFRAME,(int)My::y+48,GetColor(255,255,0),true);
		SetDrawBright(255,255,0);
		DrawRectGraph( (int)My::x-16, (int)My::y+40, 0, 0, My::DefFrame-SUBINVFRAME, 8, My::imgLeftTimeGaze, FALSE, FALSE ) ;
		SetDrawBright(255,255,255);
		DrawBox((int)My::x-16,(int)My::y+40,(int)My::x+16,(int)My::y+48,GetColor(255,255,255),false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}

	PjSys::DrawGuide((int)getX()-2,(int)getY()-2,(int)getX() + 2,(int)getY() + 2);
	//pbSub.move();
	if(My::SubFrame>0){
		if(--My::SubFrame==0){
			--My::SubLevel;
			My::Invincible=0;
		}else{
			My::Invincible=My::SubFrame;
		}
	}
	for(int i = 0; i < 5; i++){pbStraight[i].move();}

			if(My::NowBuzz>0){
				DrawRotaGraph((int)getX()+PjSys::Scr::MoveX, (int)getY()+PjSys::Scr::MoveY, 1.0f , 0 , My::imgRegion, TRUE);
				My::NowBuzz=0;
			}
}

int Player::Dead(){ //プレイヤーの死亡時。パーティクルを飛ばす
	int i=0;
	if(pPhase==0){
		My::BombFrame=0;
		if(!My::SubFrame || !My::DefFrame){
			My::SubEnergy=0;
			My::DefFrame=0;
			My::SubFrame=0;
		}
		PjSys::Scr::BGWire=false;
		PjSys::Scr::AddLog("LOST A STOCK!\0",0,GetColor(255,128,128));
		My::NowInv=true;
		PjSys::Scr::SetShake(50,-10,10);
		//PlaySoundMem(SndDead,DX_PLAYTYPE_BACK);
			if(PlaySoundMem(SndDead,DX_PLAYTYPE_BACK)==-1){
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				ErrorLogAdd("SndDead has been Reloaded.\n");
				SndDead=LoadSoundMem( "snd\\dead.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , SndDead );
				PlaySoundMem(SndDead,DX_PLAYTYPE_BACK,true);
			}
		//}else if(pPhase==20){
		PjSys::Scr::IsNoise=100;
		PjSys::Scr::NoiseAlpha=96;
	}else if(pPhase==100){
		if(My::Left==0){
			//PjSys::Scr::ImgScrShot = MakeGraph( 640 , 480 ) ;
			// 画面データの取りこみ
			//GetDrawScreenGraph( 0 , 0 , 640 , 480 , PjSys::Scr::ImgScrShot ) ;

			My::GOver=true;
		}else{
			My::Left--;
			PjSys::Scr::AddLog((My::Left>1)?("%d STOCKS LEFT.\0"):("%d STOCK LEFT.\0"),My::Left,GetColor(255,255,255));
		}
	}
	while(i++<180){
		if(pPhase==0){
			double s;
			math m;
			s=m.irand(1,8)*(1+(double)rand()/(double)(RAND_MAX+0.1));
			pImgNo[i]=m.irand(0,7);
			pvx[i]=mysin(m.ToRadian(i*2))*s;
			pvy[i]=mycos(m.ToRadian(i*2))*s;
			px[i]=My::x;
			py[i]=My::y;
		}else if(pPhase==100){
			My::IsHit=false;
			My::Born=true;
			MV1SetWireFrameDrawFlag(My::Model,false);

			for(int j=0;j<50*5;j++){
				My::Bullet::x[j]=0;
				My::Bullet::y[j]=0;
				My::Bullet::flg[j]=false;
			}

			//My::Move=true;
			pPhase=0;
			return 1;
		}else{
			//PjSys::Scr::SetShake(2,(int)(20-(pPhase/5))*-1,(int)(20-(pPhase/5)));
			My::Invincible=1;
			px[i]+=pvx[i];
			py[i]+=pvy[i];
			//SetDrawBright( 255 - pPhase , 255 - pPhase , 255 - pPhase ) ;
			SetDrawMode(1);
			SetDrawBlendMode(DX_BLENDMODE_ADD,192-pPhase);
			DrawLine((int)(px[i]+PjSys::Scr::MoveX) , (int)(py[i]+PjSys::Scr::MoveY)  ,(int)(px[i]-pvx[i]*10+PjSys::Scr::MoveX) ,(int)(py[i]-pvy[i]*10+PjSys::Scr::MoveY),GetColor( 255 - pPhase*2 , 128-pPhase , 128-pPhase));
			//DrawModiGraph((int)(px[i]+PjSys::Scr::MoveX) , (int)(py[i]+PjSys::Scr::MoveY),(int)(px[i]+PjSys::Scr::MoveX+1) , (int)(py[i]+PjSys::Scr::MoveY+1),(int)(px[i]-pvx[i]*10+PjSys::Scr::MoveX) ,(int)(py[i]-pvy[i]*10+PjSys::Scr::MoveY),(int)(px[i]-pvx[i]*10+PjSys::Scr::MoveX+1) ,(int)(py[i]-pvy[i]*10+PjSys::Scr::MoveY+1),PjSys::Scr::BurstImg,TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			SetDrawMode(1);
			SetDrawBright( 255  , 255  , 255  ) ;
		}
	}
	pPhase++;
	return 0;
}
int Player::Born(int* img,int& eff){ //プレイヤーの出撃時。
	if(pPhase==0){
		My::SubFrame=0;
		My::DefFrame=0;
		My::NowInv=true;
		My::Move=false;
		My::IsBurner=true;
		//PlaySoundMem(SndBorn,DX_PLAYTYPE_BACK);
			if(PlaySoundMem(SndBorn,DX_PLAYTYPE_BACK)==-1){
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				ErrorLogAdd("Born has been Reloaded.\n");
				SndBorn=LoadSoundMem( "snd\\born.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , SndBorn );
				PlaySoundMem(SndBorn,DX_PLAYTYPE_BACK,true);
			}
		My::Exp=MY_MODEL_EXP;
		My::Invincible=47;
		PjSys::Scr::AddLog("DIANA SYSTEM STARTED...",0,GetColor(128,255,128));
	}else if(pPhase==45){
		My::Born=false;
		My::Move=true;
		//My::NowInv=false;
		My::Invincible=INVFRAME;
		My::Bomb=My::DefaultBomb;
		My::Exp=MY_MODEL_EXP;
		My::IsBurner=false;
		pPhase=0;
		PjSys::Scr::AddLog("READY TO FIGHT.",0,GetColor(128,255,255));
		return 1;
	}else{
		//DrawRectGraph((int)My::x-24+PjSys::Scr::MoveX,(int)My::y-24+PjSys::Scr::MoveY,0,0,48,pPhase,img[1], true, false );//上から下へ
		//DrawRotaGraph((int)My::x+PjSys::Scr::MoveX,(int)My::y+pPhase-24+PjSys::Scr::MoveY,1.0,0,eff,true) ;
		My::Exp=MY_MODEL_EXP+mycos(DX_PI_F/90.0f*pPhase)*5;
		My::NowInv=true;
		//自機モデルの描画
		MV1SetDifColorScale( My::Model, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
		SetCameraPositionAndAngle( PjSys::CameraPos, DX_PI_F/-2.0f, 0, 0 ) ;
		DxLib::VECTOR pLoc={(float)getX()+PjSys::Scr::MoveX,(float)getY()+PjSys::Scr::MoveY+mysin(pPhase*4*DX_PI_F/180.0f)*-100.0f,0.3f};
		MV1SetPosition( My::Model, ConvScreenPosToWorldPos( pLoc ) ) ;
		MV1SetScale( My::Model, VGet(My::Exp,My::Exp,My::Exp )) ;
		MV1SetRotationXYZ(My::Model, VGet(0,0,DX_PI_F/180*pPhase*7.5f)) ;
		MV1DrawModel( My::Model ) ;
		Vapor::Make(0,(int)(getX()+PjSys::Scr::MoveX-mycos(DX_PI_F/180*pPhase*7.5f)*24*My::Exp/MY_MODEL_EXP),(int)(getY()+PjSys::Scr::MoveY+mysin(pPhase*4*DX_PI_F/180.0f)*-100.0f),255);
		Vapor::Make(1,(int)(getX()+PjSys::Scr::MoveX+mycos(DX_PI_F/180*pPhase*7.5f)*24*My::Exp/MY_MODEL_EXP),(int)(getY()+PjSys::Scr::MoveY+mysin(pPhase*4*DX_PI_F/180.0f)*-100.0f),255);
		Vapor::Move();
	}
	pPhase++;
	return 0;
}
//ボムチェック
void Player::Bomb(int& img){
	if(My::BombFrame==0){
		if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::bomb_p ) != 0){
			if(My::Bomb>0){
				PjSys::Scr::SetShake(BMBFRAME,-6,6);
				//PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK);
				if(PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK)==-1){
					//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
					ErrorLogAdd("SndBomb has been Reloaded.\n");
					My::SndBomb=LoadSoundMem( "snd\\bomb.wav" ) ;
					ChangeVolumeSoundMem(Setting.General.SEVolume , My::SndBomb );
					PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK,true);
				}
				My::Invincible=120;
				My::BuzzLv=0;
				My::IsAutoBomb=false;
				My::BombDeletedBullet=0;
				PjSys::Scr::SetBurst(320,240,12,40,255,255,255,false,32);
				My::BombFrame++;
				My::Bomb--;
				PjSys::Scr::AddLog("BOMB LAUNCHED...OK\0",0,GetColor(128,255,128));
				if(My::Bomb>1){
					PjSys::Scr::AddLog("%d BOMBS LEFT.\0",My::Bomb,GetColor(255,255,255));
				}else{
					PjSys::Scr::AddLog("%d BOMB LEFT.\0",My::Bomb,GetColor(255,255,255));
				}
			}else{
				//PjSys::Scr::AddLog("BOMB LAUNCHED...FAILED!",0,GetColor(255,128,128));
			}
		}
	}else if(++My::BombFrame==BMBFRAME || My::Move==false){
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		PjSys::Scr::BGColor=GetColorF(1.0f,1.0f,1.0f,1.0f);
		My::BombFrame=0;
	}else{
		PjSys::Scr::BGColor=GetColorF(1.0f,0.0f,0.0f,0.7f);
		SetDrawBright(255,128,128);
		SetDrawMode(1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-My::BombFrame*4);
		DrawRotaGraph(320,240,(double)My::BombFrame/2,0,img,true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		SetDrawMode(0);
		SetDrawBright(255,255,255);
	}
}
//===========================================
//  自機の移動
//===========================================
void Player::Move(){
	int angle=-1;
	bool right = false,left = false,up = false,down = false,shot=false,horizon=false;
	//右へ
	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_RIGHT ) != 0 ){
		right = true;
		if(My::Rot>-15){
			if(My::Rot<15 && frmLRoll==0 && frmRRoll==0){
				My::Rot++;
			}
		}else{
			if(frmLRoll==0 && frmRRoll==0){My::Rot=4;frmLRoll=60;}
		}
	}

	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_LEFT ) != 0 ){
		left = true;
		if(My::Rot<15){
			if(My::Rot>-15 && frmLRoll==0 && frmRRoll==0){
				My::Rot--; //傾ける
			}
		}else{
			if(frmLRoll==0 && frmRRoll==0){
				My::Rot=-4;
				frmRRoll=60;
			}
		}
	}
	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_UP ) != 0 ){up = true;}
	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_DOWN ) != 0 ){down = true;}

	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::slow_p ) != 0){
		IsSlow = true;
	}else{
		IsSlow=false;
	}
	//if(::CheckHitKey(KEY_INPUT_LCONTROL)){fast = true;}

	//メインショットを撃っているか？
	if(My::Bullet::frm>=0 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0){
		My::Bullet::frm=0;
		shot=true;
	}else{
		My::Bullet::frm++;
	}
	/*
	bool LaserFlg=false; //レーザー専用ボタン？
	//サブウェポン
	if((PjSys::key::UseLaser==true && GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::laser_p ) != 0 ){
			LaserFlg=true;
	}
	*/

	if(My::SubLevel>0 &&
		My::DefFrame<=0 &&
		(GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::sub_p ) != 0){ //サブウェポン
		//if(LaserFlg==true || (PjSys::key::UseLaser==false && shot==true)){//同時押し
				switch(My::SubLevel){
					case SUB_LEVEL-4:
						My::Laser::Limit=2;
						break;
					case SUB_LEVEL-3:
						My::Laser::Limit=4;
						break;
					case SUB_LEVEL-2:
						My::Laser::Limit=8;
						break;
					case SUB_LEVEL-1:
						My::Laser::Limit=16;
						break;

					case SUB_LEVEL:
						My::Laser::Limit=32;
						break;
				}
				My::Laser::Init();
				for(int l=0;l<My::Laser::Limit;l++){
					My::Laser::Regist();
				}

				/*
				if(CheckSoundMem(SndDefS)!=1){
					//PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK,true);

					if(PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK)==-1){
						//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
						ErrorLogAdd("SndDefS has been Reloaded.\n");
						SndDefS=LoadSoundMem( "snd\\def_start.wav" ) ;
						ChangeVolumeSoundMem(Setting.General.SEVolume , SndDefS );
						PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK,true);
					}
				} //サブウェポン始動
				*/
				PjSys::Scr::AddLog("DEFENDER[%d]...OK\0",My::SubLevel,GetColor(128,255,128));
				//PjSys::Scr::AddLog("LEVEL[%d] NOW.",My::Bomb,GetColor(255,255,255));

				swflg=0;
			//}else{
				//PjSys::Scr::AddLog("SW2[%d] LAUNCHED...FAILED!",My::SubLevel,GetColor(255,128,128));
				//swflg=0;
		if(My::SubLevel>0 && My::SubFrame<=0){
			//PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK,true); //サブウェポン始動
					if(PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK)==-1){
#ifdef RELOADSOUND
						//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
						ErrorLogAdd("SndDefS has been Reloaded.\n");
						SndDefS=LoadSoundMem( "snd\\def_start.wav" ) ;
						ChangeVolumeSoundMem(Setting.General.SEVolume , SndDefS );
						PlaySoundMem(SndDefS,DX_PLAYTYPE_BACK,true);
#endif
					}
			My::SubFrame += SUBFRAMEMIN*My::SubLevel;
			//PjSys::Scr::AddLog("PROTECTOR[%d]...OK",My::SubLevel,GetColor(128,255,128));
			PjSys::Scr::SetBurst((int)My::x,(int)My::y);
		//My::SubLevel--;
			if(My::SubLevel>SUB_LEVEL){
				My::SubLevel=SUB_LEVEL;
			}else if(My::SubLevel<0){
				My::SubLevel=0;
			}

			//PjSys::Scr::AddLog("LEVEL[%d] NOW.",My::Bomb,GetColor(255,255,255));
				My::DefFrame=SUBFRAMECNT*My::SubLevel;
				PjSys::Scr::SetBurst((int)My::x,(int)My::y,8,40,255,127,127,false,32);
			
			My::SubEnergy=0;
			swflg=0;
			//if(My::SubLevel<2){swkeycheck=0;}
		}
	}else{
		swkeycheck=0;
		swflg=0;
	}

	//My::IsBurner=false;
	if(up && right){angle=45;}
	else if(left && up){angle=135;}
	else if(left && down){angle=225;}
	else if(down && right){angle=315;}
	else if(up){angle=90;horizon=true;}
	else if(down){angle=270;horizon=true;}
	else if(left){angle=180;}
	else if(right){angle=0;}

	//angleの値が変わっていたらキャラクタの座標を変更する
	if(angle!=-1){
		int mv = SpeedNormal;//３の速さ
		double tx , ty;
		if (IsSlow){mv=SpeedSlow;}
		math m;
		tx = getX() + mysin(m.ToRadian(angle+90))*mv;
		ty = getY() + mycos(m.ToRadian(angle+90))*mv;

		if(tx>144 && tx<496 ){setX(tx);}
		if(ty>24 && ty<464 ){setY(ty);}
	}else{horizon=true;}
	if(horizon && frmLRoll==0 && frmRRoll==0){
		if(My::Rot<0){My::Rot++;}
		else if(My::Rot>0){My::Rot--;}
	}

	//ロール
	if(frmLRoll>0){
		frmLRoll--;
		My::Rot+=2;
		My::BuzzRegion=(int)(BUZZ_REGION_DEFAULT*1.5);
		if(abs((int)(My::Rot)%120)<4){
			My::Rot=0;
			frmLRoll=0;
		}
		Vapor::Make(0,My::x-(int)(mycos(PI/60*My::Rot)*24),My::y,128);
		Vapor::Make(1,My::x+(int)(mycos(PI/60*My::Rot)*24),My::y,128);
	}else if(frmRRoll>0){
		frmRRoll--;
		My::Rot-=2;
		My::BuzzRegion=(int)(BUZZ_REGION_DEFAULT*1.5);
		if(abs((int)(My::Rot)%120)<4){
			My::Rot=0;
			frmRRoll=0;
		}
		Vapor::Make(0,My::x-(int)(mycos(PI/60*My::Rot)*24),My::y,128);
		Vapor::Make(1,My::x+(int)(mycos(PI/60*My::Rot)*24),My::y,128);
	}else{
		My::BuzzRegion=BUZZ_REGION_DEFAULT;
	}
	//ショット
	if(shot){
		if(CheckSoundMem(SndShoot)!=1){
					if(PlaySoundMem(SndShoot,DX_PLAYTYPE_BACK)==-1){
#ifdef RELOADSOUND
						//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
						ErrorLogAdd("SndShoot has been Reloaded.\n");
						SndShoot=LoadSoundMem( "snd\\shoot.wav" ) ;
						ChangeVolumeSoundMem(Setting.General.SEVolume , SndShoot );
						PlaySoundMem(SndShoot,DX_PLAYTYPE_BACK,true);
#endif
					}
			//PlaySoundMem(SndShoot,DX_PLAYTYPE_BACK,true);
		} //ショット音
		My::shooting=true;
		//bangle+=0.5;
		if(bangle++>15){ //ショットの傾き
			bangle=5;
		}
		if(IsSlow){ //低速時の前方集中ショット
			pbStraight[0].create((int)getX(),(int)getY()-16,0,16,0);
			pbStraight[1].create((int)getX()-(int)(mycos(PI/60*My::Rot)*4),(int)getY()-16,0,16,1);
			pbStraight[2].create((int)getX()+(int)(mycos(PI/60*My::Rot)*4),(int)getY()-16,0,16,2);
			pbStraight[3].create((int)getX()-(int)(mycos(PI/60*My::Rot)*8),(int)getY()-16,0,16,3);
			pbStraight[4].create((int)getX()+(int)(mycos(PI/60*My::Rot)*8),(int)getY()-16,0,16,4);
		}else{ //通常ショット
			pbStraight[0].create((int)getX(),(int)getY()-16,0,16,0);
			pbStraight[1].create((int)getX(),(int)getY()-16,-3,16,1);
			pbStraight[2].create((int)getX(),(int)getY()-16,3,16,2);
			pbStraight[3].create((int)getX()+(int)(mycos(PI/60*My::Rot)*16),(int)getY(),bangle,12,3);
			pbStraight[4].create((int)getX()-(int)(mycos(PI/60*My::Rot)*16),(int)getY(),bangle*-1,12,4);
		}
		shot=false;
	}else{My::shooting=false;}
	return;
}