#include "Common.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
string_t cfunc::KeyName;

bool Vapor::VisibleAll=true; //�S�̂�\�����邩�ۂ�
bool Vapor::Visible[VAPOR_NUM][VAPOR_PARTS_NUM]; //�\�����邩�ǂ���
//x,y�̈ʒu�֌W:
//0- 1- 2- 3- 4- 5- 6- 7- 8- 9- 10- 11- 12- 13- 14- 15...
double Vapor::x[VAPOR_NUM][VAPOR_PARTS_NUM];
double Vapor::y[VAPOR_NUM][VAPOR_PARTS_NUM];
int Vapor::Alpha[VAPOR_NUM][VAPOR_PARTS_NUM]; //�����x

bool Vapor::IsMake[VAPOR_NUM];
double Vapor::MakeX[VAPOR_NUM];
double Vapor::MakeY[VAPOR_NUM];
int Vapor::MakeAlpha[VAPOR_NUM];

//������
void Vapor::Init(){
	VisibleAll=false;
	for(int i=0; i<VAPOR_NUM; i++){
		for(int j=0; j<VAPOR_PARTS_NUM; j++){
			Visible[i][j]=false;
			x[i][j]=0;
			y[i][j]=0;
			Alpha[i][j]=0;
		}
	}
}

//�x�C�p�[����
int Vapor::Make(int idx, double SetX, double SetY,int SetAlpha){
	if(idx>=VAPOR_NUM){return -1;} //�w�肵��ID�����X�̖{����葽��
	VisibleAll=true;
	IsMake[idx]=true;
	MakeX[idx]=SetX;
	MakeY[idx]=SetY;
	MakeAlpha[idx]=SetAlpha;
	return 1;
}

//�x�C�p�[������
void Vapor::Move(){
	if(VisibleAll==false){
		return;
	} //�`�悷�ׂ��Ώۂ��Ȃ���ΏI��
	bool AnyVisible=false;
	//double a=1.0/VAPOR_PARTS_NUM;
	for(int i=0; i<VAPOR_NUM; i++){
		for(int j=VAPOR_PARTS_NUM-1; j>0; j--){
			int k=j-1;
			Visible[i][j]=Visible[i][k];
			x[i][j]=x[i][k];
			y[i][j]=y[i][k]+VAPOR_DIST;//���Ɍ������ĐL�΂�
			Alpha[i][j]=Alpha[i][k];
			if(Visible[i][j]==true){
				AnyVisible=true;
			}
		}

		if(IsMake[i]==true){
			Visible[i][0]=true;
			x[i][0]=MakeX[i];
			y[i][0]=MakeY[i];
			Alpha[i][0]=MakeAlpha[i];
			IsMake[i]=false;
			MakeX[i]=0;
			MakeY[i]=0;
			MakeAlpha[i]=0;
		}else{
			Visible[i][0]=false;
			x[i][0]=0;
			y[i][0]=0;
			Alpha[i][0]=0;
		}
	}
	if(AnyVisible==false){
		VisibleAll=false;
		return; //�`�悷�ׂ��Ώۂ��Ȃ���ΏI��
	}else{
		//�`��
		for(int i=0; i<VAPOR_NUM; i++){
			for(int j=0; j<VAPOR_PARTS_NUM-1; j++){
				int k=j+1;
				if(Visible[i][j]==true && Visible[i][k]==true){
					double t=Alpha[i][j]*j/VAPOR_PARTS_NUM;
					int a=(int)(Alpha[i][j]-t);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,a);
					DrawLine((int)x[i][j],(int)y[i][j],(int)x[i][k],(int)y[i][k],GetColor(255,255,255));
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				}
			}
		}
	}
		return;
}

int GetScrCapture(int CenterX,int CenterY,int Width, int Height){
	if((int)(CenterX-Width/2)<0){Width=CenterX*2;}
	if((int)(CenterX+Width/2)>640){Width=(640-CenterX)*2;}
	if((int)(CenterY-Height/2)<0){Height=CenterY*2;}
	if((int)(CenterY+Height/2)>480){Height=(480-CenterY)*2;}
	int img=MakeGraph(Width,Height);
	GetDrawScreenGraph(CenterX-Width/2 , CenterY-Height/2,
					   CenterX+Width/2 , CenterY+Height/2,img);
	return img;
}

int DeadImg::frm=0;
int DeadImg::frm_start=0;
int DeadImg::img;

