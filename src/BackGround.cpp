#include "Common.h"
/*#############################################################

						   画面構成本体

##############################################################*/

/*=============================================
3Dの背景関係本体
===============================================*/
void bg3d::imgset(int g1,int scroll){
	FCnt=0;
	Scr=scroll;
	// モデルの読み込み
	hField = g1;
	hField2 = MV1DuplicateModel(hField);

	SetupCamera_Perspective( DX_PI_F /4.0f );
	SetUseLighting( TRUE ) ;
	SetGlobalAmbientLight( GetColorF( 1.0f, 1.0f, 1.0f, 0.0f ) ) ;
	SetCameraNearFar( 400.0f, 1000.0f ) ;
	SetFogEnable( TRUE ) ;
	SetFogColor( 64, 64, 64 ) ;
	SetFogStartEnd( 600.0f, 900.0f ) ;
	SetLightEnable( TRUE ) ;
	ChangeLightTypeDir( VGet( -0.8f, 0.8f, 0.5f ) ) ;
	SetLightDifColor( GetColorF(  1.0f,  1.0f,  1.0f, 0.0f ) ) ;
	SetLightSpcColor( GetColorF(  1.0f,  1.0f,  1.0f, 0.0f ) ) ;
	SetLightAmbColor( GetColorF( 1.0f, 1.0f, 1.0f, 0.0f ) ) ;
}
void bg3d::changespeed(int speed){
	Scr=speed;
}

void bg3d::move(){
	int height =1500;
	FCnt+=Scr;
	FCnt%=height;

	// カメラの位置と回転値をセット、カメラの位置は原点
	SetCameraPositionAndAngle( PjSys::CameraPos, PjSys::CameraVRota, PjSys::CameraHRota, PjSys::CameraTRota ) ;
	MV1SetPosition( PjSys::Scr::BGModel, VGet( 0.0f/*+(float)(320-My::x)/5.0f*/, 400.0f, 0.0f ) ) ;
	MV1SetPosition( hField, VGet( 0.0f/*+(float)(320-My::x)/5.0f*/, 400.0f, FCnt+0.0f ) ) ;
	MV1SetWireFrameDrawFlag(PjSys::Scr::BGModel,PjSys::Scr::BGWire);
	if(PjSys::Scr::BGWire==false){
		SetFogColor( 64, 64, 64 ) ;
		SetFogStartEnd( 600.0f, 900.0f ) ;
		SetFogEnable( TRUE ) ;
	}else{SetFogEnable( FALSE ) ;}
	MV1SetScale(hField,VGet(1.5f,1.0f,1.5f)) ;
	MV1SetDifColorScale( PjSys::Scr::BGModel, PjSys::Scr::BGColor ) ;
	MV1DrawModel( PjSys::Scr::BGModel ) ;
	MV1SetWireFrameDrawFlag(hField,PjSys::Scr::BGWire);
	MV1SetDifColorScale( hField, PjSys::Scr::BGColor ) ;
	MV1DrawModel( hField ) ;
	MV1SetPosition( hField2, VGet( 0.0f, 400.0f, (float)(FCnt-height) ) ) ;
	MV1SetWireFrameDrawFlag(hField2,PjSys::Scr::BGWire);
	MV1SetScale(hField2,VGet(1.5f,1.0f,1.5f)) ;
	MV1SetDifColorScale( hField2, PjSys::Scr::BGColor ) ;
	MV1DrawModel( hField2 ) ;
}

/*=============================================
2Dの背景関係本体
===============================================*/
void bgmain::imgset(int g1, int g2, int scroll){
	img1=g1;
	img2=g2;
	y1=0;
	y2=-480;
	sspeed=scroll;
}

