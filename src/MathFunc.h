#pragma once
#ifndef __MATHFUNC
#define __MATHFUNC

#define PI 3.1415926535897932384626433832795 //π=3.14159265...
#define RIGHT_ANGLE PI/2 //π/2=90°
#define PI_F 3.1415926535897932384626433832795f
#define RIGHT_ANGLE_F PI_F/2.0f
#define RAD PI/180

//======================
//高速三角関数関係
//======================
#define TABLESIZE 128 //2の乗数であること
#define SUBBIT    8
#define SUBINDEX  (1 << SUBBIT)
#define I_PI      (TABLESIZE * SUBINDEX * 2)
#define I_HPI     (TABLESIZE * SUBINDEX)

extern const unsigned short sin_table[];
extern const double atan_table[];
extern const int atan_table_num;

double mysin(double x);
double mycos(double rad);
float mysin(float x);
float mycos(float rad);
double myatan2(double y, double x);
float myatan2(float y, float x);

//2次ベジェ曲線取得
void Get2DBezier(double StartX, double StartY,
			   double EndX,   double EndY,
			   double CtrlX,  double CtrlY,
			   int DivNum,    int NowPhase,
			   double* RtnX,  double* RtnY,
			   double* RtnV, double* RtnRadian);

void Get2DBezier(double StartX, double StartY,
			   double EndX,   double EndY,
			   double CtrlX,  double CtrlY,
			   int DivNum,    int NowPhase,
			   double* RtnX,  double* RtnY);

//回転矩形対点のコリジョン判定
int CheckHitRotaRect(int x, int y, int cx, int cy, double angle, int width, int height);

//NumDivideByで割り切れるNumDivided以下の最大数
int NumDividable(const int NumDivided,const int NumDivideBy);

/********************************************
数学的関数を扱うクラス
*********************************************/
class math{
public:
	//度をラジアンに変換
	double ToRadian(double Degrees);
	//ラジアンを度に変換
	double ToDegree(double Radian);
	//当たり判定
	int hitcheck(double x1, double y1, int Width1, int Height1,
				 double x2, double y2, int Width2, int Height2);
	//ベクトル成分からラジアンに変換
	double vec2rad(const double& vx, const double& vy);
	//ベクトル成分からラジアンに変換
	double vec2rad2(const double& vx, const double& vy);

	//2つの座標からサインを返す
	double getcos(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//2つの座標からコサインを返す
	double getsin(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//mからnまでの整数をランダムで返す
	int irand(int m,int n);
	//2つの座標間の距離を求める
	double GetDist(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//2つの座標間の距離を求める(若干高速)
	double GetDist2(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
};

#endif