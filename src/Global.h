#pragma once
#include "Common.h"
//****************************************
//�O���[�o���Ȗ��O���
//****************************************

//=================================================
//���@�֌W�̖��O��ԁB
//�ϐ���ǉ������ۂ̓C�j�V�����C�Y��Y��Ȃ����ƁI
//=================================================
namespace My{
	void Init();
	extern int_score Score; //�X�R�A
	void AddScore(int i); //�X�R�A���Z
	const int Region = 2; //����͈�
	const int DefaultLeft = 3;
	const int DefaultBomb = 3;
	extern int SndBomb;
	extern int SndExtend;
	extern int SndBombExtend; //�{����SE
	extern int Left; //�c�@
	extern int Bomb; //�{��
	void AddLeft(); //�c�@���Z
	void AddBomb(); //�{�����Z
	extern int BombFrame; //�{���t���O
	extern bool IsAutoBomb; //���������{�����I�[�g�{�����ۂ�
	extern int BombDeletedBullet; //�������e�̐�
	extern bool AutoBomb; //�I�[�g�{�����g�p�\��
	extern double x;
	extern double y; //���W

	extern int SubEnergy; //�T�u�E�F�|���̃G�l���M�[
	extern char SubLevel; //�T�u�E�F�|���̃��x��
	extern int SubFrame;
	extern int DefFrame; //�f�B�t�F���_�[�̃t���O

	//�G�l���M�[�ǉ�
	void AddSubEnergy(int i);
	//���@�ړ��ʂ̃X�J��

	namespace sw{
		extern int sndLv[5];
	}
	namespace Bullet{
		extern bool flg[MBCAP];
		extern int x[MBCAP];
		extern int y[MBCAP];
		extern bool IsHit[MBCAP];
		extern int frm;
		extern int pow1;
		extern int pow2;
		extern int region;
		extern int pbFire[2][8];
		extern bool EffFlg[5];
		extern int EffX[5];
		extern int EffY[5];
		extern int EffImg[2][8];
		extern int EffFrm[5];
	}
	//���@���[�U�[
	namespace Laser{
		void Init();
		extern int img;
		extern int hitimg[16];
		extern int ShotSnd;
		extern int Limit; //���[�U�[�̓o�^����B���x���ɂ���ĈقȂ�B
		extern bool flg[LASER_MAX];
		extern bool IsDemo;
		extern double sx[LASER_MAX];
		extern double sy[LASER_MAX];
		extern double cx[LASER_MAX];
		extern double cy[LASER_MAX];
		extern double ex[LASER_MAX];
		extern double ey[LASER_MAX];
		extern double x[LASER_MAX][LASER_TRACE_MAX];
		extern double y[LASER_MAX][LASER_TRACE_MAX];
		extern double px[LASER_MAX][LASER_TRACE_MAX][4];
		extern double py[LASER_MAX][LASER_TRACE_MAX][4];

		extern double v[LASER_MAX][LASER_TRACE_MAX];
		extern double Dist[LASER_MAX];

		extern double vx[LASER_MAX];
		extern double vy[LASER_MAX];
		extern double angle[LASER_MAX][LASER_TRACE_MAX];
		extern int phase[LASER_MAX];
		extern int StartPhase[LASER_MAX];
		extern int tx[LASER_MAX];
		extern int ty[LASER_MAX];
		extern int vanishcount[LASER_MAX];
		extern bool IsVanish[LASER_MAX];
		extern bool ReplaceFlg[LASER_MAX];
		extern bool TargetFlg[LASER_MAX];
		extern int TargetID[LASER_MAX];
		extern long TargetDist[LASER_MAX];
		extern int RefCounter[LASER_MAX]; //���[�U�[�����T�ڂ�
		extern int RefCounterMax; //��̍ő吔
		extern int RefCounterMin; //��̍ŏ���
		extern int Pow(int Counter);

		void Vanish(int idx); //����
		int Regist();
		void Move();
		void WriteStatus(int x,int y);
	}

	extern bool IsHit;
	extern bool Move;
	extern bool Born;
	extern bool shooting;
	extern bool IsHitFrm;
	extern bool NowInv;
	extern bool GOver;
	extern bool Pause;
	extern int Invincible;
	extern int particle[8];
	extern int NowStage;
	extern int chartip;
	extern int ctphase;
	extern int numtip;
	extern int ntphase;
	extern int BuzzRegion;//�o�Y��͈�
	extern int NowBuzz;//�o�Y���Ă邩�H
	extern int BuzzLv; //�o�Y�̃��x��
	extern int BuzzLvFrame;
	extern int imgRegion;
	extern int imgLeftTimeGaze; //�T�u�E�F�|���̎c�莞�ԃQ�[�W
	extern int imgBuzz; //�o�Y���Ă�

