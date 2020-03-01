//FPS����
#pragma once
#include "Fps.h"

//=================================================================================================
//�R���X�g���N�^
//=================================================================================================
FPS::FPS(bool IsFixFps, bool IsShowFps, int FixedFPS){
	IsFixFPS = IsFixFps;
	ShowFPS = IsShowFps;
	DefaultFPS = FixedFPS;
}

//=================================================================================================
//�f�X�g���N�^
//=================================================================================================
FPS::~FPS(){}

//=================================================================================================
//FPS�������I�ɌŒ肷��
//=================================================================================================
void FPS::Fix(){
	//�t���O�������Ă��Ȃ���Δ�����
	if(IsFixFPS == false){return;}

	int nowtime = GetNowCount(); //����̎���
	static int oldtime = 0; //�O��̎���
	static int frametime = 1000 / DefaultFPS;	//�P�t���[���̎���

	//�P�t���[���̎��Ԃƌ��݂̌o�ߎ��Ԃ��r
	int diftime = nowtime - oldtime;	//����

	for(;;){
		if(diftime >= frametime){ //���Ԃ��߂��Ă��邩�H
			oldtime = nowtime;	//���̌v���̂��ߍ���̎��Ԃ�ۑ�
			return;
		}else{ //���Ԃ��]������ҋ@
			WaitTimer(1);
			nowtime = GetNowCount();
			diftime = nowtime - oldtime;
		}
	}
}

/*===============================================================
FPS���擾����
=================================================================*/
int FPS::Get(){
	//FPS��\�����Ȃ��H
	if(ShowFPS == false){return -1;}

	static int oldtime = GetNowCount(); //�O��̎��Ԃ�ۑ�
	static int fpscount = 0;  //FPS���J�E���g
	static int fps = 0; //�\���p
	int nowtime = GetNowCount(); //����̎���

	fpscount++;

	//1000ms�߂������H
	if((nowtime - oldtime) >= 1000){
		int dif = ((nowtime - oldtime) - 1000);
		//����̎��Ԃ�ۑ�
		oldtime = nowtime - dif;	//�o�߂���������������
		//FPS��ۑ�
		fps = fpscount;
		//�J�E���^��������
		fpscount = 0;
	}
	return fps;
}