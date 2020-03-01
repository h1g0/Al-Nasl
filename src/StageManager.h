#pragma once
#include "Common.h"
/*#############################################################

					�X�e�[�W�i�s�Ǘ��N���X

##############################################################*/
//�w���v�Ƃ��\�����鏬��
class SmallWindow{
	int width;
	int height;
	int flg;
	int dialog; //�_�C�A���O�̑I�����̎��
	int dialog_selected; //�ǂ̑I�������I�΂�Ă��邩�H
	int status; //���
	int SndOpen; //�J���Ƃ��̉�
	int SndClose;//����Ƃ��̉�
	int ImgSelected;
	vector<string_t> DialogSelect; //�_�C�A���O�̑I��������

	static const int FadeFrm = 20; //�t�F�[�h�C���A�E�g�ɗv����t���[��
	static const int ShowingFrm = FadeFrm+1; //�\�����̃t���[��
	static const int FontSize = 14; //�t�H���g�T�C�Y
	vector<string_t> Str; //�\�����镶����
	void AnalyzeStr(string_t& String); //����������s�ŕ�������
	void SwitchDialog(int DialogType); //�_�C�A���O�̑I�����Ԃ�̔z����m��
public:
	static const int DialogOK = 0; //<OK>
	static const int DialogYesNo = 1; //<YES> <NO>

	//�R���X�g���N�^
	SmallWindow(int Width=320,int Height=240, string_t String="",int DialogType = 0){
		width=Width;
		height=Height;
		flg=0;
		AnalyzeStr(String);
		dialog=DialogType;
		dialog_selected=0;
		SwitchDialog(dialog); //������Ԃ�̃x�N�^���m��
	}
	void SetWH(int Width,int Height){
		width=Width;
		height=Height;
	}
	//�������ݒ�
	void SetString(string_t String, int DialogType = DialogOK){
		AnalyzeStr(String);
		dialog=DialogType;
		dialog_selected=0;
		SwitchDialog(dialog); //������Ԃ�̃x�N�^���m��
	}
	void SetDialogString(string_t String,int Idx =0){
		if((int)DialogSelect.size()<Idx+1){return;}
		DialogSelect[Idx]=String;
	}
	//�T�E���h�t�@�C����ǂݍ���
	void SetSound(string_t OpenSndFile, string_t CloseSndFile){
		SndOpen = LoadSoundMem( OpenSndFile.c_str() );
		ChangeVolumeSoundMem( Setting.General.SEVolume , SndOpen );
		SndClose = LoadSoundMem( CloseSndFile.c_str() );
		ChangeVolumeSoundMem( Setting.General.SEVolume , SndClose );
	}
	void SetImg(const int& Selected){
		ImgSelected = Selected;
	}
		//�\���t���O�𗧂Ă�
	void SetFlag(){
		flg=1;
	}
	int GetStatus(){
		return status;
	}
	/*�`��B
	�߂�l:
	-2: �`��Ώۂ����݂��Ȃ�
	-1: �`�撆�A�������͑ҋ@��
	0: OK�AYES���������ꂽ
	1: NO���������ꂽ

	*/
	int Draw();
};

class StageManager{
	int logo;
	int mMenuImg[7],BarImg,SelectedNo,SelectKey[4],mPhase,mSelected;
	int SndSelect,SndOK,SndCancel;
	string_t mMenuStr[7];
	string_t mOperateStr;

	SmallWindow Window;

	int eidx[10];
	int phase,rphase,bgphase;
	int warnimg,warnmov,stgimg;
	int bgimg[8];
	int ResultScore[2],BossRemainSec;
	bg3d bg2;
	bgmain bg;
	bgsub cloud;
	bgside side;
	int Menu(int* img,string_t str[], int Max);
	void Loading(int& img);
	int ImgLoadStr; //�uLoading...�v�̉摜
	int warn();
	int result();
	int ShowStageTitle(int phase); //�X�e�[�W�^�C�g����\��
	void stgmove(); //���C���̃X�e�[�W�Ǘ�
	//int bgm,bossbgm;
	int SndAlarm;
	int LoadElements;
	int LoadFramework(int phase);
	int LoadSt1(int phase);
	int LoadSt2(int phase);
	int LoadSt3(int phase);

	void UnloadSt1();
	void UnloadSt2();
	void UnloadSt3();

	void InitCommon();

//�ŏ��̕\��
	int StgNotice();
//���j���[
	int stg00(); //���C�����j���[���[�h
	int stg01();
	int stg08(); //�t���[�����[�N���[�h
//���x�����j���[
	int stg80(); //���j���[���[�h
	int stg81(); //���x�����j���[

	int stg90(); //�ݒ胁�j���[���[�h
	int stg91(); //�ݒ胁�j���[

	int stg92(); //�L�[�R���t�B�O1���[�h
	int stg93(); //�L�[�R���t�B�O1

	int stg94(); //�L�[�R���t�B�O2���[�h
	int stg95(); //�L�[�R���t�B�O2

	int stg96(); //�ݒ�1���[�h
	int stg97(); //�ݒ�1

	int stg98(); //�ݒ�2���[�h
	int stg99(); //�ݒ�2

	void KeyConfig1(); //�L�[�R���t�B�O1�̎���
	void KeyConfig2(); //�L�[�R���t�B�O2�̎���

	int stgA0(); //�����L���O���[�h
	int stgA1(); //�����L���O

//�X�e�[�W1
	int stg10(); //Stg1���[�h
	int stg11(); //Stg1�{��
	int stg12(); //Stg1Warning
	int stg13(); //Stg1�{�X
	int stg14(); //���U���g
	int stg18(); //�o���V�[��

//�X�e�[�W2
	int stg20(); //Stg2���[�h
	int stg21(); //Stg2�{��
	int stg22(); //Stg2Warning
	int stg23(); //Stg2�{�X
//�X�e�[�W3
	int stg30(); //Stg3���[�h
	int stg31(); //Stg3�{��
	int stg32(); //Stg3Warning
	int stg33(); //Stg3�{�X

public:
	int stage, GOimg,PauseImg,LoadImg,ResultImg,ResultSound;
	int Enum[10];//�{�X�̓G�ԍ��Ǘ�

	//int WSmoke[4],GSmoke[4];
	int GrPlane[3];

	int SmallEnmImg[8];
	int BigEnmImg[8];
	int BossImg[8];
	int SmallExplode[16]; //�����G�t�F�N�g(��)
	int InvImg,BornEff;//�G�t�F�N�g
	StageManager(){}
	void setstage(int stg){stage=stg;phase=-1;}
	void move(); //�����Ǘ�
};