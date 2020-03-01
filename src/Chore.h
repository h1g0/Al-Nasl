#pragma once
#include "Common.h"
//****************************************
//Mainを見やすくするために移動した雑用関数群。
//****************************************

//キーコンフィグ用の、キー文字列から数値へ変換する関数。
namespace cfunc{
	int KeyStr2Int(string_t str);
	//キーコンフィグ用の、数値から文字列へ変換する関数。
	string_t KeyInt2Str(int num, bool isPad=false);

	int KeyInt2PadNo(int num);
	int WhichButtonPressed();

	int WhichKeyPressed();

	extern string_t KeyName;
	void KeyInt2Chr(int num);

	string_t ReplaceKeyNameAll(string_t str);
	void ReplaceKeyName(string_t& str, string_t id, int& key, bool IsPad);
}

//=========================================================
//ベイパー関係
//=========================================================
#define VAPOR_NUM 2 //ベイパーは何本か
#define VAPOR_PARTS_NUM 24 //1本を構成する部品の個数
#define VAPOR_DIST 16 //部品一つ一つの距離

namespace Vapor{
	extern bool VisibleAll; //全体を表示するか否か
	extern bool Visible[VAPOR_NUM][VAPOR_PARTS_NUM]; //表示するかどうか
	//x,yの位置関係:
	//0- 1- 2- 3- 4- 5- 6- 7- 8- 9- 10- 11- 12- 13- 14- 15...
	extern double x[VAPOR_NUM][VAPOR_PARTS_NUM];
	extern double y[VAPOR_NUM][VAPOR_PARTS_NUM];
	extern int Alpha[VAPOR_NUM][VAPOR_PARTS_NUM]; //透明度

	extern bool IsMake[VAPOR_NUM];
	extern double MakeX[VAPOR_NUM];
	extern double MakeY[VAPOR_NUM];
	extern int MakeAlpha[VAPOR_NUM];

	//初期化
	void Init();

	//ベイパー生成
	int Make(int idx, double SetX, double SetY,int SetAlpha);

	//ベイパー動かす
	void Move();
}

//画面をキャプチャして返す
int GetScrCapture(int CenterX,int CenterY,int Width, int Height);

//死んだ時に画像表示
#define DEADIMG_WIDTH  48
#define DEADIMG_HEIGHT 48
#define DEADIMG_EXP 2

namespace DeadImg{
	extern int frm;
	extern int frm_start;
	extern int img;
	void Set(int x,int y,int frame);
	void Draw(int x,int y);
}

//疑似ブラー
namespace Blur{
	extern int frm;
	extern int frm_start;
	extern int layer;
	extern double vx,vy,exp,cx,cy;
	void set(int CenterX=320,int CenterY=240,int Frame=60,
			 int LayerNum=5, double MoveX=0, double MoveY=0, double Expand=0.01);

	int move();
}

namespace BGMTitle{
	extern int Frame;
	extern int fnt;
	extern string_t str;
	void Set(string_t String);
	void Draw();
}