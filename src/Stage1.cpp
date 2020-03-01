#include "Common.h"
/*#############################################################

					  Stage: 01 進行記述

##############################################################*/

//-------------------------------------------------
//Stage1ロード
//------------------------------------------------
int StageManager::LoadSt1(int phase){
	LoadElements=24;
	switch(phase){
		case 0:
			LoadImg=LoadGraph("img\\loadbg.png");
			ImgLoadStr=LoadGraph("img\\load.bmp");

			My::NowStage=1;
			return 0;
		case 1:
			bgimg[0]=MV1LoadModel("img\\bg_forest.mv1" );
			return 0;
		case 2:
			bgimg[1]=MV1LoadModel("img\\bg_pipe.mv1" );
			return 0;
		case 3:
			bg2.imgset(bgimg[1],8);
			return 0;
		case 4:
			PjSys::Scr::BGModel=MV1LoadModel("img\\dome_sky1.mv1" );
			return 0;
		case 5:
			stgimg=LoadGraph("img\\stg1.bmp");
			return 0;
		case 6:
			e1.setcap(100);
			InitCommon();
			return 0;
		case 7:
			return 0;
		case 8:
			SmallEnmImg[0]=MV1LoadModel("img\\small0.mv1") ;
			return 0;
		case 9:
			SmallEnmImg[1]=MV1LoadModel("img\\small1.mv1") ;
			return 0;
		case 10:
			BigEnmImg[0]=MV1LoadModel("img\\big1.mv1") ;
			return 0;
		case 11:
			BigEnmImg[7]=MV1LoadModel("img\\launcher.mv1") ;
			return 0;
		case 12:
			BossImg[0]=MV1LoadModel("img\\boss1.mv1") ;
			return 0;
		case 13:
			BossImg[1]=MV1LoadModel("img\\boss1_1.mv1") ;
			return 0;
		case 14:
			BossImg[2]=MV1LoadModel("img\\boss1_2.mv1") ;
			return 0;
		case 15:
			SetCreateSoundDataType( Setting.General.LoadMode) ;
			return 0;
		case 16:
			PjSys::bgm=LoadSoundMem("snd\\stg1.mp3");
			return 0;
		case 17:
			PjSys::bossbgm=LoadSoundMem("snd\\boss1.mp3");
			return 0;
		case 18:
			ChangeVolumeSoundMem( Setting.General.BGMVolume ,PjSys::bgm ) ;
			return 0;
		case 19:
			SetCreateSoundDataType( DX_SOUNDDATATYPE_MEMNOPRESS	) ;
			return 0;
		case 20:
			gPlayer.setX(320);
			return 0;
		case 21:
			gPlayer.setY(400);
			return 0;
		case 22:
			gPlayer.clearParticle();
			return 0;
		case 23:
			DeleteGraph(LoadImg);
			DeleteGraph(ImgLoadStr);
			My::BombFrame=0;
			LoadElements=0;
			return 1;
		//メモ:ロードファイルを追加した際はLoadElements及びUnloadSt1()を書き換えるのを忘れない事！
	}
	return -1;
}
//1面アンロード
void StageManager::UnloadSt1(){
	MV1DeleteModel(bgimg[0]);
	MV1DeleteModel(bgimg[1]);
	MV1DeleteModel(PjSys::Scr::BGModel);
	DeleteGraph(stgimg);
	MV1DeleteModel(SmallEnmImg[0]);
	MV1DeleteModel(SmallEnmImg[1]);
	MV1DeleteModel(BigEnmImg[0]);
	MV1DeleteModel(BigEnmImg[7]);
	MV1DeleteModel(BossImg[0]);
	MV1DeleteModel(BossImg[1]);
	MV1DeleteModel(BossImg[2]);
	//DeleteSoundMem(PjSys::bgm);
	//DeleteSoundMem(PjSys::bossbgm);
	return;
}
int StageManager::stg10(){
	if(phase>=0 &&LoadSt1(phase)==1){
		return 1;
	}
	Loading(LoadImg);
	return 0;
}