void DeadImg::Set(int x,int y,int frame){
	img=GetScrCapture(x,y,DEADIMG_WIDTH,DEADIMG_HEIGHT);
	frm_start=frame+20;
	frm=frm_start;
}
void DeadImg::Draw(int x,int y){
	if(frm==0){
		return;
	}else if(frm_start-frm<=10){
		int f=frm_start-frm;
		SetDrawBlendMode(DX_BLENDMODE_ADD,255-25*f);
		SetDrawMode(1);
		DrawModiGraph((int)(x-DEADIMG_WIDTH/2-(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y-f*2.4*DEADIMG_EXP),
					  (int)(x+DEADIMG_WIDTH/2+(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y-f*2.4*DEADIMG_EXP),
					  (int)(x+DEADIMG_WIDTH/2+(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y+f*2.4*DEADIMG_EXP),
					  (int)(x-DEADIMG_WIDTH/2-(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y+f*2.4*DEADIMG_EXP),
					  img,FALSE);
		SetDrawMode(0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(frm>10){
		SetDrawMode(1);
		DrawBox(x-DEADIMG_WIDTH*DEADIMG_EXP/2+1,y-DEADIMG_HEIGHT*DEADIMG_EXP/2+1,
				x+DEADIMG_WIDTH*DEADIMG_EXP/2+1,y+DEADIMG_HEIGHT*DEADIMG_EXP/2+1,
				GetColor(127,127,127),FALSE);
		DrawRotaGraph(x,y,DEADIMG_EXP,0,img,FALSE);
		DrawBox(x-DEADIMG_WIDTH*DEADIMG_EXP/2,y-DEADIMG_HEIGHT*DEADIMG_EXP/2,
				x+DEADIMG_WIDTH*DEADIMG_EXP/2,y+DEADIMG_HEIGHT*DEADIMG_EXP/2,
				GetColor(255,255,255),FALSE);
		SetDrawMode(0);
	}else{
		int f=frm;
		SetDrawMode(1);
		SetDrawBlendMode(DX_BLENDMODE_ADD,255-25*f);
		DrawModiGraph((int)(x-DEADIMG_WIDTH/2-(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y-f*2.4*DEADIMG_EXP),
					  (int)(x+DEADIMG_WIDTH/2+(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y-f*2.4*DEADIMG_EXP),
					  (int)(x+DEADIMG_WIDTH/2+(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y+f*2.4*DEADIMG_EXP),
					  (int)(x-DEADIMG_WIDTH/2-(10-f)*DEADIMG_HEIGHT/10*DEADIMG_EXP),
					  (int)(y+f*2.4*DEADIMG_EXP),
					  img,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		SetDrawMode(0);
	}
	if(frm>0){frm--;}
}

int Blur::frm=0;
int Blur::frm_start=0;
int Blur::layer=0;
double Blur::vx;
double Blur::vy;
double Blur::exp;
double Blur::cx;
double Blur::cy;

void Blur::set(int CenterX,int CenterY,int Frame,int LayerNum, double MoveX, double MoveY, double Expand){
	if(LayerNum<=0){return;}
	cx=CenterX;
	cy=CenterY;
	frm_start=Frame;
	frm=frm_start;
	layer=LayerNum;
	vx=MoveX;
	vy=MoveY;
	exp=Expand;
}

int Blur::move(){
	if(frm<=0){return -1;}
	int scr=GetScrCapture(320,240,640,480);
	SetDrawMode(1);
	int frame=frm_start-frm;
	for(int i=1;i<=layer;i++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(64/i));
		DrawRotaGraph2((int)(cx+vx*frame*i),(int)(cy+vy*frame*i),(int)(cx),(int)(cy),1.0+exp*frame*i,0.0,scr,FALSE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	SetDrawMode(0);
	frm--;
	return 1;
}

int BGMTitle::Frame=0;
int BGMTitle::fnt;
string_t BGMTitle::str;

void BGMTitle::Set(string_t String){
	fnt=CreateFontToHandle(NULL,SHOW_BGM_TITLE_SIZE , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	str=String;
	Frame=SHOW_BGM_TITLE_FRM+30;
}
void BGMTitle::Draw(){
	if(Frame==0){
		return;
	}else{
		int addx=0;
		int addy=0;
		if(Frame<=15){ //�t�F�[�h�A�E�g
			addy=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(mysin(DX_PI_F*Frame/30.0f)*255));
		}else if(Frame<=SHOW_BGM_TITLE_FRM+15){ //�ʏ�\��
			addy=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		}else if(Frame<=SHOW_BGM_TITLE_FRM+30){ //�t�F�[�h�C��
			int frm=Frame-(SHOW_BGM_TITLE_FRM+15);
			addy=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(mycos(DX_PI_F*frm/30.0f)*255));
		}

		int x=SHOW_BGM_TITLE_X-GetDrawStringWidthToHandle(str.c_str() ,str.size() , fnt ) + addx;
		int y=SHOW_BGM_TITLE_Y-SHOW_BGM_TITLE_SIZE + addy;
		DrawStringToHandle( x , y , str.c_str() , GetColor(255,255,255) , fnt ) ;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		Frame--;
		return;
	}
}

//�N�\�݂����Ȋ֐��Q

//�L�[������L�[�萔��
int cfunc::KeyStr2Int(string_t str){
	if(str== "BACK"){
		return(KEY_INPUT_BACK);// �o�b�N�X�y�[�X�L�[
	}else if(str == "TAB"){
		return(KEY_INPUT_TAB);// �^�u�L�[
	}else if(str == "RETURN"){
		return(KEY_INPUT_RETURN);// �G���^�[�L�[
	}else if(str == "LSHIFT"){
		return(KEY_INPUT_LSHIFT);// ���V�t�g�L�[
	}else if(str == "RSHIFT"){
		return(KEY_INPUT_RSHIFT);// �E�V�t�g�L�[
	}else if(str == "LCONTROL"){
		return(KEY_INPUT_LCONTROL);// ���R���g���[���L�[
	}else if(str == "RCONTROL"){
		return(KEY_INPUT_RCONTROL);// �E�R���g���[���L�[
	}else if(str == "ESCAPE"){
		return(KEY_INPUT_ESCAPE);// �G�X�P�[�v�L�[
	}else if(str == "SPACE"){
		return(KEY_INPUT_SPACE);// �X�y�[�X�L�[
	}else if(str == "PGUP"){
		return(KEY_INPUT_PGUP);// �o�������t�o�L�[
	}else if(str == "PGDN"){
		return(KEY_INPUT_PGDN);// �o�������c�������L�[
	}else if(str == "END"){
		return(KEY_INPUT_END);// �G���h�L�[
	}else if(str == "HOME"){
		return(KEY_INPUT_HOME);// �z�[���L�[
	}else if(str == "LEFT"){
		return(KEY_INPUT_LEFT);// ���L�[
	}else if(str == "UP"){
		return(KEY_INPUT_UP);// ��L�[
	}else if(str == "RIGHT"){
		return(KEY_INPUT_RIGHT);// �E�L�[
	}else if(str == "DOWN"){
		return(KEY_INPUT_DOWN);// ���L�[
	}else if(str == "INSERT"){
		return(KEY_INPUT_INSERT);// �C���T�[�g�L�[
	}else if(str == "DELETE"){
		return(KEY_INPUT_DELETE);// �f���[�g�L�[
	}else if(str == "MINUS"){
		return(KEY_INPUT_MINUS);// -�L�[
	}else if(str == "YEN"){
		return(KEY_INPUT_YEN);// ���L�[
	}else if(str == "PREVTRACK"){
		return(KEY_INPUT_PREVTRACK);// �O�L�[
	}else if(str == "PERIOD"){
		return(KEY_INPUT_PERIOD);// �D�L�[
	}else if(str == "SLASH"){
		return(KEY_INPUT_SLASH);// �^�L�[
	}else if(str == "LALT"){
		return(KEY_INPUT_LALT);// ���`�k�s�L�[
	}else if(str == "RALT"){
		return(KEY_INPUT_RALT);// �E�`�k�s�L�[
	}else if(str == "SCROLL"){
		return(KEY_INPUT_SCROLL);// ScrollLock�L�[
	}else if(str == "SEMICOLON"){
		return(KEY_INPUT_SEMICOLON);// �G�L�[
	}else if(str == "COLON"){
		return(KEY_INPUT_COLON);// �F�L�[
	}else if(str == "LBRACKET"){
		return(KEY_INPUT_LBRACKET);// �m�L�[
	}else if(str == "RBRACKET"){
		return(KEY_INPUT_RBRACKET);// �n�L�[
	}else if(str == "AT"){
		return(KEY_INPUT_AT);// ���L�[
	}else if(str == "BACKSLASH"){
		return(KEY_INPUT_BACKSLASH);// �_�L�[
	}else if(str == "COMMA"){
		return(KEY_INPUT_COMMA);// �C�L�[
	}else if(str == "CAPSLOCK"){
		return(KEY_INPUT_CAPSLOCK);// CaspLock�L�[
	}else if(str == "SYSRQ"){
		return(KEY_INPUT_SYSRQ);// PrintScreen�L�[
	}else if(str == "PAUSE"){
		return(KEY_INPUT_PAUSE);// PauseBreak�L�[
	}else if(str == "NUMPAD0"){
		return(KEY_INPUT_NUMPAD0);// �e���L�[�O
	}else if(str == "NUMPAD1"){
		return(KEY_INPUT_NUMPAD1);// �e���L�[�P
	}else if(str == "NUMPAD2"){
		return(KEY_INPUT_NUMPAD2);// �e���L�[�Q
	}else if(str == "NUMPAD3"){
		return(KEY_INPUT_NUMPAD3);// �e���L�[�R
	}else if(str == "NUMPAD4"){
		return(KEY_INPUT_NUMPAD4);// �e���L�[�S
	}else if(str == "NUMPAD5"){
		return(KEY_INPUT_NUMPAD5);// �e���L�[�T
	}else if(str == "NUMPAD6"){
		return(KEY_INPUT_NUMPAD6);// �e���L�[�U
	}else if(str == "NUMPAD7"){
		return(KEY_INPUT_NUMPAD7);// �e���L�[�V
	}else if(str == "NUMPAD8"){
		return(KEY_INPUT_NUMPAD8);// �e���L�[�W
	}else if(str == "NUMPAD9"){
		return(KEY_INPUT_NUMPAD9);// �e���L�[�X
	}else if(str == "MULTIPLY"){
		return(KEY_INPUT_MULTIPLY);// �e���L�[���L�[
	}else if(str == "ADD"){
		return(KEY_INPUT_ADD);// �e���L�[�{�L�[
	}else if(str == "SUBTRACT"){
		return(KEY_INPUT_SUBTRACT);// �e���L�[-�L�[
	}else if(str == "DECIMAL"){
		return(KEY_INPUT_DECIMAL);// �e���L�[�D�L�[
	}else if(str == "DIVIDE"){
		return(KEY_INPUT_DIVIDE);// �e���L�[�^�L�[
	}else if(str == "NUMPADENTER"){
		return(KEY_INPUT_NUMPADENTER);// �e���L�[�̃G���^�[�L�[
	}else if(str == "F1"){
		return(KEY_INPUT_F1);// �e�P�L�[
	}else if(str == "F2"){
		return(KEY_INPUT_F2);// �e�Q�L�[
	}else if(str == "F3"){
		return(KEY_INPUT_F3);// �e�R�L�[
	}else if(str == "F4"){
		return(KEY_INPUT_F4);// �e�S�L�[
	}else if(str == "F5"){
		return(KEY_INPUT_F5);// �e�T�L�[
	}else if(str == "F6"){
		return(KEY_INPUT_F6);// �e�U�L�[
	}else if(str == "F7"){
		return(KEY_INPUT_F7);// �e�V�L�[
	}else if(str == "F8"){
		return(KEY_INPUT_F8);// �e�W�L�[
	}else if(str == "F9"){
		return(KEY_INPUT_F9);// �e�X�L�[
	}else if(str == "F10"){
		return(KEY_INPUT_F10);// �e�P�O�L�[
	}else if(str == "F11"){
		return(KEY_INPUT_F11);// �e�P�P�L�[
	}else if(str == "F12"){
		return(KEY_INPUT_F12);// �e�P�Q�L�[
	}else if(str == "A"){
		return(KEY_INPUT_A);// �`�L�[
	}else if(str == "B"){
		return(KEY_INPUT_B);// �a�L�[
	}else if(str == "C"){
		return(KEY_INPUT_C);// �b�L�[
	}else if(str == "D"){
		return(KEY_INPUT_D);// �c�L�[
	}else if(str == "E"){
		return(KEY_INPUT_E);// �d�L�[
	}else if(str == "F"){
		return(KEY_INPUT_F);// �e�L�[
	}else if(str == "G"){
		return(KEY_INPUT_G);// �f�L�[
	}else if(str == "H"){
		return(KEY_INPUT_H);// �g�L�[
	}else if(str == "I"){
		return(KEY_INPUT_I);// �h�L�[
	}else if(str == "J"){
		return(KEY_INPUT_J);// �i�L�[
	}else if(str == "K"){
		return(KEY_INPUT_K);// �j�L�[
	}else if(str == "L"){
		return(KEY_INPUT_L);// �k�L�[
	}else if(str == "M"){
		return(KEY_INPUT_M);// �l�L�[
	}else if(str == "N"){
		return(KEY_INPUT_N);// �m�L�[
	}else if(str == "O"){
		return(KEY_INPUT_O);// �n�L�[
	}else if(str == "P"){
		return(KEY_INPUT_P);// �o�L�[
	}else if(str == "Q"){
		return(KEY_INPUT_Q);// �p�L�[
	}else if(str == "R"){
		return(KEY_INPUT_R);// �q�L�[
	}else if(str == "S"){
		return(KEY_INPUT_S);// �r�L�[
	}else if(str == "T"){
		return(KEY_INPUT_T);// �s�L�[
	}else if(str == "U"){
		return(KEY_INPUT_U);// �t�L�[
	}else if(str == "V"){
		return(KEY_INPUT_V);// �u�L�[
	}else if(str == "W"){
		return(KEY_INPUT_W);// �v�L�[
	}else if(str == "X"){
		return(KEY_INPUT_X);// �w�L�[
	}else if(str == "Y"){
		return(KEY_INPUT_Y);// �x�L�[
	}else if(str == "Z"){
		return(KEY_INPUT_Z);// �y�L�[
	}else if(str == "0" ){
		return(KEY_INPUT_0);// �O�L�[
	}else if(str == "1"){
		return(KEY_INPUT_1);// �P�L�[
	}else if(str == "2"){
		return(KEY_INPUT_2);// �Q�L�[
	}else if(str == "3"){
		return(KEY_INPUT_3);// �R�L�[
	}else if(str == "4"){
		return(KEY_INPUT_4);// �S�L�[
	}else if(str == "5"){
		return(KEY_INPUT_5);// �T�L�[
	}else if(str == "6"){
		return(KEY_INPUT_6);// �U�L�[
	}else if(str == "7"){
		return(KEY_INPUT_7);// �V�L�[
	}else if(str == "8"){
		return(KEY_INPUT_8);// �W�L�[
	}else if(str == "9"){
		return(KEY_INPUT_9);// �X�L�[
	}
	//PAD
	if(str == "PAD_DOWN"){
		return (0x00000001); // ���`�F�b�N�}�X�N
	}else if(str == "PAD_LEFT"){
		return (0x00000002); // ���`�F�b�N�}�X�N
	}else if(str == "PAD_RIGHT"){
		return (0x00000004); // ���`�F�b�N�}�X�N
	}else if(str == "PAD_UP"){
		return (0x00000008); // ���`�F�b�N�}�X�N
	}else if(str == "PAD_1"){
		return (0x00000010); // �`�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_2"){
		return (0x00000020); // �a�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_3"){
		return (0x00000040); // �b�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_4"){
		return (0x00000080); // �w�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_5"){
		return (0x00000100); // �x�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_6"){
		return (0x00000200); // �y�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_7"){
		return (0x00000400); // �k�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_8"){
		return (0x00000800); // �q�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_9"){
		return (0x00001000); // �r�s�`�q�s�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_10"){
		return (0x00002000); // �l�{�^���`�F�b�N�}�X�N
	}else if(str == "PAD_11"){
		return (0x00004000);
	}else if(str == "PAD_12"){
		return (0x00008000);
	}else if(str == "PAD_13"){
		return (0x00010000);
	}else if(str == "PAD_14"){
		return (0x00020000);
	}else if(str == "PAD_15"){
		return (0x00040000);
	}else if(str == "PAD_16"){
		return (0x00080000);
	}else if(str == "PAD_17"){
		return (0x00100000);
	}else if(str == "PAD_18"){
		return (0x00200000);
	}else if(str == "PAD_19"){
		return (0x00400000);
	}else if(str == "PAD_20"){
		return (0x00800000);
	}else if(str == "PAD_21"){
		return (0x01000000);
	}else if(str == "PAD_22"){
		return (0x02000000);
	}else if(str == "PAD_23"){
		return (0x04000000);
	}else if(str == "PAD_24"){
		return (0x08000000);
	}else if(str == "PAD_25"){
		return (0x10000000);
	}else if(str == "PAD_26"){
		return (0x20000000);
	}else if(str == "PAD_27"){
		return (0x40000000);
	}else if(str == "PAD_28"){
		return (0x80000000);
	}else{
		return(-1);
	}
}
//�L�[�R���t�B�O�p�́A���l���當����֕ϊ�����֐��B
string_t cfunc::KeyInt2Str(int num, bool isPad){
	if(isPad==false){
		switch(num){
			case KEY_INPUT_BACK:
				// �o�b�N�X�y�[�X�L�[
				return("BACK");
			case KEY_INPUT_TAB:
				// �^�u�L�[
				return("TAB");
			case KEY_INPUT_RETURN:
				// �G���^�[�L�[
				return("RETURN");
			case KEY_INPUT_LSHIFT:
				// ���V�t�g�L�[
				return("LSHIFT");
			case KEY_INPUT_RSHIFT:
				// �E�V�t�g�L�[
				return("RSHIFT");
			case KEY_INPUT_LCONTROL:
				// ���R���g���[���L�[
				return("LCONTROL");
			case KEY_INPUT_RCONTROL:
				// �E�R���g���[���L�[
				return("RCONTROL");
			case KEY_INPUT_ESCAPE:
				// �G�X�P�[�v�L�[
				return("ESCAPE");
			case KEY_INPUT_SPACE:
				// �X�y�[�X�L�[
				return("SPACE");
			case KEY_INPUT_PGUP:
				// �o�������t�o�L�[
				return("PGUP");
			case KEY_INPUT_PGDN:
				// �o�������c�������L�[
				return("PGDN");
			case KEY_INPUT_END:
				// �G���h�L�[
				return("END");
			case KEY_INPUT_HOME:
				// �z�[���L�[
				return("HOME");
			case KEY_INPUT_LEFT:
				// ���L�[
				return("LEFT");
			case KEY_INPUT_UP:
				// ��L�[
				return("UP");
			case KEY_INPUT_RIGHT:
				// �E�L�[
				return("RIGHT");
			case KEY_INPUT_DOWN:
				// ���L�[
				return("DOWN");
			case KEY_INPUT_INSERT:
				// �C���T�[�g�L�[
				return("INSERT");
			case KEY_INPUT_DELETE:
				// �f���[�g�L�[
				return("DELETE");
			case KEY_INPUT_MINUS:
				// -�L�[
				return("MINUS");
			case KEY_INPUT_YEN:
				// ���L�[
				return("YEN");
			case KEY_INPUT_PREVTRACK:
				// �O�L�[
				return("PREVTRACK");
			case KEY_INPUT_PERIOD:
				// �D�L�[
				return("PERIOD");
			case KEY_INPUT_SLASH:
				// �^�L�[
				return("SLASH");
			case KEY_INPUT_LALT:
				// ���`�k�s�L�[
				return("LALT");
			case KEY_INPUT_RALT:
				// �E�`�k�s�L�[
				return("RALT");
			case KEY_INPUT_SCROLL:
				// ScrollLock�L�[
				return("SCROLL");
			case KEY_INPUT_SEMICOLON:
				// �G�L�[
				return("SEMICOLON");
			case KEY_INPUT_COLON:
				// �F�L�[
				return("COLON");
			case KEY_INPUT_LBRACKET:
				// �m�L�[
				return("LBRACKET");
			case KEY_INPUT_RBRACKET:
				// �n�L�[
				return("RBRACKET");
			case KEY_INPUT_AT:
				// ���L�[
				return("AT");
			case KEY_INPUT_BACKSLASH:
				// �_�L�[
				return("BACKSLASH");
			case KEY_INPUT_COMMA:
				// �C�L�[
				return("COMMA");
			case KEY_INPUT_CAPSLOCK:
				// CaspLock�L�[
				return("CAPSLOCK");
			case KEY_INPUT_SYSRQ:
				// PrintScreen�L�[
				return("SYSRQ");
			case KEY_INPUT_PAUSE:
				// PauseBreak�L�[
				return("PAUSE");
			case KEY_INPUT_NUMPAD0:
				// �e���L�[�O
				return("NUMPAD0");
			case KEY_INPUT_NUMPAD1:
				// �e���L�[�P
				return("NUMPAD1");
			case KEY_INPUT_NUMPAD2:
				// �e���L�[�Q
				return("NUMPAD2");
			case KEY_INPUT_NUMPAD3:
				// �e���L�[�R
				return("NUMPAD3");
			case KEY_INPUT_NUMPAD4:
				// �e���L�[�S
				return("NUMPAD4");
			case KEY_INPUT_NUMPAD5:
				// �e���L�[�T
				return("NUMPAD5");
			case KEY_INPUT_NUMPAD6:
				// �e���L�[�U
				return("NUMPAD6");
			case KEY_INPUT_NUMPAD7:
				// �e���L�[�V
				return("NUMPAD7");
			case KEY_INPUT_NUMPAD8:
				// �e���L�[�W
				return("NUMPAD8");
			case KEY_INPUT_NUMPAD9:
				// �e���L�[�X
				return("NUMPAD9");
			case KEY_INPUT_MULTIPLY:
				// �e���L�[���L�[
				return("MULTIPLY");
			case KEY_INPUT_ADD:
				// �e���L�[�{�L�[
				return("ADD");
			case KEY_INPUT_SUBTRACT:
				// �e���L�[-�L�[
				return("SUBTRACT");
			case KEY_INPUT_DECIMAL:
				// �e���L�[�D�L�[
				return("DECIMAL");
			case KEY_INPUT_DIVIDE:
				// �e���L�[�^�L�[
				return("DIVIDE");
			case KEY_INPUT_NUMPADENTER:
				// �e���L�[�̃G���^�[�L�[
				return("NUMPADENTER");
			case KEY_INPUT_F1:
				// �e�P�L�[
				return("F1");
			case KEY_INPUT_F2:
				// �e�Q�L�[
				return("F2");
			case KEY_INPUT_F3:
				// �e�R�L�[
				return("F3");
			case KEY_INPUT_F4:
				// �e�S�L�[
				return("F4");
			case KEY_INPUT_F5:
				// �e�T�L�[
				return("F5");
			case KEY_INPUT_F6:
				// �e�U�L�[
				return("F6");
			case KEY_INPUT_F7:
				// �e�V�L�[
				return("F7");
			case KEY_INPUT_F8:
				// �e�W�L�[
				return("F8");
			case KEY_INPUT_F9:
				// �e�X�L�[
				return("F9");
			case KEY_INPUT_F10:
				// �e�P�O�L�[
				return("F10");
			case KEY_INPUT_F11:
				// �e�P�P�L�[
				return("F11");
			case KEY_INPUT_F12:
				// �e�P�Q�L�[
				return("F12");
			case KEY_INPUT_A:
				// �`�L�[
				return("A");
			case KEY_INPUT_B:
				// �a�L�[
				return("B");
			case KEY_INPUT_C:
				// �b�L�[
				return("C");
			case KEY_INPUT_D:
				// �c�L�[
				return("D");
			case KEY_INPUT_E:
				// �d�L�[
				return("E");
			case KEY_INPUT_F:
				// �e�L�[
				return("F");
			case KEY_INPUT_G:
				// �f�L�[
				return("G");
			case KEY_INPUT_H:
				// �g�L�[
				return("H");
			case KEY_INPUT_I:
				// �h�L�[
				return("I");
			case KEY_INPUT_J:
				// �i�L�[
				return("J");
			case KEY_INPUT_K:
				// �j�L�[
				return("K");
			case KEY_INPUT_L:
				// �k�L�[
				return("L");
			case KEY_INPUT_M:
				// �l�L�[
				return("M");
			case KEY_INPUT_N:
				// �m�L�[
				return("N");
			case KEY_INPUT_O:
				// �n�L�[
				return("O");
			case KEY_INPUT_P:
				// �o�L�[
				return("P");
			case KEY_INPUT_Q:
				// �p�L�[
				return("Q");
			case KEY_INPUT_R:
				// �q�L�[
				return("R");
			case KEY_INPUT_S:
				// �r�L�[
				return("S");
			case KEY_INPUT_T:
				// �s�L�[
				return("T");
			case KEY_INPUT_U:
				// �t�L�[
				return("U");
			case KEY_INPUT_V:
				// �u�L�[
				return("V");
			case KEY_INPUT_W:
				// �v�L�[
				return("W");
			case KEY_INPUT_X:
				// �w�L�[
				return("X");
			case KEY_INPUT_Y:
				// �x�L�[
				return("Y");
			case KEY_INPUT_Z:
				// �y�L�[
				return("Z");
			case KEY_INPUT_0:
				// �O�L�[
				return("0");
			case KEY_INPUT_1:
				// �P�L�[
				return("1");
			case KEY_INPUT_2:
				// �Q�L�[
				return("2");
			case KEY_INPUT_3:
				// �R�L�[
				return("3");
			case KEY_INPUT_4:
				// �S�L�[
				return("4");
			case KEY_INPUT_5:
				// �T�L�[
				return("5");
			case KEY_INPUT_6:
				// �U�L�[
				return("6");
			case KEY_INPUT_7:
				// �V�L�[
				return("7");
			case KEY_INPUT_8:
				// �W�L�[
				return("8");
			case KEY_INPUT_9:
				// �X�L�[
				return("9");
		}
	}else{
		switch(num){
			case 0x00000001:
			 return("PAD_DOWN");
			case 0x00000002:
				 return("PAD_LEFT");
			case 0x00000004:
				 return("PAD_RIGHT");
			case 0x00000008:
				 return("PAD_UP");
			case 0x00000010:
				 return("PAD_1");
			case 0x00000020:
				 return("PAD_2");
			case 0x00000040:
				 return("PAD_3");
			case 0x00000080:
				 return("PAD_4");
			case 0x00000100:
				 return("PAD_5");
			case 0x00000200:
				 return("PAD_6");
			case 0x00000400:
				 return("PAD_7");
			case 0x00000800:
				 return("PAD_8");
			case 0x00001000:
				 return("PAD_9");
			case 0x00002000:
				 return("PAD_10");
			case 0x00004000:
				return("PAD_11");
			case 0x00008000:
				return("PAD_12");
			case 0x00010000:
				return("PAD_13");
			case 0x00020000:
				return("PAD_14");
			case 0x00040000:
				return("PAD_15");
			case 0x00080000:
				return("PAD_16");
			case 0x00100000:
				return("PAD_17");
			case 0x00200000:
				return("PAD_18");
			case 0x00400000:
				return("PAD_19");
			case 0x00800000:
				return("PAD_20");
			case 0x01000000:
				return("PAD_21");
			case 0x02000000:
				return("PAD_22");
			case 0x04000000:
				return("PAD_23");
			case 0x08000000:
				return("PAD_24");
			case 0x10000000:
				return("PAD_25");
			case 0x20000000:
				return("PAD_26");
			case 0x40000000:
				return("PAD_27");
			case 0x80000000:
				return("PAD_28");
		}
	}
	return("");
}

int cfunc::KeyInt2PadNo(int num){ //�L�[�}�b�s���O���ꂽ�l����p�b�h�̔ԍ���Ԃ��B�㉺���E��-1�A���̑���0�B
		switch(num){
			case 0x00000001:
			 return(-1);
			case 0x00000002:
				 return(-1);
			case 0x00000004:
				 return(-1);
			case 0x00000008:
				 return(-1);
			case 0x00000010:
				 return(1);
			case 0x00000020:
				 return(2);
			case 0x00000040:
				 return(3);
			case 0x00000080:
				 return(4);
			case 0x00000100:
				 return(5);
			case 0x00000200:
				 return(6);
			case 0x00000400:
				 return(7);
			case 0x00000800:
				 return(8);
			case 0x00001000:
				 return(9);
			case 0x00002000:
				 return(10);
			case 0x00004000:
				return(11);
			case 0x00008000:
				return(12);
			case 0x00010000:
				return(13);
			case 0x00020000:
				return(14);
			case 0x00040000:
				return(15);
			case 0x00080000:
				return(16);
			case 0x00100000:
				return(17);
			case 0x00200000:
				return(18);
			case 0x00400000:
				return(19);
			case 0x00800000:
				return(20);
			case 0x01000000:
				return(21);
			case 0x02000000:
				return(22);
			case 0x04000000:
				return(23);
			case 0x08000000:
				return(24);
			case 0x10000000:
				return(25);
			case 0x20000000:
				return(26);
			case 0x40000000:
				return(27);
			case 0x80000000:
				return(28);
		}
	return 0;
}
int cfunc::WhichButtonPressed(){
	if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_1 ) != 0 ){
		return PAD_INPUT_1;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_2 ) != 0 ){
		return PAD_INPUT_2;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_3 ) != 0 ){
		return PAD_INPUT_3;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4 ) != 0 ){
		return PAD_INPUT_4;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_5 ) != 0 ){
		return PAD_INPUT_5;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_6 ) != 0 ){
		return PAD_INPUT_6;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_7 ) != 0 ){
		return PAD_INPUT_7;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_8 ) != 0 ){
		return PAD_INPUT_8;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_9 ) != 0 ){
		return PAD_INPUT_9;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_10 ) != 0 ){
		return PAD_INPUT_10;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_11 ) != 0 ){
		return PAD_INPUT_11;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_12 ) != 0 ){
		return PAD_INPUT_12;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_13 ) != 0 ){
		return PAD_INPUT_13;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_14 ) != 0 ){
		return PAD_INPUT_14;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_15 ) != 0 ){
		return PAD_INPUT_15;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_16 ) != 0 ){
		return PAD_INPUT_16;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_17 ) != 0 ){
		return PAD_INPUT_17;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_18 ) != 0 ){
		return PAD_INPUT_18;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_19 ) != 0 ){
		return PAD_INPUT_19;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_20 ) != 0 ){
		return PAD_INPUT_20;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_21 ) != 0 ){
		return PAD_INPUT_21;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_22 ) != 0 ){
		return PAD_INPUT_22;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_23 ) != 0 ){
		return PAD_INPUT_23;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_24 ) != 0 ){
		return PAD_INPUT_24;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_25 ) != 0 ){
		return PAD_INPUT_25;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_26 ) != 0 ){
		return PAD_INPUT_26;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_27 ) != 0 ){
		return PAD_INPUT_27;
	}else if( ( GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_28 ) != 0 ){
		return PAD_INPUT_28;
	}else{
		return 0;
	}
}

