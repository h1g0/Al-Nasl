#include "Common.h"
/*#############################################################

						   敵本体

##############################################################*/

/***************************************************************************************
敵実体
***************************************************************************************/

//敵初期化
void Enemy::init(){
	int i = 0;
	while(i<c){ //ループ回し
		flg[i]=false;
		deadflg[i]=0;
		hp[i]=0;
		score[i]=0; //スコア決定
		x[i]=0;
		y[i]=0;
		IsRotate[i]=0;
		rotaflg[i]=0;
		phase[i]=0;
		MV1DuplicateModel( img[i]) ;

		//img[i]=0;
		expansion[i]=0;
//			deg[i]=degree;
		type[i]=0;
		btype[i]=0;
		HaveItem[i]=false;
		ItemType[i]=0;
		regx[i]=0;
		regy[i]=0;
		eb1[i].init();
		i++;
		//i=0;
	}

	//爆発フェーズ初期化
	for(int i=0;i<EXPLODE_MAX;i++){
		BExpPhase[i]=0;
	}
	//大爆発フェーズ初期化
	bephase=0;
}

//爆発登録
int Enemy::RegistExp(int x, int y, double exp, int delay){
	for(int i=0;i<EXPLODE_MAX;i++){
		if(BExpPhase[i]<=0){
			math m;
			BExpPhase[i]=32+delay;
			BExpX[i]=x;
			BExpY[i]=y;
			BExpNo[i]=m.irand(0,7);
			BExpEx[i]=exp;
			BExpAngle[i]=RAD*m.irand(0,359);
			return i;
		}
	}
	return -1;
}
	/*===敵生成===*/
int Enemy::create(int ehp, double defx, double defy, int movetype,int& eimg, float eexpansion,
				  int rotaptn, int bltptn, int bltcap, int* bltimg,int HitRegionX,int HitRegionY,
				  bool ImgRotate,bool IsHitMyBullet, bool IsHitMe, bool Item,
				  char ItmType,float ZOrder){
	int i = 0;
	while(i<c){ //ループ回し
		if(flg[i]==false){ //存在フラグが立っていない場合
			flg[i]=true;
			deadflg[i]=0;
			hp[i]=ehp;
			score[i]=ehp; //スコア決定
			x[i]=defx;
			y[i]=defy;
			IsRotate[i]=ImgRotate;
			rotaflg[i]=rotaptn;
			//img[i]=eimg;
			img[i]= MV1DuplicateModel( eimg ) ;
			expansion[i]=eexpansion;
//				deg[i]=degree;
			type[i]=movetype;
			btype[i]=bltptn;
			regx[i]=HitRegionX;regy[i]=HitRegionY;
			IsHitBlt[i]=IsHitMyBullet;
			IsHitPlayer[i]=IsHitMe;
			eb1[i].Create(bltcap,btype[i],x[i],y[i]);
			eb1[i].setimg(bltimg);
			mphase[i]=0;
			HaveItem[i]=Item;
			ItemType[i]=ItmType;
			Locked[i]=0;
			Enm::LaserUnlockNum[i]=0;
			int j=0;while(j++<8){BExpPhase[j]=0;}
			z[i]=ZOrder;
			eb1[i].vanishfrm=0;
			break;
		}
		i++;
		//i=0;
	}
	return i;
}

void Enemy::bltchange(int idx, int* bltimg, int bltcap,int bltptn){
	//flg[idx]=0;
	BulletEnd[idx]=false;
	btype[idx]=bltptn;
	eb1[idx].Create(bltcap,btype[idx],x[idx],y[idx]);
	eb1[idx].setimg(bltimg);
}

