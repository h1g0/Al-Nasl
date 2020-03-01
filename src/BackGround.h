#pragma once
#include "Common.h"
/*#############################################################

						   画面構成

##############################################################*/

//3D関係の背景クラス
class bg3d{
private:
	int FCnt; //位置カウンタ
public:
	//TODO: 余裕があったらセッタとゲッタ書く
	int hField, hField2 ,Scr; //モデル1、モデル2、スクロール速度
	bg3d(){}//コンストラクタ
	void imgset(int g1,int scroll); //モデルセット
	void changespeed(int speed); //スクロール速度変更
	void move(); //動かす
};

//2Dの背景クラス
class bgmain{
private:
	int y1,y2; //各画像のY座標
	int img1; //画像情報1
	int img2;//画像情報2
	int sspeed; //スクロール速度
public:
	bgmain(){}//コンストラクタ
	void imgset(int g1, int g2, int scroll); //画像1、画像2、スクロール速度をセット
	void move(); //動かす
};

//2Dの背景クラスその2
class bgsub{
private:
	int sspeed; //スクロール速度
	int y1,y2; //各画像のY座標
	int img1; //画像情報1
	int img2;
public:
	//TODO: 手を抜かずにゲッタとセッタを書くべき

	bool Visible; //表示するか？
	int alpha; //透明度
	bgsub(); //コンストラクタ
	void imgset(int g1, int g2, int scroll); //画像とスクロール速度をセット
	void move(); //動かす
};

//画面脇の情報群
class bgside{
private:
	int GrBGL,GrBGR;
	unsigned int phase,score;
	int gzPhase, gzCnt;
public:
	bgside(){}//コンストラクタ
	void imgset(int imgLeft, int imgRight); //左右の画像をセット
	void draw(); //描画
};