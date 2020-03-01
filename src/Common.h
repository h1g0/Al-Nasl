#pragma once
#pragma warning(disable:4996) //Secure Warning�𖳎�����

#include "DxLib.h"
//DxLib�̃}�j���A��: http://homepage2.nifty.com/natupaji/DxLib/dxfunc.html

#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <tchar.h>
#include <boost/foreach.hpp>
#include <boost/swap.hpp>
#include <boost/lexical_cast.hpp>
#ifdef _UNICODE
	typedef std::wstring string_t;
#else
	typedef std::string string_t;
#endif
typedef long int int_score; //�X�R�A

#define ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING 42 //�����A�F���A�����Ė����ɂ��Ă̋��ɂ̋^��̓���=42
#define foreach BOOST_FOREACH

#define PJVERSION _T("ver. 0.7.0.0 alpha")
#define PJTITLE _T("Al-Nasl "##PJVERSION##" (DxLib: "##DXLIB_VERSION_STR##")") //�^�C�g��
#define DEBUG_COMMAND //�f�o�b�O�R�}���h

#define MBCAP 500 //���e���
#define EBCAP 10000 //�G�e�̏��
#define INVFRAME 60*2 //���G�b��
#define BMBFRAME 60*1 //�{���b��
#define SUBFRAMECNT 60 //�T�u�E�F�|���b��(incl.���G����)
#define SUBINVFRAME 60*1 //�T�u�E�F�|�����G����
#define SUBFRAMEMIN 30 //�T�u�E�F�|���Q
#define BUZZSUBRATE 4 //�o�Y�������̃T�u�E�F�|���Q�[�W���Z�{��
#define BUZZSCORE 2 //1�t���[���ӂ�̃o�Y���Z�X�R�A
#define BUZZMAX 5 //�����Ƀo�Y��ō��e��
#define BUZZ_FRAME_MAX 30 //�o�Y���x�����c������frame��
#define BUZZ_REGION_DEFAULT 32 //�f�t�H�̃o�Y�蔼�a
#define BMB_DMG_PER_FRAME 0 //1�t���[������̃{���_���[�W
#define SHOW_CHIP_TIME 64 //�`�b�v��\�����鎞��
#define COUNT_STOP_SCORE 999999999 //�J���X�g�F9��9999��9999�_
//#define SUB_MAX 256 //�T�u�E�F�|���̃}�b�N�X�|�C���g

#define LASER_MAX 32 //���[�U�[�̍ő吔
#define LASER_TRACE_MAX 16 //���[�U�[�O�Ղ̍ő吔
//#define LASER_POWER 256 //���[�U�[�̈З�
#define LASER_SCORE 10 //���[�U�[�f�_

#define EXPLODE_MAX 16 //�����̍ő吔

#define MAXLEFT 30 //�c�@�̍ő吔
#define MAXBOMB 7 //�{���̍ő吔
#define SUB_LEVEL 5 //�T�u�E�F�|���̃��x��
#define IRODORI_RATE 1.1 //�ʃ��[�h�̔{��
#define ACCELERATOR_RATE 1.01 //�������[�h�̔{��
#define ENEMY_INV -127 //�G�����G�ɂȂ����萔
#define MY_MODEL_EXP 1.3f //�f�t�H���g�̎��@���f���g�嗦

using namespace std; //�X�^���_�[�h���C�u�������O��Ԃ��g�p

#include "SettingIni.h" //INI
extern SettingIni Setting;

#include "Fps.h" //FPS�֌W
#include "Chore.h" //�G�p�֐��Q
#include "BgmTitle.h" //BGM�̃^�C�g��
#include "CommandInput.h" //�R�}���h���͊֌W
#include "MathFunc.h" //���w�֌W
#include "Global.h" //�O���[�o���ϐ�
#include "BackGround.h" //�w�i�֌W
#include "Player.h" //���@�E���e�֌W
#include "EnemyBullet.h" //�G�e�֌W
#include "Enemy.h" //�G�֌W
#include "StageManager.h" //�X�e�[�W�i�s
//#include "Ranking.h" //�����L���O
//extern RankAll gRank;
extern StageManager stage;
extern Player gPlayer;
extern Enemy e1;