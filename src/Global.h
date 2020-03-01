#pragma once
#include "Common.h"
//****************************************
//グローバルな名前空間
//****************************************

//=================================================
//自機関係の名前空間。
//変数を追加した際はイニシャライズを忘れないこと！
//=================================================
namespace My{
	void Init();
	extern int_score Score; //スコア
	void AddScore(int i); //スコア加算
	const int Region = 2; //当り範囲
	const int DefaultLeft = 3;
	const int DefaultBomb = 3;
	extern int SndBomb;
	extern int SndExtend;
	extern int SndBombExtend; //ボムのSE
	extern int Left; //残機
	extern int Bomb; //ボム
	void AddLeft(); //残機加算
	void AddBomb(); //ボム加算
	extern int BombFrame; //ボムフラグ
	extern bool IsAutoBomb; //今撃ったボムがオートボムか否か
	extern int BombDeletedBullet; //消した弾の数
	extern bool AutoBomb; //オートボムが使用可能か
	extern double x;
	extern double y; //座標

	extern int SubEnergy; //サブウェポンのエネルギー
	extern char SubLevel; //サブウェポンのレベル
	extern int SubFrame;
	extern int DefFrame; //ディフェンダーのフラグ

	//エネルギー追加
	void AddSubEnergy(int i);
	//自機移動量のスカラ

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
	//自機レーザー
	namespace Laser{
		void Init();
		extern int img;
		extern int hitimg[16];
		extern int ShotSnd;
		extern int Limit; //レーザーの登録上限。レベルによって異なる。
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
		extern int RefCounter[LASER_MAX]; //レーザーが何週目か
		extern int RefCounterMax; //上の最大数
		extern int RefCounterMin; //上の最小数
		extern int Pow(int Counter);

		void Vanish(int idx); //消去
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
	extern int BuzzRegion;//バズる範囲
	extern int NowBuzz;//バズってるか？
	extern int BuzzLv; //バズのレベル
	extern int BuzzLvFrame;
	extern int imgRegion;
	extern int imgLeftTimeGaze; //サブウェポンの残り時間ゲージ
	extern int imgBuzz; //バズってる

	extern int SubEnergyMax;
	void CalcSubEnergyMax();

	extern int Model; //3Dモデル
	extern int burner;
	extern bool IsBurner; //アフタバーナーを表示するか？
	extern float Rot; //機体軸の回転
	extern float fLoop;
	extern float Exp; //拡大率

	//アイテム
	namespace Item{
		extern bool Exist[16]; //存在するか？
		extern int GeneralImg[8]; //モデルの原型
		extern float exp[8];//拡大率
		extern int img[16]; //個々のモデル
		extern int x[16];
		extern int y[16]; //座標
		extern double vx[16],vy[16]; //ベクトル
		extern char type[16]; //タイプ
		extern int phase[16]; //フェーズ
		extern int SndGet; //取得したときの効果音
		void Init(); //全て初期化
		//追加
		int Add(int AddX, int AddY, double AddVX, double AddVY, char AddType);
	}
}

//=================================================
//システム関係の名前空間。
//変数を追加した際はイニシャライズを忘れないこと！
//=================================================
namespace PjSys{
	void Init();
/******** 設定項目 *************/
	//extern bool IsWnd; //フルスクリーンか否か
	//extern double WndExRate;
	//extern int ColorBit; //カラービット数
	//extern bool UseVSync;
	//extern bool OutputDebugFile; //デバッグファイルを出力するか否か
	extern bool ShowGuide; //当り判定ガイドを表示するか否か
	extern bool ShowInsane; //隠し難易度のInsaneを表示するか
	extern int GameLevel; //表面上の難易度。0:Insane 1:Hard 2:Standard 3:Easy
	extern int Hard; //実質的な難易度　7:最易～1:最難
	extern int HardConst; //実質的な難易度(↑の固定版)
	void SetLank(); //ランク調整
	//extern bool ShowTrack; //弾幕の軌跡を表示するか
	//extern bool ShowProspect;//弾幕の予測表示
	extern bool IrodoriMode; //Another Mode::IRODORI MODE(彩モード：弾速が早くなる)
	extern bool AccelMode; //Another Mode::ACCELERATOR MODE(アクセルモード：弾が加速)
	//void LoadSetting(); //設定をロード
	//void SaveSetting(); //設定をセーブ
	bool i2b(int i);

