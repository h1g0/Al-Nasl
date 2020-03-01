#include "Ranking.h"
//String���疼�O�ցB
long RankPerson::Str2Name(string_t str){
	long result=0;
	result += str[0] << 16;
	result += str[1] << 8;
	result += str[2];
	return result;
}
//String���疼�O�ցB
string_t RankPerson::Name2Str(long name){
	string_t str("ALN"); //���Ƀ������m��
	str[0]=(name >> 16) & 0xFF;
	str[1]=(name >> 8) & 0xFF;
	str[2]=name & 0xFF;
	return str;
}

void RankPerson::SetDefaultName(int difficulty, int rank, int_score &score, long &name, int &stage){
	const int NameEasy[RANK_MEMBER]={
		Str2Name("AL-"),
		Str2Name("NSL"),
		Str2Name("---"),
		Str2Name("NAM"),
		Str2Name("ETR"),
		Str2Name("---"),
		Str2Name("ESY"),
		Str2Name("MOD"),
		Str2Name("---"),
		Str2Name("DEF")};

	const int NameNormal[RANK_MEMBER]={
		Str2Name("AAA"),
		Str2Name("BBB"),
		Str2Name("CCC"),
		Str2Name("DDD"),
		Str2Name("EEE"),
		Str2Name("FFF"),
		Str2Name("GGG"),
		Str2Name("HHH"),
		Str2Name("III"),
		Str2Name("JJJ")};

	const int NameHard[RANK_MEMBER]={
		Str2Name("IKA"),
		Str2Name("PSV"),
		Str2Name("G.W"),
		Str2Name("RSG"),
		Str2Name("CHR"),
		Str2Name("GTS"),
		Str2Name("'43"),
		Str2Name("R-T"),
		Str2Name("GRD"),
		Str2Name("EG2")};

	const int NameInsane[RANK_MEMBER]={
		Str2Name("---"),
		Str2Name("ALL"),
		Str2Name("U-R"),
		Str2Name("NAM"),
		Str2Name("ARE"),
		Str2Name("BLG"),
		Str2Name("2US"),
		Str2Name("---"),
		Str2Name("---"),
		Str2Name("---")};

	const int NameDesparete[RANK_MEMBER]={
		Str2Name("---"),
		Str2Name("KIL"),
		Str2Name("ROY"),
		Str2Name("WAS"),
		Str2Name("HER"),
		Str2Name("E!!"),
		Str2Name("---"),
		Str2Name("---"),
		Str2Name("---"),
		Str2Name("---")};

	switch(difficulty){
		case 4:
			score=1;
			name=NameEasy[rank];
			break;
		case 3:
			score=2;
			name=NameNormal[rank];
			break;
		case 2:
			score=3;
			name=NameHard[rank];
			break;
		case 1:
			score=31337;
			name=NameInsane[rank];
			break;
		case 0:
			score=42;
			name=NameDesparete[rank];
			break;
		default:
			name=Str2Name("ALN");
			break;
	}
	score+=(RANK_MEMBER-rank)*100000;
	stage = 1;
}
int RankPerson::DrawStrByImg(string_t str, int x, int y, const int *img, int width, int StrRevision){
	for(int i=0;(unsigned)i<str.size();i++){
		char chr = str.at(i) - StrRevision;
		DrawGraph(x+width*i,y,img[chr],TRUE);
	}
	return x+str.size()*width;
}

//�`��ʒu�Z�b�g�ƃt���[��������
void RankPerson::SetDraw(int Frame,int DrawX, int DrawY,int Rank){
	prank=Rank;
	x=DrawX;
	y=DrawY;
	frm=Frame;
}

/*�`��B
�Ԃ�l:
�`��Ώۖ���: -1
�`�撆(incl. �t�F�[�h�C���A�E�g): 0
�`��I��(���̒l��frm���蓮�Ń��Z�b�g����܂ŕԂ��ꑱ����) : 1
*/
int RankPerson::Draw(int* img, int width){
	if(frm<=0){frm++;return -1;}//�`��Ώۖ���
	if(frm>FadeFrm*2+1){return 1;} //�t�F�[�h�A�E�g�I��
	int lx=x;
	int ly=y;
	int alpha=255;
	if(frm<=FadeFrm){ //�t�F�[�h�C��
		lx = x+(FadeFrm-frm)*10;
		ly = y /*+ (FadeFrm-frm)*prank*/;
		alpha = (int)(255/FadeFrm*frm);
		frm++;
	}else if(frm>FadeFrm+1){ //�t�F�[�h�A�E�g
		int lfrm=frm-(FadeFrm+1);
		lx = x - lfrm;
		ly = y - lfrm;
		alpha = (int)(255 - 255/FadeFrm*lfrm);
		frm++;
	}

	//==========
	//�`��
	//==========

	//�����N
	string_t str("???");
	switch(prank){
		case 1:
			str=" 1st";
			break;
		case 2:
			str=" 2nd";
			break;
		case 3:
			str=" 3rd";
			break;
		case 10:
			str="10th";
			break;
		default:
			str=" "+boost::lexical_cast<string_t>(prank) + "th";
			break;
	}
	SetDrawBright(255,255-(int)(127/RANK_MEMBER*prank),255-(int)(127/RANK_MEMBER*prank));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);
	lx=DrawStrByImg(str,lx,ly,img,width);
	lx+=16;

	//���O
	str=RankPerson::Name2Str(pname);
	lx=DrawStrByImg(str,lx,ly,img,width);
	lx+=16;

	//�X�e�[�W
	str=boost::lexical_cast<string_t>(pstage);
	lx=DrawStrByImg(str,lx,ly,img,width);
	lx+=16;

	//�X�R�A
	str=boost::lexical_cast<string_t>(pscore);
	str.insert(0,"         ",(unsigned int)(9 - str.size()));
	lx=DrawStrByImg(str,lx,ly,img,width);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawBright(255,255,255);

	return 0;
}