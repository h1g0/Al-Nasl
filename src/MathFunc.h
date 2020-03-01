#pragma once
#ifndef __MATHFUNC
#define __MATHFUNC

#define PI 3.1415926535897932384626433832795 //��=3.14159265...
#define RIGHT_ANGLE PI/2 //��/2=90��
#define PI_F 3.1415926535897932384626433832795f
#define RIGHT_ANGLE_F PI_F/2.0f
#define RAD PI/180

//======================
//�����O�p�֐��֌W
//======================
#define TABLESIZE 128 //2�̏搔�ł��邱��
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

//2���x�W�F�Ȑ��擾
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

//��]��`�Γ_�̃R���W��������
int CheckHitRotaRect(int x, int y, int cx, int cy, double angle, int width, int height);

//NumDivideBy�Ŋ���؂��NumDivided�ȉ��̍ő吔
int NumDividable(const int NumDivided,const int NumDivideBy);

/********************************************
���w�I�֐��������N���X
*********************************************/
class math{
public:
	//�x�����W�A���ɕϊ�
	double ToRadian(double Degrees);
	//���W�A����x�ɕϊ�
	double ToDegree(double Radian);
	//�����蔻��
	int hitcheck(double x1, double y1, int Width1, int Height1,
				 double x2, double y2, int Width2, int Height2);
	//�x�N�g���������烉�W�A���ɕϊ�
	double vec2rad(const double& vx, const double& vy);
	//�x�N�g���������烉�W�A���ɕϊ�
	double vec2rad2(const double& vx, const double& vy);

	//2�̍��W����T�C����Ԃ�
	double getcos(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//2�̍��W����R�T�C����Ԃ�
	double getsin(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//m����n�܂ł̐����������_���ŕԂ�
	int irand(int m,int n);
	//2�̍��W�Ԃ̋��������߂�
	double GetDist(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
	//2�̍��W�Ԃ̋��������߂�(�኱����)
	double GetDist2(const double& FromX,const double& FromY,const double& ToX,const double& ToY);
};

#endif