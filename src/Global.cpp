#include "Common.h"
#include "KeyConfigIni.h"
#include "SettingIni.h"

/*=============================
My�̃O���[�o���ϐ��{��
==============================*/
int_score My::Score; //�X�R�A
/*
int My::Region=3; //����͈�
int My::DefaultLeft=3;
int My::DefaultBomb=3;
*/
int My::SndBomb;
int My::SndExtend;
int My::SndBombExtend; //�{����SE
int My::Left=My::DefaultLeft; //�c�@
int My::Bomb=My::DefaultBomb; //�{��
int My::BombFrame=0; //�{���t���O
bool My::IsAutoBomb=false; //���������{�����I�[�g�{�����ۂ�
int My::BombDeletedBullet=0; //�������e�̐�
bool My::AutoBomb=true; //�I�[�g�{�����g�p�\��
double My::x;
double My::y; //���W

int My::SubEnergy=0; //�T�u�E�F�|���̃G�l���M�[
char My::SubLevel=0; //�T�u�E�F�|���̃��x��
int My::SubFrame=0;
int My::DefFrame=0; //�f�B�t�F���_�[�̃t���O

int My::sw::sndLv[5];

bool My::Bullet::flg[MBCAP];
int My::Bullet::x[MBCAP];
int My::Bullet::y[MBCAP];
bool My::Bullet::IsHit[MBCAP];
int My::Bullet::frm=0;
int My::Bullet::pow1=2;
int My::Bullet::pow2=1;
int My::Bullet::region=16;
int My::Bullet::pbFire[2][8];
bool My::Bullet::EffFlg[5];
int My::Bullet::EffX[5];
int My::Bullet::EffY[5];
int My::Bullet::EffImg[2][8];
int My::Bullet::EffFrm[5];

//���@���[�U�[
int My::Laser::img;
int My::Laser::hitimg[16];
int My::Laser::ShotSnd;
int My::Laser::Limit=LASER_MAX; //���[�U�[�̓o�^����B���x���ɂ���ĈقȂ�B
bool My::Laser::flg[LASER_MAX];
bool My::Laser::IsDemo=false;
double My::Laser::sx[LASER_MAX];
double My::Laser::sy[LASER_MAX];
double My::Laser::cx[LASER_MAX];
double My::Laser::cy[LASER_MAX];
double My::Laser::ex[LASER_MAX];
double My::Laser::ey[LASER_MAX];
double My::Laser::x[LASER_MAX][LASER_TRACE_MAX];
double My::Laser::y[LASER_MAX][LASER_TRACE_MAX];
double My::Laser::px[LASER_MAX][LASER_TRACE_MAX][4];
double My::Laser::py[LASER_MAX][LASER_TRACE_MAX][4];

double My::Laser::v[LASER_MAX][LASER_TRACE_MAX];
double My::Laser::Dist[LASER_MAX];

double My::Laser::vx[LASER_MAX];
double My::Laser::vy[LASER_MAX];
double My::Laser::angle[LASER_MAX][LASER_TRACE_MAX];
int My::Laser::phase[LASER_MAX];
int My::Laser::StartPhase[LASER_MAX];
int My::Laser::tx[LASER_MAX];
int My::Laser::ty[LASER_MAX];
int My::Laser::vanishcount[LASER_MAX];
bool My::Laser::IsVanish[LASER_MAX];
bool My::Laser::ReplaceFlg[LASER_MAX];
bool My::Laser::TargetFlg[LASER_MAX];
int My::Laser::TargetID[LASER_MAX];
long My::Laser::TargetDist[LASER_MAX];
int My::Laser::RefCounter[LASER_MAX]; //���[�U�[�����T�ڂ�
int My::Laser::RefCounterMax; //��̍ő吔
int My::Laser::RefCounterMin; //��̍ŏ���

bool My::IsHit = false;
bool My::Move=true;
bool My::Born=true;
bool My::shooting=false;
bool My::IsHitFrm=false;
bool My::NowInv=false;
bool My::GOver=false;
bool My::Pause=false;
int My::Invincible=0;
int My::particle[8];
int My::NowStage=0;
int My::chartip=0;
int My::ctphase=0;
int My::numtip=0;
int My::ntphase=0;
int My::BuzzRegion=32;//�o�Y��͈�
int My::NowBuzz=0;//�o�Y���Ă邩�H
int My::BuzzLv=0; //�o�Y�̃��x��
int My::BuzzLvFrame=0;
int My::imgRegion;
int My::imgLeftTimeGaze; //�T�u�E�F�|���̎c�莞�ԃQ�[�W
int My::imgBuzz; //�o�Y���Ă�
int My::SubEnergyMax=0;

int My::Model; //3D���f��
int My::burner;
bool My::IsBurner=false; //�A�t�^�o�[�i�[��\�����邩�H
float My::Rot; //�@�̎��̉�]
//float fRoll=0;
float My::fLoop=0;
float My::Exp=MY_MODEL_EXP; //�g�嗦

//�A�C�e��
bool My::Item::Exist[16]; //���݂��邩�H
int My::Item::GeneralImg[8]; //���f���̌��^
float My::Item::exp[8];//�g�嗦
int My::Item::img[16]; //�X�̃��f��
int My::Item::x[16];
int My::Item::y[16]; //���W
double My::Item::vx[16];
double My::Item::vy[16]; //�x�N�g��
char My::Item::type[16]; //�^�C�v
int My::Item::phase[16]; //�t�F�[�Y
int My::Item::SndGet; //�擾�����Ƃ��̌��ʉ�

//=============================================
//My�̏�����
//=============================================
void My::Init(){
	Score=0; //�X�R�A
	Left=DefaultLeft; //�c�@
	Bomb=DefaultBomb; //�{��
	BombFrame=0; //�{���t���O
	AutoBomb=true; //�I�[�g�{�����g�p�\��
	IsAutoBomb=false; //���������{�����I�[�g�{�����ۂ�
	BombDeletedBullet=0; //�������e�̐�
	x=0;y=0; //���W

	SubEnergy=0; //�T�u�E�F�|���̃G�l���M�[
	SubLevel=0; //�T�u�E�F�|���̃��x��
	SubFrame=0;
	DefFrame=0; //�f�B�t�F���_�[�̃t���O

	//���@���[�U�[
	Laser::Init();

	IsHit = false; Move=true; Born=true; shooting=false;
	IsHitFrm=false;
	NowInv=false; GOver=false; Pause=false;
	Invincible=0;
	//particle[8];
	NowStage=0;
	//chartip,ctphase,numtip,ntphase;
	BuzzRegion=32;//�o�Y��͈�
	NowBuzz=0;//�o�Y���Ă邩�H
	BuzzLv=0; //�o�Y�̃��x��
	BuzzLvFrame=0;
	CalcSubEnergyMax();
	IsBurner=false; //�A�t�^�o�[�i�[��\�����邩�H
	 Rot=0; //�@�̎��̉�]
	fLoop=0;
	Exp=MY_MODEL_EXP; //�g�嗦

	//�A�C�e��
	Item::Init();
}

