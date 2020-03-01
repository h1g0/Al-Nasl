#include "Common.h"

/*#############################################################

						  ���j���[���L�q

##############################################################*/

//�ŏ��̕\��
int StageManager::StgNotice(){
	int fadein=60;
	int fadeout=60;
	int show=60*5;

	int fadeinshow=fadein+show;
	int total=fadein+fadeout+show;

	if(phase==0){
		PjSys::key::load();
		LoadImg=LoadGraph("img\\notice.png");
	}else if(phase==total){
		DeleteGraph(LoadImg);
		return 1;
	}else if(phase<=fadein){ //�t�F�[�h�C��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,15+phase*4);
		DrawGraph(0,0,LoadImg,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(phase > fadeinshow && phase<total){ //�t�F�[�h�A�E�g
		int lphase=255-(phase-fadeinshow)*4;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,lphase);
		DrawGraph(0,0,LoadImg,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else{ //�ʏ�
		DrawGraph(0,0,LoadImg,FALSE);
	}

	if(phase>0 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0){
		DeleteGraph(LoadImg);
		return 1;
	}
	phase++;
	return 0;
}

//���j���[���[�h
int StageManager::stg00(){
	switch(phase){
		case 0:
			InitGraph();
			InitSoundMem();
			PjSys::Init();
			My::Init();
			Enm::Init();
			PjSys::Scr::BGColor=GetColorF(1.0f,1.0f,1.0f,1.0f);
			//PjSys::font::menu = CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
			PjSys::font::log = CreateFontToHandle(NULL , 10 , 1 , DX_FONTTYPE_ANTIALIASING ) ;
			PjSys::font::caption = CreateFontToHandle(NULL , 14 , 4 , DX_FONTTYPE_ANTIALIASING ) ;
			LoadDivGraph("img\\num.bmp",10,10,1,16,32,PjSys::MainNum); //����
			//LoadDivGraph("img\\char.bmp",7,1,7,98,16,PjSys::MainChar);//����
			PjSys::FPSChar=LoadGraph("img\\fps.bmp");
			//bg.imgset(LoadGraph( "img\\bg_box.bmp" ),LoadGraph( "img\\bg_box.bmp" ),1);
			bg2.imgset(MV1LoadModel("img\\player2.mv1" ),0);
			SetFogEnable( FALSE ) ;
			bgphase=0;
			//bg2.imgset(MV1LoadModel("img\\pjf.x" ),3);
			//My::Model=MV1LoadModel( "img\\player2.mv1" ) ;
			PjSys::CameraVRota=DX_PI_F/-2.0f;
			PjSys::CameraHRota=0;
			PjSys::CameraTRota=0;
			PjSys::CameraPos=VGet( 0.0f, -300.0f, 0.0f);
			//My::x=320;
			LoadImg=LoadGraph("img\\load.bmp");
			logo=LoadGraph("img\\pjf.bmp");
			BarImg=LoadGraph("img\\selectbar.bmp");
			LoadDivGraph("img\\mmenu1.bmp",6,1,6,192,24,mMenuImg); //���j���[
			SndSelect=LoadSoundMem("snd\\select.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , SndSelect );
			SndOK=LoadSoundMem("snd\\ok.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , SndOK );
			SndCancel=LoadSoundMem("snd\\cancel.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , SndCancel );

			if(Setting.General.English){
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): Accept / %KEY_SUB%(%PAD_SUB%): Cancel / %KEY_BOMB%(%PAD_BOMB%): Instructions");
				mMenuStr[0]="Start the game.";
				mMenuStr[1]="(Unimplemented)#Show some bonus functions.";
				mMenuStr[2]="(Unimplemented)#Show the rankings";
				mMenuStr[3]="(Unimplemented)#Show how to play the game.";
				mMenuStr[4]="Show the configuration menu.";
				mMenuStr[5]="Exit the game.";
			}else{
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): ���� / %KEY_SUB%(%PAD_SUB%): �L�����Z�� / %KEY_BOMB%(%PAD_BOMB%): ����");
				mMenuStr[0]="�Q�[�����J�n���܂��B";
				mMenuStr[1]="(������)#�l�X�Ȃ��܂��@�\��\�����܂��B";
				mMenuStr[2]="(������)#�����L���O��\�����܂��B";
				mMenuStr[3]="(������)#�Q�[���̐�������\�����܂��B";
				mMenuStr[4]="�ݒ胁�j���[��\�����܂��B";
				mMenuStr[5]="�Q�[�����I�����܂��B";
			}
			Window.SetWH(320,240);
			Window.SetSound("snd\\window_open.wav","snd\\window_close.wav");
			Window.SetImg(BarImg);
			//Window.SetString("�O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e\n0123456789abcdef\nALL\nYOUR\nBASE\nARE\nBELONG\nTO\nUS.",Window.DialogYesNo);
			//Window.SetFlag();

			PjSys::key::load();
			return 1;
			break;
	}
	Loading(LoadImg);
	return 0;
}
//�ŏ��̃��j���[�\��
int StageManager::stg01(){
	int n=Menu(mMenuImg,mMenuStr,5);
	switch(n){
		case -1:
			return 0;
		case 0:
			stage=0x80;
			return 0;
		case 4:
			stage=0x90;
			return 0;
		case 5:
			PjSys::Exit=true;
			return 0;
	}
	return 0;
}

int StageManager::stg08(){
	if(phase>=0 &&LoadFramework(phase)==1){
		return 1;
	}
	Loading(LoadImg);

	return 0;
}

//��Փx���j���[���[�h
int StageManager::stg80(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\hard.bmp",4,1,4,192,24,PjSys::mHardImg); //���j���[
			if(Setting.General.English){
				mMenuStr[0]="Easier level.#Recommended for newcomers.";
				mMenuStr[1]="The standard level.";
				mMenuStr[2]="Harder level.";
				mMenuStr[3]="Literally INSANE level.#It's very dangerous!";
			}else{
				mMenuStr[0]="�ȒP�ȃ��x���ł��B#�C�y�Ƀv���C���邱�Ƃ��o���܂��B";
				mMenuStr[1]="�W���ƂȂ郌�x���ł��B#��ʓI�ȓ�Փx�ɐݒ肳��Ă��܂��B";
				mMenuStr[2]="�኱��߂̃��x���ł��B#�r�𖁂��������͂ǂ����B";
				mMenuStr[3]="2���ڈȏ��z�肵��##�u�B����Փx�v##�ł��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}
//=======================================
//�t���[�����[�N���[�h
//=======================================
int StageManager::LoadFramework(int phase){
	LoadElements=91;
	switch(phase){
		case 0:
			InitGraph();
			InitSoundMem();
			LoadImg=LoadGraph("img\\loadbg.png");
			ImgLoadStr=LoadGraph("img\\load.bmp");
			return 0;
		case 1:
			LoadDivGraph("img\\num.bmp",10,10,1,16,32,PjSys::MainNum); //����
			return 0;
		case 2:
			LoadDivGraph("img\\char.bmp",7,1,7,98,16,PjSys::MainChar);//����
			return 0;
		case 3:
			LoadDivGraph("img\\num_s.bmp",10,10,1,8,16,PjSys::SmallNum); //�����Ȑ���
			return 0;
		case 4:
			LoadDivGraph("img\\char_s.bmp",8,1,8,64,16,PjSys::SmallChar);//�����ȕ���
			return 0;
		case 5:
			PjSys::Scr::BurstImg=LoadGraph("img\\ring.bmp" );
			return 0;
		case 6:
			side.imgset(LoadGraph( "img\\bgl.bmp" ),LoadGraph( "img\\bgr.bmp" ));
			return 0;
		case 7:
			LoadDivGraph("img\\gaze.bmp" , 16 , 16 , 1 , 16 , 256 , PjSys::Gaze);
			return 0;
		case 8:
			PjSys::GazeFrame=LoadGraph("img\\gaze_frame.bmp");
			return 0;
		case 9:
			PjSys::FPSChar=LoadGraph("img\\fps.bmp");
			return 0;
		case 10:
			PjSys::BuzzCnt=LoadGraph("img\\buzz.bmp");
			return 0;
		case 11:
			LoadDivGraph("img\\char_gaze.bmp" , 2 , 2 , 1 ,32 , 128 , PjSys::GazeChar);
			return 0;
		case 12:
			LoadDivGraph("img\\hard.bmp",4,1,4,192,24,PjSys::mHardImg); //���j���[
			return 0;
		case 13:
			PjSys::ImgNull=LoadGraph("img\\null.bmp");
			return 0;
		case 14:
			LoadDivGraph("img\\noise.bmp",100,10,10,64,48,PjSys::Scr::NoiseImg);
			return 0;
		case 15:
			LoadDivGraph("img\\blt_red.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::RBullet ) ;
			return 0;
		case 16:
			LoadDivGraph("img\\blt_green.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::GBullet ) ;
			return 0;
		case 17:
			LoadDivGraph("img\\blt_blue.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::BBullet ) ;
			return 0;
		case 18:
			LoadDivGraph("img\\lz_red.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::RLaser ) ;
			return 0;
		case 19:
			LoadDivGraph("img\\lz_green.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::GLaser ) ;
			return 0;
		case 20:
			LoadDivGraph("img\\lz_blue.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::BLaser ) ;
			return 0;
		case 21:
			LoadDivGraph("img\\lz_yellow.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::YLaser ) ;
			return 0;
		case 22:
			LoadDivGraph("img\\lz_orange.bmp" , 4 , 4 , 1 , 16 , 16 , Enm::OLaser ) ;
			return 0;
		case 23:
			LoadDivGraph("img\\blt_disappear.bmp" , 16 , 8 , 2 , 32 , 32 , Enm::ImgBltItem ) ;
			return 0;
		case 24:
			LoadDivGraph("img\\exp0.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[0] ) ;
			return 0;
		case 25:
			LoadDivGraph("img\\exp1.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[1] ) ;
			return 0;
		case 26:
			LoadDivGraph("img\\exp2.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[2] ) ;
			return 0;
		case 27:
			LoadDivGraph("img\\exp3.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[3] ) ;
			return 0;
		case 28:
			LoadDivGraph("img\\exp4.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[4] ) ;
			return 0;
		case 29:
			LoadDivGraph("img\\exp5.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[5] ) ;
			return 0;
		case 30:
			LoadDivGraph("img\\exp6.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[6] ) ;
			return 0;
		case 31:
			LoadDivGraph("img\\exp7.bmp" , 16 , 8 , 2 , 96 , 96 , Enm::SmallExplode[7] ) ;
			return 0;
		case 32:
			e1.SndSmallExp=LoadSoundMem("snd\\smallexp.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , e1.SndSmallExp );
			return 0;
		case 33:
			e1.SndBigExp=LoadSoundMem("snd\\bigexp.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , e1.SndBigExp );
			return 0;
		case 34:
			e1.SndBossExp=LoadSoundMem("snd\\bossexp.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , e1.SndBossExp );
			return 0;
		case 35:
			e1.SndHit=LoadSoundMem("snd\\hit.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , e1.SndHit );
			return 0;
		case 36:
			Enm::SndBuzz=LoadSoundMem("snd\\buzz.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , Enm::SndBuzz );
			return 0;
		case 37:
			Enm::SndRef=LoadSoundMem( "snd\\reflect.wav" ) ;
			ChangeVolumeSoundMem(Setting.General.SEVolume , Enm::SndRef);
			return 0;
		case 38:
			Enm::SndShot=LoadSoundMem( "snd\\enmshot.wav" ) ;
			ChangeVolumeSoundMem(Setting.General.SEVolume , Enm::SndShot );
			return 0;
		case 39:
			My::Model=MV1LoadModel( "img\\player2.mv1" ) ;
			return 0;
		case 40:
			My::burner=MV1LoadModel( "img\\ab.mv1" );
			for(int i=0; i<MV1GetMaterialNum( My::burner ); i++){
				MV1SetMaterialDrawBlendMode( My::burner, i, DX_BLENDMODE_ADD);
				MV1SetMaterialDrawBlendParam( My::burner, i, 255 );
			}
			return 0;
		case 41:
			InvImg=LoadGraph("img\\inv.bmp");
			return 0;
		case 42:
			My::Item::SndGet=LoadSoundMem( "snd\\item.wav" ) ;
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::Item::SndGet );
			return 0;
		case 43:
			GOimg=LoadGraph("img\\gover.bmp");
			return 0;
		case 44:
			PauseImg=LoadGraph("img\\pause.bmp");
			return 0;
		case 45:
			gPlayer.pbStraight[0].imgset(LoadGraph("img\\pbullet.bmp"))	;
			return 0;
		case 46:
			gPlayer.pbStraight[1].imgset(LoadGraph("img\\pbullet.bmp"))	;
			return 0;
		case 47:
			gPlayer.pbStraight[2].imgset(LoadGraph("img\\pbullet.bmp"))	;
			return 0;
		case 48:
			gPlayer.pbStraight[3].imgset(LoadGraph("img\\pbullet_w.bmp"))	;
			return 0;
		case 49:
			gPlayer.pbStraight[4].imgset(LoadGraph("img\\pbullet_w.bmp"))	;
			return 0;
		case 50:
			LoadDivGraph("img\\pbeffg.bmp" , 8 , 8 , 1 , 48 , 48 , My::Bullet::EffImg[1] );
			return 0;
		case 51:
			My::Laser::img=LoadGraph("img\\pb_lz.bmp");
			return 0;
		case 52:
			LoadDivGraph("img\\pbeff.bmp" , 8 , 8 , 1 , 48 , 48 , My::Bullet::EffImg[0] );
			return 0;
		case 53:
			My::imgRegion=LoadGraph("img\\ziki_region.bmp");
			return 0;
		case 54:
			My::imgLeftTimeGaze=LoadGraph("img\\gaze_s.bmp");
			return 0;
		case 55:
			My::Born=true;
			return 0;
		case 56:
			My::SubEnergy=0;
			return 0;
		case 57:
			My::SubLevel=0;
			return 0;
		case 58:
			gPlayer.SndDead=LoadSoundMem("snd\\dead.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , gPlayer.SndDead );
			return 0;
		case 59:
			gPlayer.SndBorn=LoadSoundMem("snd\\born.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , gPlayer.SndBorn );
			return 0;
		case 60:
			gPlayer.SndShoot=LoadSoundMem("snd\\shoot.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , gPlayer.SndShoot );
			return 0;
		case 61:
			My::SndBomb=LoadSoundMem("snd\\bomb.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::SndBomb );
			return 0;
		case 62:
			My::SndExtend=LoadSoundMem("snd\\extend.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::SndExtend);
			return 0;
		case 63:
			My::sw::sndLv[0]=LoadSoundMem("snd\\lv1.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::sw::sndLv[0] );
			return 0;
		case 64:
			My::sw::sndLv[1]=LoadSoundMem("snd\\lv2.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::sw::sndLv[1] );
			return 0;
		case 65:
			My::sw::sndLv[2]=LoadSoundMem("snd\\lv3.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::sw::sndLv[2] );
			return 0;
		case 66:
			My::sw::sndLv[3]=LoadSoundMem("snd\\lv4.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::sw::sndLv[3] );
			return 0;
		case 67:
			My::sw::sndLv[4]=LoadSoundMem("snd\\lvmax.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::sw::sndLv[4] );
			return 0;
		case 68:
			My::SndBombExtend=LoadSoundMem("snd\\bombextend.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::SndBombExtend );
			return 0;
		case 69:
			gPlayer.SndDefS=LoadSoundMem("snd\\def_start.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , gPlayer.SndDefS );
			return 0;
		case 70:
			gPlayer.SndDefE=LoadSoundMem("snd\\def_end.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , gPlayer.SndDefE );
			return 0;
		case 71:
			warnimg=LoadGraph("img\\warn.bmp"); //Warning��ʂ̃��[�h
			return 0;
		case 72:
			warnmov=LoadGraph("img\\warn.avi");
			return 0;
		case 73:
			SndAlarm=LoadSoundMem("snd\\alarm.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , SndAlarm );
			return 0;
		case 74:
			My::Item::exp[0]=0.004f;
			return 0;
		case 75:
			My::Item::GeneralImg[0]=MV1LoadModel( "img\\item_point_s.mv1" ) ;
			return 0;
		case 76:
			My::Item::exp[1]=0.005f;
			return 0;
		case 77:
			My::Item::GeneralImg[1]=MV1LoadModel( "img\\item_point_m.mv1" ) ;
			return 0;
		case 78:
			My::Item::exp[2]=0.006f;
			My::Item::GeneralImg[2]=MV1LoadModel( "img\\item_point_l.mv1" ) ;
			return 0;
		case 79:
			My::Item::exp[3]=0.006f;
			My::Item::GeneralImg[3]=MV1LoadModel( "img\\item_lvup.mv1" ) ;
			return 0;
		case 80:
			My::Item::exp[4]=0.005f;
			My::Item::GeneralImg[4]=MV1LoadModel( "img\\item_lvm.mv1" ) ;
			return 0;
		case 81:
			My::Item::exp[5]=0.007f;
			My::Item::GeneralImg[5]=MV1LoadModel( "img\\item_bomb.mv1" ) ;
			return 0;
		case 82:
			My::Item::exp[6]=0.007f;
			My::Item::GeneralImg[6]=MV1LoadModel( "img\\item_stock.mv1" ) ;
			return 0;
		case 83:
			My::Item::exp[7]=0.007f;
			My::Item::GeneralImg[7]=MV1LoadModel( "img\\item_secret.mv1" ) ;
			return 0;
		case 84:
			//PjSys::Scr::imgFlare=LoadGraph("img\\flare.bmp");
			return 0;
		case 85:
			My::imgBuzz=LoadGraph("img\\buzzflare.bmp");
			return 0;
		case 86:
			Enm::FireFlare=LoadGraph("img\\blt_launch.bmp");
			return 0;
		case 87:
			My::Laser::ShotSnd=LoadSoundMem("snd\\laser.wav");
			ChangeVolumeSoundMem(Setting.General.SEVolume , My::Laser::ShotSnd );
			return 0;
		case 88:
			LoadDivGraph("img\\laser_hit.bmp",16,8,2,48,48,My::Laser::hitimg);
			return 0;
		case 89:
			LoadDivGraph("img\\pbfire.bmp",8,8,1,32,32,My::Bullet::pbFire[0]);
			return 0;
		case 90:
			LoadDivGraph("img\\pbfireg.bmp",8,8,1,32,32,My::Bullet::pbFire[1]);
			LoadDivGraph("img\\afterburner.bmp",4,4,1,32,32,Enm::imgAB);
			//LoadDivGraph("img\\fire.bmp",16,16,1,32,32,Enm::imgBurn);

			DeleteGraph(LoadImg);
			DeleteGraph(ImgLoadStr);

			LoadElements=0;
			return 1;
		//����:���[�h�t�@�C����ǉ������ۂ�LoadElements������������̂�Y��Ȃ����I
	}
	return -1;
}

//�Q�[����Փx�I��
int StageManager::stg81(){
	int n;
	static int Warning=0;
	if(PjSys::ShowInsane==true){
		n=Menu(PjSys::mHardImg,mMenuStr,3);
	}else{
		n=Menu(PjSys::mHardImg,mMenuStr,2);
	}
	switch(n){
		case -2:
			stage=0x00;
			return 0;
		case -1:
			return 0;
		case 0:
			PjSys::Hard=6;
			PjSys::HardConst=PjSys::Hard;
			PjSys::GameLevel=3;
			break;
		case 1:
			PjSys::Hard=4;
			PjSys::HardConst=PjSys::Hard;
			PjSys::GameLevel=2;
			break;
		case 2:
			PjSys::Hard=2;
			PjSys::HardConst=PjSys::Hard;
			PjSys::GameLevel=1;
			break;
		case 3:
			if(Setting.General.English==1){
				Window.SetString("#- WARNING -##This difficulty is literally#\"insane\" one.#Therefore, you have to prepare to#endure any outrageous violence.#Do you dare to try?",Window.DialogYesNo);
				Window.SetDialogString("< Abort >",0);
				Window.SetDialogString("< Continue >",1);
			}else{
				Window.SetString("#- �x�� -##���̓�Փx�́A���̓�Փx�Ƒ啝�ɈقȂ�A#�����ʂ�u���C���݂��v��Փx��#�Ȃ��Ă���܂��B#�̂ɁA�����Ȃ�����ŗ��s�s�Ȗ\�s�ɂ�#�ς���o�傷��K�v������܂��B#��������m�̏�ŁA#���̓�Փx�ɒ��킵�Ă݂܂����H",Window.DialogYesNo);
				Window.SetDialogString("< ��߂� >",0);
				Window.SetDialogString("< �Â��� >",1);
			}
			Window.SetFlag();
			SelectedNo=3;
			Warning=1;
			return 0;
		case 0x10:
			return 0;
		case 0x11:
			if(Warning==1){
				PjSys::Hard=2;
				PjSys::HardConst=PjSys::Hard;
				PjSys::GameLevel=0;
			}
			break;
	}
	//stage=0x10;
	My::CalcSubEnergyMax(); //�T�u�E�F�|���Q�[�W�̍ő�l������
	return 1;
}

//�Z�b�e�B���O���j���[���[�h
int StageManager::stg90(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\msetting0.bmp",5,1,5,256,24,mMenuImg); //���j���[
			//bg.imgset(LoadGraph( "img\\bg_mesh.bmp" ),LoadGraph( "img\\bg_mesh.bmp" ),1);
			if(Setting.General.English){
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): Accept / %KEY_SUB%(%PAD_SUB%): Cancel / %KEY_BOMB%(%PAD_BOMB%): Instructions");
				mMenuStr[0]="Configuration 1.";
				mMenuStr[1]="Configuration 2.";
				mMenuStr[2]="Change assignment of#a keyboard and a gamepad.";
				mMenuStr[3]="(Unimplemented)#Set whether assign a button#to player's laser.";
				mMenuStr[4]="Return to the main menu.";
			}else{
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): ���� / %KEY_SUB%(%PAD_SUB%): �L�����Z�� / %KEY_BOMB%(%PAD_BOMB%): ����");
				mMenuStr[0]="�ݒ�1:#��ʕ\���Ȃǂ̐ݒ���s���܂��B#�ݒ�ύX��ċN�����K�v�ɂȂ���̂�����܂��B";
				mMenuStr[1]="�ݒ�2:#�T�E���h�⃍�[�h�Ɋւ���ݒ���s���܂��B";
				mMenuStr[2]="�L�[��Q�[���p�b�h�̊�����ύX���܂��B#�Ȃ��A�L�[�R���t�B�O���͏I���L�[��#�L�����Z���L�[�������ƂȂ�܂��B";
				mMenuStr[3]="(������)#���@�̃��[�U�[���˂Ƀ{�^����#���蓖�Ă邩�ݒ肵�܂��B";
				mMenuStr[4]="���C�����j���[�ɖ߂�܂��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}

//�Z�b�e�B���O���j���[�{��
int StageManager::stg91(){
	int n=Menu(mMenuImg,mMenuStr,2);
	switch(n){
		case -2:
			setstage(0x0);
			return 0;
		case 0:
			setstage(0x96);
			return 0;
		case 1:
			setstage(0x98);
			return 0;
		case 2:
			setstage(0x92);
			return 0;
		case 3:
			setstage(0x94);
			return 0;
/*		case 4:
			setstage(0x00);
			return 0;
			*/
	}
	return 0;
}

//�L�[�R���t�B�O�P���[�h
int StageManager::stg92(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\mkeyconf1.bmp",7,1,7,400,24,mMenuImg); //���j���[
			//bg.imgset(LoadGraph( "img\\bg_mesh.bmp" ),LoadGraph( "img\\bg_mesh.bmp" ),1);
			if(Setting.General.English){
				mOperateStr="Any key or button: Change assignment of a button selected";
				mMenuStr[0]="Change [Shot] button.";
				mMenuStr[1]="Change [Defender] button. ";
				mMenuStr[2]="Change [Bomb] button.";
				mMenuStr[3]="Change [Slow Down] button.";
				mMenuStr[4]="Change [Pause] button.";
				mMenuStr[5]="Change [Exit] button.";
				mMenuStr[6]="Return to the configuration menu.";
			}else{
				mOperateStr="�C�ӂ̃L�[��{�^��: �I�����ꂽ���ڂ̊����ύX";
				mMenuStr[0]="�V���b�g�{�^����ύX���܂��B";
				mMenuStr[1]="�f�B�t�F���_�[�{�^����ύX���܂��B";
				mMenuStr[2]="�{���{�^����ύX���܂��B";
				mMenuStr[3]="���x�ቺ�{�^����ύX���܂��B";
				mMenuStr[4]="�|�[�Y�{�^����ύX���܂��B";
				mMenuStr[5]="�����I���{�^����ύX���܂��B";
				mMenuStr[6]="�ݒ胁�j���[�ɖ߂�܂��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}

//�L�[�R���t�B�O�P�`��
int StageManager::stg93(){
	int n=Menu(mMenuImg,mMenuStr,6);
	if(Window.GetStatus()==-1){return 0;}
	int btn=0;
	int ky=0;
	static int fnt=CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	for(int i=0;i<6;i++){
		switch(i){
			case 0:
				btn=PjSys::key::shot_p;
				ky=PjSys::key::shot;
				break;
			case 1:
				btn=PjSys::key::sub_p;
				ky=PjSys::key::sub;
				break;
			case 2:
				btn=PjSys::key::bomb_p;
				ky=PjSys::key::bomb;
				break;
			case 3:
				btn=PjSys::key::slow_p;
				ky=PjSys::key::slow;
				break;
			case 4:
				btn=PjSys::key::pause_p;
				ky=PjSys::key::pause;
				break;
			case 5:
				btn=PjSys::key::exit_p;
				ky=PjSys::key::exit;
				break;
		}
		cfunc::KeyInt2Chr(ky);
		DrawFormatStringToHandle( 300 , 230+32*i , (i==SelectedNo)?GetColor(255,127,127):GetColor(255,255,255) ,fnt , cfunc::KeyName.c_str() , 0, true) ;
		(i==SelectedNo)?SetDrawBright(255,127,127):SetDrawBright(255,255,255);
		PjSys::NumDraw(PjSys::MainNum,(unsigned)cfunc::KeyInt2PadNo(btn),450,230+32*i,16);
		if(i==SelectedNo){SetDrawBright(255,255,255);}
	}
		DrawFormatStringToHandle( 300 , 200 , GetColor(255,255,127),fnt , "KEYBOARD" , 0, true) ;
		DrawFormatStringToHandle( 450 , 200 , GetColor(255,255,127) ,fnt , "GAMEPAD" , 0, true) ;
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		DrawLine(290,220,570,220,GetColor(127,127,127),1);
		DrawLine(290,220,290,416,GetColor(127,127,127),1);
		DrawLine(440,220,440,416,GetColor(127,127,127),1);
		DrawLine(120,416,570,416,GetColor(127,127,127),1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	switch(n){
	case 0x10:
		//����������
		return 0;
		case -2:
			stage=0x90;
			return 0;
		case -1:
			return 0;
		case 6:
			return 1;
	}

	//stage=0x10;
	return 0;
}

void StageManager::KeyConfig1(){ //�L�[�R���t�B�O���g
		//�����ɃL�[�A�W���X�g����
		int pBtn=cfunc::WhichButtonPressed();
		if(pBtn!=0){
			if(SelectKey[2]==0){
				switch(SelectedNo){
					case 0:
						PjSys::key::shot_p=pBtn;
						break;
					case 1:
						PjSys::key::sub_p=pBtn;
						break;
					case 2:
						PjSys::key::bomb_p=pBtn;
						break;
					case 3:
						PjSys::key::slow_p=pBtn;
						break;
					case 4:
						PjSys::key::pause_p=pBtn;
						break;
					case 5:
						PjSys::key::exit_p=pBtn;
						break;
				}
				PlaySoundMem(SndOK,DX_PLAYTYPE_BACK);
				PjSys::key::save();
				SelectKey[2]=1;
			}
		}else{SelectKey[2]=0;}
		//�L�[�{�[�h�̃A�W���X�g����
		int pKey=cfunc::WhichKeyPressed();
		if(pKey!=0){
			if(SelectKey[3]==0){
				switch(SelectedNo){
					case 0:
						PjSys::key::shot=pKey;
						break;
					case 1:
						PjSys::key::sub=pKey;
						break;
					case 2:
						PjSys::key::bomb=pKey;
						break;
					case 3:
						PjSys::key::slow=pKey;
						break;
					case 4:
						PjSys::key::pause=pKey;
						break;
					case 5:
						PjSys::key::exit=pKey;
						break;
				}
				PlaySoundMem(SndOK,DX_PLAYTYPE_BACK);
				PjSys::key::save();
				SelectKey[3]=1;
			}
		}else{SelectKey[3]=0;}
}
void StageManager::KeyConfig2(){ //�L�[�R���t�B�O2���g
	if(PjSys::key::UseLaser){ //���[�U�[�ɃL�[�����蓖�Ă�H
		//�����ɃL�[�A�W���X�g����
		int pBtn=cfunc::WhichButtonPressed();
		if(pBtn!=0){
			if(SelectKey[2]==0 || SelectedNo == 1){
				PjSys::key::laser_p=pBtn;
				PlaySoundMem(SndOK,DX_PLAYTYPE_BACK);
				PjSys::key::save();
				SelectKey[2]=1;
			}
		}else{SelectKey[2]=0;}
		//�L�[�{�[�h�̃A�W���X�g����
		int pKey=cfunc::WhichKeyPressed();
		if(pKey!=0){
			if(SelectKey[3]==0){
				PjSys::key::laser=pKey;
				PlaySoundMem(SndOK,DX_PLAYTYPE_BACK);
				PjSys::key::save();
				SelectKey[3]=1;
			}
		}else{SelectKey[3]=0;}
	}
}

//�L�[�R���t�B�O2���[�h
int StageManager::stg94(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\mkeyconf2.bmp",4,1,4,400,24,mMenuImg); //���j���[
			//bg.imgset(LoadGraph( "img\\bg_mesh.bmp" ),LoadGraph( "img\\bg_mesh.bmp" ),1);
			if(Setting.General.English){
				mOperateStr=cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): Save and back / %KEY_SUB%(%PAD_SUB%): Cancel / %KEY_BOMB%(%PAD_BOMB%): Instructions");
				mMenuStr[0]="Set whether assign a button#to the player's laser.";
				mMenuStr[1]="Change [Laser] button. ";
				mMenuStr[2]="Reset the key configulation to the default.";
				mMenuStr[3]="Return to the configuration menu.";
			}else{
				mOperateStr=cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): �ۑ����Ė߂� / %KEY_SUB%(%PAD_SUB%): �L�����Z�� / %KEY_BOMB%(%PAD_BOMB%): ����");
				mMenuStr[0]="���@�̃��[�U�[�Ƀ{�^�������蓖�Ă邩#�ݒ肵�܂��B";
				mMenuStr[1]="���[�U�[�{�^����ύX���܂��B";
				mMenuStr[2]="�L�[��{�^���̊��蓖�Ă��f�t�H���g��#���Z�b�g���܂��B#�u!Set!�v�̈ʒu�ɐݒ肵�A�ۑ������#���Z�b�g����܂��B";
				mMenuStr[3]="�ݒ胁�j���[�ɖ߂�܂��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}

//�L�[�R���t�B�O2�`��
int StageManager::stg95(){
	static const string_t OpStr(mOperateStr);
	static const string_t KeyOpStr((Setting.General.English==1)?"Any key/button: Change the assignment.":"�C�ӂ̃L�[��{�^��: �����̕ύX");
	if(SelectedNo==1){
		mOperateStr=KeyOpStr;
	}else{
		mOperateStr=OpStr;
	}
	int n=Menu(mMenuImg,mMenuStr,3);
	if(Window.GetStatus()==-1){return 0;}
	int btn=0;
	int ky=0;
	static const int fnt = CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	static int LeftKey=0;
	static int RightKey=0;
	static int SetDefault=0;
	string_t Caption("0000000000");
	bool LeftAvaliable=false;
	bool RightAvaliable=false;
	bool Left=false;
	bool Right=false;
	//DrawStringToHandle( 300 , 230+32*i , (i==SelectedNo)?GetColor(255,127,127):GetColor(255,255,255) ,PjSys::font::caption , cfunc::KeyName.c_str() , 0, true) ;
	//(i==SelectedNo)?SetDrawBright(255,127,127):SetDrawBright(255,255,255);

	//����������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)!=0){
		LeftKey++;
		if(LeftKey<30){
			if(LeftKey==1){
				Left=true;
			}else{
				Left=false;
			}
		}else{
			if(LeftKey%2==0){
				Left=true;
			}
		}
	}else{
		LeftKey=0;
		Left=false;
	}

	//�E��������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)!=0){
		RightKey++;
		if(RightKey<30){
			if(RightKey==1){
				Right=true;
			}else{
				Right=false;
			}
		}else{
			if(RightKey%2==0){
				Right=true;
			}
		}
	}else{
		RightKey=0;
		Right=false;
	}
	string_t Key("KEY: " + cfunc::KeyName );
	int col=GetColor(127,127,127);

	for(int i=0;i<3;i++){
		switch(i){
			case 0:
				//Assignment for Laser
				if(PjSys::key::UseLaser){
					LeftAvaliable=true; //���Z�\
					RightAvaliable=false;//���Z�s�\
					if(Left && i==SelectedNo){PjSys::key::UseLaser=false;}
					Caption="On";
				}else{
					LeftAvaliable=false; //���Z�s��
					RightAvaliable=true;//���Z�\
					if(Right && i==SelectedNo){PjSys::key::UseLaser=true;}
					Caption="Off";
				}

				break;
			case 1:
				//Laser_Key
				btn=PjSys::key::laser_p;
				ky=PjSys::key::laser;
				cfunc::KeyInt2Chr(ky);
				if(PjSys::key::UseLaser){
					if(i==SelectedNo){
						col=GetColor(255,127,127);
					}else{
						col=GetColor(255,255,255);
					}
				}
				DrawStringToHandle( 350 , 230+32*i ,Key.c_str(), col ,fnt) ;
				DrawStringToHandle( 500 , 230+32*i ,"/ PAD: ", col ,fnt) ;

				SetDrawBright(127,127,127);
				if(PjSys::key::UseLaser){
					if(i==SelectedNo){
						SetDrawBright(255,127,127);
					}else{
						SetDrawBright(255,255,255);
					}
				}
				PjSys::NumDraw(PjSys::MainNum,(unsigned)cfunc::KeyInt2PadNo(btn),580,230+32*i,16);
				SetDrawBright(255,255,255);

				break;
			case 2:
				//Default
				if(SetDefault==0){
					LeftAvaliable=false; //���Z�\
					RightAvaliable=true;//���Z�s�\
					if(Right && i==SelectedNo){SetDefault++;}
					Caption="Don't";
				}else if(SetDefault==2){
					LeftAvaliable=true; //���Z�s��
					RightAvaliable=false;//���Z�\
					if(Left && i==SelectedNo){SetDefault--;}
					Caption="!Set!";
				}else{
					LeftAvaliable=true; //���Z�\
					RightAvaliable=true;//���Z�\
					if(Left && i==SelectedNo){SetDefault--;}
					if(Right && i==SelectedNo){SetDefault++;}
					Caption="Sure?";
				}
				break;
		}
		if(i==0 || i==2){
			if(i==SelectedNo){
				if(LeftAvaliable){
					Caption="<< "+Caption;
				}else{
					Caption="   "+Caption;
				}
				if(RightAvaliable){Caption+=" >>";}
				DrawStringToHandle(500,230+i*32,Caption.c_str(),GetColor(255,127,127),fnt);
			}else{
				Caption="   "+Caption;
				DrawStringToHandle(500,230+i*32,Caption.c_str(),GetColor(255,255,255),fnt);
			}
		}
	}

	switch(n){
	case 0x10:
		return 0;
	case -2:
		stage=0x90;
		PjSys::key::load();
		return 0;
	case -1:
		return 0;
	default:
		if(SetDefault==2){
			PjSys::key::init();//������
		}
		PjSys::key::save();
		return 1;
	}

	//stage=0x10;
	return 0;
}

//�ݒ�P���[�h
int StageManager::stg96(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\msetting1.bmp",7,1,7,400,24,mMenuImg); //���j���[
			//bg.imgset(LoadGraph( "img\\bg_mesh.bmp" ),LoadGraph( "img\\bg_mesh.bmp" ),1);
			if(Setting.General.English){
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): Save and back / %KEY_SUB%(%PAD_SUB%): Cancel / %KEY_BOMB%(%PAD_BOMB%): Instructions");
				mMenuStr[0]="Set if window-mode or full-screen.#Reboot to apply.";
				mMenuStr[1]="Set color bit.#16bit mode is lighter but#inferior in quality.#Reboot to apply.";
				mMenuStr[2]="Set if the vertical sync is valid.#It is recommended to setting \"On\".#Reboot to apply.";
				mMenuStr[3]="Set the language.#You can choose Japanese or English.";
				mMenuStr[4]="Set if the game pad's vibration is#available.";
				mMenuStr[5]="Set the anti-aliasing, which makes#a little beauty but heavy.#Reboot to apply.";
				mMenuStr[6]="Set all settings to the default.#Be careful!";
			}else{
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): �ۑ����Ė߂� / %KEY_SUB%(%PAD_SUB%): �L�����Z�� / %KEY_BOMB%(%PAD_BOMB%): ����");
				mMenuStr[0]="�E�B���h�E���[�h��L���ɂ��邩#�ݒ肵�܂��B#�ċN����ɓK�p����܂��B";
				mMenuStr[1]="�F�[�x��ݒ肵�܂��B#16bit�͌y���ł����Y�킳�ł͗��܂��B#�ċN����ɓK�p����܂��B";
				mMenuStr[2]="����������L���ɂ��邩��ݒ肵�܂��B#On�𐄏����܂��B#�ċN����ɓK�p����܂��B";
				mMenuStr[3]="�����ݒ肵�܂��B#���{�ꂩ�p�ꂪ�I���ł��܂��B";
				mMenuStr[4]="�p�b�h�̃o�C�u���[�V�����@�\��#�L���ɂ��邩�ݒ肵�܂��B";
				mMenuStr[5]="�A���`�G�C���A�V���O��ݒ肵�܂��B#��������Y��ɂȂ�܂����d���ł��B#�ċN����ɓK�p����܂��B";
				mMenuStr[6]="�S�Ă̐ݒ�����Z�b�g���܂��B#�u!Set!�v�̈ʒu�ɐݒ肵�A�ۑ������#���Z�b�g����܂��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}

//�ݒ�P�`��
int StageManager::stg97(){
	int n=Menu(mMenuImg,mMenuStr,6);
	if(Window.GetStatus()==-1){return 0;}

	static int LeftKey=0;
	static int RightKey=0;
	static int fnt=CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	static int SetDefault=0;
	string_t Caption("0000000000");
	bool LeftAvaliable=false;
	bool RightAvaliable=false;
	bool Left=false;
	bool Right=false;
	//DrawStringToHandle( 300 , 230+32*i , (i==SelectedNo)?GetColor(255,127,127):GetColor(255,255,255) ,PjSys::font::caption , cfunc::KeyName.c_str() , 0, true) ;
	//(i==SelectedNo)?SetDrawBright(255,127,127):SetDrawBright(255,255,255);

	//����������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)!=0){
		LeftKey++;
		if(LeftKey<30){
			if(LeftKey==1){
				Left=true;
			}else{
				Left=false;
			}
		}else{
			if(LeftKey%2==0){
				Left=true;
			}
		}
	}else{
		LeftKey=0;
		Left=false;
	}

	//�E��������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)!=0){
		RightKey++;
		if(RightKey<30){
			if(RightKey==1){
				Right=true;
			}else{
				Right=false;
			}
		}else{
			if(RightKey%2==0){
				Right=true;
			}
		}
	}else{
		RightKey=0;
		Right=false;
	}
	for(int i=0;i<7;i++){
		Caption="";
		LeftAvaliable=false;
		RightAvaliable=false;
		switch(i){
		case 0:
			//Window
			if(Setting.General.Window==1){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.Window=0;}
				Caption="On";
			}else{
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.Window=1;}
				Caption="Off";
			}
			break;
		case 1:
			//Color Bit;
			if(Setting.General.ColorBit==16){
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z��
				if(Right && i==SelectedNo){Setting.General.ColorBit=32;}
				Caption="16 bit";
			}else{
				LeftAvaliable=true; //���Z��
				RightAvaliable=false;//���Z�s��
				if(Left && i==SelectedNo){Setting.General.ColorBit=16;}
				Caption="32 bit";
			}

			break;
		case 2:
			//VSync
			if(Setting.General.VSync==1){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.VSync=0;}
				Caption="On";
			}else{
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.VSync=1;}
				Caption="Off";
			}
			break;
		case 3:
			//Language
			if(Setting.General.English==1){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.English=0;}
				Caption="English";
			}else{
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.English=1;}
				Caption="���{��";
			}
			break;
		case 4:
			//Vibration
			if(Setting.General.UseVibration==1){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.UseVibration=0;}
				Caption="On";
			}else{
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.UseVibration=1;}
				Caption="Off";
			}
			break;
		case 5:
			if(Setting.General.AntiAliasing==3){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.AntiAliasing--;}
				Caption="3(Max)";
			}else if(Setting.General.AntiAliasing==0){
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.AntiAliasing++;}
				Caption="0(Off)";
			}else{
				LeftAvaliable=true; //���Z�\
				RightAvaliable=true;//���Z�\
				if(Left && i==SelectedNo){Setting.General.AntiAliasing--;}
				if(Right && i==SelectedNo){Setting.General.AntiAliasing++;}

				Caption=boost::lexical_cast<string_t>(Setting.General.AntiAliasing);
			}
			break;
		case 6:
			if(SetDefault==0){
				LeftAvaliable=false; //���Z�\
				RightAvaliable=true;//���Z�s�\
				if(Right && i==SelectedNo){SetDefault++;}
				Caption="Don't";
			}else if(SetDefault==2){
				LeftAvaliable=true; //���Z�s��
				RightAvaliable=false;//���Z�\
				if(Left && i==SelectedNo){SetDefault--;}
				Caption="!Set!";
			}else{
				LeftAvaliable=true; //���Z�\
				RightAvaliable=true;//���Z�\
				if(Left && i==SelectedNo){SetDefault--;}
				if(Right && i==SelectedNo){SetDefault++;}
				Caption="Sure?";
			}

			break;
		}
		if(i==SelectedNo){
			if(LeftAvaliable){
				Caption="<< "+Caption;
			}else{
				Caption="   "+Caption;
			}
			if(RightAvaliable){Caption+=" >>";}
			DrawStringToHandle(400,230+i*32,Caption.c_str(),GetColor(255,127,127),fnt);
		}else{
			Caption="   "+Caption;
			DrawStringToHandle(400,230+i*32,Caption.c_str(),GetColor(255,255,255),fnt);
		}
	}

	//�����ꂽ�L�[�ɂ�镪��
	switch(n){
	case 0x10:
		//����������
		return 0;

	case -2:
		//�L�����Z��
		stage=0x90;
		Setting.load();
		return 0;

	case -1:
		//�����N����񂩂���
		return 0;
	default:
		if(SetDefault==2){
			Setting.init();
			SetDefault=0;
		}
		Setting.save();
		return 1;
	}

	return 0;
}

//�ݒ�2���[�h
int StageManager::stg98(){
	switch(phase){
		case 0:
			LoadDivGraph("img\\msetting2.bmp",5,1,5,400,24,mMenuImg); //���j���[
			//bg.imgset(LoadGraph( "img\\bg_mesh.bmp" ),LoadGraph( "img\\bg_mesh.bmp" ),1);
			if(Setting.General.English){
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): Save and back / %KEY_SUB%(%PAD_SUB%): Cancel / %KEY_BOMB%(%PAD_BOMB%): Instructions");
				mMenuStr[0]="Set BGM volume from 0(Mute)#to 255(Max).";
				mMenuStr[1]="Set SE volume from 0(Mute)#to 255(Max).";
				mMenuStr[2]="Set the load mode.#---#0: Load: Slow#   Using Memory: High#   Using CPU: Low#2: Load: Middle#   Using Memory: Middle#   Using CPU: Middle#3: Load: Fast#   Using Memory: Low#   Using CPU: High";
				mMenuStr[3]="Set if sounds are handled by#software.#Set \"On\" ONLY if something is#wrong!";
				mMenuStr[4]="Reset the ranking. Be careful!";
			}else{
				mOperateStr = cfunc::ReplaceKeyNameAll("%KEY_SHOT%(%PAD_SHOT%): �ۑ����Ė߂� / %KEY_SUB%(%PAD_SUB%): �L�����Z�� / %KEY_BOMB%(%PAD_BOMB%): ����");
				mMenuStr[0]="BGM�̉��ʂ�0(�~���[�g)����#c255(�ő�)�̊ԂŕύX���܂��B";
				mMenuStr[1]="SE�̉��ʂ�0(�~���[�g)����#255(�ő�)�̊ԂŕύX���܂��B";
				mMenuStr[2]="���[�h���[�h��ݒ肵�܂��B#���[�h���ԁE�������g�p�ʁE�Q�[������#CPU���ׂ��ς��܂��B#�ǂꂪ�ǂ�����PC�̃X�y�b�N���ɂ��̂ŁA#�ݒ肷����͉��̐������Q�l�ɂ��ĉ������B#(�f�t�H���g��2)#---#0: ���[�h-�x �������g�p-�� CPU����-��#2: ���[�h-�� �������g�p-�� CPU����-��#3: ���[�h-�� �������g�p-�� CPU����-��";
				mMenuStr[3]="�T�E���h�֌W���\�t�g�E�F�A���ŏ������邩#���肵�܂��B#������肪����ꍇ�̂�On�ɂ��ĉ������B";
				mMenuStr[4]="�����L���O�����ׂă��Z�b�g���܂��B#�u!Set!�v�̈ʒu�ɐݒ肵�A�ۑ������#���Z�b�g����܂��B";
			}
			//stage=0x81;
			return 1;
			//break;
	}
	Loading(LoadImg);
	return 0;
}

//�ݒ�Q�`��
int StageManager::stg99(){
	int n=Menu(mMenuImg,mMenuStr,4);
	if(Window.GetStatus()==-1){return 0;}

	static int LeftKey=0;
	static int RightKey=0;
	static int fnt=CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	static int RankReset=0;
	string_t Caption("0000000000");
	string_t Caption2("(Read Instructions)");
	if(Setting.General.English==0){Caption2="(�����Q��)";}
	bool LeftAvaliable=false;
	bool RightAvaliable=false;
	bool Left=false;
	bool Right=false;
	//DrawStringToHandle( 300 , 230+32*i , (i==SelectedNo)?GetColor(255,127,127):GetColor(255,255,255) ,PjSys::font::caption , cfunc::KeyName.c_str() , 0, true) ;
	//(i==SelectedNo)?SetDrawBright(255,127,127):SetDrawBright(255,255,255);

	//����������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)!=0){
		LeftKey++;
		if(LeftKey<30){
			if(LeftKey==1){
				Left=true;
			}else{
				Left=false;
			}
		}else{
			if(LeftKey%2==0){
				Left=true;
			}
		}
	}else{
		LeftKey=0;
		Left=false;
	}

	//�E��������Ă���H
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)!=0){
		RightKey++;
		if(RightKey<30){
			if(RightKey==1){
				Right=true;
			}else{
				Right=false;
			}
		}else{
			if(RightKey%2==0){
				Right=true;
			}
		}
	}else{
		RightKey=0;
		Right=false;
	}
	for(int i=0;i<7;i++){
		Caption="";
		LeftAvaliable=false;
		RightAvaliable=false;
		switch(i){
		case 0:
			//BGM Volume
			if(Setting.General.BGMVolume==255){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.BGMVolume--;}
				Caption="255(Max, Default)";
			}else if(Setting.General.BGMVolume==0){
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.BGMVolume++;}
				Caption="0(Mute)";
			}else{
				LeftAvaliable=true; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.BGMVolume++;}
				if(Left && i==SelectedNo){Setting.General.BGMVolume--;}
				Caption=boost::lexical_cast<string_t>(Setting.General.BGMVolume);
			}
			break;
		case 1:
			//SE Volume
			if(Setting.General.SEVolume==255){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.SEVolume--;}
				Caption="255(Max, Default)";
			}else if(Setting.General.BGMVolume==0){
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.SEVolume++;}
				Caption="0(Mute)";
			}else{
				LeftAvaliable=true; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.SEVolume++;}
				if(Left && i==SelectedNo){Setting.General.SEVolume--;}
				Caption=boost::lexical_cast<string_t>(Setting.General.SEVolume);
			}
			break;
		case 2:
			//LoadMode
			switch(Setting.General.LoadMode){
			case 0:
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.LoadMode=2;}
				Caption="0"+Caption2;
				break;
			case 1:
				LeftAvaliable=true; //���Z��
				RightAvaliable=true;//���Z�\
				if(Left && i==SelectedNo){Setting.General.LoadMode=0;}
				if(Right && i==SelectedNo){Setting.General.LoadMode=2;}
				Caption="1(Not Recommended!)";
				break;

			case 2:
				LeftAvaliable=true; //���Z��
				RightAvaliable=true;//���Z�\
				if(Left && i==SelectedNo){Setting.General.LoadMode=0;}
				if(Right && i==SelectedNo){Setting.General.LoadMode=3;}
				Caption="2"+Caption2;
				break;
			case 3:
				LeftAvaliable=true; //���Z��
				RightAvaliable=false;//���Z�s��
				if(Left && i==SelectedNo){Setting.General.LoadMode=2;}
				Caption="3"+Caption2;
				break;
			default:
				Setting.General.LoadMode=2;
				break;
			}
			break;
		case 3:
			//Software Sound
			if(Setting.General.SoftwareSound==1){
				LeftAvaliable=true; //���Z�\
				RightAvaliable=false;//���Z�s�\
				if(Left && i==SelectedNo){Setting.General.SoftwareSound=0;}
				Caption="On";
			}else{
				LeftAvaliable=false; //���Z�s��
				RightAvaliable=true;//���Z�\
				if(Right && i==SelectedNo){Setting.General.SoftwareSound=1;}
				Caption="Off";
			}
			break;
		case 4:
			if(RankReset==0){
				LeftAvaliable=false; //���Z�\
				RightAvaliable=true;//���Z�s�\
				if(Right && i==SelectedNo){RankReset++;}
				Caption="Don't";
			}else if(RankReset==2){
				LeftAvaliable=true; //���Z�s��
				RightAvaliable=false;//���Z�\
				if(Left && i==SelectedNo){RankReset--;}
				Caption="!Reset!";
			}else{
				LeftAvaliable=true; //���Z�\
				RightAvaliable=true;//���Z�\
				if(Left && i==SelectedNo){RankReset--;}
				if(Right && i==SelectedNo){RankReset++;}
				Caption="Sure?";
			}

			break;
		}
		if(i==SelectedNo){
			if(LeftAvaliable){
				Caption="<< "+Caption;
			}else{
				Caption="   "+Caption;
			}
			if(RightAvaliable){Caption+=" >>";}
			DrawStringToHandle(400,230+i*32,Caption.c_str(),GetColor(255,127,127),fnt);
		}else{
			Caption="   "+Caption;
			DrawStringToHandle(400,230+i*32,Caption.c_str(),GetColor(255,255,255),fnt);
		}
	}

	//�����ꂽ�L�[�ɂ�镪��
	switch(n){
	case 0x10:
		//����������
		return 0;

	case -2:
		//�L�����Z��
		stage=0x90;
		Setting.load();
		return 0;

	case -1:
		//�����N����񂩂���
		return 0;
	default:
		/*
		if(RankReset==2){
			RankAll InitRank;
			InitRank.Init();
			RankAll::Save(InitRank);
			RankReset=0;
		}
		*/
		Setting.save();
		return 1;
	}

	return 0;
}

//�����L���O���[�h
int StageManager::stgA0(){
	return 1;
}

//�����L���O
int StageManager::stgA1(){
	/*
	static RankAll gRank;
	if(phase==0){
		RankAll::Load(gRank);
		//RankAll::Save(gRank);
		gRank.SetImg("img\\rank_char.bmp","img\\loadbg.png");
		gRank.SetSnd(SndSelect,SndCancel);
		gRank.Difficulty[gRank.EASY].SetDraw(gRank.ConstX,gRank.ConstY,gRank.ChrHeight);
	}
	gRank.Draw();
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PjSys::key::sub_p ) != 0 ){
		return 1;
	}
	phase++;
	*/
	return 0;
	
}