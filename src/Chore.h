#pragma once
#include "Common.h"
//****************************************
//Main�����₷�����邽�߂Ɉړ������G�p�֐��Q�B
//****************************************

//�L�[�R���t�B�O�p�́A�L�[�����񂩂琔�l�֕ϊ�����֐��B
namespace cfunc{
	int KeyStr2Int(string_t str);
	//�L�[�R���t�B�O�p�́A���l���當����֕ϊ�����֐��B
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
//�x�C�p�[�֌W
//=========================================================
#define VAPOR_NUM 2 //�x�C�p�[�͉��{��
#define VAPOR_PARTS_NUM 24 //1�{���\�����镔�i�̌�
#define VAPOR_DIST 16 //���i���̋���

namespace Vapor{
	extern bool VisibleAll; //�S�̂�\�����邩�ۂ�
	extern bool Visible[VAPOR_NUM][VAPOR_PARTS_NUM]; //�\�����邩�ǂ���
	//x,y�̈ʒu�֌W:
	//0- 1- 2- 3- 4- 5- 6- 7- 8- 9- 10- 11- 12- 13- 14- 15...
	extern double x[VAPOR_NUM][VAPOR_PARTS_NUM];
	extern double y[VAPOR_NUM][VAPOR_PARTS_NUM];
	extern int Alpha[VAPOR_NUM][VAPOR_PARTS_NUM]; //�����x

	extern bool IsMake[VAPOR_NUM];
	extern double MakeX[VAPOR_NUM];
	extern double MakeY[VAPOR_NUM];
	extern int MakeAlpha[VAPOR_NUM];

	//������
	void Init();

	//�x�C�p�[����
	int Make(int idx, double SetX, double SetY,int SetAlpha);

	//�x�C�p�[������
	void Move();
}

//��ʂ��L���v�`�����ĕԂ�
int GetScrCapture(int CenterX,int CenterY,int Width, int Height);

//���񂾎��ɉ摜�\��
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

//�^���u���[
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