int StageManager::stg18(){
	My::SubEnergy=0;
	int pMod= MV1DuplicateModel(My::Model);
	int pBurn=MV1DuplicateModel(My::burner);
	//int ring=MV1DuplicateModel(PjSys::Scr::BurstImg);

	if(phase<0){
		/*
		PlayMusic( "snd\\departure.ogg" , DX_PLAYTYPE_BACK) ;
		SetVolumeMusic( Setting.General.BGMVolume ) ;

		//BGMタイトルの表示
		if(Setting.General.English==0){
			BGMTitle::Set(BGM_DEPARTURE);
		}else{
			BGMTitle::Set(BGM_DEPARTURE_E);
		}
		*/
		int launch=LoadSoundMem("snd\\launch.wav" ) ;
		ChangeVolumeSoundMem((int)(Setting.General.SEVolume/2) , launch );
		PlaySoundMem(launch, DX_PLAYTYPE_BACK ) ;
		My::SubLevel=5;
	}
	if(phase<=180){
		bg2.Scr=0;
		PjSys::CameraVRota=(-90+mysin((phase/4.0f)*(DX_PI_F/180.0f))*-90)*(DX_PI_F/180.0f);
		PjSys::CameraHRota=0;//cos(phase/4.0f*DX_PI_F/180.0f)*90*(DX_PI_F/180.0f);
	}else if(phase<=360){
		PjSys::CameraVRota=-90*(DX_PI_F/180.0f);
		PjSys::CameraHRota=0;//cos(phase/4.0f*DX_PI_F/180.0f)*90*(DX_PI_F/180.0f);
		bg2.Scr=10;
	//}else if(phase<=540){
	//	PjSys::CameraVRota=-180*DX_PI_F/180.0f;
	//	bg2.Scr=10;
	}else{
		//int p2=phase-540;
		//PjSys::CameraVRota=(-90+cos((p2/2.0f)*(DX_PI_F/180.0f))*-90)*(DX_PI_F/180.0f);
		PjSys::CameraVRota=(-90+mysin((phase/4.0f)*(DX_PI_F/180.0f))*-90)*(DX_PI_F/180.0f);
		PjSys::CameraHRota=0;
		bg2.Scr=10;
	}
	bg2.move();

	if(phase<=180){
		SetCameraPositionAndTargetAndUpVec( VGet(-80.0f,0.0f,0.0f), VGet(0.0f,0.0f,90.0f-(phase*phase)/45), VGet(0.0f,mysin(phase/2.0f*DX_PI_F/180.0f)*-1,mycos(phase/2.0f*DX_PI_F/180.0f))) ;
		MV1SetPosition( pMod, VGet( 0.0f, 0.0f, 90.0f-(phase*phase)/45 )) ;
		MV1SetPosition( pBurn, VGet( 0.0f, 0.0f, 90.0f-(phase*phase)/45) ) ;
		MV1SetPosition( BigEnmImg[7], VGet( 0.0f, 50.0f, (90.0f+phase)*2) ) ;
		MV1SetScale(BigEnmImg[7],VGet(0.8f,0.8f,0.8f));

		MV1SetScale(pMod,VGet(10.0f,10.0f,10.0f));
		MV1SetScale(pBurn,VGet(0.01f,0.01f,0.02f));
	}else if(phase<=360){
		SetCameraPositionAndTargetAndUpVec( VGet(cos((phase-180)*DX_PI_F/180.0f)*-80.0f,mysin((phase-180)*DX_PI_F/180.0f)*-400.0f,(90.0f-phase)*2), VGet(0.0f,0.0f,(90.0f-phase)*2), VGet(0.0f,mysin(phase/2.0f*DX_PI_F/180.0f),mysin(phase/2.0f*DX_PI_F/180.0f)*-1)) ;
		MV1SetPosition( pMod, VGet( 0.0f, 0.0f, (90.0f-phase)*2) ) ;
		MV1SetPosition( pBurn, VGet( 0.0f, 0.0f, (90.0f-phase)*2) ) ;
		MV1SetPosition( BigEnmImg[7], VGet( 0.0f, 0.0f, (90.0f+phase)*2) ) ;

		//MV1SetScale(BigEnmImg[7],VGet(1.0f,1.0f,1.0f));
		MV1SetScale(pMod,VGet(9.0f,9.0f,9.0f));
		MV1SetScale(pBurn,VGet(0.1f,0.1f,0.2f));
		//MV1SetPosition( BigEnmImg[6], VGet( 0.0f, 0.0f, -180.0f) ) ;
		//DrawCircle(320,240,phase-180,GetColor(255,255,255),0);
	}else if(phase<=640){ // 360 < phase <= 640
		if(phase==361){
			PjSys::Scr::SetShake(30,-5,5);
			Blur::set(320,240,30,10,0,0,0.1);
			PjSys::Scr::SetBurst(320,240,12,40,255,255,255,true,32);
		}
		if(phase<=390){ //レーザー
			int lphase=phase-360;
			int distin=0; //レーザー先っちょの距離
			int distout=0; //レーザー後ろの距離

			if(lphase<=15){
				distin=(15-lphase)*200/15;
				distout=300;
			}else{
				distin=0;
				distout=(30-lphase)*200/15;
			}
			SetDrawMode(1);
			//SetDrawBlendMode(DX_BLENDMODE_ADD,255);
			for(int i=0;i<32;i++){
				float angle=0;
				float addangle=0;
				if(i%2==0){
					angle=260-10*i/2.0f;
					addangle=-10.0f;
				}else{
					angle=-80+10*(i-1)/2.0f;
					addangle=10.0f;
				}
				float x1=320+mycos(angle*DX_PI_F/180)*distout;
				float y1=240+mysin(angle*DX_PI_F/180)*distout;
				float x2=320+mycos((angle+addangle)*DX_PI_F/180)*distout;
				float y2=240+mysin((angle+addangle)*DX_PI_F/180)*distout;
				float x3=320+mycos((angle+addangle)*DX_PI_F/180)*distin;
				float y3=240+mysin((angle+addangle)*DX_PI_F/180)*distin;
				float x4=320+mycos(angle*DX_PI_F/180)*distin;
				float y4=240+mysin(angle*DX_PI_F/180)*distin;
				DrawModiGraphF(x1,y1,x2,y2,x3,y3,x4,y4,My::Laser::img,TRUE);
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			SetDrawMode(0);
		}else{
			if(phase==391){
				PlaySoundMem(e1.SndBossExp ,DX_PLAYTYPE_BACK ,true ) ;
				PjSys::Scr::SetShake(120,-10,10);
			}
				e1.BigExp(0,320,240);
		}
	}

	e1.ShowExp();

	if(phase<=540){
		MV1DrawModel(BigEnmImg[7]);

		if(phase<=30){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-phase*8);
			DrawBox(0,0,640,460,GetColor(255,255,255),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}//else if(phase>240 && phase<360){
			//MV1DrawModel(ring);
		//}
		//PjSys::Scr::IsNoise=true;
		//PjSys::Scr::NoiseAlpha=128;
		//MV1DrawModel( BigEnmImg[6] ) ;
		MV1DrawModel( pMod ) ;
		MV1DrawModel( pBurn ) ;
	}

	side.draw();
	if(phase<=180){ //ランチャーの中
		phase+=3;
	}else if(phase<=360){ //外に飛び出る
		phase++;
	}else if(phase<=390){ //レーザーばしゅーん
		phase++;
		if(phase%2==0){
			math m;
			e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
		}

			float scl=0.005f*mysin((phase-360)*DX_PI_F/60.0f);
			MV1SetScale(BossImg[0],VGet(scl,scl,scl));
			MV1SetRotationXYZ(BossImg[0], VGet(0.0f,0.0f,0.0f)) ;
			DxLib::VECTOR p={320.0f,240.0f+0*mycos((phase-360)*DX_PI_F/60.0f),0.4f+0.6f*mycos((phase-360)*DX_PI_F/60.0f)};
			MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( p ) ) ;
			MV1DrawModel(BossImg[0]);

			scl=0.003f*mysin((phase-360)*DX_PI_F/60.0f);
			MV1SetScale(SmallEnmImg[1],VGet(scl,scl,scl));
			MV1SetRotationXYZ(SmallEnmImg[1], VGet(0.0f,0.0f,0.0f)) ;
			float mov=(390-phase)/4.0f;
			for(int i=0;i<10;i++){
				DxLib::VECTOR p={320.0f-16.0f*(1+mov)*(i-5),240.0f-4+8*(i%2)*(1+mov),0.4f};
				MV1SetPosition( SmallEnmImg[1], ConvScreenPosToWorldPos( p ) ) ;
				MV1DrawModel(SmallEnmImg[1]);
			}
	}else if(phase<=560){ //ボス飛び去る
		phase++;
			MV1SetScale(BossImg[0],VGet(0.005f+0.1f-0.1f*mycos((phase-390)*3*DX_PI_F/900.0f),0.005f+0.1f-0.1f*mycos((phase-390)*3*DX_PI_F/900.0f),0.005f+0.1f-0.1f*mycos((phase-390)*3*DX_PI_F/900.0f)));
			MV1SetRotationXYZ(BossImg[0], VGet(45.0f*(phase-390)*DX_PI_F/(180.0f*170),0.0f,0.0f)) ;
			DxLib::VECTOR p={320.0f,240.0f-(float)(phase-390)*5*mysin((phase-390)*DX_PI_F/360.0f),0.4f-0.0f*mysin((phase-390)*DX_PI_F/360.0f)};
			MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( p ) ) ;
			MV1DrawModel(BossImg[0]);
	}else{
		phase+=2;
	}
	if(phase>=720){
		//My::Move=true;My::Born=false;
		My::Born=true;
		return 1;
	}else{
		math m;
		switch(phase){
			case 2:
				PjSys::Scr::AddLog("HUD SYSTEM ACTIVATED.",0,GetColor(0,255,0));
				break;
			case 5:
				PjSys::Scr::AddLog("IGNITED MAIN ENGINES.",0,GetColor(255,255,255));
				break;
			case 8:
				PjSys::Scr::AddLog("IGNITED VERNIER ENGINES.",0,GetColor(255,255,255));
				break;
			case 14:
				PjSys::Scr::AddLog("CTRL SYSTEM CHECKING...",0,GetColor(255,255,255));
				break;
			case 59:
				PjSys::Scr::AddLog("OK.",0,GetColor(127,255,127));
				break;
			case 65:
				PjSys::Scr::AddLog("DEF SYSTEM CHECKING...",0,GetColor(255,255,255));
				break;
			case 83:
				PjSys::Scr::AddLog("OK.",0,GetColor(127,255,127));
				break;
			case 89:
				PjSys::Scr::AddLog("WEAPONS CHECKING...",0,GetColor(255,255,255));
				break;
			case 131:
				PjSys::Scr::AddLog("OK.",0,GetColor(127,255,127));
				break;
			case 191:
				PjSys::Scr::AddLog("REQUESTING PERMISSION",0,GetColor(255,255,255));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10);

				break;
			case 197:
				PjSys::Scr::AddLog("TO ENGAGE...",0,GetColor(255,255,255));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));
				break;

			case 235:
				PjSys::Scr::AddLog("ACCEPTED.",0,GetColor(127,255,127));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));
				PjSys::Scr::SetBurst(320,240,12,40,255,127,127,false,32);
				My::Laser::Init();
				My::Laser::Limit=32;
				My::x=320;
				My::y=240;
				My::Laser::IsDemo=true;
				for(int i=0; i<32;i++){My::Laser::Regist();}
				My::Laser::IsDemo=false;
				My::SubLevel=0;
				break;

		//爆発
			case 241:
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));

				break;
			case 261:
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));

				break;
			case 281:
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));

				break;

			case 297:
				PjSys::Scr::AddLog("START COUNTDOWN FOR\0",0,GetColor(255,255,127));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));

				break;
			case 327:
				PjSys::Scr::AddLog("RELEASING AUTOPILOT.",0,GetColor(255,255,127));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));

				break;
			case 357:
				PjSys::Scr::AddLog("STANDBY...\0",0,GetColor(255,255,255));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(0,16));
				e1.RegistExp(m.irand(200,440),m.irand(0,480),m.irand(5,20)/10,m.irand(16,32));
				break;
			case 417:
				//bg2.imgset(bgimg[1],8);
				PjSys::Scr::AddLog("     5     \0",0,GetColor(255,127,127));
				break;
			case 477:
				PjSys::Scr::AddLog("     4     \0",0,GetColor(255,127,127));
				break;
			case 537:
				PjSys::Scr::AddLog("     3     \0",0,GetColor(255,127,127));
				break;
			case 597:
				PjSys::Scr::AddLog("     2     \0",0,GetColor(255,127,127));
				break;
			case 657:
				PjSys::Scr::AddLog("     1     \0",0,GetColor(255,127,127));
				break;
			case 717:
				PjSys::Scr::AddLog("     0     \0",0,GetColor(255,127,127));
				break;
			case 719:
				PjSys::Scr::AddLog("GOOD LUCK.\0",0,GetColor(127,255,0));
				break;
		}

		return 0;
	}
}
//#######################################################
//Stage1本体
//########################################################

