#pragma once
#include "Common.h"
/*
#include <vector>
#include "DxLib.h"
using namespace std;
//*/
/*########################################################################

						�R�}���h���̓N���X

########################################################################*/

/*=======================================================================
�g����:

���炩���߉��݂����Ȋ����Ő錾���Ƃ��Ă��
��
�R�}���h���͂���Ă邩�`�F�b�N�������Ƃ���Check()���ĂԁB
��
Check()��true���A���Ă���΃R�}���h���͐���

�T���v���R�[�h
--------------------------------------------------------------------------
//�R�}���h�̐錾(��Ƃ��āu����������������BA�v�̃R���~�R�}���h)
int KC[] = {PAD_INPUT_UP, PAD_INPUT_UP, PAD_INPUT_DOWN, PAD_INPUT_DOWN,
			PAD_INPUT_LEFT, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_RIGHT,
			PAD_INPUT_2, PAD_INPUT_1};

//�z��̗v�f��
const int KCNum = sizeof KC / sizeof KC[0];

//�N���X�̐錾
CommandInput KonantokaCommand(KC,KCNum);
----------------------------------------------------------------------------
==============================================================================*/

class CommandInput{
	vector<int> Cmd; //�R�}���h
	unsigned int Phase;
	int InputData;
	int OldInputData; // �ЂƂO�̃L�[���̓f�[�^
public:
	//�R���X�g���N�^
	CommandInput(const vector<int>& Command){
		Cmd=Command;
		InputData=0;
		OldInputData=0;
		Phase=0;
	}
	//�R�}���h���������z��̃|�C���^
	CommandInput(int* Command, int ElementNum){
		Cmd.assign(&Command[0], &Command[ElementNum]);
		InputData=0;
		OldInputData=0;
		Phase=0;
	}

	bool Check(); //�R�}���h�`�F�b�N
};