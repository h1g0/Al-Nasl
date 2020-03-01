#pragma once
#include "Common.h"
/*#############################################################

						   敵

##############################################################*/

//***************************************************************************************
//敵クラス
//***************************************************************************************

class Enemy{
	int pPhase[100], pImgNo[100],Locked[100];
	double pvx[100][72],pvy[100][72],px[100][72],py[100][72];
	bool pflg[100];

public:
	int c, mflg,mhp,mt,mimg,mreg; //作成するフラグ、及びその他
	double mx,my,mvx,mvy;//〃
	bool mrotate;
	int score[100];

	float mexp,mdeg;
	bool BulletEnd[100],IsRotate[100],IsHitBlt[100],IsHitPlayer[100],HaveItem[100];
	char ItemType[100];
	bool flg[100];
	int hp[100],type[100],btype[100],phase[100],img[100],regx[100],regy[100],deadflg[100],exp[100],rotaflg[100],mphase[100]; //配列
	double x[100],y[100],vx[100],vy[100],expdeg[100]; //配列
	double lvx[100]; //前回のvx
	float expansion[100],deg[100],z[100]; //倍率、及び角度、z距離
	char BPRotate[10]; //ボスの弾幕ローテート
	char BPPhase; //ボスの発狂段階
	int BFrm; //ボスの残り秒数
	int MogiMogiPhase; //ボスの発狂トリガー判定
	void ShowExp(); //爆発表示
	int BExpPhase[EXPLODE_MAX],BExpX[EXPLODE_MAX],BExpY[EXPLODE_MAX],BExpNo[EXPLODE_MAX],bephase;//ボスの爆発関係
	double BExpAngle[EXPLODE_MAX],BExpEx[EXPLODE_MAX];

	int sndSE[10]; //SE関係
	//爆発登録
	int RegistExp(int x, int y, double exp=1.0, int delay=0);
	int SndHit,SndSmallExp,SndBigExp,SndBossExp,SndBuzz;
	int BigExp(int i, int x, int y); //大爆発

	void init(); //初期化

	EBCmd eb1[100];

	Enemy(){c=100;}
	void setcap(int cap){c=cap;}
	//敵生成
	int create(int ehp, double defx, double defy, int movetype,int& eimg, float eexpansion,
			   int rotaptn, int bltptn, int bltcap, int* bltimg,int HitRegionX,int HitRegionY,
			   bool ImgRotate,bool IsHitMyBullet=true, bool IsHitMe=true, bool Item=false,
			   char ItmType=0,float ZOrder=0.4f);

	//敵弾幕変更
	void bltchange(int idx, int* bltimg, int bltcap,int bltptn);

	int Dead(int& i);
	int Move();//動かす

	void ptndead(int& idx);
	void ptn10(int& idx);
	void ptn11(int& idx);
	void ptn12(int& idx);
	void ptn13(int& idx);
	void ptn14(int& idx);
	void ptn15(int& idx);
	void ptn16(int& idx);
	void ptn17(int& idx);
	void ptn18(int& idx);
	void ptn19(int& idx);
	void ptn1a(int& idx);
	void ptn1b(int& idx);
	void ptn1c(int& idx);
	void ptn1d(int& idx);
	void ptn1e(int& idx);
	void ptn1f(int& idx);
	void ptn20(int& idx);
	void ptn21(int& idx);
	void ptn22(int& idx);
	void ptn23(int& idx);
	void ptn24(int& idx);
	void ptn25(int& idx);
	void ptn26(int& idx);
	void ptn27(int& idx);
	void ptn28(int& idx);
	void ptn29(int& idx);
	void ptn2a(int& idx);
	void ptn2b(int& idx);
	void ptn2c(int& idx);
	void ptn2d(int& idx);
	void ptn2e(int& idx);
	void ptn2f(int& idx);

	void ptn3a(int& idx);
	void ptn3b(int& idx);

}; //End of Enemy class.