/**************************
PjSys�O���[�o���ϐ�����
****************************/
//bool PjSys::IsWnd=false; //�t���X�N���[�����ۂ�
//double PjSys::WndExRate=1.0;
//int PjSys::ColorBit=32; //�J���[�r�b�g��
//bool PjSys::UseVSync=true;
//bool PjSys::OutputDebugFile=true; //�f�o�b�O�t�@�C�����o�͂��邩�ۂ�
bool PjSys::ShowGuide=false; //���蔻��K�C�h��\�����邩�ۂ�
bool PjSys::ShowInsane=true; //�B����Փx��Insane��\�����邩
int PjSys::GameLevel=1; //�\�ʏ�̓�Փx�B0:Insane 1:Hard 2:Standard 3:Easy
int PjSys::Hard=1; //�����I�ȓ�Փx�@7:�ňՁ`1:�œ�
int PjSys::HardConst=1; //�����I�ȓ�Փx(���̌Œ��)
//bool Setting.Optional.DrawTrack=false; //�e���̋O�Ղ�\�����邩
//bool Setting.Optional.DrawProspect=false;//�e���̗\���\��
bool PjSys::IrodoriMode=false; //Another Mode::IRODORI MODE(�ʃ��[�h�F�e���������Ȃ�)
bool PjSys::AccelMode=false; //Another Mode::ACCELERATOR MODE(�A�N�Z�����[�h�F�e������)

bool PjSys::cheat::Inv=false; //��ɖ��G
bool PjSys::cheat::Go2Boss=false; //�{�X��֔�΂���
bool PjSys::cheat::Peacist=false; //�G���e�������Ă��Ȃ�
bool PjSys::cheat::LevelMax=false; //��Ƀ��x��5

//bool Setting.General.English=false; //�p�ꂩ�ۂ�
//int Setting.General.SEVolume=255;
//int Setting.General.BGMVolume=255;
int PjSys::bgm;
int PjSys::bossbgm;
//bool PjSys::IsSoftSound=false; //�\�t�g�E�F�A�ŉ����������邩
//int PjSys::UseAntiAliasing=0;

int PjSys::Extend=1000000; //�G�N�X�e���h����_��
int PjSys::BombExtend=500000; //�{�����G�N�X�e���h����_��

int PjSys::StartStage=0x10; //�X�^�[�g����X�e�[�W

int PjSys::key::shot_p=PAD_INPUT_1;
int PjSys::key::shot=KEY_INPUT_Z;
int PjSys::key::sub_p=PAD_INPUT_2;
int PjSys::key::sub=KEY_INPUT_C;
int PjSys::key::laser=KEY_INPUT_V;
int PjSys::key::laser_p=PAD_INPUT_4;
bool PjSys::key::UseLaser=false;

int PjSys::key::bomb_p=PAD_INPUT_3;
int PjSys::key::bomb=KEY_INPUT_X;
int PjSys::key::slow_p=PAD_INPUT_7;
int PjSys::key::slow=KEY_INPUT_LSHIFT;
int PjSys::key::exit_p=PAD_INPUT_9;
int PjSys::key::exit=KEY_INPUT_ESCAPE;
int PjSys::key::pause_p=PAD_INPUT_10;
int PjSys::key::pause=KEY_INPUT_P;

bool PjSys::key::vib=true;
bool PjSys::key::sbconv=false;

