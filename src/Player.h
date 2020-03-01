#pragma once
#include "Common.h"
/*#############################################################

						   �v���[���[���@

##############################################################*/

/*==============================================================
���e�N���X
===============================================================*/
class PBullet{
	int pbNo[MBCAP],pbImg[MBCAP],pbIdx[MBCAP]; //�e�̃t���O�A�摜
	float pbx[MBCAP], pby[MBCAP], pbvx[MBCAP], pbvy[MBCAP], pbrad[MBCAP]; //�e�̍��W�A�x�N�g���A�p�x(���W�A��)
	int mkflg, mkx, mky, mkidx; //�쐬����t���O�A���̎���x,y
	int mkImg; //�摜
	double mkDeg,mkScl; //�쐬�������̊p�x�A�i�s��
public:
	int Cap;
	PBullet(){}
	int imgset(int bimage); //�摜�Z�b�g
	void Init(); //������
	//�e�̍쐬
	void create(int x, int y, double Deg, double scalar, int idx);
	//�ړ��A�y�ѕ`��
	void move();
};

/*==========================================================
�v���C���[�N���X
===========================================================*/

class Player{
	double bangle; //���V���b�g�̊p�x
	int imgNo;
	int pPhase, pImgNo[180];
	int PauseKey, PausePhase; //�|�[�Y�֌W�̃L�[�ƃt�F�[�Y
	bool NowPause; //���̃t�F�[�Y
	double pvx[180],pvy[180],px[180],py[180];
	//int knmphase,knmkey[6];
	int swkeycheck;
	int swflg;
	bool IsBGMPaused;
	bool IsBossBGMPaused;

	bool IsSlow; //�ړ����ᑬ���H

	double SubDeg;

	int frmLRoll,frmRRoll;

	static const int SpeedNormal=4; //�ʏ�̈ړ����x
	static const int SpeedSlow=2; //�ᑬ���̈ړ����x

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
	void Draw(int* img,int* inv);//�`��
};