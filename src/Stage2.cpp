#include "Common.h"
/*#############################################################

					  Stage: 02 進行記述

##############################################################*/

//-------------------------------------------------
//Stage2ロード
//------------------------------------------------
int StageManager::LoadSt2(int phase){
	LoadElements=31;
	//int dbg;
	switch(phase){
		case 0:
			My::NowStage=3;
			LoadImg=LoadGraph("img\\loadbg2.png");
			ImgLoadStr=LoadGraph("img\\load.bmp");
			return 0;
		case 1:
			UnloadSt1();

			return 0;
		case 2:
			PjSys::Scr::BGModel=MV1LoadModel("img\\dome_bluesky.mv1" );
			return 0;
		case 3:
			bgimg[0]=MV1LoadModel("img\\bg_sea2.mv1" );
			return 0;
		case 4:
			cloud.imgset(LoadGraph("img\\air.bmp"),LoadGraph("img\\air.bmp"),24);
			return 0;
		case 5:
			stgimg=LoadGraph("img\\stg3.bmp");
			return 0;
		case 6:
			bgimg[1]=MV1LoadModel("img\\bg_cloudbank.mv1" );
			PjSys::CameraVRota=DX_PI_F/-180.0f*90;
			return 0;
		case 7:
			PjSys::CameraHRota=0;
			bg2.imgset(bgimg[0],6);
			return 0;
		case 8:
			PjSys::CameraTRota=0;
			return 0;
		case 9:
			PjSys::CameraPos=VGet( 0.0f, -200.0f, 0.0f);
			return 0;
		case 10:
			e1.setcap(100);
			InitCommon();
			return 0;
		case 11:

			return 0;
		case 12:
			SmallEnmImg[0]=MV1LoadModel("img\\small0.mv1") ;
			return 0;
		case 13:
			SmallEnmImg[1]=MV1LoadModel("img\\small1.mv1") ;
			return 0;
		case 14:
			SmallEnmImg[2]=MV1LoadModel("img\\missile.mv1") ;
			return 0;
		case 15:
			SmallEnmImg[3]=MV1LoadModel("img\\container.mv1") ;
			return 0;
		case 16:
			SmallEnmImg[4]=MV1LoadModel("img\\air2air_cannon.mv1") ;
			return 0;
		case 17:
			BigEnmImg[0]=MV1LoadModel("img\\big1.mv1") ;
			return 0;
		case 18:
			BigEnmImg[1]=MV1LoadModel("img\\stg2_middleboss.mv1") ;
			return 0;
		case 19:
			BigEnmImg[2]=MV1LoadModel("img\\stg2_middleboss_wing.mv1") ;
			return 0;
		case 20:
			BigEnmImg[3]=MV1LoadModel("img\\stg2_middleboss_1.mv1") ;
			return 0;
		case 21:
			BossImg[0]=MV1LoadModel("img\\boss2.mv1") ;
			BossImg[1] = MV1LoadModel("img\\stg2_boss_bit.mv1");
			return 0;
		case 22:
			SetCreateSoundDataType( Setting.General.LoadMode	) ;
			return 0;
		case 23:
			PjSys::bgm=LoadSoundMem("snd\\stg2.mp3");
			return 0;
		case 24:
			PjSys::bossbgm=LoadSoundMem("snd\\boss2.mp3");
			return 0;
		case 25:
			ChangeVolumeSoundMem( Setting.General.BGMVolume ,PjSys::bgm ) ;
			return 0;
		case 26:
			SetCreateSoundDataType( DX_SOUNDDATATYPE_MEMNOPRESS	) ;
			return 0;
		case 27:
			e1.sndSE[0]=LoadSoundMem("snd\\missile.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , e1.sndSE[0] );
			return 0;
		case 28:
			gPlayer.setX(320);
			gPlayer.setY(400);
			return 0;
		case 29:
			gPlayer.clearParticle();
			My::Born=true;
			return 0;
		case 30:
			DeleteGraph(LoadImg);
			DeleteGraph(ImgLoadStr);
			LoadElements=0;
			return 1;
		//メモ:ロードファイルを追加した際はLoadElements及びUnloatSt2を書き換えるのを忘れない事！
	}
	return -1;
}
void StageManager::UnloadSt2(){
			MV1DeleteModel(PjSys::Scr::BGModel);;
			MV1DeleteModel(bg2.hField);
			MV1DeleteModel(bg2.hField2);
			cloud.imgset(MakeGraph(0 , 0),MakeGraph(0 , 0),0);
			DeleteGraph(stgimg);
			MV1DeleteModel(SmallEnmImg[0]) ;
			MV1DeleteModel(SmallEnmImg[1]) ;
			MV1DeleteModel(SmallEnmImg[2]) ;
			MV1DeleteModel(SmallEnmImg[3]) ;
			MV1DeleteModel(SmallEnmImg[4]) ;
			MV1DeleteModel(BigEnmImg[0]) ;
			MV1DeleteModel(BigEnmImg[1]) ;
			MV1DeleteModel(BigEnmImg[2]) ;
			MV1DeleteModel(BigEnmImg[3]) ;
			MV1DeleteModel(BossImg[0]) ;
			MV1DeleteModel(BossImg[1]);
			DeleteSoundMem(PjSys::bgm);
			DeleteSoundMem(PjSys::bossbgm);
			DeleteSoundMem(e1.sndSE[0]);
			for(int i=0;i<16;i++){DeleteGraph(Enm::imgBurn[i]);}
			return;
}

void StageManager::InitCommon(){
	for(int i=0;i<5;i++){
		gPlayer.pbStraight[i].Init();
	}
	e1.init();
	Enm::Refuge::AnyAvaliable=false;
	My::Item::Init();
	for(int i=0;i<10;i++){
		PjSys::Scr::LogChar[i].clear();
	}
	return;
}

int StageManager::stg20(){
	if(phase>=0 &&LoadSt2(phase)==1){
		return 1;
	}
	Loading(LoadImg);
	return 0;
}
//#######################################################
//Stage2本体
//########################################################

int StageManager::stg21(){
	static const int HpSmall0=20;
	static const int HpSmall1=20;
	static const int HpSmall2=20;
	static int HpSmall3=(PjSys::HardConst<3)?256:128;

	static const int HpSmall4=(8-PjSys::HardConst)*50;
	static const int HpBig0=300+(8-PjSys::HardConst)*50;

	//拡大率
	static const float ExpSmall[8]={0.009f,0.007f,0.012f,0.011f,0.004f,0.01f};
	static const float ExpBig[8]={0.02f,0.08f,0.08f,0.035f,1.0f,1.0f,1.0f,100.0f};
	int i=0;
	int bp;
	//フェーズによる場合分け
	switch(phase){
		case 0:
			//pushright=0;
			//My::Score=0;
			//PjSys::BombExtendPhase=1;
			//PjSys::ExtendPhase=1;
			//My::SubEnergy=0;
			//My::Bomb=My::DefaultBomb;
			//My::Left=My::DefaultLeft;
			Enm::BossPhase=8500;
			SetCameraPositionAndAngle( VGet( 0.0f+PjSys::Scr::MoveX, -230.0f, 0.0f+PjSys::Scr::MoveY ), DX_PI_F/-2.0f, 0, 0 ) ;
			My::BombFrame=0;
			My::Rot=0;
			PjSys::Scr::AddLog("DIANA SYSTEM READY.",My::NowStage,GetColor(127,255,127));
			if(PjSys::cheat::Go2Boss){phase=Enm::BossPhase-1;}else{PlaySoundMem(PjSys::bgm ,DX_PLAYTYPE_LOOP ,FALSE) ;}
			bp=e1.create(-127,0,240,0x1d,BigEnmImg[7],ExpBig[7],2,0x100,30,Enm::RLaser,0,0,true,false,false);
			e1.mphase[bp]=4;
			break;

		//ステージ表示(10frm-430frm)
		//------------------------------------------------

		//====================
		//ミサイル地帯
		//====================

		case 452:
			e1.create(HpSmall2,181,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,30,Enm::RLaser,24,24,true);
			break;
		case 457:
			e1.create(HpSmall2,415,-5,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 462:
			e1.create(HpSmall2,410,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 470:
			//e1.create(HpSmall2,123,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 475:
			e1.create(HpSmall2,410,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 482:
			e1.create(HpSmall2,280,-18,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 487:
			e1.create(HpSmall2,188,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 494:
			//e1.create(HpSmall2,162,-2,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 498:
			e1.create(HpSmall2,301,-17,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 505:
			e1.create(HpSmall2,375,-18,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 512:
			e1.create(HpSmall2,397,-1,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 518:
			//e1.create(HpSmall2,380,-6,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 524:
			e1.create(HpSmall2,368,-11,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 529:
			e1.create(HpSmall2,216,-2,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 534:
			e1.create(HpSmall2,181,-14,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 542:
			//e1.create(HpSmall2,476,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 546:
			e1.create(HpSmall2,407,-9,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 552:
			e1.create(HpSmall2,171,-5,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 559:
			e1.create(HpSmall2,154,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 564:
			//e1.create(HpSmall2,440,-15,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 570:
			e1.create(HpSmall2,420,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 578:
			e1.create(HpSmall2,342,-19,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 584:
			e1.create(HpSmall2,389,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 589:
			//e1.create(HpSmall2,331,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 594:
			e1.create(HpSmall2,436,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 600:
			e1.create(HpSmall2,515,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 607:
			e1.create(HpSmall2,326,-1,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 614:
			//e1.create(HpSmall2,480,-2,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 620:
			e1.create(HpSmall2,222,-10,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 624:
			e1.create(HpSmall2,473,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 631:
			e1.create(HpSmall2,120,-3,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 638:
			//e1.create(HpSmall2,285,-17,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 642:
			e1.create(HpSmall2,432,-18,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 649:
			e1.create(HpSmall2,471,-2,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 654:
			e1.create(HpSmall2,272,-4,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 662:
			//e1.create(HpSmall2,359,-1,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 667:
			e1.create(HpSmall2,412,-15,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 672:
			e1.create(HpSmall2,433,-15,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 678:
			e1.create(HpSmall2,223,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<4)?0x201:0x100,30,Enm::RLaser,24,24,true);
			break;
		case 686:
			//e1.create(HpSmall2,425,-2,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 690:
			e1.create(HpSmall2,144,-4,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			break;
		case 696:
			e1.create(HpSmall2,169,-10,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 703:
			e1.create(HpSmall2,518,-14,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<5)?0x201:0x100,30,Enm::RLaser,24,24,true);
			break;
		case 708:
			//e1.create(HpSmall2,258,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 714:
			e1.create(HpSmall2,225,-17,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<4)?0x201:0x100,30,Enm::RLaser,24,24,true);
			break;
		case 721:
			e1.create(HpSmall2,222,-18,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 727:
			e1.create(HpSmall2,234,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<3)?0x201:0x100,30,Enm::RLaser,24,24,true);
			break;
		case 734:
			//e1.create(HpSmall2,188,-17,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		case 740:
			e1.create(HpSmall2,437,-10,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,30,Enm::RLaser,24,24,true);
			break;
		case 744:
			e1.create(HpSmall2,274,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
			break;
		//====================
		//ミサイル地帯終了
		//====================
		case 800:
			e1.create(HpSmall3,98,450,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::RLaser,48,48,true);
			break;
		case 890:
			e1.create(HpSmall2,64,64,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall2,80,96,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall2,96,128,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::RBullet,24,24,true);
			break;
		case 920:
			e1.create(HpSmall2,32,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall2,48,32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::RBullet,24,24,true);
			break;
		case 950:
			e1.create(HpSmall3,48,450,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::RLaser,48,48,true);
			break;
		case 980:
			e1.create(HpSmall2,616,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall2,600,32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::GBullet,24,24,true);
			break;
		case 1010:
			e1.create(HpSmall2,584,64,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall2,568,96,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,100,Enm::GBullet,24,24,true);
			break;
		case 1040:
			e1.create(HpSmall3,18,450,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::RLaser,48,48,true);
			e1.create(HpSmall2,552,128,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 1160:
			e1.create(HpSmall3,200,-48,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x100,30,Enm::RLaser,48,48,true);
			e1.create(HpSmall3,320,-32,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x100,30,Enm::RLaser,48,48,true);
			e1.create(HpSmall3,440,-16,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x100,30,Enm::RLaser,48,48,true);
			break;
		case 1360:
			if(PjSys::Hard>3){
				bp=e1.create(HpSmall3*2,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=0;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=60;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=120;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=180;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=240;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=300;
			}else{
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RBullet,48,48,true);
				e1.mphase[bp]=0;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x102,300,Enm::GBullet,48,48,true);
				e1.mphase[bp]=60;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RBullet,48,48,true);
				e1.mphase[bp]=120;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::GBullet,48,48,true);
				e1.mphase[bp]=180;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x104,300,Enm::RBullet,48,48,true);
				e1.mphase[bp]=240;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::GBullet,48,48,true);
				e1.mphase[bp]=300;
			}
			break;
		case 1540:
			i=320;
			e1.create(HpSmall2,124+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			e1.create(HpSmall2,180+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<5)?0x201:0x100,60,Enm::BBullet,24,24,true);
			e1.create(HpSmall2,174+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			break;
		case 1700:
			i=120;
			e1.create(HpSmall2,142+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			e1.create(HpSmall2,132+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			e1.create(HpSmall2,120+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::BBullet,24,24,true);
			e1.create(HpSmall2,160+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			break;
		case 1760:
			i=320;
			e1.create(HpSmall2,42+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
			e1.create(HpSmall2,98+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			e1.create(HpSmall2,38+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<3)?0x201:0x100,60,Enm::BBullet,24,24,true);
			e1.create(HpSmall2,28+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
			break;
			//====================
			//バキュラ地帯
			//====================

			case 1909:
				bp=e1.create(HpSmall3,500,0,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=9;
				e1.create(HpSmall2,315,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 1923:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,200,-44,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=6;
				}
				break;
			case 1942:
				bp=e1.create(HpSmall3,450,-32,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=6;
				break;
			case 1969:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,193,-18,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=9;
				}
				break;
			case 1983:
				bp=e1.create(HpSmall3,400,-36,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=6;
				break;
			case 2016:
				if(PjSys::Hard<5){
					bp=e1.create(HpSmall3,189,-39,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=5;
				}
				e1.create(HpSmall2,350,-18,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2022:
				bp=e1.create(HpSmall3,300,-23,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=8;
				break;
			case 2047:
				if(PjSys::Hard<6){
					bp=e1.create(HpSmall3,364,-41,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=8;
				}
				break;
			case 2061:
				bp=e1.create(HpSmall3,250,-35,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=10;
				break;
			case 2083:
				if(PjSys::Hard<7){
					bp=e1.create(HpSmall3,145,-21,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=8;
				}
				break;
			case 2105:
				bp=e1.create(HpSmall3,200,-27,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=7;
				e1.create(HpSmall2,320,-8,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2126:
				bp=e1.create(HpSmall3,150,-32,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=6;

				i=320;
				e1.create(HpSmall2,55+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,182+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,32+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<5)?0x201:0x100,60,Enm::BBullet,24,24,true);
				e1.create(HpSmall2,-124+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
				break;

			case 2140:
				bp=e1.create(HpSmall3,200,-14,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=9;
				break;
			case 2177:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,250,-30,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=1;
				}
				break;
			case 2194:
				if(PjSys::Hard<5){
					bp=e1.create(HpSmall3,301,-7,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
					e1.mphase[bp]=1;
				}
				break;
			case 2205:
				bp=e1.create(HpSmall3,300,-48,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=12;
				e1.create(HpSmall2,358,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2238:
				if(PjSys::Hard<6){
					bp=e1.create(HpSmall3,230,-5,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
					e1.mphase[bp]=8;
				}
				break;
			case 2255:
				bp=e1.create(HpSmall3,350,0,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=3;
				break;
			case 2261:
				if(PjSys::Hard<7){
					bp=e1.create(HpSmall3,222,-44,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
					e1.mphase[bp]=7;
				}
				break;
			case 2295:
				bp=e1.create(HpSmall3,400,-44,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=4;
				break;
			case 2317:
				bp=e1.create(HpSmall3,450,-16,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=14;
				e1.create(HpSmall2,490,-19,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2322:

				bp=e1.create(HpSmall3,500,-44,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=7;
				break;
			case 2349:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,239,-46,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
					e1.mphase[bp]=2;
				}
				break;
			case 2371:
				if(PjSys::Hard<5){
					bp=e1.create(HpSmall3,292,-29,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=8;
				}
				e1.create(HpBig0,290,0,0x12,BigEnmImg[0],ExpBig[0],0,0x107,500,Enm::GLaser,48,48,true);
				break;
			case 2386:
				bp=e1.create(HpSmall3,520,-1,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=10;

				i=100;
				e1.create(HpSmall2,55+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,182+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,32+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<5)?0x201:0x100,60,Enm::BBullet,24,24,true);
				e1.create(HpSmall2,-124+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);

				break;
			case 2407:
				if(PjSys::Hard<6){
					bp=e1.create(HpSmall3,459,-15,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=9;
				}
				e1.create(HpSmall2,229,-10,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2428:
				bp=e1.create(HpSmall3,450,-40,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=8;
				break;
			case 2448:
				if(PjSys::Hard<7){
					bp=e1.create(HpSmall3,298,-9,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=8;
				}
				break;
			case 2467:
				bp=e1.create(HpSmall3,400,-17,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=8;
				break;
			case 2492:
				bp=e1.create(HpSmall3,350,-14,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=12;
				break;
			case 2517:
				bp=e1.create(HpSmall3,300,-34,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=6;
				e1.create(HpSmall2,390,-4,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2536:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,443,-34,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=2;
				}
				break;
			case 2554:
				bp=e1.create(HpSmall3,250,-45,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=5;
				break;
			case 2573:
				if(PjSys::Hard<5){
					bp=e1.create(HpSmall3,318,-31,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=1;
				}
				break;
			case 2583:
				bp=e1.create(HpSmall3,200,-31,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=6;
				break;
			case 2611:
				if(PjSys::Hard<6){
					bp=e1.create(HpSmall3,265,-24,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=5;
				}
				e1.create(HpSmall2,140,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2629:
				bp=e1.create(HpSmall3,150,-36,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=4;
				break;
			case 2655:
				if(PjSys::Hard<7){
					bp=e1.create(HpSmall3,206,-13,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=6;
				}
				break;
			case 2672:
				bp=e1.create(HpSmall3,120,-14,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=7;
				i=380;
				e1.create(HpSmall2,55+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,182+i,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
				e1.create(HpSmall2,32+i,-48,0x1c,SmallEnmImg[2],ExpSmall[2],0,(PjSys::Hard<5)?0x201:0x100,60,Enm::BBullet,24,24,true);
				e1.create(HpSmall2,-124+i,-32,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,300,Enm::RLaser,24,24,true);
				break;

			case 2694:
				bp=e1.create(HpSmall3,150,-26,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
				e1.mphase[bp]=7;
				break;
			case 2703:
				bp=e1.create(HpSmall3,200,-48,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=4;
				e1.create(HpSmall2,416,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2728:
				if(PjSys::Hard<4){
					bp=e1.create(HpSmall3,294,-4,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=3;
				}
				break;
			case 2747:
				bp=e1.create(HpSmall3,250,-37,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=4;
				break;
			case 2761:
				if(PjSys::Hard<5){
					bp=e1.create(HpSmall3,297,-34,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=1;
				}
				break;
			case 2782:
				bp=e1.create(HpSmall3,300,-17,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=1;
				break;
			case 2819:
				if(PjSys::Hard<6){
					bp=e1.create(HpSmall3,316,-15,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=5;
				}
				e1.create(HpSmall2,492,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 2823:
				bp=e1.create(HpSmall3,350,-16,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=3;
				break;
			case 2843:
				if(PjSys::Hard<7){
					bp=e1.create(HpSmall3,334,-17,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x102,100,Enm::YLaser,48,48,true);
					e1.mphase[bp]=6;
				}
				break;
			case 2860:
				bp=e1.create(HpSmall3,400,-22,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=5;
				break;
			case 2890:
				bp=e1.create(HpSmall3,450,-7,0x1d,SmallEnmImg[3],ExpSmall[3],1,0x200,100,Enm::BLaser,48,48,true);
				e1.mphase[bp]=4;
				break;
			//====================
			//バキュラ地帯終了
			//====================
			case 3000:
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true,true,true,true,3);
				e1.mphase[bp]=0;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true,true,true,true,3);
				e1.mphase[bp]=120;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x103,300,Enm::BBullet,48,48,true,true,true,true,0);
				e1.mphase[bp]=240;
				break;
			case 3250:
				e1.create(HpSmall2,329,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 3257:
				e1.create(HpSmall2,266,0,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
				break;
			case 3263:
				e1.create(HpSmall2,398,-16,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 3269:
				e1.create(HpSmall2,121,-10,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
				break;
			case 3266:
				e1.create(HpSmall2,294,-12,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 3280:
				e1.create(HpSmall2,252,-19,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);

				break;
			case 3288:
				e1.create(HpSmall2,430,-1,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;

			case 3294:
				e1.create(HpSmall2,460,-19,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
				break;
			case 3299:
				e1.create(HpSmall2,451,-3,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				break;
			case 3300:
				e1.create(HpSmall2,306,-4,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=60;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,300,Enm::RLaser,48,48,true);
				e1.mphase[bp]=180;
				bp=e1.create(HpSmall3*3,340,-48,0x21,SmallEnmImg[3],ExpSmall[3],1,0x100,10,Enm::RBullet,48,48,true,true,true,true,7);
				e1.mphase[bp]=300;
				break;

			case 3350:
				e1.create(HpBig0,290,0,0x12,BigEnmImg[0],ExpBig[0],0,0x107,500,Enm::GLaser,48,48,true,true,true,true,3);
				e1.create(HpSmall3,18,450,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::RLaser,48,48,true);
				break;

				//中ボス巨大輸送機
			case 4000:
				e1.bephase=0;

				Enum[1]=e1.create(10000,520,-240,0x2a,BigEnmImg[2],ExpBig[2],0,0x100,5,Enm::GLaser,460,48,false);//翼
				Enum[2]=e1.create(10000,400,-240,0x2a,BigEnmImg[3],ExpBig[3],0,0x100,5,Enm::GLaser,24,180,false);//左エンジン1
				Enum[3]=e1.create(10000,640,-240,0x2a,BigEnmImg[3],ExpBig[3],0,0x100,5,Enm::GLaser,24,180,false);//右エンジン1
				Enum[0]=e1.create(7000+(7-PjSys::HardConst)*500,520,-240,0x2a,BigEnmImg[1],ExpBig[1],6,0x100,5,Enm::GLaser,80,400,false);//本体
				Enum[8]=e1.create(-127,520,-240,0x2a,BigEnmImg[1],ExpBig[1]*0.0001f,6,0x100,5,Enm::GLaser,0,0,false,false,false);//本体

				int blt1;
				int blt2;
				blt1=0x101;
				blt2=0x101;

				if(PjSys::HardConst<6){
					blt1=0x103;
					blt2=0x103;
				}
				if(PjSys::HardConst<4){
					blt2=0x105;
				}
				e1.create(256,500,-40,0x2a,SmallEnmImg[4],ExpSmall[4],4,blt1,100,Enm::RLaser,48,48,true); //左尾翼砲塔1
				e1.create(256,500,0,0x2a,SmallEnmImg[4],ExpSmall[4],4,blt2,100,Enm::RLaser,48,48,true); //左尾翼砲塔2
				e1.create(256,540,-40,0x2a,SmallEnmImg[4],ExpSmall[4],4,blt1,100,Enm::RLaser,48,48,true); //右尾翼砲塔1
				e1.create(256,540,0,0x2a,SmallEnmImg[4],ExpSmall[4],4,blt2,100,Enm::RLaser,48,48,true); //右尾翼砲塔2
				PjSys::Scr::AddLog("ALEART!",0,GetColor(255,0,0));
				break;

			case 4020:
				Enum[4]=e1.create(10000,760,-210,0x2a,SmallEnmImg[4],ExpSmall[4]/100,4,0x100,5,Enm::BBullet,128,32,true); //右砲塔ダミー
				e1.phase[Enum[4]]=20;
				Enum[5]=e1.create(10000,280,-210,0x2a,SmallEnmImg[4],ExpSmall[4]/100,4,0x100,5,Enm::GBullet,128,32,true); //左砲塔ダミー
				e1.phase[Enum[5]]=20;
				Enum[6]=e1.create(10000,280,-210,0x2a,BigEnmImg[3],ExpBig[3],0,0x100,5,Enm::GLaser,24,180,false);//左エンジン2
				e1.phase[Enum[6]]=20;
				Enum[7]=e1.create(10000,760,-210,0x2a,BigEnmImg[3],ExpBig[3],0,0x100,5,Enm::GLaser,24,180,false);//右エンジン2
				e1.phase[Enum[7]]=20;

				PjSys::Scr::AddLog("VISUAL CONTACT WITH",0,GetColor(255,255,255));
				break;
			case 4040:
				PjSys::Scr::AddLog("\"ARSENAL SHIP <<AJAX>>\"",0,GetColor(255,255,127));
				break;
			case 4060:
				PjSys::Scr::AddLog("CONFIRMED.",0,GetColor(255,255,127));
				break;

			case 4100:
				//bp=e1.create(HpSmall4*2,520,0,0x2a,SmallEnmImg[4],ExpSmall[4]*2,4,0x100,1,Enm::RLaser,64,64,true); //機体中央砲塔
				//e1.phase[bp]=100;
				break;

			case 4700:
				if(e1.bephase==0){
					e1.create(HpSmall2,240,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				}
				break;
			case 4710:
				if(e1.bephase==0){
					e1.create(HpSmall2,280,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				}
				break;
			case 4720:
				if(e1.bephase==0){
					e1.create(HpSmall2,320,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				}
				break;
			case 4730:
				if(e1.bephase==0){
					e1.create(HpSmall2,360,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				}
				break;
			case 4740:
				if(e1.bephase==0){
					e1.create(HpSmall2,400,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x101,30,Enm::RLaser,24,24,true);
				}
				break;
//でかいミサイルのラッシュ
			case 4750:
				if(e1.bephase==0){
					e1.create(HpSmall3,98,450,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x100,3,Enm::RLaser,48,48,true);

					bp=e1.create(HpBig0,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 4800:
				if(e1.bephase==0){
					if(PjSys::Hard<3){
						//e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,280,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,360,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,200,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,440,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 4850:
				if(e1.bephase==0){
					if(PjSys::Hard<5){
						e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 4900:
				if(e1.bephase==0){
					if(PjSys::Hard<3){
						//e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,280,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,360,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,200,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,440,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
				}
				break;
			case 4950:
				if(e1.bephase==0){
					if(PjSys::Hard<3){
						e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 5000:
				if(e1.bephase==0){
					if(PjSys::Hard<6){
						e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,280,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,360,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,200,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
					bp=e1.create(HpBig0,440,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=15;
				}
				break;
			case 5050:
				if(e1.bephase==0){
					if(PjSys::Hard<3){
						//e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 5100:
				if(e1.bephase==0){
					if(PjSys::Hard<6){
						e1.create(HpSmall3,98,My::y,0x1e,SmallEnmImg[3],ExpSmall[3],1,0x10d,300,Enm::GLaser,48,48,true);
					}
					bp=e1.create(HpBig0,280,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,360,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,200,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,440,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;
			case 5150:
				if(e1.bephase==0){
					bp=e1.create(HpBig0,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x100,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
				}
				break;

			case 5200:
				if(e1.bephase==0){
					e1.create(HpSmall2,e1.x[Enum[0]]-100,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::RLaser,24,24,true);
				}
				break;
			case 5300:
				if(e1.bephase==0){
					e1.create(HpSmall2,e1.x[Enum[0]]-50,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::RLaser,24,24,true);
				}
				break;
			case 5400:
				if(e1.bephase==0){
					e1.create(HpSmall2,e1.x[Enum[0]]+50,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}
				break;
			case 5500:
				if(e1.bephase==0){
					e1.create(HpSmall2,e1.x[Enum[0]]+100,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::RLaser,24,24,true);
				}
				break;

//ワインダー
			case 5600:
				if(e1.bephase==0){
					bp=e1.create(-127,200,120,0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x20a,2500,Enm::GLaser,2,2,false,false,false);//ワインダー１
					e1.phase[bp]=1600;
					bp=e1.create(-127,440,120,0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x20a,2500,Enm::GLaser,2,2,false,false,false);//ワインダー２
					e1.phase[bp]=1600;
					//bp=e1.create(-127,e1.x[Enum[0]],e1.y[Enum[0]],0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x103,90,Enm::RLaser,2,2,false,false,false);//ワインダー２
					//e1.phase[bp]=1600;
				}
				break;
			case 6000:
				if(e1.bephase==0){
				}else{ //早回し
					e1.create(HpBig0,290,0,0x12,BigEnmImg[0],ExpBig[0],0,0x20b,2000,Enm::BLaser,48,48,true,true,true,true,7);
				}
				break;
			case 6240:
				e1.create(HpBig0,640-160,0,0x12,BigEnmImg[0],ExpBig[0],0,0x108,2000,Enm::BLaser,48,48,true); //一回目の轢き殺し誘導
				break;
			case 6400:
				if(e1.bephase==0){
					e1.create(HpSmall2,e1.x[Enum[0]]-100,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::GBullet,24,24,true);
					if(PjSys::HardConst<4){
						e1.create(HpSmall2,e1.x[Enum[0]]+100,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::GBullet,24,24,true);
					}
				}

				break;
			case 6500:
				if(e1.bephase==0){
					if(PjSys::HardConst<3){
						e1.create(HpSmall2,e1.x[Enum[0]]+200,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::BBullet,24,24,true);
					}
					if(PjSys::Hard<6){
						e1.create(HpSmall2,e1.x[Enum[0]]-200,e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x201,60,Enm::BBullet,24,24,true);
					}
				}else{
				}
				break;
			//でっかいミサイル単発
			case 6620:
				if(e1.bephase==0){
					bp=e1.create(HpBig0,340,550,0x22,SmallEnmImg[2],ExpSmall[2]*2,3,0x1a5,1000,Enm::RLaser,32,32,true);
					e1.mphase[bp]=270;
				}else{
					//早回し
					//bp=e1.create(HpSmall3,My::x,550,0x22,SmallEnmImg[3],ExpSmall[3],1,0x1a5,1000,Enm::RLaser,32,32,true);
					//e1.mphase[bp]=270;
				}
				break;
			case 6900:
				if(e1.bephase==0){
					e1.create(HpSmall2,540,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::RLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6910:
				if(e1.bephase==0){
					e1.create(HpSmall2,460,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6920:
				if(e1.bephase==0){
					e1.create(HpSmall2,380,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6930:
				if(e1.bephase==0){
					e1.create(HpSmall2,300,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6940:
				if(e1.bephase==0){
					e1.create(HpSmall2,220,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6950:
				if(e1.bephase==0){
					e1.create(HpSmall2,180,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 6960:
				if(e1.bephase==0){
					e1.create(HpSmall2,140,-13,0x1c,SmallEnmImg[2],ExpSmall[2],0,0x103,30,Enm::BLaser,24,24,true);
				}else{
					e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::RBullet,24,24,true);
				}
				break;
			case 7100:
				//でかいミサイルが上下から
				if(e1.bephase==0 && PjSys::Hard<=2){
					
					//上から
					bp=e1.create(HpBig0/2,320,-100,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0/2,240,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0/2,400,-140,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0/2,160,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					bp=e1.create(HpBig0/2,480,-180,0x1d,SmallEnmImg[2],ExpSmall[2]*2,0,0x200,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=25;
					//下から
					bp=e1.create(HpBig0/2,280,620,0x23,SmallEnmImg[2],ExpSmall[2]*2,0,0x201,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=-90;
					bp=e1.create(HpBig0/2,360,620,0x23,SmallEnmImg[2],ExpSmall[2]*2,0,0x201,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=-90;
					bp=e1.create(HpBig0/2,200,680,0x23,SmallEnmImg[2],ExpSmall[2]*2,0,0x201,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=-90;
					bp=e1.create(HpBig0/2,440,680,0x23,SmallEnmImg[2],ExpSmall[2]*2,0,0x201,30,Enm::RLaser,32,32,true);
					e1.mphase[bp]=-90;
					
				}else{
				}

				break;
			case 7160:
					e1.create(HpBig0,160,0,0x12,BigEnmImg[0],ExpBig[0],0,0x108,256,Enm::BLaser,48,48,true);
					break;

			case 7600:
				if(e1.bephase==0){
					bp=e1.create(-127,e1.x[Enum[0]],e1.y[Enum[0]],0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x202,1500,Enm::RLaser,2,2,false,false,false);//ワインダー１
					e1.phase[bp]=3600;

					//ばら撒き
					bp=e1.create(-127,e1.x[Enum[0]]-120,e1.y[Enum[0]]+20,0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x105,400,Enm::BBullet,2,2,false,false,false);//ワインダー１
					e1.phase[bp]=3600;
					bp=e1.create(-127,e1.x[Enum[0]]+120,e1.y[Enum[0]]+20,0x2a,SmallEnmImg[4],ExpSmall[4]/100,0,0x107,400,Enm::BBullet,2,2,false,false,false);//ワインダー２
					e1.phase[bp]=3600;
				}else{
					e1.create(HpBig0,350,0,0x12,BigEnmImg[0],ExpBig[0],0,0x202,2000,Enm::BLaser,48,48,true);
				}
				break;
			case 8000:
				e1.create(HpBig0,380,0,0x12,BigEnmImg[0],ExpBig[0],0,0x106,2000,Enm::BLaser,48,48,true,true,true,true,3);

				break;
			case 8300:
				if(e1.bephase==0){
					bp=e1.create(-127,(int)e1.x[Enum[0]],(int)e1.y[Enum[0]],0x23,BossImg[0],0.01f,1,0x00,1,Enm::BBullet,0,0,true,false,false,false,0,0.35f);
					e1.mphase[bp]=270;
				}
				break;
	}

	if(phase==Enm::BossPhase){
		return 1;
	}
	math m;
		PjSys::CameraPos.y=-100;
	if(phase<=720){
		PjSys::CameraVRota=(float)(DX_PI_F/180.0f * ((mycos(m.ToRadian((float)phase/2+10))*40 - 140)));
		PjSys::CameraHRota=DX_PI_F/-360.0f *phase+(float)(DX_PI_F/180.0f * (mysin(m.ToRadian((float)phase/80))*45));
	}else{
		PjSys::CameraHRota=(float)(DX_PI_F/180.0f * (mysin(m.ToRadian((float)phase/80))*45));
	}

	stgmove();
	if(My::GOver==true || My::Pause==true){return 0;}

	if(phase>=0 && phase<250){
		cloud.Visible=true;
		cloud.alpha=255;
		//cloud.sspeed=24;
	}else if(phase<314){
		cloud.alpha=(313-phase)*4;
	}else if(phase<=500){
		cloud.Visible=false;
	}else if(phase>500 && phase<532){
		cloud.Visible=true;
		cloud.alpha=phase-500;
		//cloud.sspeed=24;
	}

	if(phase>=10 && phase<430){ //ステージ表示
		ShowStageTitle(phase-10);
	}else if( phase>4000 && phase<=8500){ //中ボス死んでるか？
		if(e1.bephase==0 && e1.hp[Enum[0]]<=0 /*&& e1.type[Enum[0]]==0x2a*/){
			e1.bephase=1;
			e1.expansion[Enum[8]]=ExpBig[1];
			My::Invincible+=180;
			for(int i=1;i<9;i++){
				//死亡処理
					e1.IsHitBlt[Enum[i]]=false;
					e1.IsHitPlayer[Enum[i]]=false;
					e1.rotaflg[Enum[i]]=3;
					e1.type[Enum[i]]=0x2b;
					e1.eb1[Enum[i]].init();
					if(i==1 ||i==8){e1.mphase[Enum[i]]=0;}else{e1.mphase[Enum[i]]=i-4;}
			}
		}else if(e1.bephase==0 && e1.hp[Enum[0]]>=0){
			for(int j=0;j<10;j++){
				if(j>0 && j<8){
					int damage=e1.score[Enum[j]]-e1.hp[Enum[j]];
					e1.hp[Enum[0]]-=(int)(damage/2);
					e1.hp[Enum[j]]=e1.score[Enum[j]];
				}
			}
			Enm::drawHP(e1.score[Enum[0]],e1.hp[Enum[0]],(int)((8500-phase)/60));

			if((PjSys::GameLevel<=1 ||(e1.hp[Enum[0]]<e1.score[Enum[0]]/2)) && phase >= 6400){
				if(e1.x[Enum[0]]>=120 && e1.x[Enum[0]]<=520 && e1.y[Enum[0]]<=240 && phase%60==0){
					int i=e1.create(HpSmall2,e1.x[Enum[0]],e1.y[Enum[0]],0x1c,SmallEnmImg[2],ExpSmall[2],0,0x100,30,Enm::RLaser,24,24,true);
					e1.x[i]+=((i*31337)%200)-100;
				}else if(phase%120==0){
					int i=e1.create(HpSmall0,-64,-64,0x27,SmallEnmImg[0],ExpSmall[0],0,0x103,100,Enm::RBullet,24,24,true);
					e1.mphase[i]=((i*31337)%41)*10+120;
				}
			}
		}
		//int bs;
		if(e1.bephase==2){
			e1.bephase=3;
			PlaySoundMem(e1.SndBossExp,DX_PLAYTYPE_BACK);
			PjSys::Scr::SetShake(180,-10,10);
			Enum[9]=e1.create(-127,(int)e1.x[Enum[8]],490,0x23,BossImg[0],0.005f,1,0x00,1,Enm::BBullet,0,0,true,false,false,false,0,0.35f);
			e1.mphase[Enum[9]]=270;
		}else if(e1.bephase>2 && e1.bephase<183){
			e1.bephase-=3;
			//double my=e1.bephase/8;
			//double my2=480-my*my;
			//MV1SetPosition( BossImg[0], VECTOR Position )
			int bs=Enum[9];
			SetDrawMode(1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,190-e1.bephase);
			DrawModiGraph((int)(e1.x[bs]),(int)(e1.y[bs]+16),
						  (int)(e1.x[bs]),(int)(e1.y[bs]+16),
						  (int)(e1.x[bs]+4),(int)(e1.y[bs]+200),
						  (int)(e1.x[bs]-4),(int)(e1.y[bs]+200),
						  PjSys::Scr::BurstImg,TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			SetDrawMode(0);
			if(e1.BigExp(Enum[8],(int)e1.x[Enum[8]],490)==1){e1.bephase++;}
			e1.bephase+=3;
			My::Invincible=180;
		}else if(e1.bephase>=183){ //早回し
			if(phase<=8000 && phase%15==0){
				int i=e1.create(HpSmall0,-64,-64,0x27,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
				e1.mphase[i]=((i*31337)%41)*10+120;
			}
		}
	}
	e1.ShowExp();

	return 0;
}
//-------------------------------------------------
//Stage2本体終了
//------------------------------------------------

//=================================================
//Stage2 Warning
//=================================================
int StageManager::stg22(){
	return warn();
}

//=================================================
//Stage2 ボス戦
//=================================================
int StageManager::stg23(){
	int BossHP=16000+(7-PjSys::HardConst)*2000;
	int HakkyoHP[3];
	HakkyoHP[0]=12000+(7-PjSys::HardConst)*1000;
	HakkyoHP[1]=8000+(7-PjSys::HardConst)*500;
	HakkyoHP[2]=4000+(7-PjSys::HardConst)*200;
	/*
	if(PjSys::cheat::Go2Boss==true){
		BossHP/=10;
		HakkyoHP[0]/=10;
		HakkyoHP[1]/=10;
		HakkyoHP[2]/=10;
	}
	*/
	int BitHP=ENEMY_INV;

	stgmove();
	if(My::GOver==true || My::Pause==true){return 0;}

	if(phase==0){
		e1.setcap(10);
		e1.init();
		ChangeVolumeSoundMem(Setting.General.BGMVolume,PjSys::bossbgm);
		PlaySoundMem( PjSys::bossbgm , DX_PLAYTYPE_LOOP, FALSE) ;
		//My::Move=false;
		cloud.alpha=0;
		int j=0;while(j++<8){e1.BExpPhase[j]=0;}
		//bg2.changespeed(10);
		e1.BFrm=0;
		PjSys::Scr::AddLog("IDENTIFIED AS",0,GetColor(255,255,255));
	}else if(phase==10){
		PjSys::Scr::AddLog("\"AIRBORNE EARLY WARNING",0,GetColor(255,255,255));
	}else if(phase==20){
		PjSys::Scr::AddLog("<< EDERWEISS >>\".",0,GetColor(255,255,127));
	}else if(phase<=80){ //20<phase<=80 敵機動表示
		int local=phase-20;
		for(int j=0;j<=60;j++){
			int p1=j*3; //フェーズ1
			int p2=(j+1)*3;
			if(j==60){
				p2=p1;
			}else if(j==local){
				SetDrawBlendMode(DX_BLENDMODE_ADD,255);
			}else if(abs(local-j)<15){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(mycos(abs(local-j)*6*RAD)*255));
			}else{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			}
			for(int i=0;i<6;i++){
				double rad=i*60*RAD;
				int CenterX=320;
				int CenterY=120;
				int CircleMin=96;
				/*最初ベジェ曲線で*/
				//始点
				int sx=(int)(CenterX-mycos(rad)*200);
				int sy=-64;
				//制御点
				int cx;
				if(PjSys::HardConst<4){cx=(int)(CenterX+mycos(rad)*400);}else{cx=(int)(CenterX+mycos(rad)*200);}
				int cy=760;
				//終点
				int ex=(int)(CenterX+mycos(rad)*CircleMin);
				int ey=(int)(CenterY+mysin(rad)*CircleMin);
				double x1, y1, x2, y2;
				Get2DBezier(sx,sy,ex,ey,cx,cy,180,p1,&x1,&y1);
				Get2DBezier(sx,sy,ex,ey,cx,cy,180,p2,&x2,&y2);
				DrawLine((int)x1,(int)y1,(int)x2,(int)y2,GetColor(128,255,128),2);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}else if(phase==90){
		My::Rot=0;
		My::Exp=MY_MODEL_EXP;
		My::Move=true;
		e1.BPPhase=0;
		e1.BFrm=120*60;
		//本体
		Enum[0]=e1.create(BossHP,-64,-64,0x2c,BossImg[0],0.02f,1,0x100,100,Enm::BLaser,96,96,false);
		e1.BPRotate[Enum[0]]=1;

		//ビット1
		Enum[1] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::RLaser, 32, 32, true);
		e1.mphase[Enum[1]]=0;
		e1.BPRotate[Enum[1]]=1;

		//ビット2
		Enum[2] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::GLaser, 32, 32, true);
		e1.mphase[Enum[2]]=60;
		e1.BPRotate[Enum[2]]=1;

		//ビット3
		Enum[3] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::BLaser, 32, 32, true);
		e1.mphase[Enum[3]]=120;
		e1.BPRotate[Enum[3]]=1;

		//ビット4
		Enum[4] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::RLaser, 32, 32, true);
		e1.mphase[Enum[4]]=180;
		e1.BPRotate[Enum[4]]=1;

		//ビット5
		Enum[5] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::GLaser, 32, 32, true);
		e1.mphase[Enum[5]]=240;
		e1.BPRotate[Enum[5]]=1;

		//ビット6
		Enum[6] = e1.create(BitHP, -64, -64, 0x2d, BossImg[1], 0.01f, 1, 0x100, 300, Enm::BLaser, 32, 32, true);
		e1.mphase[Enum[6]]=300;
		e1.BPRotate[Enum[6]]=1;

		e1.MogiMogiPhase=0;
		//PjSys::Scr::AddLog("",0,GetColor(255,192,192));

		//PjSys::CameraHRota=DX_PI_F/180.0f * (sin((float)phase/50)*10); //背景のカメラワーク
	}else if(phase==270){
		for(int i=0;i<7;i++){
			e1.BulletEnd[Enum[i]]=true; //ボム対策
		}
	}

	if(My::BombFrame==BMBFRAME-1||My::IsHit){
		for(int i=0;i<7;i++){
			e1.BulletEnd[Enum[i]]=true; //ボム対策
		}
	}

		if(phase>=90&&e1.hp[Enum[0]]<HakkyoHP[0]){ //発狂分岐
		if(e1.MogiMogiPhase==0){ //発狂時の動作
			for(int i=0;i<7;i++){
				e1.BPRotate[Enum[i]]=1;
				e1.BulletEnd[Enum[i]]=true; //弾を消す
				e1.eb1[Enum[i]].init();
			}
			e1.BPPhase=1;
			e1.MogiMogiPhase=1;
			//爆発設定
			int i=0;
			math m;
			while(i++<8){
				e1.RegistExp((int)(e1.x[Enum[0]]-64+m.irand(0,128)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.5,m.irand(0,32));
			}
		}
	}

	//===========発狂分岐==============
	if(phase>=90&&e1.hp[Enum[0]]<HakkyoHP[1]){
		if(e1.MogiMogiPhase==1){ //発狂時の動作
			for(int i=0;i<7;i++){
				e1.BPRotate[Enum[i]]=1;
				e1.BulletEnd[Enum[i]]=true; //弾を消す
				e1.eb1[Enum[i]].init();
			}
			//e1.img[Enum[0]]=BossImg[0];
			e1.BPPhase=2;
			e1.MogiMogiPhase=2;
			//爆発設定
			int i=0;
			math m;
			while(i++<8){
				e1.RegistExp((int)(e1.x[Enum[0]]-64+m.irand(0,128)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.5,m.irand(0,32));
			}
		}
	}
	if(phase>=90&&e1.hp[Enum[0]]<HakkyoHP[2]){ //発狂分岐
		if(e1.MogiMogiPhase==2){ //発狂時の動作
			for(int i=0;i<7;i++){
				e1.BPRotate[Enum[i]]=1;
				e1.BulletEnd[Enum[i]]=true; //弾を消す
				e1.eb1[Enum[i]].init();
			}
			e1.BPPhase=3;
			e1.MogiMogiPhase=3;
			//爆発設定
			int i=0;
			math m;
			while(i++<8){
				e1.RegistExp((int)(e1.x[Enum[0]]-64+m.irand(0,128)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.5,m.irand(0,32));
			}
		}
	}

	//================弾幕切り替え==================
	//メイン
	if(e1.BulletEnd[Enum[0]]==true && e1.hp[Enum[0]]>0){
		int Blt = (10-PjSys::Hard)*100;
		e1.eb1[Enum[0]].init();
		if(e1.BPPhase==0){
			switch(e1.BPRotate[Enum[0]]){
				case 1:
					e1.bltchange(Enum[0],Enm::BLaser,Blt*2,0x20c); //くねくね2
					e1.BPRotate[Enum[0]]++;
					break;
				case 2:
					e1.bltchange(Enum[0],Enm::BLaser,Blt,0x203); //サイン波同心円
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}else if(e1.BPPhase==1){
			switch(e1.BPRotate[0]){
				case 1:
					e1.bltchange(Enum[0],Enm::BLaser,Blt,0x105); //旋回砲塔
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}else if(e1.BPPhase==2){
			switch(e1.BPRotate[Enum[0]]){
				case 1:
					e1.bltchange(Enum[0],Enm::BBullet,Blt*3,0x205); //x軸反跳
					e1.BPRotate[Enum[0]]++;
					break;
				case 2:
					e1.bltchange(Enum[0],Enm::BBullet,Blt*2,0x204); //円形狙撃++
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}else if(e1.BPPhase==3){
			switch(e1.BPRotate[Enum[0]]){
				case 1:
					e1.bltchange(Enum[0],Enm::BLaser,Blt,0x108); //旋回砲塔
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}
	}

	//ビット
	for(int i=1;i<7;i++){
		if(e1.BulletEnd[Enum[i]]==true){
			int Blt = (15-PjSys::Hard)*20;
			e1.eb1[Enum[i]].init();
			if(e1.BPPhase==0){
				switch(e1.BPRotate[Enum[i]]){
					case 1:
						Enm::Refuge::AnyAvaliable=false;
						e1.bltchange(Enum[i],Enm::RBullet,Blt,/*(PjSys::Hard<3)?0x105:*/0x100); //何もしない
						e1.BPRotate[Enum[i]]=1;
						break;
				}
			}else if(e1.BPPhase==1){
				switch(e1.BPRotate[Enum[i]]){
					case 1:
						Enm::Refuge::AnyAvaliable=false;
						e1.bltchange(Enum[i],Enm::RLaser,Blt*2,0x20d);//下へ斑鳩C3中ボス風
						e1.BPRotate[Enum[i]]++;
						break;
					case 2:
						e1.bltchange(Enum[i],Enm::RLaser,Blt,0x20f); //同心円
						e1.BPRotate[Enum[i]]=1;
						break;
				}
			}else if(e1.BPPhase==2){
				switch(e1.BPRotate[Enum[i]]){
					case 1:
						e1.bltchange(Enum[i],Enm::RLaser,Blt,/*(PjSys::Hard<3)?0x106:*/0x100);//何もしない
						e1.BPRotate[Enum[i]]=1;
						break;
				}
			}else if(e1.BPPhase==3){
				switch(e1.BPRotate[Enum[i]]){
					case 1:
						e1.bltchange(Enum[i],Enm::RLaser,Blt,0x20e); //しばらく残る→円形に広がる
						e1.BPRotate[Enum[i]]=1;
						break;
				}
			}
		}
		//無敵地帯設定
		/*
		if(Enm::Refuge::AnyAvaliable==true){
			Enm::Refuge::flg[i]=true;
			Enm::Refuge::x[i]=(int)(e1.x[Enum[i]]);
			Enm::Refuge::y[i]=(int)(e1.y[Enum[i]]);
			Enm::Refuge::width[i]=32;
			Enm::Refuge::height[i]=32;
		}
		*/
	}

	//===================ボスが死んだら=============================
	if(phase>=90&&e1.hp[Enum[0]]<=0){
		//本来は発狂段階フェーズだが、死んだときのフレーム計算にも使い回す
		if(e1.MogiMogiPhase<4||e1.MogiMogiPhase>=180){
			e1.MogiMogiPhase++;
		}else{
			if(phase%2==0){e1.MogiMogiPhase++;}
		}

		if(e1.MogiMogiPhase==4){
			rphase=0;
			BossRemainSec=(int)((e1.BFrm-e1.BFrm%60)/60);

			My::Move=false;
			math m;
			for(int i=0;i<7;i++){
				e1.RegistExp((int)(e1.x[Enum[0]]-128+m.irand(0,256)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.0,m.irand(0,32));
				e1.eb1[Enum[i]].init();
				e1.bltchange(Enum[i],Enm::BLaser,10,0x100);
				e1.IsHitPlayer[Enum[i]]=false;
				if(i>0){
					e1.hp[Enum[i]]=256;
					e1.score[Enum[i]]=256;
				}
			}
			//e1.MogiMogiPhase++;
		}
		math m;
		for(int i=1;i<7;i++){
			if(e1.MogiMogiPhase==110+i*2){
				e1.hp[Enum[i]]=0;
			}
		}
		if(e1.MogiMogiPhase==32){
			for(int i=0;i<EXPLODE_MAX;i++){e1.BExpPhase[i]=0;}
			e1.RegistExp((int)(e1.x[Enum[0]]-128+m.irand(0,256)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.5);
		}else if(e1.MogiMogiPhase==64){
			e1.RegistExp((int)(e1.x[Enum[0]]-96+m.irand(0,192)),(int)(e1.y[Enum[0]]-48+m.irand(0,96)),1.25);
		}else if(e1.MogiMogiPhase==96){
			e1.RegistExp((int)(e1.x[Enum[0]]-64+m.irand(0,128)),(int)(e1.y[Enum[0]]-32+m.irand(0,64)));
		}else if(e1.MogiMogiPhase==112){
			e1.RegistExp((int)(e1.x[Enum[0]]-32+m.irand(0,64)),(int)(e1.y[Enum[0]]-16+m.irand(0,32)),0.75);
		}else if(e1.MogiMogiPhase==120){
			PjSys::Scr::SetBurst((int)e1.x[Enum[0]],(int)e1.y[Enum[0]],12,40,255,255,255,true,40);
		}else if(e1.MogiMogiPhase==128){
			//e1.RegistExp((int)(e1.x[Enum[0]]-16+m.irand(0,32)),(int)(e1.y[Enum[0]]-8+m.irand(0,16)),0.5);
		}
		if(e1.MogiMogiPhase>=120 && e1.MogiMogiPhase<=180){
			PjSys::Scr::BurstX=(int)e1.x[Enum[0]];
			PjSys::Scr::BurstY=(int)e1.y[Enum[0]];
		}

		if(e1.MogiMogiPhase==180){
			//Blur::set((int)(e1.x[Enum[0]]),(int)(e1.y[Enum[0]]),140,5,0,0,0.001);
			//e1.bephase=0;

			int i=0;
			//math m;
			//while(i++<8){
			//	e1.RegistExp((int)(e1.x[Enum[0]]-128+m.irand(0,256)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.0,35+m.irand(32,64));
			//}
			e1.bephase=0;
			PlaySoundMem(e1.SndBossExp ,DX_PLAYTYPE_BACK ,true ) ;
			PjSys::Scr::SetShake(180,-40,40);

			e1.BExpY[1]=(int)e1.y[Enum[0]];
			e1.BExpPhase[1]=0;
		}else if(e1.MogiMogiPhase>=560){
			bg2.changespeed(0);
			e1.vx[Enum[0]]=0;
			e1.vy[Enum[0]]=0;
			gPlayer.setXY(320,-120);
			//PjSys::CameraHRota=0;
			My::Move=true;
			My::IsBurner=false;
			PjSys::Scr::BGColor=GetColorF(1.0f,1.0f,1.0f,1.0f);
				return 1;
		}else if(e1.MogiMogiPhase>=500){ //ばしゅーん
					My::IsBurner=false;
			int lphase=e1.MogiMogiPhase-500;
			if(lphase==0){
				PjSys::Scr::SetBurst((int)My::x,(int)My::y,30,40,255,255,255,false,40);
				PjSys::Scr::SetShake(10,-10,20);
				//Blur::set();
				//PlaySoundMem(gPlayer.SndBorn,DX_PLAYTYPE_BACK);
			}
			gPlayer.addX((320-My::x)/(60-lphase));
			gPlayer.addY((240-My::y)/(60-lphase));
			My::Exp/=1.1f;
			My::x=gPlayer.getX();
			My::y=gPlayer.getY();
		}else if(e1.MogiMogiPhase>=320){//ループ
			//My::Rot=(e1.MogiMogiPhase-320)*2.0f;
			My::IsBurner=false;
			int lphase=e1.MogiMogiPhase-320;
			//My::Rot=lphase*1.33f;
			My::Exp+=mycos(lphase*DX_PI_F/180.0f)*0.1f;
			gPlayer.addY(mycos(lphase*DX_PI_F/180.0f)*-2);
			My::fLoop=lphase*-1.5f*DX_PI_F/180.0f;
			My::x=gPlayer.getX();
			My::y=gPlayer.getY();
			//bg2.changespeed(0);
			PjSys::CameraVRota=(180+lphase)*DX_PI_F/-360.0f;
			//PjSys::CameraHRota=0;

			//PjSys::Scr::BGColor=GetColorF(1.0f,e1.MogiMogiPhase/480.0f,e1.MogiMogiPhase/480.0f,0.5f);
			e1.BigExp(Enum[0],(int)e1.x[Enum[0]],(int)e1.y[Enum[0]]);
			return 0;
		}else if(e1.MogiMogiPhase>=180){//敵爆発
			//bg2.changespeed(0);
			//PjSys::CameraHRota=0;
			//e1.x[Enum[0]]=e1.BExpX[1]+PjSys::Scr::MoveX;
			//e1.y[Enum[0]]=e1.BExpY[1]+PjSys::Scr::MoveY;
			e1.vx[Enum[0]]=0;
			e1.vy[Enum[0]]=0;
			MV1SetWireFrameDrawFlag(BossImg[0],true);
			MV1SetOpacityRate( BossImg[0], 0.0f) ;
			MV1SetDifColorScale( BossImg[0], GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
			MV1SetScale( BossImg[0], VGet((0.04f-0.012f),(0.04f-0.012f)*(e1.MogiMogiPhase-180)/4,(0.04f-0.012f))) ;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(300-e1.MogiMogiPhase)*2);
			DrawBox(0,0,640,480,GetColor(255,255,255),true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

			e1.BigExp(Enum[0],(int)e1.x[Enum[0]],(int)e1.y[Enum[0]]);
		}else{
					//math m;
					//自機の挙動
						My::IsBurner=false;
						My::Rot=e1.MogiMogiPhase*1.33f;
						gPlayer.addX((400-My::x)/180);
						gPlayer.addY((180-My::y)/180);
						My::Exp+=0.004f;
					My::x=gPlayer.getX();
					My::y=gPlayer.getY();

					PjSys::Scr::BGColor=GetColorF(1.0f,1.0f,1.0f,1.0f);
					//bg2.changespeed((int)(cos(m.ToRadian((double)e1.MogiMogiPhase/2))*10));

					//e1.x[Enum[0]]+=(320-e1.x[Enum[0]])/(180-e1.MogiMogiPhase);
					e1.y[Enum[0]]+=0.1;

					MV1SetOpacityRate( BossImg[0], 1.0f) ;
					e1.BExpX[1]=(int)e1.x[Enum[0]];
					e1.BExpY[1]=(int)e1.y[Enum[0]];
			//MV1SetScale( BossImg[0], VGet(0.02f-e1.MogiMogiPhase*0.00009f,0.02f-e1.MogiMogiPhase*0.00009f,0.02f-e1.MogiMogiPhase*0.00009f)) ;
			MV1SetScale( BossImg[0], VGet(0.02f,0.02f,0.02f)) ;
			for(int i=1;i<7;i++){
				e1.z[Enum[i]]=0.6f+e1.MogiMogiPhase*0.001f;
				//e1.expansion[Enum[i]]=0.02f-e1.MogiMogiPhase*0.00009f;
			}
			MV1SetDifColorScale( BossImg[0], GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) ) ;
			MV1SetRotationXYZ(BossImg[0], VGet(0.0f,(float)e1.MogiMogiPhase * DX_PI_F / -180.0f  , 0.0f )) ;
			MV1SetWireFrameDrawFlag(BossImg[0],false);
		}
			DxLib::VECTOR pLoc={(float)e1.x[Enum[0]],(float)e1.y[Enum[0]],0.6f+e1.MogiMogiPhase*0.001f};
			MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( pLoc ) ) ;

			MV1DrawModel( BossImg[0] ) ;
	}

	e1.ShowExp();

	//秒数カウント
	if(e1.MogiMogiPhase<4){
		if(phase>=90 && --e1.BFrm<=0){
			e1.type[Enum[0]]=0x1b;
			e1.eb1[Enum[0]].init();
			e1.bltchange(Enum[0],Enm::RBullet,3,0x100); //何もしない

			for(int i=1;i<7;i++){
				e1.type[Enum[i]]=0x2b;
				e1.eb1[Enum[i]].init();
				e1.bltchange(Enum[0],Enm::RBullet,3,0x100); //何もしない
			}
			e1.hp[Enum[0]]=BossHP;
			My::NowInv=true;
			My::Move=false;
			if(e1.BFrm<=-60){
				My::Move=true;
				My::IsBurner=false;
				My::NowInv=false;
				BossRemainSec=0;
				return 1;
			}
		}else if(phase>=90 && e1.hp[Enum[0]]>0){
			Enm::drawHP(BossHP,e1.hp[Enum[0]],(int)((e1.BFrm-e1.BFrm%60)/60)); //HP描画
		}
	}
	return 0;
}
//-------------------------------------------------
//Stage2ボス戦終了
//------------------------------------------------