void bgmain::move(){
	y1+=sspeed;
	y2+=sspeed;
	if(y1==0){y2=-480;}
	if(y2==0){y1=-480;}
	DrawGraph( -280+PjSys::Scr::MoveX, y1+PjSys::Scr::MoveY, img1 , FALSE ) ;
	DrawGraph( 120+PjSys::Scr::MoveX, y1+PjSys::Scr::MoveY, img1 , FALSE ) ;
	DrawGraph( 520+PjSys::Scr::MoveX, y1+PjSys::Scr::MoveY, img1 , FALSE ) ;
	DrawGraph( -280+PjSys::Scr::MoveX, y2+PjSys::Scr::MoveY, img2 , FALSE ) ;
	DrawGraph( 120+PjSys::Scr::MoveX, y2+PjSys::Scr::MoveY, img2 , FALSE ) ;
	DrawGraph( 520+PjSys::Scr::MoveX, y2+PjSys::Scr::MoveY, img2 , FALSE ) ;
}
/*=============================================
2Dの背景クラスその2本体
===============================================*/

bgsub::bgsub(){//コンストラクタ
	Visible=false;
	alpha=255;
}

//画像とスクロール速度をセット
void bgsub::imgset(int g1, int g2, int scroll){
	img1=g1;
	img2=g2;
	y1=0;
	y2=-480;
	sspeed=scroll;
	Visible=true;
}

