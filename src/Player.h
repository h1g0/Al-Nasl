#pragma once
#include "Common.h"
/*#############################################################

						   プレーヤー自機

##############################################################*/

/*==============================================================
自弾クラス
===============================================================*/
class PBullet{
	int pbNo[MBCAP],pbImg[MBCAP],pbIdx[MBCAP]; //弾のフラグ、画像
	float pbx[MBCAP], pby[MBCAP], pbvx[MBCAP], pbvy[MBCAP], pbrad[MBCAP]; //弾の座標、ベクトル、角度(ラジアン)
	int mkflg, mkx, mky, mkidx; //作成するフラグ、その時のx,y
	int mkImg; //画像
	double mkDeg,mkScl; //作成した時の角度、進行量
public:
	int Cap;
	PBullet(){}
	int imgset(int bimage); //画像セット
	void Init(); //初期化
	//弾の作成
	void create(int x, int y, double Deg, double scalar, int idx);
	//移動、及び描画
	void move();
};

/*==========================================================
プレイヤークラス
===========================================================*/

class Player{
	double bangle; //自ショットの角度
	int imgNo;
	int pPhase, pImgNo[180];
	int PauseKey, PausePhase; //ポーズ関係のキーとフェーズ
	bool NowPause; //今のフェーズ
	double pvx[180],pvy[180],px[180],py[180];
	//int knmphase,knmkey[6];
	int swkeycheck;
	int swflg;
	bool IsBGMPaused;
	bool IsBossBGMPaused;

	bool IsSlow; //移動が低速か？

	double SubDeg;

	int frmLRoll,frmRRoll;

	static const int SpeedNormal=4; //通常の移動速度
	static const int SpeedSlow=2; //低速時の移動速度

public:
	int SndDead,SndBorn,SndShoot,SndDefS,SndDefE,SndSubS;
	PBullet pbStraight[5];
	Player(){
		mx = 0;
		my = 0;
		for(int i=0;i<5;i++){pbStraight[i].Cap=50;}
		//pbSub.Cap=500;
	}
	~Player(){}
	//typedef double Coordinates;

	double mx,my;
	double getX(){return mx;}
	double getY(){return my;}
	void clearParticle(){pPhase=0;}
	void setX(double x){mx = x;}
	void setY(double y){my = y;}
	void setXY(double x,double y){
		setX(x);
		setY(y);
	}
	void addX(double x){mx += x;}
	void addY(double y){my += y;}
	bool GetIsSlow(){return IsSlow;}

	int Pause(int& img);
	int GameOver(int& img);
	int Dead();
	int Born(int* img,int &eff);
	void Bomb(int& img);
	void Move();
	void Draw(int* img,int* inv);//描画
};