int PjSys::font::caption = CreateFontToHandle(NULL, 12 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
int PjSys::font::log = CreateFontToHandle(NULL , 9 , 2 , DX_FONTTYPE_ANTIALIASING ) ;
//int PjSys::font::menu = CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
/******** �ݒ�I�� ************/
//string_t PjSys::Path;
int PjSys::MainChar[7];//�傫�ȕ���(98x16)�@([0]FPS:[1]SCORE:[2]STOCK:[3]BOMB:[4]STAGE:[5]CREDIT:[6]LEVEL:)
int PjSys::MainNum[10];//�傫�Ȑ���(16x16)
int PjSys::SmallChar[8];//�����ȕ���(8x16) ([0]:EXTENDED [1]:BOMB++ [2]:W.E.P.)
int PjSys::SmallNum[10]; //�����Ȑ���(8x16)
int PjSys::FPSChar;//FPS�̕���
int PjSys::Gaze[16];//�T�u�E�F�|���Q�[�W(16x256)
int PjSys::GazeFrame;//�T�u�E�F�|���Q�[�W�̃t���[��(16x256)
int PjSys::GazeChar[2];//�T�u�E�F�|���̕���(16x128)
int PjSys::BuzzCnt; //�o�Y��J�E���^
int PjSys::ImgNull; //�󔒂̉摜
bool PjSys::Exit=false; //�I������t���O
bool PjSys::CanExit=true;
int PjSys::mHardImg[4]; //��Փx�\��
int PjSys::ExtendPhase=1;
int PjSys::BombExtendPhase=1; //�G�N�X�e���h�̃t�F�[�Y


int PjSys::Scr::IsArcade_Like=0; //�A�[�P�[�h���ۂ�����I�}�P�B
bool PjSys::Scr::ACKey=0;

bool PjSys::Scr::AvaliableShake=true; //�Ԃ�Ԃ邪�L����
int PjSys::Scr::MoveX=0;
int PjSys::Scr::MoveY=0;
int PjSys::Scr::MoveFrame=0;
int PjSys::Scr::MoveFrameConst=0;
int PjSys::Scr::MaxShake=0;
int PjSys::Scr::MinShake=0;
int PjSys::Scr::RmtX=0;
int PjSys::Scr::RmtY=0;
int PjSys::Scr::sx;
int PjSys::Scr::sy;

string_t PjSys::Scr::LogChar[10];
int PjSys::Scr::LogFrm[10];
int PjSys::Scr::LogCol[10];
int PjSys::Scr::LogInt[10];
DxLib::COLOR_F PjSys::Scr::BGColor=GetColorF( 1.0f, 1.0f, 1.0f, 1.0f );
bool PjSys::Scr::BGWire=false;
int PjSys::Scr::BGModel;

int PjSys::Scr::BurstFrm=60;
int PjSys::Scr::BurstImg;
int PjSys::Scr::BurstX=0;
int PjSys::Scr::BurstY=0;
int PjSys::Scr::BurstSpeed=0;
int PjSys::Scr::BurstColor[3]={255,255,255};
int PjSys::Scr::BurstDivision=0;
int PjSys::Scr::BurstThickness=16;
bool PjSys::Scr::BurstAbsorb=false;
int PjSys::Scr::IsNoise=0;

int PjSys::Scr::NoiseImg[100];
int PjSys::Scr::NoiseAlpha=255;

//�X�N���[���V���b�g
DATEDATA PjSys::Date;
int PjSys::ssf=0;
int PjSys::ssec=-1;
int PjSys::scnt=0;
bool PjSys::IsScreenShot=false;
// ���l���O���t�B�b�N�\������֐�
float PjSys::CameraVRota=DX_PI_F/-2.0f;
float PjSys::CameraHRota=0;
float PjSys::CameraTRota=0;
DxLib::VECTOR PjSys::CameraPos=VGet( 0.0f, -230.0f, 0.0f);
//=============================================
//PjSys�̏�����
//=============================================
void PjSys::Init(){
	SRand(42);
	Extend=1000000; //�G�N�X�e���h����_��
	BombExtend=500000; //�{�����G�N�X�e���h����_��
	StartStage=0x10; //�X�^�[�g����X�e�[�W

	font::caption = CreateFontToHandle(NULL, 12 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	font::log = CreateFontToHandle(NULL , 9 , 2 , DX_FONTTYPE_ANTIALIASING ) ;
	//font::menu = CreateFontToHandle(NULL , 16 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;

	Exit=false; //�I������t���O
	CanExit=true;
	ExtendPhase=1;BombExtendPhase=1; //�G�N�X�e���h�̃t�F�[�Y

	Scr::ACKey=0;
	Scr::MoveX=0;
	Scr::MoveY=0;
	Scr::MoveFrame=0;
	Scr::MoveFrameConst=0;
	Scr::MaxShake=0;
	Scr::MinShake=0;
	Scr::RmtX=0;
	Scr::RmtY=0;
//		 sx, sy;

	Scr::BGColor=GetColorF( 1.0f, 1.0f, 1.0f, 1.0f );
	Scr::BGWire=false;

	Scr::BurstFrm=60;
	Scr::BurstX=0;
	Scr::BurstY=0;
	Scr::BurstSpeed=0;
	foreach(int e,Scr::BurstColor){e=255;}
	Scr::BurstDivision=0;
	Scr::BurstThickness=16;
	Scr::BurstAbsorb=false;
	Scr::IsNoise=0;
	Scr::NoiseAlpha=255;

	ssf=0;ssec=-1; scnt=0;
	IsScreenShot=false;
	CameraVRota=DX_PI_F/-2.0f;
	CameraHRota=0;
	CameraTRota=0;
	CameraPos=VGet( 0.0f, -230.0f, 0.0f);
}

/*********************************************
Enm�O���[�o����Ԗ{��
*********************************************/
int Enm::BltRegion=2;
	int Enm::ImgBltItem[16];
	int Enm::SmallExplode[8][16];
	int Enm::BossPhase;
	int Enm::LaserUnlockNum[100];
	int Enm::SndBuzz;
	int Enm::SndRef;
	int Enm::SndShot;
	int Enm::FireFlare;
	int Enm::imgBurn[16];
	int Enm::imgAB[4];

	int Enm::RBullet[4];
	int Enm::GBullet[4];
	int Enm::BBullet[4];
	int Enm::RLaser[4];
	int Enm::GLaser[4];
	int Enm::BLaser[4];
	int Enm::YLaser[4];
	int Enm::OLaser[4];

	bool Enm::Refuge::AnyAvaliable=false; //1�ł����G�n�т����݂��邩�H
	bool Enm::Refuge::flg[REFUGE_MAX];
	int Enm::Refuge::x[REFUGE_MAX];
	int Enm::Refuge::y[REFUGE_MAX];
	int Enm::Refuge::width[REFUGE_MAX];
	int Enm::Refuge::height[REFUGE_MAX];

void Enm::Init(){
	BltRegion=2;
	Refuge::AnyAvaliable=false;
}

/***********************************************************
���O��Ԏ���
**************************************************************/

//�X�R�A���Z
void My::AddScore(int i){
	if(Score+i<COUNT_STOP_SCORE){
		Score+=i;
	}else{
		Score=(unsigned long int)COUNT_STOP_SCORE;
	}
}
void My::CalcSubEnergyMax(){
	switch(PjSys::GameLevel){
	case 0:
		SubEnergyMax = 512;
		break;
	case 1:
		//Hard
		SubEnergyMax = 384;
		break;
	case 2:
		//Standard
		SubEnergyMax = 256;
		break;
	case 3:
		//Easy
		SubEnergyMax = 192;
		break;
	default:
		SubEnergyMax=256;
		break;
	}
}
//�G�l���M�[���Z
void My::AddSubEnergy(int i){
	if(SubFrame>0){return;}
	if(SubEnergy<SubEnergyMax*(SubLevel+1)){
		SubEnergy+=i;
		if(SubEnergy>=SubEnergyMax*(SubLevel+1)){
			SubEnergy=SubEnergyMax*(SubLevel+1);
			//GazeReady=GazeReadyFrame;
		}
	}else{
		SubEnergy=SubEnergyMax*(SubLevel+1);
		/*
		//���x���ő傩�Q�[�W�ő�Ȃ�X�R�A�ϊ�
		if(SubLevel>=SUB_LEVEL){
			AddScore(i);
		}
		*/
	}
}

//�{���ǉ�
void My::AddLeft(){
	if(Left<MAXLEFT){
		Left++;
		PjSys::Scr::AddLog("GOT A STOCK!\0",0,GetColor(128,255,128));
		if(My::Left>1){
			PjSys::Scr::AddLog("%d STOCKS LEFT.\0",My::Left,GetColor(255,255,255));
		}else{
			PjSys::Scr::AddLog("%d STOCK LEFT.\0",My::Left,GetColor(255,255,255));
		}
		PlaySoundMem(My::SndExtend,DX_PLAYTYPE_BACK , true ) ;
		PjSys::ExtendPhase++;
		My::ctphase=SHOW_CHIP_TIME;
		My::chartip=0;
		}else{
		AddScore(100000);
		PjSys::Scr::AddLog("[MAXIMUM STOCKS!]\0",0,GetColor(128,255,128));
		PjSys::Scr::AddLog("BONUS +[100K]\0",My::Bomb,GetColor(255,255,255));
		return;
	}
}
void My::AddBomb(){
	if(Bomb<MAXBOMB){
		Bomb++;
			PjSys::Scr::AddLog("GOT A BOMB!\0",0,GetColor(128,255,128));
			if(My::Bomb>1){
				PjSys::Scr::AddLog("%d BOMBS LEFT.\0",My::Bomb,GetColor(255,255,255));
			}else{
				PjSys::Scr::AddLog("%d BOMB LEFT.\0",My::Bomb,GetColor(255,255,255));
			}
			PlaySoundMem(My::SndBombExtend,DX_PLAYTYPE_BACK , true ) ;
			PjSys::BombExtendPhase++;
			My::ctphase=SHOW_CHIP_TIME;
			My::chartip=1;
	}else{
		AddScore(10000);
		PjSys::Scr::AddLog("[MAXIMUM BOMBS!]\0",0,GetColor(128,255,128));
		PjSys::Scr::AddLog("BONUS +[10K]\0",My::Bomb,GetColor(255,255,255));
	}
}
//�A�C�e���ǉ�
int My::Item::Add(int AddX, int AddY, double AddVX, double AddVY, char AddType){
	for(int i=0;i<16;i++){
		if(Exist[i]==false){
			Exist[i]=true;
			phase[i]=0;
			x[i]=(int)AddX;
			y[i]=(int)AddY;
			img[i]=MV1DuplicateModel(GeneralImg[AddType]);
			vx[i]=AddVX;
			vy[i]=AddVY;
			type[i]=AddType;
			return i;
		}
	}
	return -1; //�󂫂�������Ȃ�����
}
/*�����[�U�[�̏������֐�*/
void My::Laser::Init(){
	for(int i=0;i<Limit;i++){
		if(TargetFlg[i]==true){
			Enm::LaserUnlockNum[TargetID[i]]+=Pow(RefCounter[i]);
		}
			flg[i]=false;
			//targetflg[i]=false;
			RefCounter[i]=0; //���[�U�[1����
			//if(i>Limit){break;}
	}
	RefCounterMax=0;
	RefCounterMin=8;
	return;
}
/*�����[�U�[�̓o�^�֐�*/
int My::Laser::Regist(){
	for(int i=0;i<Limit;i++){
		if(flg[i]==false && RefCounter[i]<8){
			if(i%2==0){
				sx[i]=My::x-8;
				sy[i]=My::y+(i+2)/2;
				cx[i]=My::x;//-(i+2)*2-8;
				cy[i]=My::y+200-(i+2)*5;
				ex[i]=My::x-(i+2)*4-16;
				ey[i]=sy[i];
				x[i][0]=(int)sx[i];
				y[i][0]=(int)sy[i];
			}else{
				sx[i]=My::x+8;
				sy[i]=My::y+(i+1)/2;
				cx[i]=My::x;//+(i+1)*2+8;
				cy[i]=My::y+200-(i+1)*5;
				ex[i]=My::x+(i+1)*4+16;
				ey[i]=sy[i];
				x[i][0]=(int)sx[i];
				y[i][0]=(int)sy[i];
			}

			tx[i]=320;
			ty[i]=-31337;
			flg[i]=true;
			phase[i]=0;
			TargetFlg[i]=false;
			TargetDist[i]=-1; //�_�~�[�̐���
			TargetID[i]=-1; //�^�[�Q�b�g���o�^
			IsVanish[i]=false;
			RefCounter[i]++;

			//�X�R�A�ǉ�
			if(IsDemo==false){
				int score=0;
				int ex=(int)((1+i)*My::Laser::RefCounter[i]);
				score=LASER_SCORE*ex;
				My::AddScore(score);
				PjSys::Scr::AddLog("LASER LAUNCHED x[%d]",ex,GetColor(255,127+16*My::Laser::RefCounter[i],127));
			}
			if(CheckSoundMem(My::Laser::ShotSnd)==0){ //���ɍĐ�����ĂȂ���΍Đ�
				PlaySoundMem(My::Laser::ShotSnd,DX_PLAYTYPE_BACK,true);
			}else if(CheckSoundMem(My::Laser::ShotSnd)==1){ //���ɍĐ�����Ă���Β�~���čŏ�����
				StopSoundMem(My::Laser::ShotSnd);
				PlaySoundMem(My::Laser::ShotSnd,DX_PLAYTYPE_BACK,true);
			}else if(CheckSoundMem(My::Laser::ShotSnd)==-1){ //�G���[(���[�h���ĂȂ��Ƃ�)�Ȃ烍�[�h�������čĐ�
				My::Laser::ShotSnd=LoadSoundMem( "snd\\laser.wav" );
				ChangeVolumeSoundMem(Setting.General.SEVolume , My::Laser::ShotSnd );
				PlaySoundMem(My::Laser::ShotSnd,DX_PLAYTYPE_BACK,true);
			}

			return i;
		}
	}
	//�X�R�A�ǉ�
	int score=0;
	int ex=2*My::Laser::RefCounterMax;
	score=LASER_SCORE*ex;
	My::AddScore(score);
	PjSys::Scr::AddLog("ABSORBED x[%d]",ex,GetColor(127+16*My::Laser::RefCounterMax,127+16*My::Laser::RefCounterMax,127+16*My::Laser::RefCounterMax));
	if(CheckSoundMem(Enm::SndRef)==0){
		PlaySoundMem(Enm::SndRef,DX_PLAYTYPE_BACK,true);}
	else if(CheckSoundMem(Enm::SndRef)==-1){
		Enm::SndRef=LoadSoundMem( "snd\\reflect.wav" ) ;
		ChangeVolumeSoundMem(Setting.General.SEVolume , Enm::SndRef );
		PlaySoundMem(Enm::SndRef,DX_PLAYTYPE_BACK,true);
	}

	return -1;
}

void My::Laser::Vanish(int idx){ //��������
	IsVanish[idx]=true;
	vanishcount[idx]=0;
	Enm::LaserUnlockNum[TargetID[idx]]+=Pow(RefCounter[idx]);//�G�Ƀ_���[�W�����Z
}

//���[�U�[�̈З͂��Z�o
int My::Laser::Pow(int Counter){
	int r=0;
	//128/(����)
	switch(Counter){
		case 1:
			r=128;
			break;
		case 2:
			r=64;
			break;
		case 3:
			r=43;
			break;
		case 4:
			r=32;
			break;
		case 5:
			r=26;
			break;
		case 6:
			r=21;
			break;
		case 7:
			r=18;
			break;
		case 8:
			r=16;
			break;
		default:
			r=128;
			break;
	}
	return r;
}

/*�����[�U�[�̈ړ��`��֐�*/
void My::Laser::Move(){
	for(int i=0;i<Limit;i++){
		if(flg[i]==true){ //���[�U�[����
			bool wiped=true; //�S�ď�������Ă��邩�H1�ł��c���Ă����烌�[�U�[���������Ȃ��B
			if(IsVanish[i]==true){vanishcount[i]++;}
			//�O�Օ\���p�̃��[�v
			for(int j=LASER_TRACE_MAX-1;j>0;j--){
			//for(int j=1;j<LASER_TRACE_MAX;j++){
			int k=j-1;

				x[i][j]=x[i][k];
				y[i][j]=y[i][k];
				//z[i][j]=z[i][k];
				v[i][j]=v[i][k];
				angle[i][j]=angle[i][k];

				double px1=x[i][j]+mycos(angle[i][j])*(v[i][j]/2);
				double py1=y[i][j]+mysin(angle[i][j])*(v[i][j]/2);
				double rangle=angle[i][j]+RIGHT_ANGLE;
				double langle=angle[i][j]-RIGHT_ANGLE;

				px[i][j][1]=px1+mycos(rangle)*8;
				py[i][j][1]=py1+mysin(rangle)*8;
				px[i][j][0]=px1+mycos(langle)*8;
				py[i][j][0]=py1+mysin(langle)*8;
				if(j==LASER_TRACE_MAX-1){
					double px2=x[i][j]-mycos(angle[i][j])*(v[i][j]/2);
					double py2=y[i][j]-mysin(angle[i][j])*(v[i][j]/2);
					px[i][j][2]=px2+mycos(rangle)*8;
					py[i][j][2]=py2+mysin(rangle)*8;
					px[i][j][3]=px2+mycos(langle)*8;
					py[i][j][3]=py2+mysin(langle)*8;
				}else{
					px[i][j][2]=px[i][j+1][1];
					py[i][j][2]=py[i][j+1][1];
					px[i][j][3]=px[i][j+1][0];
					py[i][j][3]=py[i][j+1][0];
				}

				if(phase[i]<=60 || (x[i][j]>=120 && x[i][j]<=520 && y[i][j]>=0 && y[i][j]<=480)){ //���[�U�[����ʓ��ɑ���
					wiped=false;
				}
				//SetDrawBlendMode(DX_BLENDMODE_ALPHA,63+192/LASER_TRACE_MAX*(LASER_TRACE_MAX-j));
				if(IsVanish[i]==true && vanishcount[i]>j){
					//�����鏈��
					if(vanishcount[i]>=LASER_TRACE_MAX){
						wiped=true;
					}else{
						if(j==1){
							SetDrawMode( 1 ) ;
							SetDrawBlendMode(DX_BLENDMODE_ADD,128-6*j);
							DrawRotaGraph((int)x[i][j],(int)y[i][j],2.0,angle[i][j]-RIGHT_ANGLE,My::Laser::hitimg[vanishcount[i]],true,0);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
							SetDrawMode( 0 ) ;
						}
					}
				}else{
					if(phase[i]>=j){
						SetDrawBlendMode(DX_BLENDMODE_ADD,255-12*j);

						SetDrawBright(255,127+(int)(128/LASER_TRACE_MAX*j),(127-My::Laser::RefCounter[i]*15)+(int)(128/LASER_TRACE_MAX*j));
						SetDrawMode( 1 ) ;
						DrawModiGraphF((float)px[i][j][0],(float)py[i][j][0],
									  (float)px[i][j][1],(float)py[i][j][1],
									  (float)px[i][j][2],(float)py[i][j][2],
									  (float)px[i][j][3],(float)py[i][j][3],img,TRUE);
						SetDrawMode( 0 ) ;
						SetDrawBright(255,255,255);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
					}
				}
			}
			if(wiped==true){
				flg[i]=false;
				//TargetFlg[i]=false;
			}

			/*���[�U�[�ړ��A���S���Y��*/
			math m;
			//double v=0; //�X�J��
			//15�t���[���ȉ��Ȃ�ڕW�̈ʒu�Ɋ֌W�Ȃ�������
			if(phase[i]++<15){
				Get2DBezier(sx[i],sy[i],ex[i],ey[i],cx[i],cy[i],15,phase[i],&x[i][0],&y[i][0],&v[i][0],&angle[i][0]);
				vx[i]=0;
				vy[i]=0;
			}else if(phase[i]<=105 && IsVanish[i]==false){
				if(phase[i]==15){
					if(TargetFlg[i]==true){
						ReplaceFlg[i]=true;
					}else{
						v[i][0]=16;
					}
				}
				if(ReplaceFlg[i]==true){
					sx[i]=x[i][1]+mycos(angle[i][1])*v[i][1];
					sy[i]=y[i][1]+mysin(angle[i][1])*v[i][1];
					Dist[i]=m.GetDist(sx[i],sy[i],tx[i],ty[i]);
					cx[i]=x[i][1]+mycos(angle[i][1])*(Dist[i]/2);
					cy[i]=y[i][1]+mysin(angle[i][1])*(Dist[i]/2);
					StartPhase[i]=phase[i];
					ReplaceFlg[i]=false;
				}
				int div=(int)(Dist[i]/16)+1;
				if(TargetFlg[i]==true && phase[i]-StartPhase[i]<=div){
					Get2DBezier(sx[i],sy[i],tx[i],ty[i],cx[i],cy[i],div,phase[i]-StartPhase[i],&x[i][0],&y[i][0],&v[i][0],&angle[i][0]);
					vx[i]=0;
					vy[i]=0;
				}else{
					vx[i]=mycos(angle[i][0])*16;
					vy[i]=mysin(angle[i][0])*16;
				}
			}else{
				vx[i]=mycos(angle[i][0])*16;
				vy[i]=mysin(angle[i][0])*16;
			}
			if(IsVanish[i]==false){
				x[i][0]+=vx[i];
				y[i][0]+=vy[i];

				//���[�U�[�擪
				double px1=x[i][0]+mycos(angle[i][0])*v[i][0]/2;//�������
				double py1=y[i][0]+mysin(angle[i][0])*v[i][0]/2;
				double rangle=angle[i][0]+RIGHT_ANGLE;
				double langle=angle[i][0]-RIGHT_ANGLE;
				px[i][0][0]=px1+mycos(langle)*8;
				py[i][0][0]=py1+mysin(langle)*8;
				px[i][0][1]=px1+mycos(rangle)*8;
				py[i][0][1]=py1+mysin(rangle)*8;

				px[i][0][2]=px[i][1][1];
				py[i][0][2]=py[i][1][1];
				px[i][0][3]=px[i][1][0];
				py[i][0][3]=py[i][1][0];

				SetDrawBlendMode(DX_BLENDMODE_ADD,255);
				SetDrawBright(255,127,(127-My::Laser::RefCounter[i]*15));
				SetDrawMode( 1 ) ;
				DrawModiGraphF((float)px[i][0][0],(float)py[i][0][0],
							  (float)px[i][0][1],(float)py[i][0][1],
							  (float)px[i][0][2],(float)py[i][0][2],
							  (float)px[i][0][3],(float)py[i][0][3],img,TRUE);
				SetDrawMode( 0 ) ;
				SetDrawBright(255,255,255);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
			//DrawFormatString( x[i][0]+PjSys::Scr::MoveX+8 , y[i][0]+PjSys::Scr::MoveY-8 , GetColor(127,255,127) ,"%f" , angle[i][0]) ;

			/*���[�U�[�ړ��A���S���Y���I��*/
		}
		//���t���N�g�J�E���^�ő吔����
		if(RefCounterMax < RefCounter[i]){
			RefCounterMax = RefCounter[i];
		}
		if(RefCounterMin>RefCounter[i]){
			RefCounterMin = RefCounter[i];
		}
	}
	//���[�U�[�{���\���B���Ȃ̂ō�蒼���Ȃ��ƁB
	//if(My::Laser::RefCounterMax>0){
	//	DrawFormatString((int)My::x+32,(int)My::y+32,GetColor(255,127,127),"x%d",My::Laser::RefCounterMax*2);
	//}
}
void My::Laser::WriteStatus(int x,int y){
	int lsmax=0;
	int lsnow=0;
	int lim=0;

	//DrawBox(x+1,y-1,x+118,y+180,GetColor(128,128,128),FALSE);
	//DrawLine(x+59,y,x+59,y+180,GetColor(128,128,128),1);
	for(int i=0;i<32;i++){
		int laser_id=i+1; //�\�ʏ�̃��[�U�[�ԍ�
		int x2,y2;
		///* //2�ɕ�����p
		if(i%2==0){
			x2=x;
			y2=y+i/2*10+10; //Y���W
		}else{
			x2=x+60;
			y2=y+(i-1)/2*10+10; //Y���W
		}
		//*/

		/*x2=x;  //1�s�`��p
		y2=y2=y+i*10+10;*/

		int cl=0; //���[�U�[�ԍ���`��
		int cl_unavailable=GetColor(128,128,128);
		int cl_avaliable=GetColor(255,255,255);
		int x3=x2+15; //��̓I�ȏ��̕`��J�n�ʒu
		//���x���ɂ���ĕ`��F����
		if(My::SubLevel>0){
			switch(My::SubLevel){
				case 1:
					lim=2;
					break;
				case 2:
					lim=4;
					break;
				case 3:
					lim=8;
					break;
				case 4:
					lim=16;
					break;
				case 5:
					lim=32;
					break;
			}
			if(i<lim){
				cl=cl_avaliable;
				if(My::DefFrame>0){
					//SetDrawBlendMode(DX_BLENDMODE_ADD,128);
					lsmax+=8;
					lsnow+=My::Laser::RefCounter[i];
					DrawFormatStringToHandle(x3,y2,GetColor(255,255-My::Laser::RefCounter[i]*16,255-My::Laser::RefCounter[i]*16),PjSys::font::log,"%d/8(x%d)",My::Laser::RefCounter[i],My::Laser::RefCounter[i]*(i+1)*2);
					//SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				}else{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
					DrawStringToHandle(x3,y2,"READY",GetColor(128,255,128),PjSys::font::log);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				}
			}else{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
				DrawStringToHandle(x3,y2," - ",cl_unavailable,PjSys::font::log);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				cl=cl_unavailable;
			}
		}else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,96);
			DrawStringToHandle(x3,y2," - ",cl_unavailable,PjSys::font::log);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			cl=cl_unavailable;
		}
		if(laser_id<10){
			DrawFormatStringToHandle(x2,y2,cl,PjSys::font::log," %d:",laser_id);
		}else{
			DrawFormatStringToHandle(x2,y2,cl,PjSys::font::log,"%d:",laser_id);
		}
	}
	if(lim>0){
		if(My::DefFrame>0){
			DrawFormatStringToHandle(x,y,GetColor(255,127,127),PjSys::font::log,"REACT LASER: (%d/%d)",lsnow,lsmax);
		}else{
			DrawStringToHandle(x,y,"REACT LASER: READY.",GetColor(127,255,127),PjSys::font::log,0,0);
		}
	}else{
		DrawStringToHandle(x,y,"REACT LASER: -",GetColor(255,255,255),PjSys::font::log,0,0);
	}
}

void My::Item::Init(){
	for(int i=0;i<16;i++){
		Exist[i]=false;
	}
} //�S�ď�����

bool PjSys::i2b(int i){
	if(i==1){
		return true;
	}else{
		return false;
	}
}
/*	//BGMLoadMode����DxLib�̒l�ɕϊ�
int PjSys::SetBGMLoadMode(int i){
	switch(i){
		case 0:
			return DX_SOUNDDATATYPE_MEMNOPRESS;
		case 1:
			return DX_SOUNDDATATYPE_MEMPRESS;
		case 2:
			return DX_SOUNDDATATYPE_FILE;
		default:
			return DX_SOUNDDATATYPE_MEMPRESS;
	}
}

//DxLib�̒l����BGMLoadMode�ɕϊ�
int PjSys::GetBGMLoadMode(int i){
	switch(i){
		case DX_SOUNDDATATYPE_MEMNOPRESS:
			return 0;
		case DX_SOUNDDATATYPE_MEMPRESS:
			return 1;
		case DX_SOUNDDATATYPE_FILE:
			return 2;
		default:
			return 1;
	}
}
*/
//�����N��ݒ�
void PjSys::SetLank(){
	if(My::SubLevel>=SUB_LEVEL){ //���x���ő�̏ꍇ�͓�Փxup
		switch(PjSys::GameLevel){
			case 0:
				//��Փx
				PjSys::Hard=2;
				//PjSys::AccelMode=true;
				//PjSys::IrodoriMode=false;
				break;
			case 1:
				PjSys::Hard=1;
				break;
			case 2:
				PjSys::Hard=3;
				break;
			case 3:
				PjSys::Hard=5;
				break;
			default:
				PjSys::Hard=1;
				break;
		}
	}else if(My::SubLevel<1){ //���x��0�̏ꍇ�͓�Փxdown
		switch(PjSys::GameLevel){
			case 0:
				PjSys::Hard=6;
				PjSys::AccelMode=false;
				PjSys::IrodoriMode=false;
				break;
			case 1:
				PjSys::Hard=3;
				break;
			case 2:
				PjSys::Hard=5;
				break;
			case 3:
				PjSys::Hard=7;
				break;
			default:
				PjSys::Hard=3;
				break;
		}
	}else{ //���̑��͒ʏ�
		switch(PjSys::GameLevel){
			case 0:
				PjSys::Hard=4;
				PjSys::AccelMode=false;
				PjSys::IrodoriMode=false;
				break;
			case 1:
				PjSys::Hard=2;
				break;
			case 2:
				PjSys::Hard=4;
				break;
			case 3:
				PjSys::Hard=6;
				break;
			default:
				PjSys::Hard=2;
				break;
		}
	}
}
/*
void PjSys::LoadSetting(){
	string_t ini;
	ini=PjSys::Path+"Setting.ini";
	SettingIni set(ini);
	PjSys::IsWnd=i2b(set.General.Window);
	PjSys::WndExRate=set.General.WindowExtendRate;
	PjSys::UseVSync=i2b(set.General.VSync);
	Setting.General.English=i2b(set.General.English);
	PjSys::key::vib=i2b(set.General.UseVibration);
	PjSys::IsSoftSound=i2b(set.General.SoftwareSound);
	PjSys::UseAntiAliasing=set.General.AntiAliasing;
	Setting.General.BGMVolume=set.General.BGMVolume;
	Setting.General.SEVolume=set.General.SEVolume;
	PjSys::OutputDebugFile=i2b(set.Debug.OutputLog);
	Setting.Optional.DrawTrack=i2b(set.Optional.DrawTrack);
	Setting.Optional.DrawProspect=i2b(set.Optional.DrawProspect);
*/

/*

void PjSys::SaveSetting(){
	string_t ini;
	ini=PjSys::Path+"Setting.ini";
	//SettingIni set(ini);
	set.General.VSync=PjSys::UseVSync;
	set.General.English=Setting.General.English;
	set.General.UseVibration=PjSys::key::vib;
	set.General.SoftwareSound=PjSys::IsSoftSound;
	set.General.AntiAliasing=PjSys::UseAntiAliasing;
	set.General.BGMVolume=Setting.General.BGMVolume;
	set.General.SEVolume=Setting.General.SEVolume;
	set.General.LoadMode=PjSys::GetBGMLoadMode(Setting.General.LoadMode);
	set.Debug.OutputLog=PjSys::OutputDebugFile;
	set.Optional.DrawTrack=Setting.Optional.DrawTrack;
	set.Optional.DrawProspect=Setting.Optional.DrawProspect;

	set.save(ini);
}
*/
void PjSys::ScreenShot(){
	stringstream ss;
	if(CheckHitKey(KEY_INPUT_F3)==1||IsScreenShot==true){
		IsScreenShot=false;
		if(ssf==0){
			GetDateTime(&Date);
			if(Date.Sec==ssec){scnt++;}else{scnt=0;ssec=Date.Sec;}
			ss.clear();
			ss.str("");
			ss << "ScreenShots\\img_"<<Date.Mon<<"_"<<Date.Day<<"_"<<Date.Hour<<"_"<<Date.Min<<"_"<<Date.Sec<<"_"<<scnt<<".png";
			SaveDrawScreenToPNG( 0 , 0 , 640 , 480 , ss.str().c_str());
			PjSys::Scr::AddLog("CAPTURING SCREEN... OK",0,GetColor(0,255,255));
		}
	ssf=1;
	}else{
		ssf=0;
		//IsScreenShot=false;
	}
}
void PjSys::NumDraw(int* img, unsigned int Num,int stx,int sty,int width,double exp ){
	unsigned int i , BeamWidth , x ;
	BeamWidth = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ){BeamWidth++;}
	x = BeamWidth * width +stx ;
	for( i = 0 ; i <= BeamWidth ; i ++ ){
		if(exp!=1.0){
			SetDrawMode( 1 ) ;
			DrawRotaGraph(x+PjSys::Scr::MoveX , sty+PjSys::Scr::MoveY,exp,0, img[ Num % 10 ], true ) ;
			SetDrawMode( 0 ) ;
		}else{
			DrawGraph( x+PjSys::Scr::MoveX , sty+PjSys::Scr::MoveY , img[ Num % 10 ], true ) ;
		}
		x -= width ;
		Num /= 10 ;
	}
}

