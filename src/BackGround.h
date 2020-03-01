#pragma once
#include "Common.h"
/*#############################################################

						   ��ʍ\��

##############################################################*/

//3D�֌W�̔w�i�N���X
class bg3d{
private:
	int FCnt; //�ʒu�J�E���^
public:
	//TODO: �]�T����������Z�b�^�ƃQ�b�^����
	int hField, hField2 ,Scr; //���f��1�A���f��2�A�X�N���[�����x
	bg3d(){}//�R���X�g���N�^
	void imgset(int g1,int scroll); //���f���Z�b�g
	void changespeed(int speed); //�X�N���[�����x�ύX
	void move(); //������
};

//2D�̔w�i�N���X
class bgmain{
private:
	int y1,y2; //�e�摜��Y���W
	int img1; //�摜���1
	int img2;//�摜���2
	int sspeed; //�X�N���[�����x
public:
	bgmain(){}//�R���X�g���N�^
	void imgset(int g1, int g2, int scroll); //�摜1�A�摜2�A�X�N���[�����x���Z�b�g
	void move(); //������
};

//2D�̔w�i�N���X����2
class bgsub{
private:
	int sspeed; //�X�N���[�����x
	int y1,y2; //�e�摜��Y���W
	int img1; //�摜���1
	int img2;
public:
	//TODO: ��𔲂����ɃQ�b�^�ƃZ�b�^�������ׂ�

	bool Visible; //�\�����邩�H
	int alpha; //�����x
	bgsub(); //�R���X�g���N�^
	void imgset(int g1, int g2, int scroll); //�摜�ƃX�N���[�����x���Z�b�g
	void move(); //������
};

//��ʘe�̏��Q
class bgside{
private:
	int GrBGL,GrBGR;
	unsigned int phase,score;
	int gzPhase, gzCnt;
public:
	bgside(){}//�R���X�g���N�^
	void imgset(int imgLeft, int imgRight); //���E�̉摜���Z�b�g
	void draw(); //�`��
};