	extern int SubEnergyMax;
	void CalcSubEnergyMax();

	extern int Model; //3D���f��
	extern int burner;
	extern bool IsBurner; //�A�t�^�o�[�i�[��\�����邩�H
	extern float Rot; //�@�̎��̉�]
	extern float fLoop;
	extern float Exp; //�g�嗦

	//�A�C�e��
	namespace Item{
		extern bool Exist[16]; //���݂��邩�H
		extern int GeneralImg[8]; //���f���̌��^
		extern float exp[8];//�g�嗦
		extern int img[16]; //�X�̃��f��
		extern int x[16];
		extern int y[16]; //���W
		extern double vx[16],vy[16]; //�x�N�g��
		extern char type[16]; //�^�C�v
		extern int phase[16]; //�t�F�[�Y
		extern int SndGet; //�擾�����Ƃ��̌��ʉ�
		void Init(); //�S�ď�����
		//�ǉ�
		int Add(int AddX, int AddY, double AddVX, double AddVY, char AddType);
	}
}

//=================================================
//�V�X�e���֌W�̖��O��ԁB
//�ϐ���ǉ������ۂ̓C�j�V�����C�Y��Y��Ȃ����ƁI
//=================================================
namespace PjSys{
	void Init();
/******** �ݒ荀�� *************/
	//extern bool IsWnd; //�t���X�N���[�����ۂ�
	//extern double WndExRate;
	//extern int ColorBit; //�J���[�r�b�g��
	//extern bool UseVSync;
	//extern bool OutputDebugFile; //�f�o�b�O�t�@�C�����o�͂��邩�ۂ�
	extern bool ShowGuide; //���蔻��K�C�h��\�����邩�ۂ�
	extern bool ShowInsane; //�B����Փx��Insane��\�����邩
	extern int GameLevel; //�\�ʏ�̓�Փx�B0:Insane 1:Hard 2:Standard 3:Easy
	extern int Hard; //�����I�ȓ�Փx�@7:�ňՁ`1:�œ�
	extern int HardConst; //�����I�ȓ�Փx(���̌Œ��)
	void SetLank(); //�����N����
	//extern bool ShowTrack; //�e���̋O�Ղ�\�����邩
	//extern bool ShowProspect;//�e���̗\���\��
	extern bool IrodoriMode; //Another Mode::IRODORI MODE(�ʃ��[�h�F�e���������Ȃ�)
	extern bool AccelMode; //Another Mode::ACCELERATOR MODE(�A�N�Z�����[�h�F�e������)
	//void LoadSetting(); //�ݒ�����[�h
	//void SaveSetting(); //�ݒ���Z�[�u
	bool i2b(int i);

	namespace cheat{
		extern bool Inv; //��ɖ��G
		extern bool Go2Boss; //�{�X��֔�΂���
		extern bool Peacist; //�G���e�������Ă��Ȃ�
		extern bool LevelMax; //��Ƀ��x��5
	}
	//extern bool English; //�p�ꂩ�ۂ�
	//extern int SEVolume;
	//extern int Volume;
	extern int bgm;
	extern int bossbgm;
	extern int BGMLoadMode;
	//extern bool IsSoftSound; //�\�t�g�E�F�A�ŉ����������邩
	//extern int UseAntiAliasing;

	//BGMLoadMode����DxLib�̒l�ɕϊ�
	//void SetBGMLoadMode(int i);
	//DxLib�̒l����BGMLoadMode�ɕϊ�
	//int GetBGMLoadMode(int i);

	extern int Extend; //�G�N�X�e���h����_��
	extern int BombExtend; //�{�����G�N�X�e���h����_��

	extern int StartStage; //�X�^�[�g����X�e�[�W

	namespace key{
		extern int shot_p;
		extern int shot;
		extern int sub_p;
		extern int sub;
		extern int laser;
		extern int laser_p;
		extern bool UseLaser;

		extern int bomb_p;
		extern int bomb;
		extern int slow_p;
		extern int slow;
		extern int exit_p;
		extern int exit;
		extern int pause_p;
		extern int pause;