int cfunc::WhichKeyPressed(){
	if(CheckHitKeyAll()==0){return 0;}
	char Buf[256];
	GetHitKeyStateAll(Buf ) ;
	if(Buf[KEY_INPUT_BACK]==1){return(KEY_INPUT_BACK);}	// �o�b�N�X�y�[�X�L�[
	else if(Buf[KEY_INPUT_TAB]==1){return(KEY_INPUT_TAB);}	// �^�u�L�[
	else if(Buf[KEY_INPUT_RETURN]==1){return(KEY_INPUT_RETURN);}	// �G���^�[�L�[
	else if(Buf[KEY_INPUT_LSHIFT]==1){return(KEY_INPUT_LSHIFT);}	// ���V�t�g�L�[
	else if(Buf[KEY_INPUT_RSHIFT]==1){return(KEY_INPUT_RSHIFT);}	// �E�V�t�g�L�[
	else if(Buf[KEY_INPUT_LCONTROL]==1){return(KEY_INPUT_LCONTROL);}	// ���R���g���[���L�[
	else if(Buf[KEY_INPUT_RCONTROL]==1){return(KEY_INPUT_RCONTROL);}	// �E�R���g���[���L�[
	else if(Buf[KEY_INPUT_ESCAPE]==1){return(KEY_INPUT_ESCAPE);}	// �G�X�P�[�v�L�[
	else if(Buf[KEY_INPUT_SPACE]==1){return(KEY_INPUT_SPACE);}	// �X�y�[�X�L�[
	else if(Buf[KEY_INPUT_PGUP]==1){return(KEY_INPUT_PGUP);}	// �o�������t�o�L�[
	else if(Buf[KEY_INPUT_PGDN]==1){return(KEY_INPUT_PGDN);}	// �o�������c�������L�[
	else if(Buf[KEY_INPUT_END]==1){return(KEY_INPUT_END);}	// �G���h�L�[
	else if(Buf[KEY_INPUT_HOME]==1){return(KEY_INPUT_HOME);}	// �z�[���L�[
	//else if(Buf[KEY_INPUT_LEFT]==1){return(KEY_INPUT_LEFT);}	// ���L�[
	//else if(Buf[KEY_INPUT_UP]==1){return(KEY_INPUT_UP);}	// ��L�[
	//else if(Buf[KEY_INPUT_RIGHT]==1){return(KEY_INPUT_RIGHT);}	// �E�L�[
	//else if(Buf[KEY_INPUT_DOWN]==1){return(KEY_INPUT_DOWN);}	// ���L�[
	else if(Buf[KEY_INPUT_INSERT]==1){return(KEY_INPUT_INSERT);}	// �C���T�[�g�L�[
	else if(Buf[KEY_INPUT_DELETE]==1){return(KEY_INPUT_DELETE);}	// �f���[�g�L�[
	else if(Buf[KEY_INPUT_MINUS]==1){return(KEY_INPUT_MINUS);}	// �|�L�[
	else if(Buf[KEY_INPUT_YEN]==1){return(KEY_INPUT_YEN);}	// ���L�[
	else if(Buf[KEY_INPUT_PREVTRACK]==1){return(KEY_INPUT_PREVTRACK);}	// �O�L�[
	else if(Buf[KEY_INPUT_PERIOD]==1){return(KEY_INPUT_PERIOD);}	// �D�L�[
	else if(Buf[KEY_INPUT_SLASH]==1){return(KEY_INPUT_SLASH);}	// �^�L�[
	else if(Buf[KEY_INPUT_LALT]==1){return(KEY_INPUT_LALT);}	// ���`�k�s�L�[
	else if(Buf[KEY_INPUT_RALT]==1){return(KEY_INPUT_RALT);}	// �E�`�k�s�L�[
	else if(Buf[KEY_INPUT_SCROLL]==1){return(KEY_INPUT_SCROLL);}	// ScrollLock�L�[
	else if(Buf[KEY_INPUT_SEMICOLON]==1){return(KEY_INPUT_SEMICOLON);}	// �G�L�[
	else if(Buf[KEY_INPUT_COLON]==1){return(KEY_INPUT_COLON);}	// �F�L�[
	else if(Buf[KEY_INPUT_LBRACKET]==1){return(KEY_INPUT_LBRACKET);}	// �m�L�[
	else if(Buf[KEY_INPUT_RBRACKET]==1){return(KEY_INPUT_RBRACKET);}	// �n�L�[
	else if(Buf[KEY_INPUT_AT]==1){return(KEY_INPUT_AT);}	// ���L�[
	else if(Buf[KEY_INPUT_BACKSLASH]==1){return(KEY_INPUT_BACKSLASH);}	// �_�L�[
	else if(Buf[KEY_INPUT_COMMA]==1){return(KEY_INPUT_COMMA);}	// �C�L�[
	else if(Buf[KEY_INPUT_CAPSLOCK]==1){return(KEY_INPUT_CAPSLOCK);}	// CaspLock�L�[
	else if(Buf[KEY_INPUT_PAUSE]==1){return(KEY_INPUT_PAUSE);}	// PauseBreak�L�[
	else if(Buf[KEY_INPUT_NUMPAD0]==1){return(KEY_INPUT_NUMPAD0);}	// �e���L�[�O
	else if(Buf[KEY_INPUT_NUMPAD1]==1){return(KEY_INPUT_NUMPAD1);}	// �e���L�[�P
	else if(Buf[KEY_INPUT_NUMPAD2]==1){return(KEY_INPUT_NUMPAD2);}	// �e���L�[�Q
	else if(Buf[KEY_INPUT_NUMPAD3]==1){return(KEY_INPUT_NUMPAD3);}	// �e���L�[�R
	else if(Buf[KEY_INPUT_NUMPAD4]==1){return(KEY_INPUT_NUMPAD4);}	// �e���L�[�S
	else if(Buf[KEY_INPUT_NUMPAD5]==1){return(KEY_INPUT_NUMPAD5);}	// �e���L�[�T
	else if(Buf[KEY_INPUT_NUMPAD6]==1){return(KEY_INPUT_NUMPAD6);}	// �e���L�[�U
	else if(Buf[KEY_INPUT_NUMPAD7]==1){return(KEY_INPUT_NUMPAD7);}	// �e���L�[�V
	else if(Buf[KEY_INPUT_NUMPAD8]==1){return(KEY_INPUT_NUMPAD8);}	// �e���L�[�W
	else if(Buf[KEY_INPUT_NUMPAD9]==1){return(KEY_INPUT_NUMPAD9);}	// �e���L�[�X
	else if(Buf[KEY_INPUT_MULTIPLY]==1){return(KEY_INPUT_MULTIPLY);}	// �e���L�[���L�[
	else if(Buf[KEY_INPUT_ADD]==1){return(KEY_INPUT_ADD);}	// �e���L�[�{�L�[
	else if(Buf[KEY_INPUT_SUBTRACT]==1){return(KEY_INPUT_SUBTRACT);}	// �e���L�[�|�L�[
	else if(Buf[KEY_INPUT_DECIMAL]==1){return(KEY_INPUT_DECIMAL);}	// �e���L�[�D�L�[
	else if(Buf[KEY_INPUT_DIVIDE]==1){return(KEY_INPUT_DIVIDE);}	// �e���L�[�^�L�[
	else if(Buf[KEY_INPUT_NUMPADENTER]==1){return(KEY_INPUT_NUMPADENTER);}	// �e���L�[�̃G���^�[�L�[
	else if(Buf[KEY_INPUT_F1]==1){return(KEY_INPUT_F1);}	// �e�P�L�[
	else if(Buf[KEY_INPUT_F2]==1){return(KEY_INPUT_F2);}	// �e�Q�L�[
	//else if(Buf[KEY_INPUT_F3]==1){return(KEY_INPUT_F3);}	// �e�R�L�[
	else if(Buf[KEY_INPUT_F4]==1){return(KEY_INPUT_F4);}	// �e�S�L�[
	else if(Buf[KEY_INPUT_F5]==1){return(KEY_INPUT_F5);}	// �e�T�L�[
	else if(Buf[KEY_INPUT_F6]==1){return(KEY_INPUT_F6);}	// �e�U�L�[
	else if(Buf[KEY_INPUT_F7]==1){return(KEY_INPUT_F7);}	// �e�V�L�[
	else if(Buf[KEY_INPUT_F8]==1){return(KEY_INPUT_F8);}	// �e�W�L�[
	else if(Buf[KEY_INPUT_F9]==1){return(KEY_INPUT_F9);}	// �e�X�L�[
	else if(Buf[KEY_INPUT_F10]==1){return(KEY_INPUT_F10);}	// �e�P�O�L�[
	else if(Buf[KEY_INPUT_F11]==1){return(KEY_INPUT_F11);}	// �e�P�P�L�[
	else if(Buf[KEY_INPUT_F12]==1){return(KEY_INPUT_F12);}	// �e�P�Q�L�[
	else if(Buf[KEY_INPUT_A]==1){return(KEY_INPUT_A);}	// �`�L�[
	else if(Buf[KEY_INPUT_B]==1){return(KEY_INPUT_B);}	// �a�L�[
	else if(Buf[KEY_INPUT_C]==1){return(KEY_INPUT_C);}	// �b�L�[
	else if(Buf[KEY_INPUT_D]==1){return(KEY_INPUT_D);}	// �c�L�[
	else if(Buf[KEY_INPUT_E]==1){return(KEY_INPUT_E);}	// �d�L�[
	else if(Buf[KEY_INPUT_F]==1){return(KEY_INPUT_F);}	// �e�L�[
	else if(Buf[KEY_INPUT_G]==1){return(KEY_INPUT_G);}	// �f�L�[
	else if(Buf[KEY_INPUT_H]==1){return(KEY_INPUT_H);}	// �g�L�[
	else if(Buf[KEY_INPUT_I]==1){return(KEY_INPUT_I);}	// �h�L�[
	else if(Buf[KEY_INPUT_J]==1){return(KEY_INPUT_J);}	// �i�L�[
	else if(Buf[KEY_INPUT_K]==1){return(KEY_INPUT_K);}	// �j�L�[
	else if(Buf[KEY_INPUT_L]==1){return(KEY_INPUT_L);}	// �k�L�[
	else if(Buf[KEY_INPUT_M]==1){return(KEY_INPUT_M);}	// �l�L�[
	else if(Buf[KEY_INPUT_N]==1){return(KEY_INPUT_N);}	// �m�L�[
	else if(Buf[KEY_INPUT_O]==1){return(KEY_INPUT_O);}	// �n�L�[
	else if(Buf[KEY_INPUT_P]==1){return(KEY_INPUT_P);}	// �o�L�[
	else if(Buf[KEY_INPUT_Q]==1){return(KEY_INPUT_Q);}	// �p�L�[
	else if(Buf[KEY_INPUT_R]==1){return(KEY_INPUT_R);}	// �q�L�[
	else if(Buf[KEY_INPUT_S]==1){return(KEY_INPUT_S);}	// �r�L�[
	else if(Buf[KEY_INPUT_T]==1){return(KEY_INPUT_T);}	// �s�L�[
	else if(Buf[KEY_INPUT_U]==1){return(KEY_INPUT_U);}	// �t�L�[
	else if(Buf[KEY_INPUT_V]==1){return(KEY_INPUT_V);}	// �u�L�[
	else if(Buf[KEY_INPUT_W]==1){return(KEY_INPUT_W);}	// �v�L�[
	else if(Buf[KEY_INPUT_X]==1){return(KEY_INPUT_X);}	// �w�L�[
	else if(Buf[KEY_INPUT_Y]==1){return(KEY_INPUT_Y);}	// �x�L�[
	else if(Buf[KEY_INPUT_Z]==1){return(KEY_INPUT_Z);}	// �y�L�[
	else if(Buf[KEY_INPUT_0]==1){return(KEY_INPUT_0);}	// �O�L�[
	else if(Buf[KEY_INPUT_1]==1){return(KEY_INPUT_1);}	// �P�L�[
	else if(Buf[KEY_INPUT_2]==1){return(KEY_INPUT_2);}	// �Q�L�[
	else if(Buf[KEY_INPUT_3]==1){return(KEY_INPUT_3);}	// �R�L�[
	else if(Buf[KEY_INPUT_4]==1){return(KEY_INPUT_4);}	// �S�L�[
	else if(Buf[KEY_INPUT_5]==1){return(KEY_INPUT_5);}	// �T�L�[
	else if(Buf[KEY_INPUT_6]==1){return(KEY_INPUT_6);}	// �U�L�[
	else if(Buf[KEY_INPUT_7]==1){return(KEY_INPUT_7);}	// �V�L�[
	else if(Buf[KEY_INPUT_8]==1){return(KEY_INPUT_8);}	// �W�L�[
	else if(Buf[KEY_INPUT_9]==1){return(KEY_INPUT_9);}	// �X�L�[
	else{return 0;}
	}