int StageManager::stg11(){
	static int HpSmall0=40;
	static int HpSmall1=20;
	static int HpBig0=300+(8-PjSys::HardConst)*50;
	//拡大率
	static float ExpSmall[8]={0.009f,0.007f};
	static float ExpBig[8]={0.02f,0.008f};
	static int pushright=0;

	//フェーズによる場合分け
	switch(phase){
		case 0:
			My::Score=0;
			PjSys::BombExtendPhase=1;
			PjSys::ExtendPhase=1;
			My::SubEnergy=0;
			My::Bomb=My::DefaultBomb;
			My::Left=My::DefaultLeft+PjSys::GameLevel;
			Enm::BossPhase=5700;
			bg2.Scr=8;
			SetCameraPositionAndAngle( VGet( 0.0f+PjSys::Scr::MoveX, -230.0f, 0.0f+PjSys::Scr::MoveY ), DX_PI_F/-2.0f, 0, 0 ) ;
			PjSys::CameraVRota=DX_PI_F/-2.0f;
			PjSys::CameraHRota=0;
			PjSys::CameraTRota=0;
			PjSys::CameraPos=VGet( 0.0f, -230.0f, 0.0f);
			My::BombFrame=0;
			My::Rot=0;
			break;
		case 5:
			PjSys::Scr::AddLog("DIANA SYSTEM READY.",My::NowStage,GetColor(127,255,127));
			if(PjSys::cheat::Go2Boss){phase=Enm::BossPhase-1;}else{PlaySoundMem(PjSys::bgm ,DX_PLAYTYPE_LOOP ,FALSE) ;}
			break;
		//隠しキャラ
		case 40:
			pushright=e1.create(HpSmall1*3,440,0,0x18,SmallEnmImg[1],ExpSmall[1]/1000,1,0x100,30,Enm::RBullet,12,12,true,true,false,true,7);
			break;
		//飾り
		case 60:
			e1.create(-127,640,500,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 80:
			e1.create(-127,640,460,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 100:
			e1.create(-127,640,420,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 120:
			e1.create(-127,640,380,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 140:
			e1.create(-127,640,340,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 160:
			e1.create(-127,640,300,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 180:
			e1.create(-127,640,260,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 200:
			e1.create(-127,640,220,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 220:
			e1.create(-127,0,500,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 240:
			e1.create(-127,0,460,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 260:
			e1.create(-127,0,420,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 280:
			e1.create(-127,0,380,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 300:
			e1.create(-127,0,340,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 320:
			e1.create(-127,0,300,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 340:
			e1.create(-127,0,260,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		//ステージ表示(10frm-430frm)
		//------------------------------------------------
		//小型機左から1
		case 330:
			e1.create(-127,640,400,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 360:
			e1.create(-127,640,400,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			e1.create(-127,0,220,0x25,SmallEnmImg[1],ExpSmall[1]*2,1,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 390:
			e1.create(-127,640,400,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;
		case 420:
			e1.create(-127,640,400,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 450:
			e1.create(-127,640,400,0x24,SmallEnmImg[1],ExpSmall[1]*2,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 490:

			//ダミー
			e1.create(-127,0,400,0x25,SmallEnmImg[1],ExpSmall[1]*2.5f,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);

			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 510:
			//ダミー
			e1.create(-127,0,400,0x25,SmallEnmImg[1],ExpSmall[1]*2.5f,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 520:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 540:
			//ダミー
			e1.create(-127,0,400,0x25,SmallEnmImg[1],ExpSmall[1]*2.5f,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 550:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 570:
			//ダミー
			e1.create(-127,0,400,0x25,SmallEnmImg[1],ExpSmall[1]*2.5f,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 580:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 600:
			//ダミー
			e1.create(-127,0,400,0x25,SmallEnmImg[1],ExpSmall[1]*2.5f,0,0x100,30,Enm::RBullet,24,24,true,false,false,false,0,0.3f);
			break;

		case 610:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
			//小型機右から
		case 640:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 660:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 680:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 700:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 720:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 740:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 760:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 780:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 800:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 820:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;

		//----------------------------------------------------------
		//小型機左から2
		case 840:
			e1.create(HpSmall1,0,10,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 860:
			e1.create(HpSmall1,0,20,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 880:
			e1.create(HpSmall1,0,30,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 900:
			e1.create(HpSmall1,0,40,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 920:
			e1.create(HpSmall1,0,50,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 940:
			e1.create(HpSmall1,0,50,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 960:
			e1.create(HpSmall1,0,40,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 980:
			e1.create(HpSmall1,0,30,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 1000:
			e1.create(HpSmall1,0,20,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 1020:
			e1.create(HpSmall1,0,10,0x18,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;

		//小型機右から
		case 1040:
			e1.create(HpSmall1,640,100,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1060:
			e1.create(HpSmall1,640,90,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1080:
			e1.create(HpSmall1,640,80,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1100:
			e1.create(HpSmall1,640,70,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1120:
			e1.create(HpSmall1,640,60,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1140:
			e1.create(HpSmall1,640,50,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1160:
			e1.create(HpSmall1,640,40,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1180:
			e1.create(HpSmall1,640,30,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1200:
			e1.create(HpSmall1,640,20,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 1220:
			e1.create(HpSmall1,640,10,0x19,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;

		//----------------------------------------------------------
		//小型機左から3
		case 1240:
			e1.create(HpSmall1,98,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1260:
			e1.create(HpSmall1,128,-20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1280:
			e1.create(HpSmall1,98,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1300:
			e1.create(HpSmall1,128,-20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1320:
			e1.create(HpSmall1,98,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1340:
			e1.create(HpSmall1,128,-20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1360:
			e1.create(HpSmall1,98,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1380:
			e1.create(HpSmall1,128,-20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1400:
			e1.create(HpSmall1,98,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1420:
			e1.create(HpSmall1,128,-20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;

		//小型機右から
		case 1440:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1460:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1480:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1500:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1520:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1540:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1560:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1580:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1600:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 1620:
			e1.create(HpSmall1,552,-20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;

		//----------------------------------------------------------
		//小型機左から4
		case 1640:
			e1.create(HpSmall1,10,10,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1660:
			e1.create(HpSmall1,20,20,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1680:
			e1.create(HpSmall1,30,30,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1700:
			e1.create(HpSmall1,40,40,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1720:
			e1.create(HpSmall1,50,50,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 1740:
			e1.create(HpSmall1,60,60,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,30,Enm::RBullet,24,24,true);
			break;
		case 1760:
			e1.create(HpSmall1,70,70,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,30,Enm::RBullet,24,24,true);
			break;
		case 1780:
			e1.create(HpSmall1,80,80,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,30,Enm::RBullet,24,24,true);
			break;
		case 1800:
			e1.create(HpSmall1,90,90,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,30,Enm::RBullet,24,24,true);
			break;
		case 1820:
			e1.create(HpSmall1,100,100,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,30,Enm::RBullet,24,24,true);
			break;

		//小型機右から
		case 1840:
			e1.create(HpSmall1,630,10,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 1860:
			e1.create(HpSmall1,620,20,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 1880:
			e1.create(HpSmall1,610,30,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 1900:
			e1.create(HpSmall1,600,40,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::BBullet,24,24,true);
			break;
		case 1920:
			e1.create(HpSmall1,590,50,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::BBullet,24,24,true);
			break;
		case 1940:
			e1.create(HpSmall1,580,60,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::BBullet,24,24,true);
			break;
		case 1960:
			e1.create(HpSmall1,570,70,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 1980:
			e1.create(HpSmall1,560,80,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 2000:
			e1.create(HpSmall1,550,90,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 2020:
			e1.create(HpSmall1,540,100,0x11,SmallEnmImg[1],ExpSmall[1],1,0x107,30,Enm::GBullet,24,24,true);
			break;
		case 2070:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 2120:
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 2170:
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 2220:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			break;

		case 2320:
			e1.create(HpSmall1,616,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);

			e1.create(HpSmall1,32,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			break;

		//小型機の左右同時ラッシュ
		case 2550:
			e1.create(HpSmall0,98,0,0x10,SmallEnmImg[0],ExpSmall[0],0,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall0,552,0,0x11,SmallEnmImg[0],ExpSmall[0],0,0x107,100,Enm::GBullet,24,24,true);
			break;
		case 2600:
			e1.create(HpSmall0,98,20,0x10,SmallEnmImg[0],ExpSmall[0],0,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall0,552,20,0x11,SmallEnmImg[0],ExpSmall[0],0,0x107,100,Enm::GBullet,24,24,true);
			break;
		case 2650:
			e1.create(HpSmall0,98,40,0x10,SmallEnmImg[0],ExpSmall[0],0,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall0,552,40,0x11,SmallEnmImg[0],ExpSmall[0],0,0x107,100,Enm::GBullet,24,24,true);
			break;
		case 2700:
			e1.create(HpSmall0,98,60,0x10,SmallEnmImg[0],ExpSmall[0],0,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall0,552,60,0x11,SmallEnmImg[0],ExpSmall[0],0,0x107,100,Enm::GBullet,24,24,true);
			break;
		case 2750:
			e1.create(HpSmall0,98,80,0x10,SmallEnmImg[0],ExpSmall[0],0,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall0,552,80,0x11,SmallEnmImg[0],ExpSmall[0],0,0x107,100,Enm::GBullet,24,24,true);
			break;
		//中型機*1の旋回砲塔
		case 2800:
			//ここら辺で下の背景モデルを変える。モデルが重いので予め読み込んでおく。
			bg2.imgset(bgimg[0],8);

			e1.create(HpBig0,320,0,0x12,BigEnmImg[0],ExpBig[0],0,0x105,500,Enm::RLaser,48,48,true,true,true,true,0);
			//e1.create(HpBig0,350,0,0x12,BigEnmImg[0],ExpBig[0],0,0x106,500,Enm::GLaser,48,48,true);
			break;
		//小型機が上から
		case 3000:
			e1.create(HpSmall0,260,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3020:
			e1.create(HpSmall0,230,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3040:
			e1.create(HpSmall0,200,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3060:
			e1.create(HpSmall0,170,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 3080:
			e1.create(HpSmall0,140,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			break;

		case 3100:
			e1.create(HpSmall0,390,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3120:
			e1.create(HpSmall0,410,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3140:
			e1.create(HpSmall0,440,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3160:
			e1.create(HpSmall0,470,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3180:
			e1.create(HpSmall0,500,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			break;
//サイン波
		case 3300:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			break;
		case 3320:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::RLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			break;
		case 3340:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			break;
		case 3360:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::BLaser,24,24,true);
			break;
		case 3380:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::BLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::BLaser,24,24,true);
			break;
		case 3400:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::BLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::RLaser,24,24,true);
			break;
		case 3420:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			break;
		case 3440:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::RLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			break;
		case 3460:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			break;
		case 3480:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::BLaser,24,24,true);
			break;
		case 3500:
			e1.create(HpSmall0,320,0,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::BLaser,24,24,true);
			e1.create(HpSmall0,320,0,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::BLaser,24,24,true);
			break;
		//小型機の左右交互ラッシュ*5
		case 3600:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 3620:
			e1.create(HpSmall0,340,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3640:
			e1.create(HpSmall0,360,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3660:
			e1.create(HpSmall0,380,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3680:
			e1.create(HpSmall0,400,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 3700:
			e1.create(HpSmall0,470,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,552,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			break;

		case 3720:
			e1.create(HpSmall0,340,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3740:
			e1.create(HpSmall0,320,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3760:
			e1.create(HpSmall0,280,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3780:
			e1.create(HpSmall0,260,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			break;
		case 3800:
			e1.create(HpSmall0,240,0,0x13,SmallEnmImg[0],ExpSmall[0],0,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 3820:
			e1.create(HpSmall0,320,-50,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			break;
		case 3840:
			e1.create(HpSmall0,350,-50,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::RLaser,24,24,true);
			break;
		case 3860:
			e1.create(HpSmall0,380,-50,0x14,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			break;
		case 3880:
			e1.create(HpSmall0,410,-50,0x14,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			break;
		case 3900:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 3920:
			e1.create(HpSmall0,320,-50,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::RLaser,24,24,true);
			break;
		case 3940:
			e1.create(HpSmall0,290,-50,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::RLaser,24,24,true);
			break;
		case 3960:
			e1.create(HpSmall0,260,-50,0x15,SmallEnmImg[0],ExpSmall[0],0,0x101,50,Enm::GLaser,24,24,true);
			break;
		case 3980:
			e1.create(HpSmall0,230,-50,0x15,SmallEnmImg[0],ExpSmall[0],0,0x102,50,Enm::GLaser,24,24,true);
			break;
		case 4000:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			break;
		//大型機*2+小型機*10
		case 4150:
			e1.create(HpBig0,280,0,0x12,BigEnmImg[0],ExpBig[0],0,0x108,500,Enm::RLaser,48,48,true,true,true,true,0);
			break;
		case 4300:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x102,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x102,102,Enm::RBullet,24,24,true);
			break;

		//小型機の左右交互ラッシュ*5
		case 4400:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x104,100,Enm::RBullet,24,24,true);
			break;
		case 4500:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x105,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x105,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x105,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x105,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,552,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x105,100,Enm::GBullet,24,24,true);
			break;
		case 4550:
			e1.create(HpBig0,320,0,0x12,BigEnmImg[0],ExpBig[0],0,0x108,500,Enm::BLaser,48,48,true);
			break;

		case 4600:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			break;
		case 4700:
			e1.create(HpSmall1,616,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,600,32,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,584,64,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,568,96,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,552,128,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			break;
		case 4800:
			e1.create(HpSmall1,32,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,48,32,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			e1.create(HpSmall1,64,64,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::GBullet,24,24,true);
			e1.create(HpSmall1,80,96,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::BBullet,24,24,true);
			e1.create(HpSmall1,96,128,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,100,Enm::RBullet,24,24,true);
			break;
		//中型機*1の旋回砲塔
		case 4900:
			e1.create(HpBig0,290,0,0x12,BigEnmImg[0],ExpBig[0],0,0x105,500,Enm::RLaser,48,48,true,true,true,true,4);
			break;
		case 5000:
			e1.create(HpBig0,350,0,0x12,BigEnmImg[0],ExpBig[0],0,0x10c,500,Enm::GLaser,48,48,true,true,true,true,5);
			break;
		//小型機左から
		case 5200:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 5220:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 5240:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 5260:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::RBullet,24,24,true);
			break;
		case 5280:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::RBullet,24,24,true);
			break;
		case 5300:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::BBullet,24,24,true);
			break;
		case 5320:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5340:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x103,30,Enm::BBullet,24,24,true);
			break;
		case 5360:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5380:
			e1.create(HpSmall1,98,0,0x10,SmallEnmImg[1],ExpSmall[1],1,0x10f,30,Enm::BBullet,24,24,true);
			break;

		//小型機右から
		case 5400:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 5420:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 5440:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 5460:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::GBullet,24,24,true);
			break;
		case 5480:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x101,30,Enm::GBullet,24,24,true);
			break;
		case 5500:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5520:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5540:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5560:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x100,30,Enm::BBullet,24,24,true);
			break;
		case 5570:
			e1.create(HpSmall1,552,0,0x11,SmallEnmImg[1],ExpSmall[1],1,0x10f,30,Enm::BBullet,24,24,true);
			break;
	}

	if(phase==Enm::BossPhase){
		e1.setcap(5);
		e1.init();
		return 1;
	}
	math m;
	PjSys::CameraPos.y=-230.0f+(float)(mysin(m.ToRadian(phase))*50);
	if(phase<5400){
		PjSys::CameraVRota=(float)(DX_PI_F/-2.0f+DX_PI_F/-180.0f * (mysin(m.ToRadian(phase)/20)*360));
		PjSys::CameraTRota=(float)(DX_PI_F/180.0f * (mysin(m.ToRadian(phase)/20)*360));
	}
	//PjSys::CameraTRota=DX_PI_F/180.0f * (sin(m.ToRadian((float)phase/500))*360);

	stgmove();
	if(My::GOver==true || My::Pause==true){return 0;}
	if(phase>=10 && phase<430){ //ステージ表示
		ShowStageTitle(phase-10);
	}
	return 0;
}
//-------------------------------------------------
//Stage1本体終了
//------------------------------------------------

//=================================================
//Stage1 Warning
//=================================================
int StageManager::stg12(){
	//PjSys::CameraPos.y=-230.0f;
	PjSys::CameraVRota=DX_PI_F/-2.0f;
	PjSys::CameraTRota=0.0f;

	return warn();
}

//=================================================
//Stage1 ボス戦
//=================================================
int StageManager::stg13(){
	int BossHP=15000+(7-PjSys::HardConst)*1000;
	int HakkyoHP=7000+(7-PjSys::HardConst)*500;
	//int BossHP=300+(7-PjSys::Hard)*100;
	//int HakkyoHP=150+(7-PjSys::Hard)*100;

	stgmove();
	if(My::GOver==true || My::Pause==true){return 0;}

	if(phase==0){
		e1.setcap(5);
		e1.init();
		//PjSys::NowVolume=Setting.General.BGMVolume;
		ChangeVolumeSoundMem(Setting.General.BGMVolume,PjSys::bossbgm);
		PlaySoundMem( PjSys::bossbgm , DX_PLAYTYPE_LOOP, FALSE) ;
		My::Move=false;
		int j=0;while(j++<8){e1.BExpPhase[j]=0;}
		//gPlayer.frmLRoll=120;
		//My::fRoop=DX_PI_F/180*45;
		bg2.changespeed(10);
		e1.BFrm=0;
		PjSys::Scr::AddLog("IDENTIFIED AS\0",0,GetColor(255,255,255));
	}else if(phase==10){
		PjSys::Scr::AddLog("\"RECONNAISSANCE PLANE\0",0,GetColor(255,255,255));
	}else if(phase==20){
		PjSys::Scr::AddLog("<< KILROY >>\".\0",0,GetColor(255,255,127));
	}else if(phase<90){
		/*

		自機のカメラワーク

		*/
		My::IsBurner=true;
		//My::fRoop=DX_PI_F/180.0f*sin((float)m.ToRadian(phase*2))*90;
		My::Rot=phase*8/3.0f;
		gPlayer.addX((320-My::x)/90);
		gPlayer.addY((280-My::y)/90);
		My::x=gPlayer.getX();
		My::y=gPlayer.getY();
		My::Exp-=0.01f;

		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク
	}else if(phase<180){
		My::IsBurner=false;
		math m;
		My::Rot=0;
		PjSys::CameraPos.y+=(float)mysin(m.ToRadian((phase-90)*2))*6;
		PjSys::CameraVRota-=DX_PI_F/720.0f;
		gPlayer.addY((float)mysin(m.ToRadian((phase-90)*2))*2);
		My::y=gPlayer.getY();
		My::Exp+=0.01f;

		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク
	}else if(phase<420){
		/*

		ここにボスが現れるエフェクト

		*/
		if(phase==180){
			int flyin=LoadSoundMem("snd\\boss_flyin.wav" ) ;
			ChangeVolumeSoundMem(Setting.General.SEVolume , flyin );
			PlaySoundMem(flyin, DX_PLAYTYPE_BACK ) ;
		}
		math m;
		DxLib::VECTOR pLoc={320.0f,(float)(648-phase),(float)(0.3+0.1*(phase-179)/240)};
		MV1SetRotationXYZ( BossImg[0], VGet((float)m.ToRadian(mysin(m.ToRadian(phase-238))*30) , 0.0f , 0.0f));
		MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( pLoc ) ) ;
		MV1SetScale( BossImg[0], VGet(0.06f-0.02f*((float)(phase-180)/240),0.06f-0.02f*((float)(phase-180)/240),0.06f-0.02f*((float)(phase-180)/240))) ;
		MV1DrawModel( BossImg[0] ) ;
		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク
	}else if(phase<600){
			math m;
			float y=228-(float)mysin(m.ToRadian(phase-420)/2)*100;
			DxLib::VECTOR pLoc={320.0f+(float)(mysin(PI*(phase-420)/180)*-30),y,0.4f};
			MV1SetRotationXYZ( BossImg[0], VGet(0.0f, 0.0f , (float)(DX_PI_F*mysin(PI*(phase-420)/120)*-30/180)));
			MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( pLoc ) ) ;
		MV1DrawModel( BossImg[0] ) ;
		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク

	}else if(phase==600){
		My::Rot=0;
		My::Exp=MY_MODEL_EXP;
		My::Move=true;
		e1.BPPhase=0;
		e1.BPRotate[0]=1;
		e1.BPRotate[1]=1;
		e1.BPRotate[2]=0;
		e1.BPRotate[3]=0;
		e1.BFrm=120*60;
		Enum[0]=e1.create(BossHP,320,128,0x1a,BossImg[0],0.04f,5,0x1a4,100,Enm::BLaser,128,64,false);
		e1.deg[Enum[0]]=0;
		e1.MogiMogiPhase=0;
		//PjSys::Scr::AddLog("",0,GetColor(255,192,192));

		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク
	}else if(phase>600&&e1.MogiMogiPhase<3){
		PjSys::CameraHRota=DX_PI_F/180.0f * (mysin((float)phase/50)*10); //背景のカメラワーク
	}

	if(My::BombFrame==BMBFRAME-1||My::IsHit){
		e1.BulletEnd[Enum[0]]=true; //ボム対策
	}

	//弾幕切り替え
	if(e1.BulletEnd[Enum[0]]==true && e1.hp[Enum[0]]>0){
		int Blt = (10-PjSys::Hard)*50;
		e1.eb1[Enum[0]].init();
		if(e1.BPPhase==0){
			switch(e1.BPRotate[0]){
				case 1:
					//e1.bltchange(Enum[0],Enm::RLaser,Blt,0x10a);e1.BPRotate[0]++;

					e1.bltchange(Enum[0],Enm::RLaser,Blt,0x1a1);
					e1.BPRotate[Enum[0]]++;
					break;
				case 2:
					e1.bltchange(Enum[0],Enm::GLaser,720,0x1a2);
					e1.BPRotate[Enum[0]]++;
					break;
				case 3:
					e1.bltchange(Enum[0],Enm::BLaser,(int)(Blt/4),0x1a4);
					e1.BPRotate[Enum[0]]++;
					break;
				case 4:
					e1.bltchange(Enum[0],Enm::OLaser,(int)(Blt/4),0x1a7);
					e1.BPRotate[Enum[0]]++;
					break;

				case 5:
					e1.bltchange(Enum[0],Enm::BLaser,Blt,0x1a9);//ばらまき
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}else{
			switch(e1.BPRotate[0]){
				case 1:
					e1.bltchange(Enum[0],Enm::RLaser,Blt,0x1a5);//同心円落下
					e1.BPRotate[Enum[0]]++;
					break;
				case 2:
					e1.bltchange(Enum[0],Enm::GLaser,Blt*4,0x1a3);//円形→狙撃
					e1.BPRotate[Enum[0]]++;
					break;
				case 3:
					e1.bltchange(Enum[0],Enm::BLaser,Blt,0x1a6); //箒掃き
					e1.BPRotate[Enum[0]]++;
					break;
				case 4:
					e1.eb1[Enum[0]].tmp[0]=1;
					e1.eb1[Enum[0]].deg=0;
					e1.bltchange(Enum[0],Enm::OLaser,Blt*6,0x1a8);//くねくね
					e1.BPRotate[Enum[0]]=1;
					break;
			}
		}
	}

	if(phase>=600&&(e1.hp[Enum[0]]<HakkyoHP || e1.BFrm<60*60)){ //発狂分岐
		if(e1.MogiMogiPhase==0){ //発狂時の動作
			//e1.eb1[Enum[0]].init();
			e1.bltchange(Enum[0],Enm::GLaser,0,0x101);
			e1.BPRotate[0]=1;
			e1.BulletEnd[Enum[0]]=true; //弾を消す
			BossImg[0]=MV1DuplicateModel( BossImg[1] );
			e1.img[Enum[0]]=MV1DuplicateModel( BossImg[1] );
			e1.create(500,e1.x[Enum[0]],e1.y[Enum[0]],0x1d,BossImg[2],0.04f,2,0x10f,100,Enm::BBullet,32,64,false,true,true,true,7);
			e1.mphase[Enum[0]]=1;
			//e1.img[Enum[0]]=BossImg[0];
			e1.BPPhase=1;
			e1.MogiMogiPhase=1;
			//爆発設定
			int i=0;
			math m;
			while(i++<8){
				e1.RegistExp((int)(e1.x[Enum[0]]-32+m.irand(0,64)),(int)(e1.y[Enum[0]]),1.5,m.irand(0,32));
			}
		}
		//ボスが死んだら
		if(phase>=600&&e1.hp[Enum[0]]<=0){
			//本来は発狂段階フェーズだが、死んだときのフレーム計算にも使い回す
			if(e1.MogiMogiPhase<2||e1.MogiMogiPhase>=180){
				e1.MogiMogiPhase++;
			}else{
				if(phase%2==0){e1.MogiMogiPhase++;}
			}

			if(e1.MogiMogiPhase==2){
				rphase=0;
				BossRemainSec=(int)((e1.BFrm-e1.BFrm%60)/60);
				int i=0;
				My::Move=false;
				math m;
				while(i++<8){
					e1.RegistExp((int)(e1.x[Enum[0]]-128+m.irand(0,256)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.0,m.irand(0,32));
					e1.eb1[Enum[0]].init();
					e1.bltchange(Enum[0],Enm::BLaser,10,0x100);
				}
				//e1.MogiMogiPhase++;
			}
			math m;
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
				PjSys::Scr::SetBurst((int)e1.x[Enum[0]],(int)e1.y[Enum[0]],12,40,255,255,255,true,32);
			}else if(e1.MogiMogiPhase==128){
				e1.RegistExp((int)(e1.x[Enum[0]]-16+m.irand(0,32)),(int)(e1.y[Enum[0]]-8+m.irand(0,16)),0.5);
			}
			if(e1.MogiMogiPhase>=120 && e1.MogiMogiPhase<=180){
				PjSys::Scr::BurstX=(int)e1.x[Enum[0]];
				PjSys::Scr::BurstY=(int)e1.y[Enum[0]];
			}

			if(e1.MogiMogiPhase==180){
				if(e1.MogiMogiPhase==180){
					//PjSys::Scr::SetBurst((int)e1.x[Enum[0]],(int)e1.y[Enum[0]],20,GetColor(255,255,255),40);
				}
				//Blur::set((int)(e1.x[Enum[0]]),(int)(e1.y[Enum[0]]),140,5,0,0,0.001);
				//e1.bephase=0;

				int i=0;
				math m;
				while(i++<8){
					e1.RegistExp((int)(e1.x[Enum[0]]-128+m.irand(0,256)),(int)(e1.y[Enum[0]]-64+m.irand(0,128)),1.0,35+m.irand(32,64));
				}
				e1.bephase=0;
				PlaySoundMem(e1.SndBossExp ,DX_PLAYTYPE_BACK ,true ) ;
				PjSys::Scr::SetShake(180,-40,40);

				e1.BExpY[1]=(int)e1.y[Enum[0]];
				e1.BExpPhase[1]=0;
			}else if(e1.MogiMogiPhase>=480){
				bg2.changespeed(0);
				e1.vx[Enum[0]]=0;
				e1.vy[Enum[0]]=0;
				My::Move=true;
				My::IsBurner=false;
				PjSys::Scr::BGColor=GetColorF(1.0f,1.0f,1.0f,1.0f);
				return 1;
			}else if(e1.MogiMogiPhase>=320){
						My::Rot=(e1.MogiMogiPhase-320)*2.0f;
						My::IsBurner=true;
						math m;
						gPlayer.addY(mysin(m.ToRadian((e1.MogiMogiPhase-180)/3.33))*-20);
						My::y=gPlayer.getY();
						bg2.changespeed(0);
						//PjSys::CameraHRota=0;

				PjSys::Scr::BGColor=GetColorF(1.0f,e1.MogiMogiPhase/480.0f,e1.MogiMogiPhase/480.0f,0.5f);
				e1.BigExp(Enum[0],(int)e1.x[Enum[0]],(int)e1.y[Enum[0]]);
				return 0;
			}else if(e1.MogiMogiPhase>=180){
				bg2.changespeed(0);
				//PjSys::CameraHRota=0;
				//e1.x[Enum[0]]=e1.BExpX[1]+PjSys::Scr::MoveX;
				//e1.y[Enum[0]]=e1.BExpY[1]+PjSys::Scr::MoveY;
				e1.vx[Enum[0]]=0;
				e1.vy[Enum[0]]=0;
				MV1SetWireFrameDrawFlag(BossImg[0],true);
				MV1SetOpacityRate( BossImg[0], 0.0f) ;
				MV1SetDifColorScale( BossImg[0], GetColorF( 1.0f, 0.0f, 0.0f, 1.0f ) ) ;
				MV1SetScale( BossImg[0], VGet((0.04f-0.012f),(0.04f-0.012f)*(e1.MogiMogiPhase-180)/4,(0.04f-0.012f))) ;

				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(300-e1.MogiMogiPhase)*2);
				DrawBox(0,0,640,480,GetColor(255,255,255),true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

				e1.BigExp(Enum[0],(int)e1.x[Enum[0]],(int)e1.y[Enum[0]]);
			}else{
					My::IsBurner=false;
						math m;
						My::Rot=(float)(e1.MogiMogiPhase+60);
						//gPlayer.addX((float)sin(m.ToRadian(e1.MogiMogiPhase*2)*2));
						gPlayer.addX((220-My::x)/180);
						gPlayer.addY((600-My::y)/180);
						My::x=gPlayer.getX();
						My::y=gPlayer.getY();
						My::Exp+=0.01f;
						PjSys::Scr::BGColor=GetColorF(1.0f,1.0f-e1.MogiMogiPhase/280.0f,1.0f-e1.MogiMogiPhase/280.0f,0.5f);
						bg2.changespeed((int)(mycos(m.ToRadian((double)e1.MogiMogiPhase/2))*10));
						if(phase%2==0){
							e1.x[Enum[0]]+=(int)((320-e1.x[Enum[0]])/90);
							e1.y[Enum[0]]--;
						}
						MV1SetOpacityRate( BossImg[0], 1.0f) ;
						e1.BExpX[1]=(int)e1.x[Enum[0]];
						e1.BExpY[1]=(int)e1.y[Enum[0]];
				MV1SetScale( BossImg[0], VGet(0.04f-e1.MogiMogiPhase*0.00018f,0.04f-e1.MogiMogiPhase*0.00018f,0.04f-e1.MogiMogiPhase*0.00018f)) ;
				MV1SetDifColorScale( BossImg[0], GetColorF( 1.0f, 0.0f, 0.0f, 1.0f ) ) ;
				MV1SetRotationXYZ(BossImg[0], VGet(0.0f,(float)e1.MogiMogiPhase * DX_PI_F / -180.0f  , (float)e1.MogiMogiPhase * DX_PI_F / 90.0f )) ;
				MV1SetWireFrameDrawFlag(BossImg[0],false);
			}
				DxLib::VECTOR pLoc={(float)e1.x[Enum[0]],(float)e1.y[Enum[0]],0.6f};
				MV1SetPosition( BossImg[0], ConvScreenPosToWorldPos( pLoc ) ) ;

				MV1DrawModel( BossImg[0] ) ;
		}
	}else{
		e1.BPPhase=0;
	}
	e1.ShowExp();

	//秒数カウント
	if(e1.MogiMogiPhase<2){
		if(phase>=600 && --e1.BFrm<=0){
			e1.type[Enum[0]]=0x1b;
			e1.hp[Enum[0]]=BossHP;
			My::NowInv=true;
			My::Move=false;
			if(e1.BFrm<=-60){
				BossRemainSec=0;
				My::Move=true;
				My::IsBurner=false;
				My::NowInv=false;
				//InitSoundMem() ;
				return 1;
			}
		}else if(phase>=600 && e1.hp[Enum[0]]>0){
			//int sec=(int)((e1.BFrm-e1.BFrm%60)/60);
			Enm::drawHP(BossHP,e1.hp[Enum[0]],(int)((e1.BFrm-e1.BFrm%60)/60)); //HP描画
		}
	}
	//PjSys::NumDraw(PjSys::MainNum,(int)((e1.MogiMogiPhase-120)/10),340,320,32);
	return 0;
}

//-------------------------------------------------
//Stage1ボス戦終了
//------------------------------------------------
//########################################################################
int StageManager::stg14(){
	if(phase<=0){rphase=0;}
	My::Move=false;
	stgmove();
	My::Move=true;

	return result();
}