		extern bool vib;
		extern bool sbconv;
		int keyconv(string_t str);
		void load();
		void save();
		void init();
	}
	namespace font{
		extern int caption;
		extern int log;
		//extern int menu;
	}
/******** �ݒ�I�� ************/
	//extern string_t Path;
	extern int MainChar[7];//�傫�ȕ���(98x16)�@([0]FPS:[1]SCORE:[2]STOCK:[3]BOMB:[4]STAGE:[5]CREDIT:[6]LEVEL:)
	extern int MainNum[10];//�傫�Ȑ���(16x16)
	extern int SmallChar[8];//�����ȕ���(8x16) ([0]:EXTENDED [1]:BOMB++ [2]:W.E.P.)
	extern int SmallNum[10]; //�����Ȑ���(8x16)
	extern int FPSChar;//FPS�̕���
	extern int Gaze[16];//�T�u�E�F�|���Q�[�W(16x256)
	extern int GazeFrame;//�T�u�E�F�|���Q�[�W�̃t���[��(16x256)
	extern int GazeChar[2];//�T�u�E�F�|���̕���(16x128)
	extern int BuzzCnt; //�o�Y��J�E���^
	extern int ImgNull; //�󔒂̉摜
	extern bool Exit; //�I������t���O
	extern bool CanExit;
	extern int mHardImg[4]; //��Փx�\��
	extern int ExtendPhase;
	extern int BombExtendPhase; //�G�N�X�e���h�̃t�F�[�Y
	//��ʂ��Ԃ�Ԃ邷��G�t�F�N�g
	namespace Scr{
		extern int IsArcade_Like; //�A�[�P�[�h���ۂ�����I�}�P�B
		extern bool ACKey;
		void Arcade_Like();

		extern bool AvaliableShake; //�Ԃ�Ԃ邪�L����
		extern int MoveX;
		extern int MoveY;
		extern int MoveFrame;
		extern int MoveFrameConst;
		extern int MaxShake;
		extern int MinShake;
		extern int RmtX;
		extern int RmtY;
		extern int sx;
		extern int sy;
		void SetShake(int Frame, int Min, int Max);
		void Shake();

		extern string_t LogChar[10];
		extern int LogFrm[10];
		extern int LogCol[10];
		extern int LogInt[10];
		void AddLog(string_t str ,int iscr,int color);
		extern DxLib::COLOR_F BGColor;
		extern bool BGWire;
		extern int BGModel;

		extern int BurstFrm;
		extern int BurstImg;
		extern int BurstX;
		extern int BurstY;
		extern int BurstSpeed;
		extern int BurstColor[3];
		extern int BurstDivision;
		extern int BurstThickness;
		extern bool BurstAbsorb;
		void SetBurst(int x, int y, int speed=12, int div=40,int r=255,int g=255,int b=255, bool absorb=false,int thickness=16);
		void MoveBurst();
		extern int IsNoise;
		void DrawNoise();

		extern int NoiseImg[100];
		extern int NoiseAlpha;
	}
	void DrawFPS(int x,int y,int fps,int def_fps = 60);
	//�X�N���[���V���b�g
	extern DATEDATA Date;
	extern int ssf;
	extern int ssec;
	extern int scnt;
	void ScreenShot();
	extern bool IsScreenShot;
	// ���l���O���t�B�b�N�\������֐�
	void NumDraw(int* img, unsigned int Num,int stx,int sty,int width, double exp =1.0);
	//�K�C�h��\������
	void DrawGuide(int x1,int y1, int x2, int y2);
	extern float CameraVRota;
	extern float CameraHRota;
	extern float CameraTRota;
	extern DxLib::VECTOR CameraPos;
}

//=================================================
//�G�֌W�̖��O��ԁB
//�ϐ���ǉ������ۂ̓C�j�V�����C�Y��Y��Ȃ����ƁI
//=================================================

#define REFUGE_MAX 10 //���G�n�т̍ő吔
namespace Enm{
	void Init();
	extern int BltRegion;
	extern int ImgBltItem[16];
	extern int SmallExplode[8][16];
	//int BigExplode[16];
	extern int BossPhase;
	extern int LaserUnlockNum[100];
	void drawHP(int AllHP,int NowHP,int Sec);
	extern int SndBuzz;
	extern int SndRef;
	extern int SndShot;
	extern int FireFlare;
	extern int imgBurn[16];
	extern int imgAB[4];

	extern int RBullet[4];
	extern int GBullet[4];
	extern int BBullet[4];
	extern int RLaser[4];
	extern int GLaser[4];
	extern int BLaser[4];
	extern int YLaser[4];
	extern int OLaser[4];

	namespace Refuge{ //�G�e�ƓG���[�U�[��h�����G�n��
		extern bool AnyAvaliable; //1�ł����G�n�т����݂��邩�H
		extern bool flg[REFUGE_MAX];
		extern int x[REFUGE_MAX];
		extern int y[REFUGE_MAX];
		extern int width[REFUGE_MAX];
		extern int height[REFUGE_MAX];
	}
}