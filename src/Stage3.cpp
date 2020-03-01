#include "Common.h"
/*#############################################################

					  Stage: 03 êiçsãLèq

##############################################################*/

//-------------------------------------------------
//Stage3ÉçÅ[Éh
//------------------------------------------------
int StageManager::LoadSt3(int phase){
	LoadElements=31;
	//int dbg;
	switch(phase){
		case 0:
			My::NowStage=2;
			LoadImg=LoadGraph("img\\loadbg3.png");
			ImgLoadStr=LoadGraph("img\\load.bmp");
			return 0;
		case 1:
			UnloadSt2();

			return 0;
		case 2:
			PjSys::Scr::BGModel=MV1LoadModel("img\\dome_bluesky.mv1" );
			return 0;
		case 3:
			bgimg[0]=MV1LoadModel("img\\river.mv1" );
			return 0;
		case 4:
			cloud.imgset(LoadGraph("img\\air.bmp"),LoadGraph("img\\air.bmp"),24);
			return 0;
		case 5:
			stgimg=LoadGraph("img\\stg2.bmp");
			return 0;
		case 6:
			bgimg[1]=MV1LoadModel("img\\river.mv1" );
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
			return 0;
		case 15:
			return 0;
		case 16:
			return 0;
		case 17:
			BigEnmImg[0]=MV1LoadModel("img\\big1.mv1") ;
			return 0;
		case 18:
			BigEnmImg[1]=MV1LoadModel("img\\stg3_midboss.mv1") ;
			return 0;
		case 19:
			BigEnmImg[2]=MV1LoadModel("img\\stg3_midboss_bit.mv1") ;
			return 0;
		case 20:
			//BigEnmImg[3]=MV1LoadModel("img\\stg2_middleboss_1.mv1") ;
			return 0;
		case 21:
			BossImg[0]=MV1LoadModel("img\\stg3_midboss.mv1") ;
			return 0;
		case 22:
			SetCreateSoundDataType( Setting.General.LoadMode	) ;
			return 0;
		case 23:
			PjSys::bgm=LoadSoundMem("snd\\stg3.mp3");
			return 0;
		case 24:
			PjSys::bossbgm=LoadSoundMem("snd\\boss3.mp3");
			return 0;
		case 25:
			ChangeVolumeSoundMem( Setting.General.BGMVolume ,PjSys::bgm ) ;
			return 0;
		case 26:
			SetCreateSoundDataType( DX_SOUNDDATATYPE_MEMNOPRESS	) ;
			return 0;
		case 27:
			//e1.sndSE[0]=LoadSoundMem("snd\\missile.wav");
			//ChangeVolumeSoundMem(Setting.General.SEVolume , e1.sndSE[0] );
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
		//ÉÅÉÇ:ÉçÅ[ÉhÉtÉ@ÉCÉãÇí«â¡ÇµÇΩç€ÇÕLoadElementsãyÇ—UnloatSt2ÇèëÇ´ä∑Ç¶ÇÈÇÃÇñYÇÍÇ»Ç¢éñÅI
	}
	return -1;
}
void StageManager::UnloadSt3(){
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
			//MV1DeleteModel(BigEnmImg[3]) ;
			MV1DeleteModel(BossImg[0]) ;
			DeleteSoundMem(PjSys::bgm);
			DeleteSoundMem(PjSys::bossbgm);
			DeleteSoundMem(e1.sndSE[0]);
			for(int i=0;i<16;i++){DeleteGraph(Enm::imgBurn[i]);}
			return;
}


int StageManager::stg30(){
	if(phase>=0 &&LoadSt3(phase)==1){
		return 1;
	}
	Loading(LoadImg);
	return 0;
}
//#######################################################
//Stage3ñ{ëÃ
//########################################################