int Enemy::Dead(int& i){
	int j=0;
	//bool pflg=false; //パーティクルを飛ばすか否か

	if(pPhase[i]==0){
		type[i]=-1;
		eb1[i].parent_dead=1;
		int powlv=My::BuzzLv;
		if(My::BuzzLv<My::Laser::RefCounterMax){
			powlv=My::Laser::RefCounterMax;
		}
		if(score[i]>=256){
			if(score[i]>=4096){
				double ex=1+(powlv/10);
				My::AddScore((int)(score[i]*ex));
				PjSys::Scr::AddLog("TGT BRK DN x[1.%d]",powlv,GetColor(255,32,32));
				My::SubLevel=5;
			}else{
				int ex=powlv+1;
				My::AddScore((int)(score[i]*ex));
				My::AddSubEnergy(score[i]);
				PjSys::Scr::AddLog("DESTROYED x[%d]",ex,GetColor(255,128,128));
			}
			pflg[i]=true;
			//PlaySoundMem(SndBigExp,DX_PLAYTYPE_BACK);
			if(PlaySoundMem(SndBigExp,DX_PLAYTYPE_BACK)==-1){
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				#ifdef RELOADSOUND
				ErrorLogAdd("BigExp has been Reloaded.\n");
				SndBigExp=LoadSoundMem( "snd\\bigexp.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , SndBigExp );
				PlaySoundMem(SndBigExp,DX_PLAYTYPE_BACK,true);
				#endif
			}
		}else if(score[i]>0){
			int ex=(int)(pow((double)powlv,2));
			My::AddScore((int)(score[i]*ex));
			My::AddSubEnergy(score[i]);
			PjSys::Scr::AddLog("DESTROYED x[%d]",ex,GetColor(128,128,128));
			pflg[i]=false;
			if(PlaySoundMem(SndSmallExp,DX_PLAYTYPE_BACK)==-1){
				#ifdef RELOADSOUND
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				ErrorLogAdd("SmallExp has been Reloaded.\n");
				SndSmallExp=LoadSoundMem( "snd\\smallexp.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , SndSmallExp );
				PlaySoundMem(SndSmallExp,DX_PLAYTYPE_BACK,true);
				#endif
			}

			math m;
			exp[i]=m.irand(0,3);
			expdeg[i]=m.ToRadian(m.irand(0,359));
		} //大きめの雑魚

		//レーザー消す
		for(int j=0;j<My::Laser::Limit;j++){
			if(My::Laser::flg[j]==true && My::Laser::TargetID[j]==i && My::Laser::IsVanish[j]==false){
				My::Laser::TargetFlg[j]=false;
				My::Laser::TargetID[j]=-1;
				/*
				My::Laser::Vanish(j);
				int score=0;
				if(j%2==0){
					score=LASER_SCORE*32*(int)(1+(j/2));
				}else{
					score=LASER_SCORE*32*(int)((j+1)/2);
				}
				My::AddScore(score);
				PjSys::Scr::AddLog("K.B.L.Bonus [%d]\0",score,GetColor(255,255,127));
			*/
			}
		}
	}

	//大型敵を撃破した時の爆風
	if(pflg[i] &&pPhase[i]<30){
		int vin=pPhase[i]*10;
		int vout=vin+(int)(mycos(pPhase[i]*PI/45)*10);
		int BurstDivision=40;
		float rad=DX_PI_F*2/BurstDivision;
		SetDrawMode(1);
		SetDrawBlendMode(DX_BLENDMODE_ADD,240-8*pPhase[i]);
		int BurstX=(int)(x[i]+PjSys::Scr::MoveX);
		int BurstY=(int)(y[i]+PjSys::Scr::MoveY);

		for(int i=0;i<BurstDivision;i++){
			float ul[2],ur[2],dl[2],dr[2];
			ul[0]=mycos(rad*i)*vout+BurstX;
			ul[1]=mysin(rad*i)*vout+BurstY;
			ur[0]=mycos(rad*(i+1))*vout+BurstX;
			ur[1]=mysin(rad*(i+1))*vout+BurstY;
			dr[0]=mycos(rad*(i+1))*vin+BurstX;
			dr[1]=mysin(rad*(i+1))*vin+BurstY;
			dl[0]=mycos(rad*i)*vin+BurstX;
			dl[1]=mysin(rad*i)*vin+BurstY;
			DrawModiGraphF(ul[0],ul[1],ur[0],ur[1],dr[0],dr[1],dl[0],dl[1],PjSys::Scr::BurstImg,TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		SetDrawMode(0);
	}

	double kvx=pvx[i][0]*0.1,kvy=pvy[i][0]*0.1;
	int k;
	if(pflg[i]){k=36;}else{k=5;}

	while(j++ <k){
		if(pPhase[i]==0){
			double s;
			math m;
			s=m.irand(1,4)*(1+(double)rand()/(double)(RAND_MAX+0.1));
			pImgNo[j]=m.irand(0,7);
			if(pflg[i]){
				pvx[i][j]=mycos(m.ToRadian(j*10))*s;
				pvy[i][j]=mysin(m.ToRadian(j*10))*s;
				PjSys::Scr::SetShake(5,-5,5);
			}else{
				pvx[i][j]=kvx*j*2;
				pvy[i][j]=kvy*j*2;
			}
			//pvy[i][j]+=0.1;
			px[i][j]=x[i];
			py[i][j]=y[i];

			expdeg[j]=m.ToRadian(m.irand(0,359));
		}else if(pPhase[i]==100){
			return 1;
		}else{
			int ephase=(pPhase[i]-((pPhase[i]-(int)expdeg[j])%4))/4;
			if(ephase>15){ephase=-1;}
			px[i][j]+=pvx[i][j];
			py[i][j]+=pvy[i][j];
			SetDrawBlendMode(DX_BLENDMODE_ADD,(int)((164-pPhase[i])/2));
			SetDrawMode(1);
			if(ephase!=-1){DrawRotaGraph((int)px[i][j]+PjSys::Scr::MoveX , (int)py[i][j]+PjSys::Scr::MoveY  , 1.0f , expdeg[j] , Enm::SmallExplode[pImgNo[j]][ephase] , TRUE);}
			SetDrawMode(0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

	pPhase[i]++;
	return 0;
}
//========================================
//敵移動
//=========================================
int Enemy::Move(){ //動作
	bool ishit=false;
	My::IsHitFrm=false;
	int hard=1;
	if(PjSys::GameLevel==0){boost::swap(PjSys::Hard,hard);} //2周目の場合、敵動作は最高難易度に固定
	for(int i=0;i <c;i++){ //ループ回し
		if(flg[i]==true){ //存在フラグが立っている場合
			switch(type[i]){ //敵動作分岐
			case -1:
				ptndead(i);
				break;
			case 0x10:
				ptn10(i);
				break;
			case 0x11:
				ptn11(i);
				break;
			case 0x12:
				ptn12(i);
				break;
			case 0x13:
				ptn13(i);
				break;
			case 0x14:
				ptn14(i);
				break;
			case 0x15:
				ptn15(i);
				break;
			case 0x16:
				ptn16(i);
				break;
			case 0x17:
				ptn17(i);
				break;
			case 0x18:
				ptn18(i);
				break;
			case 0x19:
				ptn19(i);
				break;
			case 0x1a:
				ptn1a(i);
				break;
			case 0x1b:
				ptn1b(i);
				break;
			case 0x1c:
				ptn1c(i);
				break;
			case 0x1d:
				ptn1d(i);
				break;
			case 0x1e:
				ptn1e(i);
				break;
			case 0x1f:
				ptn1f(i);
				break;
			case 0x20:
				ptn20(i);
				break;
			case 0x21:
				ptn21(i);
				break;
			case 0x22:
				ptn22(i);
				break;
			case 0x23:
				ptn23(i);
				break;
			case 0x24:
				ptn24(i);
				break;
			case 0x25:
				ptn25(i);
				break;
			case 0x26:
				ptn26(i);
				break;
			case 0x27:
				ptn27(i);
				break;
			case 0x28:
				ptn28(i);
				break;
			case 0x29:
				ptn29(i);
				break;
			case 0x2a:
				ptn2a(i);
				break;
			case 0x2b:
				ptn2b(i);
				break;
			case 0x2c:
				ptn2c(i);
				break;
			case 0x2d:
				ptn2d(i);
				break;
			case 0x2e:
				ptn2e(i);
				break;
			case 0x2f:
				ptn2f(i);
				break;
			case 0x3a:
				ptn3a(i);
				break;

			case 0x3b:
				ptn3b(i);
				break;

			}//敵動作分岐終了
			if(PjSys::GameLevel==0){boost::swap(PjSys::Hard,hard);} //2周目の場合、敵動作は最高難易度に固定

			//実際に動かす
			x[i]+=vx[i];
			y[i]+=vy[i];
			math m;
			if(IsRotate[i]){
				deg[i]=(float)m.vec2rad(vx[i],vy[i]);
			}//else{
				//deg[i]=0;
			//}
			phase[i]++;
			//当り判定
			if(deadflg[i]==0){ //死亡フラグが立っていなかったら
				//メインショット
				for(int j=0;j<500;j++){
					if(My::Bullet::flg[j]==true){
						math m;
						if(!My::IsHit && IsHitBlt[i]==true &&  m.hitcheck(My::Bullet::x[j],My::Bullet::y[j],My::Bullet::region,My::Bullet::region,x[i],y[i],regx[i],regy[i])){
							if(hp[i]!=ENEMY_INV){
								//if(My::DefFrame>SUBINVFRAME){
								//	hp[i]-=20*My::SubLevel;
								//}else{
									if(j<50*2){
										hp[i]-=My::Bullet::pow1;
										//My::AddSubEnergy(2);
									}else{
										//My::AddSubEnergy(1);
										hp[i]-=My::Bullet::pow2;
									}
								//}
							}
							My::Bullet::IsHit[j]=true;
							int bidx=(j-(j%50))/50;
							My::Bullet::EffFlg[bidx]=true;
							My::Bullet::EffX[bidx]=My::Bullet::x[j];
							My::Bullet::EffY[bidx]=My::Bullet::y[j];
							My::Bullet::EffFrm[bidx]++;
							My::Bullet::EffFrm[bidx]%=8;

							ishit=true;
							//My::AddScore(1); //打ち込み点
						}
					}
					math m;

					//レーザー
					if(Enm::LaserUnlockNum[i]>0){
						Locked[i]-=Enm::LaserUnlockNum[i];
						if(hp[i]>0){hp[i]-=Enm::LaserUnlockNum[i];}
						Enm::LaserUnlockNum[i]=0;
					}
					if(flg[i]==true && (x[i]+regx[i]*0.5>=120 && x[i]-regx[i]*0.5<=540 && y[i]+regy[i]*0.5 >=0 && y[i]-regy[i]*0.5 <= 480) && hp[i]>0){
						for(int j=0;j<My::Laser::Limit;j++){
							if(My::Laser::flg[j]==true && My::Laser::IsVanish[j]==false){
								if(My::Laser::TargetFlg[j]==true && My::Laser::TargetID[j]==i){ //ターゲットがその敵か
									//ヒットしてる
									if(m.hitcheck(x[i],y[i],regx[i],regy[i],My::Laser::x[j][0],My::Laser::y[j][0],16,16)==1){
										My::Laser::Vanish(j);
										//Locked[i]--;
										//hp[i]-=My::Laser::Pow(My::Laser::RefCounter[j]);
										ishit=true;
									}else{
										My::Laser::tx[j]=(int)x[i];
										My::Laser::ty[j]=(int)y[i];
									}
									//TODO: レーザーがロックされないバグがある？
									//UNDONE: レーザーがロックされないバグが修正されたか確認(2/15)
								}else if(My::Laser::TargetFlg[j]==false && My::Laser::phase[j] >=j){ //ターゲット決定
									double d=m.GetDist2(x[i],y[i],My::x,My::y);

									//ターゲットへの距離が-1(初期値)もしくはターゲット候補の暫定距離よりも短ければターゲット候補に
									if(My::Laser::TargetDist[j]<0 || (int)d<=My::Laser::TargetDist[j]){
										//UNDONE: ここもう少し上手い方法を考える
										if(Locked[i]<=hp[i]){ //敵のHPはロックされた数より多いか？
											My::Laser::TargetID[j]=i;
											My::Laser::TargetDist[j]=(int)d;
											My::Laser::tx[j]=(int)x[i];
											My::Laser::ty[j]=(int)y[i];
											//Locked[i]++;
										}
									}
								}
							}
						}
					}

					//自機自身
					if(!My::NowInv && IsHitPlayer[i]==true && m.hitcheck(x[i],y[i],regx[i],regy[i],My::x,My::y,My::Region,My::Region)){
						My::IsHitFrm=true;
						//if(hp[i]!=ENEMY_INV){hp[i]-=10;}
					}
				}
				if(My::BombFrame>0){ //ボム撃ってるか
					eb1[i].dead=0;
					if(hp[i]!=ENEMY_INV){hp[i]-=BMB_DMG_PER_FRAME;}
					//SetDrawBright(255,0,0);
					//ishit=true;
				}else{eb1[i].dead=0;}
					if(hp[i]!=ENEMY_INV && hp[i]<=0){
						pPhase[i]=0;
						deadflg[i]=1;
						pvx[i][0]=vx[i];
						pvy[i][0]=vy[i];
						if(HaveItem[i]==true){
							if(ItemType[i]!=7 || (My::BombFrame==0 && My::SubFrame==0 && My::DefFrame==0)){
								My::Item::Add((int)x[i],(int)y[i],m.getcos(My::x,My::y,x[i],y[i])*3,m.getsin(My::x,My::y,x[i],y[i])*3,ItemType[i]);
							}
						}
					} //死亡フラグ

				//eb1[i].dead=0;
			}
			//飛び出し判定
			if(x[i]<-320 || x[i]>960 ||y[i]<-240 || y[i]>840 || eb1[i].vanishfrm>0){
				if(eb1[i].vanishfrm>=32){phase[i]=-1;flg[i]=false;deadflg[i]=0;}
				else{
					if(eb1[i].vanishfrm==0){
						eb1[i].dead=1;
					}
					eb1[i].vanishfrm++;
				}
				//deadflg[i]=1;
				//pPhase[i]=100;
			}//else{
				if(deadflg[i]==0){
					//if(ishit){SetDrawBright(255,0,0);}
					//DrawRotaGraph((int)x[i]+PjSys::Scr::MoveX ,(int) y[i]+PjSys::Scr::MoveY  , expansion[i] , deg[i] , img[i] , TRUE);
					//if(ishit){SetDrawBright(255,255,255);}
					SetCameraPositionAndAngle( VGet( 0.0f, -230.0f, 0.0f), DX_PI_F/-2.0f, 0, 0 ) ;
					DxLib::VECTOR pLoc={(float)x[i]+PjSys::Scr::MoveX,(float)y[i]+PjSys::Scr::MoveY,z[i]};
					if(IsHitBlt[i]==false){
						MV1SetDifColorScale( img[i], GetColorF( 0.0f, 0.0f, 0.0f, 0.0f ) ) ;
						MV1SetOpacityRate(img[i], 0.5f);
					}else{
						MV1SetDifColorScale( img[i], GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
						MV1SetOpacityRate(img[i], 1.0f);
					}

					MV1SetPosition( img[i], ConvScreenPosToWorldPos( pLoc ) ) ;
					MV1SetScale( img[i], VGet(expansion[i],expansion[i],expansion[i])) ;
					switch(rotaflg[i]){
						// 回転しない(deg依存)
						case 0:
							MV1SetRotationXYZ(img[i], VGet(0,deg[i]*-1,0)) ;
							break;
						//横方向に回転(自動)
						case 1:
							MV1SetRotationXYZ(img[i], VGet(0,DX_PI_F/90*phase[i],0)) ;
							break;
						//縦方向に回転(自動)
						case 2:
							MV1SetRotationXYZ(img[i], VGet(DX_PI_F/90*phase[i],0,0)) ;
							break;
						case 3:
							MV1SetRotationXYZ(img[i], VGet(0,0,DX_PI_F/90*phase[i])) ;
							break;
						//自機を狙う
						case 4:
							math m;
							deg[i]=(float)m.vec2rad(m.getcos(x[i],y[i],My::x,My::y),m.getsin(x[i],y[i],My::x,My::y));
							MV1SetRotationXYZ(img[i], VGet(0,deg[i]*-1,0)) ;
							break;
						//バンクを振る(deg依存)
						case 5:
							MV1SetRotationXYZ(img[i], VGet(0,0,deg[i])) ;
							break;
						//横方向に回転(deg依存)
						case 6:
							MV1SetRotationXYZ(img[i], VGet(0,deg[i],0)) ;
							break;
					}

					if(ishit){
						if(hp[i]==ENEMY_INV){
							MV1SetDifColorScale( img[i], GetColorF( 1.5f, 1.0f, 1.0f, 1.0f ) ) ;
						}else if(HaveItem[i]==true && ItemType[i]<7){
							MV1SetDifColorScale( img[i], GetColorF( 1.5f, 1.5f, 1.0f, 1.0f ) ) ;
						}else{
							MV1SetDifColorScale( img[i], GetColorF( 1.5f, 1.5f, 1.5f, 1.0f ) ) ;
						}
						if(CheckSoundMem(SndHit)==0){
							PlaySoundMem(SndHit,DX_PLAYTYPE_BACK,true);}
						else if(CheckSoundMem(SndHit)==-1){
							#ifdef RELOADSOUND
							SndHit=LoadSoundMem( "snd\\hit.wav" ) ;
							ChangeVolumeSoundMem(Setting.General.SEVolume , SndHit );
							PlaySoundMem(SndHit,DX_PLAYTYPE_BACK,true);
							#endif
						}//ヒット音
					}else if(HaveItem[i]==true && ItemType[i]<7){
						MV1SetDifColorScale( img[i], GetColorF( 1.2f, 1.2f, 1.0f, 1.0f ) ) ;
					}else{
						MV1SetDifColorScale( img[i], GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
					}
					MV1DrawModel( img[i] ) ;

					//当たり判定描画
					//DrawBox((int)x[i]-regx[i]/2,(int)y[i]-regy[i]/2,(int)(x[i]+regx[i]/2),(int)y[i]+regy[i]/2,GetColor(255,255,255),TRUE);


					//デバッグ用文字描画
					//DrawFormatString( (int)x[i], (int)y[i] , GetColor(255,127,127),"Deg: %d" ,deg[i]) ;
					//エフェクト描画
					for(int j=0;j<5;j++){
						if(My::Bullet::EffFlg[j]){
							int k=0;
							if(j>2){k=1;}
							SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
							DrawRotaGraph(My::Bullet::EffX[j]+PjSys::Scr::MoveX ,My::Bullet::EffY[j]-16+PjSys::Scr::MoveY  , 1.0f ,0 , My::Bullet::EffImg[k][My::Bullet::EffFrm[j]] , TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
						}
						My::Bullet::EffFlg[j]=false;
					}
						PjSys::DrawGuide((int)x[i]-regx[i]/2,(int)y[i]-regy[i]/2,(int)x[i]+regx[i]/2,(int)y[i]+regy[i]/2);
					//HP描画
					if(ishit && score[i]>=216 && score[i]<5000){
						SetDrawBlendMode(DX_BLENDMODE_ALPHA,96);
						DrawBox((int)x[i]-16,(int)y[i]-16,(int)x[i]+16,(int)y[i]-8,GetColor(0,0,0),TRUE);
						int width=hp[i]*32/score[i];
						SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
						//DrawBox((int)x[i]-16,(int)y[i]-16,(int)(x[i]-16+width),(int)y[i]-8,GetColor(255,127,127),TRUE);
						SetDrawBright(255-width*4,127+width*4,127);
						DrawRectGraph((int)x[i]-16,(int)y[i]-16,0,0,width,8,My::imgLeftTimeGaze,TRUE,FALSE);
						SetDrawBright(255,255,255);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
					}
					//DrawFormatString(static_cast<int>(x[i]),static_cast<int>(y[i]+8),GetColor(0,255,255),"HP: %d",hp[i]);
					ishit=false;
				}else{
					Dead(i);

					//SetDrawBright(128,128,128);
					//DrawRotaGraph((int)x[i]+PjSys::Scr::MoveX ,(int) y[i]+PjSys::Scr::MoveY  , expansion[i] , deg[i] , img[i] , TRUE);
					//SetDrawBright(255,255,255);
				}
				//eb1[i].Move();

			//}
		}
	}
	for(int i=0;i<c;i++){
		//if(i>=c){break;}
		if(flg[i]==true){
			if( eb1[i].Move()==1){ //敵の弾幕が全て画面から消えているか？
				if(deadflg[i]==1){ //敵が死んでいたら、敵の存在を消す
					phase[i]=-1;
					flg[i]=false;
					deadflg[i]=0;
					return 0;
				}
				BulletEnd[i]=true; //敵の弾幕が終了したフラグを立てる
				eb1[i].init();//敵弾初期化
				btype[i]=0x100;//撃たない
				eb1[i].Create(1,btype[i],x[i],y[i]); //敵弾を撃たないように変更
			}else{
				BulletEnd[i]=false;
			}
		}
	}
	//自機に当たってたら画像をキャプチャ
	if(My::IsHitFrm==true){
		if(My::AutoBomb&& My::Bomb>0){ //オートボムするか？
			//PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK);
			if(PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK)==-1){
				#ifdef RELOADSOUND
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				ErrorLogAdd("SndBomb has been Reloaded.\n");
				My::SndBomb=LoadSoundMem( "snd\\bomb.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , My::SndBomb );
				PlaySoundMem(My::SndBomb,DX_PLAYTYPE_BACK,true);
				#endif
			}
			My::ctphase=SHOW_CHIP_TIME;
			My::chartip=2;
			PjSys::Scr::SetShake(BMBFRAME,-6,6);
			My::BombFrame++;
			My::Bomb--;
			if(My::DefFrame>=SUBINVFRAME){
				My::DefFrame=1;
			}else{
				if(PjSys::HardConst>4 && My::SubLevel>2){ //難易度がEasyならオートボムでレベルを2つ下げるだけ
					My::SubLevel-=2;
				}else{
					My::SubLevel=0;
				}
				My::SubEnergy=0;
			}
			My::IsAutoBomb=true;
			My::BombDeletedBullet=0;
			My::BuzzLv=0;
			My::NowInv=true;
			My::Invincible=120;
			PjSys::Scr::AddLog("WEP LAUNCHED...OK.",My::SubLevel,GetColor(128,255,128));
		}else{
			My::IsHit=true;
			My::Move=false;
		}
		My::IsHitFrm=false;
		DeadImg::Set((int)My::x,(int)My::y,120);
		return 0;
	}
	//レーザー最終決定
	for(int k=0;k<My::Laser::Limit;k++){
		if(My::Laser::flg[k]==true && My::Laser::TargetFlg[k]==false &&
			My::Laser::TargetID[k]>-1 && My::Laser::IsVanish[k]==false ){
			My::Laser::TargetFlg[k]=true;
			Locked[My::Laser::TargetID[k]]+=My::Laser::Pow(My::Laser::RefCounter[k]);
			My::Laser::ReplaceFlg[k]=true;
		}
	}
	//return p;
return 0;
}

//ボス戦の最後に爆発するエフェクト
int Enemy::BigExp(int i,int x,int y){
	//if(pflg[i]){k=72;}else{k=5;}
	if(bephase==0){
		PjSys::Scr::SetBurst(x,y,8,40,255,255,255,false,64);
	}
	math m;
	for(int j=0;j<180;j++){
		double s;
		if(bephase==0){
			s=2*(1+(double)rand()/(double)(RAND_MAX+0.1));
			//s=GetRand(1000)/500;
			pImgNo[j]=m.irand(0,7);
			pvx[i][j]=mycos(m.ToRadian(j*2))*s;
			pvy[i][j]=mysin(m.ToRadian(j*2))*s;
			px[i][j]=x;
			py[i][j]=y;

			expdeg[j]=m.ToRadian(m.irand(0,359));
		}else if(bephase==120){
			return 1;
		}else{
			math m;
			int ephase=(int)(bephase+(int)(m.ToDegree(expdeg[j])/10)-((bephase+(int)(m.ToDegree(expdeg[j])/10))%3))/3;
			if(ephase>15){ephase%=16;}
			pvx[i][j]*=0.98;
			pvy[i][j]*=0.98;
			px[i][j]+=pvx[i][j];
			py[i][j]+=pvy[i][j];
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA,216-bephase);
			SetDrawBlendMode(DX_BLENDMODE_ADD,(int)(mysin(PI*(bephase+60)/180.0)*127));
			SetDrawMode(1);
			if(ephase!=-1){
				DrawRotaGraph((int)px[i][j]+PjSys::Scr::MoveX ,
							  (int)py[i][j]+PjSys::Scr::MoveY ,
							  2.0f , expdeg[j] , Enm::SmallExplode[pImgNo[j]][ephase] , TRUE);
			}
			SetDrawMode(0);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}
	bephase++;
	return 0;
}

//爆発エフェクト
void Enemy::ShowExp(){
	for(int i=0;i<EXPLODE_MAX;i++){
		if(BExpPhase[i]>0){
			BExpPhase[i]--;
			if(BExpPhase[i]==31){
				PlaySoundMem(SndBigExp ,DX_PLAYTYPE_BACK ,true ) ;
			}
			if(BExpPhase[i]<31){
				int idx=15-((BExpPhase[i]-(BExpPhase[i]%2))/2);
				SetDrawMode(1);
				SetDrawBlendMode(DX_BLENDMODE_ADD,127);
				DrawRotaGraph(BExpX[i],BExpY[i],BExpEx[i],BExpAngle[i],Enm::SmallExplode[BExpNo[i]][idx],true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				SetDrawMode(0);
			}
		}
	}
	return;
}