void PjSys::Scr::SetShake(int Frame,int Min, int Max){
	//Frame+=(10-(Frame%10));
	PjSys::Scr::MoveFrame=Frame;
	MoveFrameConst=Frame;
	PjSys::Scr::MinShake=Min;
	PjSys::Scr::MaxShake=Max;
}

void PjSys::Scr::Shake(){
	if(PjSys::Scr::MoveFrame==0){
		PjSys::Scr::MoveX=0;
		PjSys::Scr::MoveY=0;
		return;
	}

	int ShakeScr=(int)(MaxShake*MoveFrame/MoveFrameConst);
	math m;
	double rad=m.irand(0,360)*RAD;
			if(PjSys::key::vib==true){StartJoypadVibration(DX_INPUT_PAD1, ShakeScr*200, 100 ) ;}
			MoveX=(int)(mycos(rad)*ShakeScr);
			MoveY=(int)(mysin(rad)*ShakeScr);

	PjSys::Scr::MoveFrame--;
}

void PjSys::Scr::AddLog(string_t str, int iscr,int color){
	for(int i=9;i>0;i--){
		PjSys::Scr::LogChar[i]=PjSys::Scr::LogChar[i-1];
		PjSys::Scr::LogCol[i]=PjSys::Scr::LogCol[i-1];
		PjSys::Scr::LogInt[i]=PjSys::Scr::LogInt[i-1];
		PjSys::Scr::LogFrm[i]=PjSys::Scr::LogFrm[i-1];
	}
	PjSys::Scr::LogChar[0]=str;
	PjSys::Scr::LogCol[0]=color;
	PjSys::Scr::LogInt[0]=iscr;
	PjSys::Scr::LogFrm[0]=0;
}
void PjSys::Scr::SetBurst(int x, int y, int speed, int div,int r,int g,int b, bool absorb,int thickness){
	BurstColor[0]=r;
	BurstColor[1]=g;
	BurstColor[2]=b;
	BurstFrm=0;
	BurstX=x;
	BurstY=y;
	BurstSpeed=speed;
	//BurstColor=color;
	BurstDivision=div;
	BurstAbsorb=absorb;
	BurstThickness=thickness;
}