//動かす
void bgsub::move(){
	if(Visible==true){
		y1+=sspeed;
		y2+=sspeed;
		if(y1==0){y2=-480;}
		if(y2==0){y1=-480;}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);
		DrawGraph( 120+PjSys::Scr::MoveX, y1+PjSys::Scr::MoveY, img1 , TRUE ) ;
		DrawGraph( 120+PjSys::Scr::MoveX, y2+PjSys::Scr::MoveY, img2 , TRUE ) ;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

/*=============================================
画面横の情報群本体
==============================================*/
void bgside::imgset(int imgLeft, int imgRight){ //左右の画像をセット
	GrBGL = imgLeft ;
	GrBGR = imgRight ;
	phase=0;
	gzPhase=0;
	gzCnt=0;
}

//TODO: bgside::draw()の中身をリファクタリング
void bgside::draw(){ //描画
	//バースト描画
	PjSys::Scr::MoveBurst();
	//自機レーザー描画
	My::Laser::Move();

	//ブラー
	Blur::move();

	//情報描画
	DrawGraph( 0+PjSys::Scr::MoveX , 0+PjSys::Scr::MoveY  , GrBGL , TRUE ) ;
	DrawGraph( 520+PjSys::Scr::MoveX ,0+PjSys::Scr::MoveY  , GrBGR , TRUE ) ;
	DrawGraph( 4+PjSys::Scr::MoveX , 16+PjSys::Scr::MoveY  , PjSys::MainChar[1] , TRUE );
	PjSys::NumDraw(PjSys::MainNum,My::Score,16,36,12,0.75); //Score

	DrawGraph( 4 +PjSys::Scr::MoveX, 64+PjSys::Scr::MoveY  , PjSys::MainChar[2] , TRUE );
	if(My::Left==0){SetDrawBright(255,0,0);}
	PjSys::NumDraw(PjSys::MainNum,My::Left,98,64,16); //Left
	SetDrawBright(255,255,255);
	DrawGraph( 4+PjSys::Scr::MoveX , 80+PjSys::Scr::MoveY  , PjSys::MainChar[3] , TRUE );
	if(My::Bomb==0){SetDrawBright(255,0,0);}
	PjSys::NumDraw(PjSys::MainNum,My::Bomb,98,80,16); //Bomb
	SetDrawBright(255,255,255);

	//ボムエクステンド
	if(My::Score>=(PjSys::BombExtend*PjSys::BombExtendPhase)){
		My::AddBomb();
	}

	//エクステンド
	if(My::Score>=(PjSys::Extend*PjSys::ExtendPhase)){
		My::AddLeft();
	}

	//スコア表示
	if(++phase==SHOW_CHIP_TIME){
		int i=(int)My::Score-score;
		if(i>0){
			My::ntphase=SHOW_CHIP_TIME;
			My::numtip=i;
		}
		phase=0;
		score=(int)My::Score;
	}

	//サブウェポンゲージ上昇
	//if(++gzCnt==5){
		if(++gzPhase>60){
			gzPhase=0;
		}
		if(My::Move && My::SubFrame<=0 && My::DefFrame<=0){
			if(My::NowBuzz>0){

				My::AddSubEnergy(My::NowBuzz*2);
			}else{
				My::AddSubEnergy(1);
			}
		}
		//gzCnt=0;
	//}
	//チップ表示
	int gzHeight=0;
	int frm;
	if(My::SubFrame>=My::DefFrame){frm=My::SubFrame;}else{frm=My::DefFrame;}
	if(frm==0 && My::SubLevel>=0){
		gzHeight=(int)(My::SubEnergy *256 / (My::SubEnergyMax*(My::SubLevel+1)));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(192,192,255);
		SetDrawMode(1);
		DrawRectGraph(70+PjSys::Scr::MoveX,381-gzHeight+PjSys::Scr::MoveY,0,256-gzHeight,16,gzHeight,PjSys::Gaze[(int)(gzPhase/4)],false,false);
		SetDrawMode(0);
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(My::SubFrame>=My::DefFrame){
		gzHeight=(int)(frm *256 / 225);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,224);
		SetDrawBright(255,255,0);
		DrawRectGraph(70+PjSys::Scr::MoveX,381-gzHeight+PjSys::Scr::MoveY,0,256-gzHeight,16,gzHeight,PjSys::Gaze[(int)(gzPhase/4)],false,false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(frm>SUBINVFRAME){
		gzHeight=(int)((frm-SUBINVFRAME) *256 / (SUBFRAMECNT*My::SubLevel-SUBINVFRAME));
		SetDrawBlendMode(DX_BLENDMODE_ADD,192);
		SetDrawBright(255,0,0);
		DrawRectGraph(70+PjSys::Scr::MoveX,381-gzHeight+PjSys::Scr::MoveY,0,256-gzHeight,16,gzHeight,PjSys::Gaze[(int)(gzPhase/4)],false,false);
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawGraph(82+PjSys::Scr::MoveX,125+PjSys::Scr::MoveY,PjSys::GazeChar[0],true);
	}else{
		gzHeight=(int)(frm *256 / SUBINVFRAME);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
		SetDrawBright(255,255,0);
		DrawRectGraph(70+PjSys::Scr::MoveX,381-gzHeight+PjSys::Scr::MoveY,0,256-gzHeight,16,gzHeight,PjSys::Gaze[(int)(gzPhase/4)],false,false);
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawGraph(82+PjSys::Scr::MoveX,125+PjSys::Scr::MoveY,PjSys::GazeChar[1],true);
	}

	DrawGraph(70+PjSys::Scr::MoveX,125+PjSys::Scr::MoveY,PjSys::GazeFrame,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
	DrawStringToHandle( 107+PjSys::Scr::MoveX, 125+PjSys::Scr::MoveY,"DEFENDER SYSTEM LEVEL:", GetColor(255,255,255), PjSys::font::log ,0,1) ;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	if(PjSys::cheat::LevelMax==true){
		My::SubLevel=SUB_LEVEL;
	}

	if(My::SubEnergy==My::SubEnergyMax*(My::SubLevel+1) && My::SubLevel<SUB_LEVEL){ //レベル上昇
		My::SubLevel++;
		My::ctphase=SHOW_CHIP_TIME;
		My::chartip=My::SubLevel+2;
		PjSys::Scr::AddLog("LEVEL INCREASED -> [%d]\0",My::SubLevel,GetColor(128,255,128));
		if(My::SubLevel==3){
			PjSys::Scr::AddLog("REACTOR: READY.\0",My::SubLevel,GetColor(128,255,0));
		}
		PlaySoundMem(My::sw::sndLv[My::SubLevel-1],DX_PLAYTYPE_BACK,true);

		My::SubEnergy=0;
	}
	if(frm==0){
		for(int i=0; i<=SUB_LEVEL; i++){ //レベル描画
			double ext=1.0;
			if(i==My::SubLevel){
				SetDrawBright(64,64,64);
				PjSys::NumDraw(PjSys::MainNum,i,(int)(66+ext*24),(int)(i*24+ext*24+104),24,ext);
				SetDrawBright(255,128,128);
				ext=1.5;
				//PjSys::NumDraw(PjSys::MainNum,i,86,i*24+125,24);
			}else if(i>2){
				SetDrawBright(192,192,128);
			}else{
				SetDrawBright(128,128,128);
			}
			PjSys::NumDraw(PjSys::MainNum,i,(int)(62+ext*24),(int)(i*24+ext*24+100),24,ext);
			SetDrawBright(255,255,255);
		}
	}

	//内部ランク調整
	PjSys::SetLank();

	//難易度描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
	DrawRotaGraph( 580+PjSys::Scr::MoveX , 460+PjSys::Scr::MoveY  ,0.5f,0, PjSys::mHardImg[3-PjSys::GameLevel] , TRUE ) ;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	//ログ描画
	for(int i=0;i<10;i++){
		string_t str;
		int strl=PjSys::Scr::LogChar[i].size();
		if(PjSys::Scr::LogFrm[i]<=strl*2){
			int s=(PjSys::Scr::LogFrm[i]-(PjSys::Scr::LogFrm[i]%2))/2; //何文字目まで取り出すか
			str=PjSys::Scr::LogChar[i].substr(0,s);
			str+="_";
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255 -16*i);
			DrawFormatStringToHandle( 2+PjSys::Scr::MoveX, 464-9*i+PjSys::Scr::MoveY, PjSys::Scr::LogCol[i], PjSys::font::log,str.c_str(), PjSys::Scr::LogInt[i] ) ;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			PjSys::Scr::LogFrm[i]++;
		}else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255 -16*i);
			DrawFormatStringToHandle( 2+PjSys::Scr::MoveX, 464-9*i+PjSys::Scr::MoveY, PjSys::Scr::LogCol[i], PjSys::font::log,PjSys::Scr::LogChar[i].c_str(), PjSys::Scr::LogInt[i] ) ;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}

	//レーザー情報描画
	My::Laser::WriteStatus(522+PjSys::Scr::MoveX,260+PjSys::Scr::MoveY);

	//バズ個数描画
	if(My::BuzzLv<=My::NowBuzz){ //バズ残留レベル更新
		My::BuzzLv=My::NowBuzz;
		My::BuzzLvFrame=BUZZ_FRAME_MAX;
	}

	if(My::BuzzLvFrame>0 && --My::BuzzLvFrame<=0){
		My::BuzzLv--;
		My::BuzzLvFrame=BUZZ_FRAME_MAX;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
	DrawStringToHandle( 40+PjSys::Scr::MoveX, 125+PjSys::Scr::MoveY,"RISKY DODGE:", GetColor(255,255,255), PjSys::font::log,0,1 ) ;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	for(int i=0;i<5;i++){
		if(i+1<=My::NowBuzz){
			SetDrawBright(255,0,0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}else if(i+1==My::BuzzLv){
			SetDrawBright(My::BuzzLvFrame*6+64,64,64);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}else if(i+1<My::BuzzLv){
			SetDrawBright(255,127,127);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}else{
			SetDrawBright(255,255,255);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		}
		SetDrawMode(1);
		DrawGraph(10+PjSys::Scr::MoveX,340-i*12+PjSys::Scr::MoveY,PjSys::BuzzCnt,true);
		SetDrawMode(0);

		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	if(My::BuzzLv==0){SetDrawBlendMode(DX_BLENDMODE_ALPHA,64);}
	DrawRotaGraph(18+PjSys::Scr::MoveX , 174+PjSys::Scr::MoveY  ,1.0,PI/2, PjSys::MainChar[5] , TRUE );
	SetDrawBright(255,255-255*My::BuzzLv/BUZZMAX,255-255*My::BuzzLv/BUZZMAX);
	PjSys::NumDraw(PjSys::MainNum, My::BuzzLv,10,360,14); //Buzz
	SetDrawBright(255,255,255);
	if(My::BuzzLv==0){SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);}

	//ノイズ
	PjSys::Scr::DrawNoise();

	//アイテム描画
	for(int i=0;i<16;i++){
		if(My::Item::Exist[i]==true){
			My::Item::phase[i]++;
			math m;
			double d=m.GetDist2(My::Item::x[i],My::Item::y[i],My::x,My::y);
			if(d<32*32){ //アイテムゲット
				PlaySoundMem(My::Item::SndGet,DX_PLAYTYPE_BACK);
				switch(My::Item::type[i]){
					//アイテム小
					case 0:
						My::AddScore(1000);
						PjSys::Scr::AddLog("BONUS POINT +[%d]",1000,GetColor(64,127,64));
						break;
					//アイテム中
					case 1:
						My::AddScore(5000);
						PjSys::Scr::AddLog("BONUS POINT +[%d]",5000,GetColor(127,192,127));
						break;
					//アイテム大
					case 2:
						My::AddScore(10000);
						PjSys::Scr::AddLog("BONUS POINT +[%d]",10000,GetColor(127,255,127));
						break;
					//レベル上げる
					case 3:
						if(My::SubLevel<SUB_LEVEL && My::DefFrame<= 0){
							My::SubEnergy=My::SubEnergyMax*(My::SubLevel+1);
						}else{
							My::AddScore(1000);
							PjSys::Scr::AddLog("BONUS POINT +[%d]",1000,GetColor(127,255,127));
						}
						break;
					//レベル最大
					case 4:
						if(My::SubLevel<SUB_LEVEL && My::DefFrame<= 0){
							My::SubLevel=SUB_LEVEL-1;
							My::SubEnergy=My::SubEnergyMax*(My::SubLevel+1);
						}else{
							My::AddScore(5000);
							PjSys::Scr::AddLog("BONUS POINT +[%d]",5000,GetColor(127,255,127));
						}
							break;
					//ボム増やす
					case 5:
						My::AddBomb();
						break;
					//エクステンド
					case 6:
						My::AddLeft();
						break;
					//シークレット
					case 7:
						My::AddScore(10000);
						My::AddBomb();
						if(My::SubLevel<SUB_LEVEL && My::DefFrame<= 0){
							My::SubLevel=SUB_LEVEL-1;
							My::SubEnergy=My::SubEnergyMax*(My::SubLevel+1);
						}
						PjSys::Scr::AddLog("SECRET BONUS!+[%d]",100000,GetColor(255,127,127));
						break;
				}
				My::Item::Exist[i]=false;
			}else{
				if(My::shooting==true || My::DefFrame>0){
					if(d<64*64 && My::DefFrame<=SUBINVFRAME){
						My::Item::vx[i]=m.getcos(My::Item::x[i],My::Item::y[i],My::x,My::y)*5;
						My::Item::vy[i]=m.getsin(My::Item::x[i],My::Item::y[i],My::x,My::y)*5;
					}else{
						//My::Item::vx[i]*=0.8;
						if(My::Item::vy[i]<3){My::Item::vy[i]+=0.01;}
					}
				}else{
						My::Item::vx[i]=m.getcos(My::Item::x[i],My::Item::y[i],My::x,My::y)*5;
						My::Item::vy[i]=m.getsin(My::Item::x[i],My::Item::y[i],My::x,My::y)*5;
				}
				My::Item::x[i]+=(int)My::Item::vx[i];
				if(My::Item::x[i]<120 || My::Item::x[i]>520){
					if(My::Item::phase[i]<18000){My::Item::vx[i]*=-1;}else{My::Item::Exist[i]=false;}
				}
				My::Item::y[i]+=(int)My::Item::vy[i];
				if(My::Item::y[i]<0 || My::Item::y[i]>480){
					if(My::Item::phase[i]<18000){My::Item::vy[i]*=-1;}else{My::Item::Exist[i]=false;}
				}
				DxLib::VECTOR pLoc={(float)(My::Item::x[i]+PjSys::Scr::MoveX),(float)(My::Item::y[i]+PjSys::Scr::MoveY),0.4f};
				MV1SetPosition( My::Item::img[i], ConvScreenPosToWorldPos( pLoc ) );
				if(My::Item::phase[i]<=30){
					MV1SetScale( My::Item::img[i], VGet(My::Item::exp[My::Item::type[i]]/30*My::Item::phase[i],My::Item::exp[My::Item::type[i]]/30*My::Item::phase[i],My::Item::exp[My::Item::type[i]]/30*My::Item::phase[i])) ;
				}else{
					MV1SetScale( My::Item::img[i], VGet(My::Item::exp[My::Item::type[i]],My::Item::exp[My::Item::type[i]],My::Item::exp[My::Item::type[i]])) ;
				}
				MV1SetRotationXYZ(My::Item::img[i], VGet(DX_PI_F/90*My::Item::phase[i],DX_PI_F/90*My::Item::phase[i],DX_PI_F/90*My::Item::phase[i])) ;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,96);
				//SetDrawBright(255,255,255);
				DrawRotaGraph(My::Item::x[i]+PjSys::Scr::MoveX,My::Item::y[i]+PjSys::Scr::MoveY,1.0,PI*My::Item::phase[i]/90,My::imgBuzz,TRUE,FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

				//アイテム名描画
				int ix=My::Item::x[i]+24+PjSys::Scr::MoveX;
				int iy=My::Item::y[i]+24+PjSys::Scr::MoveY;
				DrawLine(ix-24,iy-16,ix,iy+16,GetColor(128,128,128),2);
				DrawLine(ix,iy+16,ix+32,iy+16,GetColor(128,128,128),2);
				switch(My::Item::type[i]){
					//アイテム小
					case 0:
						DrawStringToHandle(ix,iy,"BONUS[S]",GetColor(255,255,255),PjSys::font::caption);
						break;
					//アイテム中
					case 1:
						DrawStringToHandle(ix,iy,"BONUS[M]",GetColor(255,255,255),PjSys::font::caption);
						break;
					//アイテム大
					case 2:
						DrawStringToHandle(ix,iy,"BONUS[L]",GetColor(255,255,255),PjSys::font::caption);
						break;
					//レベル上げる
					case 3:
						DrawStringToHandle(ix,iy,"LEVEL+1",GetColor(255,255,255),PjSys::font::caption);
						break;
					//レベル最大
					case 4:
						DrawStringToHandle(ix,iy,"LEVEL MAX",GetColor(255,255,255),PjSys::font::caption);
						break;
					//ボム増やす
					case 5:
						DrawStringToHandle(ix,iy,"BOMB+1",GetColor(255,255,255),PjSys::font::caption);
						break;
					//エクステンド
					case 6:
						DrawStringToHandle(ix,iy,"STOCK+1",GetColor(255,255,255),PjSys::font::caption);
						break;
					//シークレット
					case 7:
						DrawStringToHandle(ix,iy,"SECRET",GetColor(255,255,255),PjSys::font::caption);
						break;
				}
				MV1DrawModel(My::Item::img[i]);
			}
		}
	}
//死んだ時の被弾画像
	DeadImg::Draw(580+PjSys::Scr::MoveX,120+PjSys::Scr::MoveY);
//曲名表示
	//BGMTitle::Draw();
}