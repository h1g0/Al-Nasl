
#ifndef RANKING_H
#define RANKING_H
//#include "DxLib.h"
#include "Common.h"
/*
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
*/
#include <boost/lexical_cast.hpp>

//#include <fstream>
#include <string>
using namespace std;

typedef long int int_score;
#define RANK_MEMBER 10
#define RANK_DIFFICULTY 5
#define RANK_NAME_REVISION 0x20
#define RANK_NAME_IMG_NUM 96
//�����L���O�l
class RankPerson{
private:
	static void SetDefaultName(int difficulty, int rank, int_score& score, long& name, int& stage);
	static const int FadeFrm = 20; //�t�F�[�h�C���E�A�E�g�ɗv����t���[����
	int prank;
	int_score pscore; //�X�R�A
	long pname; //���O(0xXXYYZZ�̌`���A0xXX��1�����ځAYY��2�����ځAZZ��3������)
	int pstage;

	int x;
	int y;
	int frm;

public:
	//String���疼�O�ցB
	static long Str2Name(string_t str);
	//String���疼�O�ցB
	static string_t Name2Str(long name);
	//�摜�ŕ������`��B�Ԃ�l�͕`�悵�I����x���W
	static int DrawStrByImg(string_t str, int x, int y, const int *img, int width,  int StrRevision=RANK_NAME_REVISION);

	void Init(){
		prank=1;
		pscore=0;
		pname=Str2Name("ALN");
		pstage=1;
		x=0;
		y=0;
		frm=0;
	}
	void Init(int difficulty, int rank){
		RankPerson::SetDefaultName(difficulty,rank,pscore,pname,pstage);
	}
	RankPerson(){
		Init();
	}
	void Set(int Rank, int_score Score,long Name, int Stage){
		prank=Rank;
		pscore=Score;
		pname=Name;
		pstage=Stage;
	}
	int_score GetScore(){
		return pscore;
	}
	long GetName(){
		return pname;
	}
	int GetStage(){
		return pstage;
	}
	//�`��ʒu�Z�b�g�ƃt���[��������
	void SetDraw(int Frame, int DrawX, int DrawY,int Rank);

	/*�`��B
	�Ԃ�l:
	�`��Ώۖ���: -1
	�`�撆(incl. �t�F�[�h�C���A�E�g): 0
	�`��I��(���̒l��frm���蓮�Ń��Z�b�g����܂ŕԂ��ꑱ����) : 1
	*/
	int Draw(int* img, int width);
};

//��Փx�ʂ̃����L���O
class RankDifficulty{
private:
	int x;
	int y;

public:
	//�萔
	static const int Capacity = 10;
	RankPerson Member[RANK_MEMBER];
	void Init(){
		for(int i=0;i<RANK_MEMBER;i++){
			Member[i].Init();
		}
	}
	void Init(int MyDifficulty){
		for(int i=0;i<RANK_MEMBER;i++){
			Member[i].Init(MyDifficulty,i);
		}
		x=0;
		y=0;
	}

	//�R���X�g���N�^
	RankDifficulty(){
		Init();
	}
	void SetDraw(int DrawX, int DrawY, int height){
		x=DrawX;
		y=DrawY;

		for(int i=0;i<RANK_MEMBER;i++){
			Member[i].SetDraw(i*-5, x,y+46+i*height,i+1);
		}
	}
	/*��Փx�P�ʂł܂Ƃ߂ĕ`��B*/
	void Draw(string_t difficulty, int* img, int width){
		for(int i=0;i<RANK_MEMBER;i++){
			Member[i].Draw(img,width);
		}

		RankPerson::DrawStrByImg("Ranking ["+difficulty+"]",x,y,img,width);
	}
};

class RankAll{
private:
	int NowDiff;
	int SndSelect;
	int SndCancel;


public:
	string_t FileName;//�Z�[�u�t�@�C��
	int ChrImg[RANK_NAME_IMG_NUM];
	int BGImg;
	static const int ChrWidth=23;
	static const int ChrHeight=28;
	//��Փx�萔
	static const int EASY = 4;
	static const int NORMAL = 3;
	static const int HARD = 2;
	static const int INSANE = 1;
	static const int DESPERATE = 0;

	static const int ConstX = (int)((640-ChrWidth*19)/2);
	static const int ConstY = 64;

	RankDifficulty Difficulty[RANK_DIFFICULTY];

	void Init(){
		FileName="rank.dat";
		NowDiff=4;
		DeleteSoundMem(SndSelect);
		DeleteSoundMem(SndCancel);
		for(int i=0;i<RANK_DIFFICULTY;i++){
			Difficulty[i].Init(i);
		}
	}

	RankAll(){
		Init();
	}
	void SetImg(string_t ChrFileName,string_t BGFileName){
		LoadDivGraph(ChrFileName.c_str(), RANK_NAME_IMG_NUM, 8, 12, 30, 28,ChrImg);
		BGImg = LoadGraph(BGFileName.c_str());
	}
	void SetSnd(const int& Select, const int& Cancel){
		SndSelect=Select;
		SndCancel=Cancel;
	}
	void SetDraw(){
		Difficulty[NowDiff].SetDraw(ConstX,ConstY,ChrHeight);
	}

	void Draw(){
		static bool isleft = false;
		static bool isright=false;
		if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_RIGHT) !=0){
			if(isright == false){
				PlaySoundMem(SndSelect,DX_PLAYTYPE_BACK);
				isright=true;
				if(NowDiff == 0){
					NowDiff=RANK_DIFFICULTY -1;
				}else{
					NowDiff--;
				}
				Difficulty[NowDiff].SetDraw(ConstX,ConstY,ChrHeight);
			}
		}else{isright=false;}
		if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_LEFT) !=0){
			if(isleft == false){
				PlaySoundMem(SndSelect,DX_PLAYTYPE_BACK);
				isleft=true;
				if(NowDiff == RANK_DIFFICULTY -1){
					NowDiff=0;
				}else{
					NowDiff++;
				}
				Difficulty[NowDiff].SetDraw(ConstX,ConstY,ChrHeight);
			}
		}else{isleft=false;}
		string_t strdiff;
		switch(NowDiff){
			case EASY:
				strdiff="Easy";
				break;
			case NORMAL:
				strdiff="Normal";
				break;
			case HARD:
				strdiff="Hard";
				break;
			case INSANE:
				strdiff="Insane";
				break;
			case DESPERATE:
				strdiff="Desperate";
				break;
			default:
				strdiff="Unknown";
				break;
		}

		//�w�i�`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,64);
		DrawGraph(0,0,BGImg,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		//������`��
		Difficulty[NowDiff].Draw(strdiff,ChrImg,ChrWidth);
	}

	static int Load(RankAll &Obj){

				Obj.Init();

	}

	static int Save(const RankAll &Obj){
		return 0;

	}
};


#endif