void PjSys::Scr::MoveBurst(){
	if(BurstFrm>60){return;}
	int vin=0;
	int vout=0;
	if(BurstAbsorb==true){ 	//�z�����ރt���O�������Ă��邩�H
		vout=(60-BurstFrm)*BurstSpeed;
		//vin=(int)(vout+BurstThickness*sin(PI/30.0*BurstFrm)); //���񂾂�ׂ��Ȃ�
		vin=vout+BurstThickness;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(255/60.0*BurstFrm));
	}else{
		vin=BurstFrm*BurstSpeed;
		//vout=(int)(vin+BurstThickness*cos(PI/30.0*BurstFrm)); //���񂾂�ׂ��Ȃ�
		vout=vin+BurstThickness;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(255-(255/60.0*BurstFrm)));
	}
	float rad=DX_PI_F*2/BurstDivision;
	SetDrawMode(1);
	SetDrawBright(BurstColor[0],BurstColor[1],BurstColor[2]);
	for(int i=0;i<BurstDivision;i++){
		float ul[2],ur[2],dl[2],dr[2];
		ul[0]=mycos(rad*i)*vout+BurstX+MoveX;
		ul[1]=mysin(rad*i)*vout+BurstY+MoveY;
		ur[0]=mycos(rad*(i+1))*vout+BurstX+MoveX;
		ur[1]=mysin(rad*(i+1))*vout+BurstY+MoveY;
		dr[0]=mycos(rad*(i+1))*vin+BurstX+MoveX;
		dr[1]=mysin(rad*(i+1))*vin+BurstY+MoveY;
		dl[0]=mycos(rad*i)*vin+BurstX+MoveX;
		dl[1]=mysin(rad*i)*vin+BurstY+MoveY;
		DrawModiGraphF(ul[0],ul[1],ur[0],ur[1],dr[0],dr[1],dl[0],dl[1],BurstImg,TRUE);
	}
	SetDrawBright(255,255,255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawMode(0);
	BurstFrm++;
}