	namespace cheat{
		extern bool Inv; //常に無敵
		extern bool Go2Boss; //ボス戦へ飛ばすか
		extern bool Peacist; //敵が弾を撃ってこない
		extern bool LevelMax; //常にレベル5
	}
	//extern bool English; //英語か否か
	//extern int SEVolume;
	//extern int Volume;
	extern int bgm;
	extern int bossbgm;
	extern int BGMLoadMode;
	//extern bool IsSoftSound; //ソフトウェアで音を処理するか
	//extern int UseAntiAliasing;

	//BGMLoadModeからDxLibの値に変換
	//void SetBGMLoadMode(int i);
	//DxLibの値からBGMLoadModeに変換
	//int GetBGMLoadMode(int i);

	extern int Extend; //エクステンドする点数
	extern int BombExtend; //ボムがエクステンドする点数

	extern int StartStage; //スタートするステージ

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
/******** 設定終了 ************/
	//extern string_t Path;
	extern int MainChar[7];//大きな文字(98x16)　([0]FPS:[1]SCORE:[2]STOCK:[3]BOMB:[4]STAGE:[5]CREDIT:[6]LEVEL:)
	extern int MainNum[10];//大きな数字(16x16)
	extern int SmallChar[8];//小さな文字(8x16) ([0]:EXTENDED [1]:BOMB++ [2]:W.E.P.)
	extern int SmallNum[10]; //小さな数字(8x16)
	extern int FPSChar;//FPSの文字
	extern int Gaze[16];//サブウェポンゲージ(16x256)
	extern int GazeFrame;//サブウェポンゲージのフレーム(16x256)
	extern int GazeChar[2];//サブウェポンの文字(16x128)
	extern int BuzzCnt; //バズりカウンタ
	extern int ImgNull; //空白の画像
	extern bool Exit; //終了するフラグ
	extern bool CanExit;
	extern int mHardImg[4]; //難易度表示
	extern int ExtendPhase;
	extern int BombExtendPhase; //エクステンドのフェーズ
	//画面をぶるぶるするエフェクト
	namespace Scr{
		extern int IsArcade_Like; //アーケードっぽくするオマケ。
		extern bool ACKey;
		void Arcade_Like();

		extern bool AvaliableShake; //ぶるぶるが有効か
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
	//スクリーンショット
	extern DATEDATA Date;
	extern int ssf;
	extern int ssec;
	extern int scnt;
	void ScreenShot();
	extern bool IsScreenShot;
	// 数値をグラフィック表示する関数
	void NumDraw(int* img, unsigned int Num,int stx,int sty,int width, double exp =1.0);
	//ガイドを表示する
	void DrawGuide(int x1,int y1, int x2, int y2);
	extern float CameraVRota;
	extern float CameraHRota;
	extern float CameraTRota;
	extern DxLib::VECTOR CameraPos;
}

//=================================================
//敵関係の名前空間。
//変数を追加した際はイニシャライズを忘れないこと！
//=================================================

#define REFUGE_MAX 10 //無敵地帯の最大数
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

	namespace Refuge{ //敵弾と敵レーザーを防ぐ無敵地帯
		extern bool AnyAvaliable; //1つでも無敵地帯が存在するか？
		extern bool flg[REFUGE_MAX];
		extern int x[REFUGE_MAX];
		extern int y[REFUGE_MAX];
		extern int width[REFUGE_MAX];
		extern int height[REFUGE_MAX];
	}
}