int StageManager::stg31(){
	static const int HpSmall0=20;
	static const int HpSmall1=20;
	static const int HpSmall2=20;
	static int HpSmall3=(PjSys::HardConst<3)?256:128;

	static const int HpSmall4=(8-PjSys::HardConst)*50;
	static const int HpBig0=300+(8-PjSys::HardConst)*50;

	//ägëÂó¶
	static const float ExpSmall[8]={0.009f,0.007f,0.012f,0.011f,0.004f,0.01f};
	static const float ExpBig[8]={0.02f,0.025f,0.015f,0.035f,1.0f,1.0f,1.0f,100.0f};
	int i=0;
	int bp;
	//ÉtÉFÅ[ÉYÇ…ÇÊÇÈèÍçáï™ÇØ
	switch(phase){
		case 0:
			//pushright=0;
			//My::Score=0;
			//PjSys::BombExtendPhase=1;
			//PjSys::ExtendPhase=1;
			//My::SubEnergy=0;
			//My::Bomb=My::DefaultBomb;
			//My::Left=My::DefaultLeft;
			Enm::BossPhase=7200;
			SetCameraPositionAndAngle( VGet( 0.0f+PjSys::Scr::MoveX, -1000.0f, 0.0f+PjSys::Scr::MoveY ), DX_PI_F/-2, 0, 0 ) ;
			PjSys::CameraPos = VGet( 0.0f+PjSys::Scr::MoveX, -400.0f, 0.0f+PjSys::Scr::MoveY );
			My::BombFrame=0;
			My::Rot=0;
			My::fLoop=0.0f;
			PjSys::Scr::AddLog("DIANA SYSTEM READY.",My::NowStage,GetColor(127,255,127));
			if(PjSys::cheat::Go2Boss){phase=Enm::BossPhase-1;}else{PlaySoundMem(PjSys::bgm ,DX_PLAYTYPE_LOOP ,FALSE) ;}
			bp=e1.create(-127,0,240,0x1d,BigEnmImg[7],ExpBig[7],2,0x100,30,Enm::RLaser,0,0,true,false,false);
			e1.mphase[bp]=4;
			break;

		//ÉXÉeÅ[ÉWï\é¶(10frm-430frm)
		//------------------------------------------------
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 440:
			e1.create(HpSmall0,140,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 460:
			e1.create(HpSmall0,180,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 480:
			e1.create(HpSmall0,220,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 500:
			e1.create(HpSmall0,260,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 520:
			e1.create(HpSmall0,300,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 540:
			e1.create(HpSmall0,340,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 560:
			e1.create(HpSmall0,380,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 580:
			e1.create(HpSmall0,420,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			break;

		//âEè„Ç©ÇÁíÜå^1ëÃ
		case 620:
			e1.create(HpBig0,440,-40,0x13,BigEnmImg[0],ExpBig[0],0,0x300,500,Enm::RBullet,48,48,true);
			break;
	//----
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 740:
			e1.create(HpSmall0,500,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 760:
			e1.create(HpSmall0,460,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 780:
			e1.create(HpSmall0,420,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 800:
			e1.create(HpSmall0,380,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 820:
			e1.create(HpSmall0,340,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 840:
			e1.create(HpSmall0,300,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 880:
			e1.create(HpSmall0,260,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 900:
			e1.create(HpSmall0,220,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			break;
    	//ç∂è„Ç©ÇÁíÜå^1ëÃ
		case 960:
			e1.create(HpBig0,200,-40,0x13,BigEnmImg[0],ExpBig[0],0,0x300,500,Enm::GBullet,48,48,true);
			break;
	//---
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ+âEè„Ç©ÇÁÉTÉCÉìîgéGãõ8ëÃ
		case 1100:
			e1.create(HpSmall0,140,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);
			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1120:
			e1.create(HpSmall0,180,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x15, SmallEnmImg[1], ExpSmall[0], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1140:
			e1.create(HpSmall0,220,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1160:
			e1.create(HpSmall0,260,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x15, SmallEnmImg[1], ExpSmall[0], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1180:
			e1.create(HpSmall0,300,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1200:
			e1.create(HpSmall0,340,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x15, SmallEnmImg[1], ExpSmall[0], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1220:
			e1.create(HpSmall0,380,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ç∂ë§è„Ç©ÇÁéGãõ8ëÃ
		case 1240:
			e1.create(HpSmall0,420,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 520, -60, 0x15, SmallEnmImg[1], ExpSmall[0], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1280:
			e1.create(HpSmall0,500,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1300:
			e1.create(HpSmall0,460,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x15, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1320:
			e1.create(HpSmall0,420,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1340:
			e1.create(HpSmall0,380,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x15, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1360:
			e1.create(HpSmall0,340,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1380:
			e1.create(HpSmall0,300,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x15, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1400:
			e1.create(HpSmall0,260,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x14, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//âEë§è„Ç©ÇÁéGãõ8ëÃ
		case 1420:
			e1.create(HpSmall0,220,-40,0x13,SmallEnmImg[0],ExpSmall[0],0,0x10f,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1, 120, -60, 0x15, SmallEnmImg[1], ExpSmall[1], 0, 0x101, 50, Enm::RLaser, 24, 24, true);

			break;
		//ê^ÇÒíÜÇ©ÇÁíÜå^1ëÃ
		case 1480:
			e1.create(HpBig0,320,-40,0x13,BigEnmImg[0],ExpBig[0],0,0x300,500,Enm::BBullet,48,48,true);
			break;
		//ç∂âEÇ©ÇÁÉUÉRìG
		case 1600:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x10f,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x10f,100,Enm::RBullet,24,24,true);
			break;
		case 1660:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x10f,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x10f,102,Enm::BBullet,24,24,true);
			break;

		case 1720:
			e1.create(HpSmall1,616,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x10f,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x10f,100,Enm::GBullet,24,24,true);
			break;
		case 1780:
			e1.create(HpSmall1,32,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x10f,102,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x10f,102,Enm::RBullet,24,24,true);
			break;
		//âEè„Ç©ÇÁíÜå^1ëÃ
		case 1900:
			e1.create(HpBig0,440,-40,0x12,BigEnmImg[0],ExpBig[0],0,0x1a6,500,Enm::RLaser,48,48,true,true,true,true,3);
			break;

		//ç∂è„Ç©ÇÁíÜå^1ëÃ
		case 2020:
			e1.create(HpBig0,200,-40,0x12,BigEnmImg[0],ExpBig[0],0,0x1a6,500,Enm::BLaser,48,48,true,true,true,true,5);
			break;
	//=================================
		//íÜÉ{ÉX
		case 2500:
			e1.bephase = 0;
			Enum[0] = e1.create(10000-PjSys::HardConst * 500,320,-150,0x3a,BigEnmImg[1],ExpBig[1],5,0x30d,500,Enm::GBullet,64,64,false);
			e1.BPRotate[Enum[0]]=1;

			Enum[1] = e1.create(3000,320-96,-20,0x3a,BigEnmImg[2],ExpBig[2],5,0x30e,180,Enm::RBullet,48,48,false);
			e1.BPRotate[Enum[1]]=1;

			Enum [2] = e1.create(3000,320+96,-20,0x3a,BigEnmImg[2],ExpBig[2],5,0x30f,180,Enm::RBullet,48,48,false);
			e1.BPRotate[Enum[2]]=1;

			break;

			//è¨å^ã@ÇÃç∂âEåå›ÉâÉbÉVÉÖ*5
		case 6100:
			e1.create(HpSmall1, 32, 0, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x104, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 48, 32, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x104, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 64, 64, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x104, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 80, 96, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x104, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 96, 128, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x104, 100, Enm::RBullet, 24, 24, true);
			break;
		case 6200:
			e1.create(HpSmall1, 616, 0, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x105, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 600, 32, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x105, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 584, 64, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x105, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 568, 96, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x105, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 552, 128, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x105, 100, Enm::GBullet, 24, 24, true);
			break;
		case 6350:
			e1.create(HpBig0, 320, 0, 0x12, BigEnmImg[0], ExpBig[0], 0, 0x108, 500, Enm::BLaser, 48, 48, true);
			break;

		case 6400:
			e1.create(HpSmall1, 32, 0, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 48, 32, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 64, 64, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 80, 96, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 96, 128, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			break;
		case 6500:
			e1.create(HpSmall1, 616, 0, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 600, 32, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 584, 64, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 568, 96, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 552, 128, 0x11, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::GBullet, 24, 24, true);
			break;
		case 6600:
			e1.create(HpSmall1, 32, 0, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 48, 32, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::RBullet, 24, 24, true);
			e1.create(HpSmall1, 64, 64, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::GBullet, 24, 24, true);
			e1.create(HpSmall1, 80, 96, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::BBullet, 24, 24, true);
			e1.create(HpSmall1, 96, 128, 0x10, SmallEnmImg[1], ExpSmall[1], 1, 0x101, 100, Enm::RBullet, 24, 24, true);
			break;

			//íÜå^ã@*1ÇÃê˘âÒñCìÉ
		case 6700:
			e1.create(HpBig0, 290, 0, 0x12, BigEnmImg[0], ExpBig[0], 0, 0x30c, 500, Enm::RLaser, 48, 48, true, true, true, true, 4);
			break;
		case 6800:
			e1.create(HpBig0, 350, 0, 0x12, BigEnmImg[0], ExpBig[0], 0, 0x30c, 500, Enm::GLaser, 48, 48, true, true, true, true, 5);
			break;



	}

	if(phase==Enm::BossPhase){
		return 1;
	}

	stgmove();
	if(My::GOver==true || My::Pause==true){return 0;}

	if(phase>=0 && phase<255-32){
		cloud.Visible=true;
		cloud.alpha=32;
		//cloud.sspeed=24;
	}else{
		cloud.alpha = 32;
	}
	if(phase>=0 && phase<200){
		PjSys::CameraPos = VGet( 0.0f+PjSys::Scr::MoveX, -600.0f + phase, 0.0f+PjSys::Scr::MoveY );
	}
	if (phase >= 10 && phase < 430){ //ÉXÉeÅ[ÉWï\é¶
		ShowStageTitle(phase - 10);
	}
	else if (phase >= 1900 && phase <= 2000){


	}else if(phase > 2500 && phase <= 2500 + 60 * 60){ //íÜÉ{ÉX
		if(e1.bephase==0 && My::BombFrame==BMBFRAME-1||My::IsHit || phase == 2500 + 60 *25){
			for(int i=0;i<3;i++){
				e1.BulletEnd[Enum[i]]=true; //É{ÉÄëŒçÙ
				//if(phase == 2500 + 60 * 25){e1.eb1[Enum[i]].init();}
			}
		}

		if (e1.bephase == 0 &&  e1.BulletEnd[Enum[0]] == true && e1.hp[Enum[0]]>0 && phase < 2500 + 60 * 55){ //íeñãêÿÇËë÷Ç¶
			e1.eb1[Enum[0]].init();
			switch(e1.BPRotate[Enum[0]]){
				case 1:
					e1.bltchange(Enum[0],Enm::GLaser,500,0x30c); //ë¨ìxç∑5way
					e1.BPRotate[Enum[0]]++;
					break;
				case 2:
					e1.bltchange(Enum[0],Enm::GBullet,500,0x30d); //éûä‘ç∑5way
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}

		//â°ÇÃÉpÅ[Éc
		for(int i=1;i<3;i++){
			if (e1.bephase == 0 && e1.BulletEnd[Enum[i]] == true && e1.hp[Enum[i]]>0 && phase < 2500 + 60 * 55){ //íeñãêÿÇËë÷Ç¶
				int Blt = (10-PjSys::Hard)*100;
				e1.eb1[Enum[i]].init();
				switch(e1.BPRotate[Enum[i]]){
					case 1:
						e1.bltchange(Enum[i],Enm::RLaser,Blt,0x309+i); //ê˘âÒñCìÉ*4
						e1.BPRotate[Enum[i]]++;
						break;
					case 2:
						e1.bltchange(Enum[i],Enm::RBullet,180,0x30d+i); //óéâ∫ìØêSâ~
						e1.BPRotate[Enum[i]]=1;
						break;
				}
			}
		}

		if(e1.hp[Enum[0]]>0){
			if (e1.bephase == 0){
				Enm::drawHP(10000 - PjSys::HardConst * 500, e1.hp[Enum[0]], (int)(60 - (phase - 2500) / 60)); //HPï`âÊ
			}
		}else{
			if (e1.bephase == 0){
				//éÄÇÒÇæÇÁââèoópÇÃÉ_É~Å[ìGÇê∂ê¨
				int id=e1.create(-127, e1.x[Enum[0]], e1.y[Enum[0]], 0x22, BigEnmImg[1], ExpBig[1], 3, 0x100, 100, Enm::RBullet, 64,64,true);
				e1.mphase[id] = 270;
				e1.bephase++; }
			//ëÅâÒÇµ
			if (phase % 30 == 0){
				int i = e1.create(HpSmall0, -64, -64, 0x27, SmallEnmImg[0], ExpSmall[0], 0, 0x101, 100, Enm::RBullet, 24, 24, true);
				e1.mphase[i] = ((i * 31337) % 41) * 10 + 120;
			}

		}
	}
	e1.ShowExp();

	return 0;
}
//-------------------------------------------------
//Stage3ñ{ëÃèIóπ
//------------------------------------------------

//=================================================
//Stage2 Warning
//=================================================
int StageManager::stg32(){
	return warn();
}

//=================================================
//Stage1 É{ÉXêÌ
//=================================================
int StageManager::stg33(){
	int BossHP = 16000 + (7 - PjSys::HardConst) * 1000;
	int HakkyoHP = 8000 + (7 - PjSys::HardConst) * 500;
	//int BossHP=300+(7-PjSys::Hard)*100;
	//int HakkyoHP=150+(7-PjSys::Hard)*100;

	stgmove();
	if (My::GOver == true || My::Pause == true){ return 0; }

	if (phase == 0){
		e1.setcap(5);
		e1.init();
		//PjSys::NowVolume=Setting.General.BGMVolume;
		ChangeVolumeSoundMem(Setting.General.BGMVolume, PjSys::bossbgm);
		PlaySoundMem(PjSys::bossbgm, DX_PLAYTYPE_LOOP, FALSE);
		My::Move = true;
		int j = 0; while (j++<8){ e1.BExpPhase[j] = 0; }
		//gPlayer.frmLRoll=120;
		//My::fRoop=DX_PI_F/180*45;
		bg2.changespeed(10);
		e1.BFrm = 0;
		PjSys::Scr::AddLog("IDENTIFIED AS\0", 0, GetColor(255, 255, 255));
	}
	else if (phase == 10){
		PjSys::Scr::AddLog("\"INTERCEPTER FIGHTER\0", 0, GetColor(255, 255, 255));
	}
	else if (phase == 20){
		PjSys::Scr::AddLog("<< BLITZSTRAHL >>\".\0", 0, GetColor(255, 255, 127));
	}
	else if (phase < 120){
		DxLib::VECTOR pLoc = { 320.0f, static_cast<float>(phase), (phase*3+40)/1000.f };
		MV1SetPosition(BossImg[0], ConvScreenPosToWorldPos(pLoc));
		MV1SetScale(BossImg[0], VGet(0.01f + 0.01f*(phase / 120.f), 0.01f + 0.01f*(phase / 120.f), 0.01f + 0.01f*(phase / 120.f)));
		MV1DrawModel(BossImg[0]);
	}
	else if (phase == 120){
		My::Rot = 0;
		My::Exp = MY_MODEL_EXP;
		My::Move = true;
		e1.BPPhase = 0;
		e1.BPRotate[0] = 1;
		e1.BPRotate[1] = 1;
		e1.BPRotate[2] = 0;
		e1.BPRotate[3] = 0;
		e1.BFrm = 120 * 60;
		Enum[0] = e1.create(BossHP, 320, 120, 0x3b, BossImg[0], 0.02f, 0, 0x3a0, 1500, Enm::BLaser, 64, 64, false);
		e1.deg[Enum[0]] = 0;
		e1.MogiMogiPhase = 0;
		//PjSys::Scr::AddLog("",0,GetColor(255,192,192));

	}

	if (My::BombFrame == BMBFRAME - 1 || My::IsHit){
		e1.BulletEnd[Enum[0]] = true; //É{ÉÄëŒçÙ
	}

	//íeñãêÿÇËë÷Ç¶
	if (e1.BulletEnd[Enum[0]] == true && e1.hp[Enum[0]]>0){
		int Blt = (10 - PjSys::Hard) * 50;
		e1.eb1[Enum[0]].init();
		if (e1.BPPhase == 0){
			switch (e1.BPRotate[0]){
			case 1:
				//e1.bltchange(Enum[0],Enm::RLaser,Blt,0x10a);e1.BPRotate[0]++;

				e1.bltchange(Enum[0], Enm::GBullet, Blt*4, 0x3a3);
				e1.BPRotate[Enum[0]]++;
				break;
			case 2:
				e1.bltchange(Enum[0], Enm::GLaser, 144*5, 0x3a2);
				e1.BPRotate[Enum[0]] ++;
				break;
			case 3:
				e1.bltchange(Enum[0], Enm::GBullet, 1500, 0x3a0);
				e1.BPRotate[Enum[0]]=1;

			}
		}
		else{
			switch (e1.BPRotate[0]){
			case 1:
				e1.bltchange(Enum[0], Enm::RLaser, 360, 0x3a1);
				e1.BPRotate[Enum[0]]++;
				break;
			case 2:
				e1.bltchange(Enum[0], Enm::GLaser, Blt * 4, 0x3a4);
				e1.BPRotate[Enum[0]]=1;
				break;
			case 3:
				e1.bltchange(Enum[0], Enm::BLaser, Blt, 0x1a6); //‚¥ë|Ç´
				e1.BPRotate[Enum[0]]++;
				break;
			case 4:
				e1.eb1[Enum[0]].tmp[0] = 1;
				e1.eb1[Enum[0]].deg = 0;
				e1.bltchange(Enum[0], Enm::OLaser, Blt * 6, 0x1a8);//Ç≠ÇÀÇ≠ÇÀ
				e1.BPRotate[Enum[0]] = 1;
				break;
			}
		}
	}

	if (phase >= 120 && (e1.hp[Enum[0]]<HakkyoHP || e1.BFrm<60 * 60)){ //î≠ã∂ï™äÚ
		if (e1.MogiMogiPhase == 0){ //î≠ã∂éûÇÃìÆçÏ
			//e1.eb1[Enum[0]].init();
			e1.bltchange(Enum[0], Enm::GLaser, 0, 0x101);
			e1.BPRotate[0] = 1;
			e1.BulletEnd[Enum[0]] = true; //íeÇè¡Ç∑
			e1.mphase[Enum[0]] = 1;
			//e1.img[Enum[0]]=BossImg[0];
			e1.BPPhase = 1;
			e1.MogiMogiPhase = 1;
			//îöî≠ê›íË
			int i = 0;
			math m;
			while (i++<8){
				e1.RegistExp((int)(e1.x[Enum[0]] - 32 + m.irand(0, 64)), (int)(e1.y[Enum[0]]), 1.5, m.irand(0, 32));
			}
		}
		//É{ÉXÇ™éÄÇÒÇæÇÁ
		if (phase >= 600 && e1.hp[Enum[0]] <= 0){
			//ñ{óàÇÕî≠ã∂íiäKÉtÉFÅ[ÉYÇæÇ™ÅAéÄÇÒÇæÇ∆Ç´ÇÃÉtÉåÅ[ÉÄåvéZÇ…Ç‡égÇ¢âÒÇ∑
			if (e1.MogiMogiPhase<2 || e1.MogiMogiPhase >= 180){
				e1.MogiMogiPhase++;
			}
			else{
				if (phase % 2 == 0){ e1.MogiMogiPhase++; }
			}

			if (e1.MogiMogiPhase == 2){
				rphase = 0;
				BossRemainSec = (int)((e1.BFrm - e1.BFrm % 60) / 60);
				int i = 0;
				My::Move = false;
				math m;
				while (i++<8){
					e1.RegistExp((int)(e1.x[Enum[0]] - 128 + m.irand(0, 256)), (int)(e1.y[Enum[0]] - 64 + m.irand(0, 128)), 1.0, m.irand(0, 32));
					e1.eb1[Enum[0]].init();
					e1.bltchange(Enum[0], Enm::BLaser, 10, 0x100);
				}
				//e1.MogiMogiPhase++;
			}
			/*
			if (e1.MogiMogiPhase == 32){
				for (int i = 0; i<EXPLODE_MAX; i++){ e1.BExpPhase[i] = 0; }
				e1.RegistExp((int)(e1.x[Enum[0]] - 128 + m.irand(0, 256)), (int)(e1.y[Enum[0]] - 64 + m.irand(0, 128)), 1.5);
			}
			else if (e1.MogiMogiPhase == 64){
				e1.RegistExp((int)(e1.x[Enum[0]] - 96 + m.irand(0, 192)), (int)(e1.y[Enum[0]] - 48 + m.irand(0, 96)), 1.25);
			}
			else if (e1.MogiMogiPhase == 96){
				e1.RegistExp((int)(e1.x[Enum[0]] - 64 + m.irand(0, 128)), (int)(e1.y[Enum[0]] - 32 + m.irand(0, 64)));
			}
			else if (e1.MogiMogiPhase == 112){
				e1.RegistExp((int)(e1.x[Enum[0]] - 32 + m.irand(0, 64)), (int)(e1.y[Enum[0]] - 16 + m.irand(0, 32)), 0.75);
			}
			else if (e1.MogiMogiPhase == 120){
				PjSys::Scr::SetBurst((int)e1.x[Enum[0]], (int)e1.y[Enum[0]], 12, 40, 255, 255, 255, true, 32);
			}
			else if (e1.MogiMogiPhase == 128){
				e1.RegistExp((int)(e1.x[Enum[0]] - 16 + m.irand(0, 32)), (int)(e1.y[Enum[0]] - 8 + m.irand(0, 16)), 0.5);
			}
			if (e1.MogiMogiPhase >= 120 && e1.MogiMogiPhase <= 180){
				PjSys::Scr::BurstX = (int)e1.x[Enum[0]];
				PjSys::Scr::BurstY = (int)e1.y[Enum[0]];
			}
			*/

			if (e1.MogiMogiPhase == 180){
				if (e1.MogiMogiPhase == 180){
					//PjSys::Scr::SetBurst((int)e1.x[Enum[0]],(int)e1.y[Enum[0]],20,GetColor(255,255,255),40);
				}
				//Blur::set((int)(e1.x[Enum[0]]),(int)(e1.y[Enum[0]]),140,5,0,0,0.001);
				//e1.bephase=0;

				int i = 0;
				math m;
				while (i++<8){
					e1.RegistExp((int)(e1.x[Enum[0]] - 128 + m.irand(0, 256)), (int)(e1.y[Enum[0]] - 64 + m.irand(0, 128)), 1.0, 35 + m.irand(32, 64));
				}
				e1.bephase = 0;
				PlaySoundMem(e1.SndBossExp, DX_PLAYTYPE_BACK, true);
				PjSys::Scr::SetShake(180, -40, 40);

				e1.BExpY[1] = (int)e1.y[Enum[0]];
				e1.BExpPhase[1] = 0;
			}
			else if (e1.MogiMogiPhase >= 480){
				bg2.changespeed(0);
				e1.vx[Enum[0]] = 0;
				e1.vy[Enum[0]] = 0;
				My::Move = true;
				My::IsBurner = false;
				PjSys::Scr::BGColor = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
				return 1;
			}
			else if (e1.MogiMogiPhase >= 320){
				My::Rot = (e1.MogiMogiPhase - 320)*2.0f;
				My::IsBurner = true;
				math m;
				gPlayer.addY(mysin(m.ToRadian((e1.MogiMogiPhase - 180) / 3.33))*-20);
				My::y = gPlayer.getY();
				bg2.changespeed(0);
				//PjSys::CameraHRota=0;

				PjSys::Scr::BGColor = GetColorF(1.0f, e1.MogiMogiPhase / 480.0f, e1.MogiMogiPhase / 480.0f, 0.5f);
				e1.BigExp(Enum[0], (int)e1.x[Enum[0]], (int)e1.y[Enum[0]]);
				return 0;
			}
			else if (e1.MogiMogiPhase >= 180){
				//bg2.changespeed(0);
				//PjSys::CameraHRota=0;
				//e1.x[Enum[0]]=e1.BExpX[1]+PjSys::Scr::MoveX;
				//e1.y[Enum[0]]=e1.BExpY[1]+PjSys::Scr::MoveY;
				e1.vx[Enum[0]] = 0;
				e1.vy[Enum[0]] = 0;
				MV1SetWireFrameDrawFlag(BossImg[0], true);
				MV1SetOpacityRate(BossImg[0], 0.0f);
				MV1SetDifColorScale(BossImg[0], GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
				MV1SetScale(BossImg[0], VGet((0.01f - 0.006f), (0.01f - 0.006f)*(e1.MogiMogiPhase - 180) / 4, (0.01f - 0.006f)));

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (300 - e1.MogiMogiPhase) * 2);
				DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				e1.BigExp(Enum[0], (int)e1.x[Enum[0]], (int)e1.y[Enum[0]]);
			}
			else{
				My::IsBurner = false;
				math m;
				My::Rot = (float)(e1.MogiMogiPhase + 60);
				//gPlayer.addX((float)sin(m.ToRadian(e1.MogiMogiPhase*2)*2));
				gPlayer.addX((220 - My::x) / 180);
				gPlayer.addY((600 - My::y) / 180);
				My::x = gPlayer.getX();
				My::y = gPlayer.getY();
				My::Exp += 0.01f;
				PjSys::Scr::BGColor = GetColorF(1.0f, 1.0f - e1.MogiMogiPhase / 280.0f, 1.0f - e1.MogiMogiPhase / 280.0f, 0.5f);
				//bg2.changespeed((int)(mycos(m.ToRadian((double)e1.MogiMogiPhase / 2)) * 10));
				if (phase % 2 == 0){
					e1.x[Enum[0]] += (int)((320 - e1.x[Enum[0]]) / 90);
					e1.y[Enum[0]]--;
				}
				MV1SetOpacityRate(BossImg[0], 1.0f);
				e1.y[Enum[0]] += mycos(m.ToRadian((double)e1.MogiMogiPhase / 2));
				e1.BExpX[1] = (int)e1.x[Enum[0]];
				e1.BExpY[1] = (int)e1.y[Enum[0]];
				MV1SetScale(BossImg[0], VGet(0.02f - e1.MogiMogiPhase*0.00009f, 0.02f - e1.MogiMogiPhase*0.00009f, 0.02f - e1.MogiMogiPhase*0.00009f));
				MV1SetDifColorScale(BossImg[0], GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
				MV1SetRotationXYZ(BossImg[0], VGet(0.0f, 0.0f, (float)e1.MogiMogiPhase * DX_PI_F / 30.0f));
				MV1SetWireFrameDrawFlag(BossImg[0], false);
			}
			DxLib::VECTOR pLoc = { (float)e1.x[Enum[0]], (float)e1.y[Enum[0]], 0.6f };
			MV1SetPosition(BossImg[0], ConvScreenPosToWorldPos(pLoc));

			MV1DrawModel(BossImg[0]);
		}
	}
	else{
		e1.BPPhase = 0;
	}
	e1.ShowExp();

	//ïbêîÉJÉEÉìÉg
	if (e1.MogiMogiPhase<2){
		if (phase >= 120 && --e1.BFrm <= 0){
			e1.type[Enum[0]] = 0x1b;
			e1.hp[Enum[0]] = BossHP;
			My::NowInv = true;
			My::Move = false;
			if (e1.BFrm <= -60){
				BossRemainSec = 0;
				My::Move = true;
				My::IsBurner = false;
				My::NowInv = false;
				//InitSoundMem() ;
				return 1;
			}
		}
		else if (phase >= 120 && e1.hp[Enum[0]]>0){
			//int sec=(int)((e1.BFrm-e1.BFrm%60)/60);
			Enm::drawHP(BossHP, e1.hp[Enum[0]], (int)((e1.BFrm - e1.BFrm % 60) / 60)); //HPï`âÊ
		}
	}
	//PjSys::NumDraw(PjSys::MainNum,(int)((e1.MogiMogiPhase-120)/10),340,320,32);
	return 0;
}

//-------------------------------------------------
//Stage1É{ÉXêÌèIóπ
//------------------------------------------------
