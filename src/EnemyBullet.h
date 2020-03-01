#pragma once
#include "Common.h"
/*#############################################################

                           �G�e

##############################################################*/

//***************************************************************************************
//�G�e�N���X
//***************************************************************************************
class EBullet{
public:
	int queue, phase, flg ,imgidx,imgc, *img,snipe,dead,parent_dead,buzzfrm;
	double x, y,*px,*py,vx,vy,deg,scl,snpdeg;
	bool visible,disapear;

	EBullet();

	void Init();

	//�G�e�ʏ��`�B����: �G�e�摜�E�G�e�𔭎˂�����W�A�i�s�ʁA�L���[
	void def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue);
	//void def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue,double& defdeg);

	//�G�e�i�s�ʍĒ�`�B����: �i�s��(�����Bvx��vy��ʁX��mycos()��mysin()���g���Ē�`����)
	void vectordef(double& defvx, double& defvy);
	//void vectordef(double& defvx, double& defvy,double& defdeg);

	//���@�_���G�e��`�B����: �G�e�摜�E�G�e�𔭎˂�����W�A�i�s��(����)�A���@���牽�x������(���W�A���ł͂Ȃ�)�E�L���[
	void snipedef(int& bimg,double& defx, double& defy, double scalar, double defdeg, int& defqueue);

	//���@�_���G�e�Ē�`�B����:�i�s��(����)�A���@���牽�x������(���W�A���ł͂Ȃ�)
	void sniperedef(double scalar, double defdeg);

	//��ʏ�ɑ��݂���ꍇ1�A��яo�����ꍇ-1�A�L���[���̏ꍇ0
	int Move(); //������
};

//***************************************************************************************
//�G�e���w���N���X
//***************************************************************************************
class EBCmd{
	int l;
public:
	int vanishfrm;
	//TODO: ���̕ӂ͐V�����N���X�Ƃ��ēƗ�������ׂ��B�X��std::vector�ŊǗ��ł��Ȃ����H
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

	//������
	void init();

	//�摜���Z�b�g
	void setimg(int* ebimg);

	//������
	int Move();

	//�G�e�������B����: ���G�e���E�e���̎�ށE�����W
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