void cfunc::KeyInt2Chr(int num){
		switch(num){
			case KEY_INPUT_BACK:
				// �o�b�N�X�y�[�X�L�[
				KeyName="BACK";
				return;
			case KEY_INPUT_TAB:
				// �^�u�L�[
				KeyName="TAB";
				return;
			case KEY_INPUT_RETURN:
				// �G���^�[�L�[
				KeyName="RETURN";
				return;
			case KEY_INPUT_LSHIFT:
				// ���V�t�g�L�[
				KeyName="LSHIFT";
				return;
			case KEY_INPUT_RSHIFT:
				// �E�V�t�g�L�[
				KeyName="RSHIFT";
				return;
			case KEY_INPUT_LCONTROL:
				// ���R���g���[���L�[
				KeyName="LCONTROL";
				return;
			case KEY_INPUT_RCONTROL:
				// �E�R���g���[���L�[
				KeyName="RCONTROL";
				return;
			case KEY_INPUT_ESCAPE:
				// �G�X�P�[�v�L�[
				KeyName="ESCAPE";
				return;
			case KEY_INPUT_SPACE:
				// �X�y�[�X�L�[
				KeyName="SPACE";
				return;
			case KEY_INPUT_PGUP:
				// �o�������t�o�L�[
				KeyName="PGUP";
				return;
			case KEY_INPUT_PGDN:
				// �o�������c�������L�[
				KeyName="PGDN";
				return;
			case KEY_INPUT_END:
				// �G���h�L�[
				KeyName="END";
				return;
			case KEY_INPUT_HOME:
				// �z�[���L�[
				KeyName="HOME";
				return;
			case KEY_INPUT_LEFT:
				// ���L�[
				KeyName="LEFT";
				return;
			case KEY_INPUT_UP:
				// ��L�[
				KeyName="UP";
				return;
			case KEY_INPUT_RIGHT:
				// �E�L�[
				KeyName="RIGHT";
				return;
			case KEY_INPUT_DOWN:
				// ���L�[
				KeyName="DOWN";
				return;
			case KEY_INPUT_INSERT:
				// �C���T�[�g�L�[
				KeyName="INSERT";
				return;
			case KEY_INPUT_DELETE:
				// �f���[�g�L�[
				KeyName="DELETE";
				return;
			case KEY_INPUT_MINUS:
				// -�L�[
				KeyName="MINUS";
				return;
			case KEY_INPUT_YEN:
				// ���L�[
				KeyName="YEN";
				return;
			case KEY_INPUT_PREVTRACK:
				// �O�L�[
				KeyName="PREVTRACK";
				return;
			case KEY_INPUT_PERIOD:
				// �D�L�[
				KeyName="PERIOD";
				return;
			case KEY_INPUT_SLASH:
				// �^�L�[
				KeyName="SLASH";
				return;
			case KEY_INPUT_LALT:
				// ���`�k�s�L�[
				KeyName="LALT";
				return;
			case KEY_INPUT_RALT:
				// �E�`�k�s�L�[
				KeyName="RALT";
				return;
			case KEY_INPUT_SCROLL:
				// ScrollLock�L�[
				KeyName="SCROLL";
				return;
			case KEY_INPUT_SEMICOLON:
				// �G�L�[
				KeyName="SEMICOLON";
				return;
			case KEY_INPUT_COLON:
				// �F�L�[
				KeyName="COLON";
				return;
			case KEY_INPUT_LBRACKET:
				// �m�L�[
				KeyName="LBRACKET";
				return;
			case KEY_INPUT_RBRACKET:
				// �n�L�[
				KeyName="RBRACKET";
				return;
			case KEY_INPUT_AT:
				// ���L�[
				KeyName="AT";
				return;
			case KEY_INPUT_BACKSLASH:
				// �_�L�[
				KeyName="BACKSLASH";
				return;
			case KEY_INPUT_COMMA:
				// �C�L�[
				KeyName="COMMA";
				return;
			case KEY_INPUT_CAPSLOCK:
				// CaspLock�L�[
				KeyName="CAPSLOCK";
				return;
			case KEY_INPUT_SYSRQ:
				// PrintScreen�L�[
				KeyName="SYSRQ";
				return;
			case KEY_INPUT_PAUSE:
				// PauseBreak�L�[
				KeyName="PAUSE";
				return;
			case KEY_INPUT_NUMPAD0:
				// �e���L�[�O
				KeyName="NUMPAD0";
				return;
			case KEY_INPUT_NUMPAD1:
				// �e���L�[�P
				KeyName="NUMPAD1";
				return;
			case KEY_INPUT_NUMPAD2:
				// �e���L�[�Q
				KeyName="NUMPAD2";
				return;
			case KEY_INPUT_NUMPAD3:
				// �e���L�[�R
				KeyName="NUMPAD3";
				return;
			case KEY_INPUT_NUMPAD4:
				// �e���L�[�S
				KeyName="NUMPAD4";
				return;
			case KEY_INPUT_NUMPAD5:
				// �e���L�[�T
				KeyName="NUMPAD5";
				return;
			case KEY_INPUT_NUMPAD6:
				// �e���L�[�U
				KeyName="NUMPAD6";
				return;
			case KEY_INPUT_NUMPAD7:
				// �e���L�[�V
				KeyName="NUMPAD7";
				return;
			case KEY_INPUT_NUMPAD8:
				// �e���L�[�W
				KeyName="NUMPAD8";
				return;
			case KEY_INPUT_NUMPAD9:
				// �e���L�[�X
				KeyName="NUMPAD9";
				return;
			case KEY_INPUT_MULTIPLY:
				// �e���L�[���L�[
				KeyName="MULTIPLY";
				return;
			case KEY_INPUT_ADD:
				// �e���L�[�{�L�[
				KeyName="ADD";
				return;
			case KEY_INPUT_SUBTRACT:
				// �e���L�[-�L�[
				KeyName="SUBTRACT";
				return;
			case KEY_INPUT_DECIMAL:
				// �e���L�[�D�L�[
				KeyName="DECIMAL";
				return;
			case KEY_INPUT_DIVIDE:
				// �e���L�[�^�L�[
				KeyName="DIVIDE";
				return;
			case KEY_INPUT_NUMPADENTER:
				// �e���L�[�̃G���^�[�L�[
				KeyName="NUMPADENTER";
				return;
			case KEY_INPUT_F1:
				// �e�P�L�[
				KeyName="F1";
				return;
			case KEY_INPUT_F2:
				// �e�Q�L�[
				KeyName="F2";
				return;
			case KEY_INPUT_F3:
				// �e�R�L�[
				KeyName="F3";
				return;
			case KEY_INPUT_F4:
				// �e�S�L�[
				KeyName="F4";
				return;
			case KEY_INPUT_F5:
				// �e�T�L�[
				KeyName="F5";
				return;
			case KEY_INPUT_F6:
				// �e�U�L�[
				KeyName="F6";
				return;
			case KEY_INPUT_F7:
				// �e�V�L�[
				KeyName="F7";
				return;
			case KEY_INPUT_F8:
				// �e�W�L�[
				KeyName="F8";
				return;
			case KEY_INPUT_F9:
				// �e�X�L�[
				KeyName="F9";
				return;
			case KEY_INPUT_F10:
				// �e�P�O�L�[
				KeyName="F10";
				return;
			case KEY_INPUT_F11:
				// �e�P�P�L�[
				KeyName="F11";
				return;
			case KEY_INPUT_F12:
				// �e�P�Q�L�[
				KeyName="F12";
				return;
			case KEY_INPUT_A:
				// �`�L�[
				KeyName="A";
				return;
			case KEY_INPUT_B:
				// �a�L�[
				KeyName="B";
				return;
			case KEY_INPUT_C:
				// �b�L�[
				KeyName="C";
				return;
			case KEY_INPUT_D:
				// �c�L�[
				KeyName="D";
				return;
			case KEY_INPUT_E:
				// �d�L�[
				KeyName="E";
				return;
			case KEY_INPUT_F:
				// �e�L�[
				KeyName="F";
				return;
			case KEY_INPUT_G:
				// �f�L�[
				KeyName="G";
				return;
			case KEY_INPUT_H:
				// �g�L�[
				KeyName="H";
				return;
			case KEY_INPUT_I:
				// �h�L�[
				KeyName="I";
				return;
			case KEY_INPUT_J:
				// �i�L�[
				KeyName="J";
				return;
			case KEY_INPUT_K:
				// �j�L�[
				KeyName="K";
				return;
			case KEY_INPUT_L:
				// �k�L�[
				KeyName="L";
				return;
			case KEY_INPUT_M:
				// �l�L�[
				KeyName="M";
				return;
			case KEY_INPUT_N:
				// �m�L�[
				KeyName="N";
				return;
			case KEY_INPUT_O:
				// �n�L�[
				KeyName="O";
				return;
			case KEY_INPUT_P:
				// �o�L�[
				KeyName="P";
				return;
			case KEY_INPUT_Q:
				// �p�L�[
				KeyName="Q";
				return;
			case KEY_INPUT_R:
				// �q�L�[
				KeyName="R";
				return;
			case KEY_INPUT_S:
				// �r�L�[
				KeyName="S";
				return;
			case KEY_INPUT_T:
				// �s�L�[
				KeyName="T";
				return;
			case KEY_INPUT_U:
				// �t�L�[
				KeyName="U";
				return;
			case KEY_INPUT_V:
				// �u�L�[
				KeyName="V";
				return;
			case KEY_INPUT_W:
				// �v�L�[
				KeyName="W";
				return;
			case KEY_INPUT_X:
				// �w�L�[
				KeyName="X";
				return;
			case KEY_INPUT_Y:
				// �x�L�[
				KeyName="Y";
				return;
			case KEY_INPUT_Z:
				// �y�L�[
				KeyName="Z";
				return;
			case KEY_INPUT_0:
				// �O�L�[
				KeyName="0";
				return;
			case KEY_INPUT_1:
				// �P�L�[
				KeyName="1";
				return;
			case KEY_INPUT_2:
				// �Q�L�[
				KeyName="2";
				return;
			case KEY_INPUT_3:
				// �R�L�[
				KeyName="3";
				return;
			case KEY_INPUT_4:
				// �S�L�[
				KeyName="4";
				return;
			case KEY_INPUT_5:
				// �T�L�[
				KeyName="5";
				return;
			case KEY_INPUT_6:
				// �U�L�[
				KeyName="6";
				return;
			case KEY_INPUT_7:
				// �V�L�[
				KeyName="7";
				return;
			case KEY_INPUT_8:
				// �W�L�[
				KeyName="8";
				return;
			case KEY_INPUT_9:
				// �X�L�[
				KeyName="9";
				return;
			}
			KeyName="UNKNOWN";
			return;
}

string_t cfunc::ReplaceKeyNameAll(string_t str){
	//�L�[�{�[�h
	ReplaceKeyName(str,"%KEY_SHOT%",PjSys::key::shot,false); //�V���b�g
	ReplaceKeyName(str,"%KEY_SUB%",PjSys::key::sub,false); //�f�B�t�F���_
	ReplaceKeyName(str,"%KEY_BOMB%",PjSys::key::bomb,false); //�{��
	//�p�b�h
	ReplaceKeyName(str,"%PAD_SHOT%",PjSys::key::shot_p,true); //�V���b�g
	ReplaceKeyName(str,"%PAD_SUB%",PjSys::key::sub_p,true); //�f�B�t�F���_
	ReplaceKeyName(str,"%PAD_BOMB%",PjSys::key::bomb_p,true); //�{��

	return str;
}
void cfunc::ReplaceKeyName(string_t& str, string_t id, int& key, bool IsPad){
	if(boost::find_first(str,id)){
		string_t strkey("");
		if(IsPad == false){
			strkey = KeyInt2Str(key,IsPad);
		}else{
			strkey = boost::lexical_cast<string>(KeyInt2PadNo(key));
		}
		boost::replace_all(str,id,strkey);
	}
}