void PjSys::Scr::DrawNoise(){
	if(PjSys::Scr::IsNoise>0){
		PjSys::Scr::IsNoise--;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,PjSys::Scr::NoiseAlpha);
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				math m;
				DrawGraph(i*64,j*48,PjSys::Scr::NoiseImg[m.irand(0,99)],FALSE);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

void PjSys::Scr::Arcade_Like(){
	if(CheckHitKey( KEY_INPUT_F2 )==1){
		if(ACKey==false){
			ACKey=true;
			if(IsArcade_Like==2){IsArcade_Like=0;}else{IsArcade_Like++;}
		}
	}else{
		ACKey=false;
	}
	if(IsArcade_Like>0){
		for(int i=0;i<=480;i+=2){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,127*IsArcade_Like);
			DrawLine(0,i,640,i,GetColor(0,0,0));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}
}

void PjSys::DrawFPS(int x,int y,int fps,int def_fps){
	DrawGraph( x+PjSys::Scr::MoveX, y+PjSys::Scr::MoveY, PjSys::FPSChar , true ) ;
	SetDrawBright(255,(int)(255*fps/def_fps),(int)(255*fps/def_fps)) ;
	PjSys::NumDraw(PjSys::MainNum,fps,x+58,y,16);
	SetDrawBright(255,255,255);
}
void PjSys::DrawGuide(int x1,int y1, int x2, int y2){
	if(PjSys::ShowGuide){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		DrawBox(x1,y1,x2,y2,GetColor(255,255,255),1);
		DrawBox(x1,y1,x2,y2,GetColor(64,64,64),0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}
int PjSys::key::keyconv(string_t str){
	//�\�[�X�R�[�h���璷�ɂȂ����̂ŕʂ̃t�@�C���Ɉړ��B
	return cfunc::KeyStr2Int(str);
}

void PjSys::key::load(){
	//string ini;
	//ini=PjSys::Path+"KeyConfig.ini";
	KeyConfigIni cfg;
	//cfg.load(ini);
	//cfg.save(ini);
	PjSys::key::shot_p=PjSys::key::keyconv(cfg.Pad.Shot);
	PjSys::key::sub_p=PjSys::key::keyconv(cfg.Pad.Defender);
	PjSys::key::bomb_p=PjSys::key::keyconv(cfg.Pad.Bomb);
	PjSys::key::slow_p=PjSys::key::keyconv(cfg.Pad.Slow);
	PjSys::key::exit_p=PjSys::key::keyconv(cfg.Pad.Exit);
	PjSys::key::pause_p=PjSys::key::keyconv(cfg.Pad.Pause);
	PjSys::key::laser_p=PjSys::key::keyconv(cfg.Pad.Laser);

	PjSys::key::shot=PjSys::key::keyconv(cfg.Key.Shot);
	PjSys::key::sub=PjSys::key::keyconv(cfg.Key.Defender);
	PjSys::key::bomb=PjSys::key::keyconv(cfg.Key.Bomb);
	PjSys::key::slow=PjSys::key::keyconv(cfg.Key.Slow);
	PjSys::key::exit=PjSys::key::keyconv(cfg.Key.Exit);
	PjSys::key::pause=PjSys::key::keyconv(cfg.Key.Pause);
	PjSys::key::laser=PjSys::key::keyconv(cfg.Key.Laser);
	PjSys::key::UseLaser=PjSys::i2b(cfg.Key.UseLaser);

	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::shot_p, PjSys::key::shot, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::sub_p, PjSys::key::sub, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::bomb_p, PjSys::key::bomb, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::slow_p, PjSys::key::slow, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::exit_p, PjSys::key::exit, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::pause_p, PjSys::key::pause, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::laser_p, PjSys::key::laser, -1, -1,-1 ) ;
}
void PjSys::key::save(){
	//string_t ini;
	//ini=PjSys::Path+"KeyConfig.ini";
	KeyConfigIni cfg;
	cfg.Pad.Shot=cfunc::KeyInt2Str(PjSys::key::shot_p,true);
	cfg.Pad.Defender=cfunc::KeyInt2Str(PjSys::key::sub_p,true);
	cfg.Pad.Bomb=cfunc::KeyInt2Str(PjSys::key::bomb_p,true);
	cfg.Pad.Slow=cfunc::KeyInt2Str(PjSys::key::slow_p,true);
	cfg.Pad.Pause=cfunc::KeyInt2Str(PjSys::key::pause_p,true);
	cfg.Pad.Exit=cfunc::KeyInt2Str(PjSys::key::exit_p,true);
	cfg.Pad.Laser=cfunc::KeyInt2Str(PjSys::key::laser_p,true);

	cfg.Key.Shot=cfunc::KeyInt2Str(PjSys::key::shot,false);
	cfg.Key.Defender=cfunc::KeyInt2Str(PjSys::key::sub,false);
	cfg.Key.Bomb=cfunc::KeyInt2Str(PjSys::key::bomb,false);
	cfg.Key.Slow=cfunc::KeyInt2Str(PjSys::key::slow,false);
	cfg.Key.Pause=cfunc::KeyInt2Str(PjSys::key::pause,false);
	cfg.Key.Exit=cfunc::KeyInt2Str(PjSys::key::exit,false);
	cfg.Key.Laser=cfunc::KeyInt2Str(PjSys::key::laser,false);
	cfg.Key.UseLaser=PjSys::key::UseLaser;

	cfg.save();
}

void PjSys::key::init(){
	KeyConfigIni cfg;
	cfg.init();

	PjSys::key::shot_p=PjSys::key::keyconv(cfg.Pad.Shot);
	PjSys::key::sub_p=PjSys::key::keyconv(cfg.Pad.Defender);
	PjSys::key::bomb_p=PjSys::key::keyconv(cfg.Pad.Bomb);
	PjSys::key::slow_p=PjSys::key::keyconv(cfg.Pad.Slow);
	PjSys::key::exit_p=PjSys::key::keyconv(cfg.Pad.Exit);
	PjSys::key::pause_p=PjSys::key::keyconv(cfg.Pad.Pause);
	PjSys::key::laser_p=PjSys::key::keyconv(cfg.Pad.Laser);

	PjSys::key::shot=PjSys::key::keyconv(cfg.Key.Shot);
	PjSys::key::sub=PjSys::key::keyconv(cfg.Key.Defender);
	PjSys::key::bomb=PjSys::key::keyconv(cfg.Key.Bomb);
	PjSys::key::slow=PjSys::key::keyconv(cfg.Key.Slow);
	PjSys::key::exit=PjSys::key::keyconv(cfg.Key.Exit);
	PjSys::key::pause=PjSys::key::keyconv(cfg.Key.Pause);
	PjSys::key::laser=PjSys::key::keyconv(cfg.Key.Laser);
	PjSys::key::UseLaser=PjSys::i2b(cfg.Key.UseLaser);

	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::shot_p, PjSys::key::shot, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::sub_p, PjSys::key::sub, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::bomb_p, PjSys::key::bomb, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::slow_p, PjSys::key::slow, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::exit_p, PjSys::key::exit, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::pause_p, PjSys::key::pause, -1, -1,-1 ) ;
	SetJoypadInputToKeyInput( DX_INPUT_PAD1, PjSys::key::laser_p, PjSys::key::laser, -1, -1,-1 ) ;
}
void Enm::drawHP(int AllHP,int NowHP,int Sec){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
	//DrawBox(136,8,504,16,GetColor(0,0,0),true);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
	PjSys::NumDraw(PjSys::SmallNum,Sec,486,24,8);
	DrawBox(136,8,NowHP*368/AllHP+136,16,GetColor(255-(int)(NowHP*128/AllHP),127+(int)(NowHP*128/AllHP),64),true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	DrawBox(136,8,504,16,GetColor(255,255,255),false);
}