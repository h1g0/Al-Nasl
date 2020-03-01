#pragma once
#include "Common.h"
/*#############################################################

                           敵弾

##############################################################*/

//***************************************************************************************
//敵弾クラス
//***************************************************************************************
class EBullet{
public:
	int queue, phase, flg ,imgidx,imgc, *img,snipe,dead,parent_dead,buzzfrm;
	double x, y,*px,*py,vx,vy,deg,scl,snpdeg;
	bool visible,disapear;

	EBullet();

	void Init();

	//敵弾通常定義。引数: 敵弾画像・敵弾を発射する座標、進行量、キュー
	void def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue);
	//void def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue,double& defdeg);

	//敵弾進行量再定義。引数: 進行量(速さ。vxとvyを別々にmycos()とmysin()を使って定義する)
	void vectordef(double& defvx, double& defvy);
	//void vectordef(double& defvx, double& defvy,double& defdeg);

	//自機狙い敵弾定義。引数: 敵弾画像・敵弾を発射する座標、進行量(速さ)、自機から何度離すか(ラジアンではない)・キュー
	void snipedef(int& bimg,double& defx, double& defy, double scalar, double defdeg, int& defqueue);

	//自機狙い敵弾再定義。引数:進行量(速さ)、自機から何度離すか(ラジアンではない)
	void sniperedef(double scalar, double defdeg);

	//画面上に存在する場合1、飛び出した場合-1、キュー中の場合0
	int Move(); //動かす
};

//***************************************************************************************
//敵弾幕指示クラス
//***************************************************************************************
class EBCmd{
	int l;
public:
	int vanishfrm;
	//TODO: この辺は新しいクラスとして独立させるべき。更にstd::vectorで管理できないか？
	EBullet eb[EBCAP];
	int c, q[EBCAP],  p[EBCAP], *img,t,cp,k,dead,parent_dead,tmp[20];
	double x[EBCAP], y[EBCAP],*px,*py,vx,vy,deg;

	/*
	double tx[8][10];
	double ty[8][10];
	double tvx[8][10];
	double tvy[8][10];
	*/
	EBCmd();

	//初期化
	void init();

	//画像をセット
	void setimg(int* ebimg);

	//動かす
	int Move();

	//敵弾幕生成。引数: 撃つ敵弾数・弾幕の種類・撃つ座標
	void Create(int cap, int type, double& defx, double& defy);

	void ptndead(int& idx);
	void ptn100(int& idx);
	void ptn101(int& idx);
	void ptn102(int& idx);
	void ptn103(int& idx);
	void ptn104(int& idx);
	void ptn105(int& idx);
	void ptn106(int& idx);
	void ptn107(int& idx);
	void ptn108(int& idx);
	void ptn109(int& idx);
	void ptn10a(int& idx);
	void ptn10b(int& idx);
	void ptn10c(int& idx);
	void ptn10d(int& idx);
	void ptn10e(int& idx);
	void ptn10f(int& idx);
	void ptn1a1(int& idx);
	void ptn1a2(int& idx);
	void ptn1a3(int& idx);
	void ptn1a4(int& idx);
	void ptn1a5(int& idx);
	void ptn1a6(int& idx);
	void ptn1a7(int& idx);
	void ptn1a8(int& idx);
	void ptn1a9(int& idx);
	/*
	void ptn1aa(int& idx);
	void ptn1ab(int& idx);
	void ptn1ac(int& idx);
	void ptn1ad(int& idx);
	void ptn1ae(int& idx);
	void ptn1af(int& idx);
*/
	void ptn200(int& idx);
	void ptn201(int& idx);
	void ptn202(int& idx);
	void ptn203(int& idx);
	void ptn204(int& idx);
	void ptn205(int& idx);
	void ptn206(int& idx);
	void ptn207(int& idx);
	void ptn208(int& idx);
	void ptn209(int& idx);
	void ptn20a(int& idx);
	void ptn20b(int& idx);
	void ptn20c(int& idx);
	void ptn20d(int& idx);
	void ptn20e(int& idx);
	void ptn20f(int& idx);

	void ptn300(int& idx);
	void ptn301(int& idx);
	void ptn302(int& idx);
	void ptn303(int& idx);
	void ptn304(int& idx);
	void ptn305(int& idx);
	void ptn306(int& idx);
	void ptn307(int& idx);
	void ptn308(int& idx);
	void ptn309(int& idx);
	void ptn30a(int& idx);
	void ptn30b(int& idx);
	void ptn30c(int& idx);
	void ptn30d(int& idx);
	void ptn30e(int& idx);
	void ptn30f(int& idx);

	void ptn3a0(int& idx);
	void ptn3a1(int& idx);
	void ptn3a2(int& idx);
	void ptn3a3(int& idx);
	void ptn3a4(int& idx);
	void ptn3a5(int& idx);
	void ptn3a6(int& idx);
	void ptn3a7(int& idx);
	void ptn3a8(int& idx);
	void ptn3a9(int& idx);

}; //End of EBCmd class.