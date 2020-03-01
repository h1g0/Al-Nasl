#include "Common.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
string_t cfunc::KeyName;

bool Vapor::VisibleAll=true; //全体を表示するか否か
bool Vapor::Visible[VAPOR_NUM][VAPOR_PARTS_NUM]; //表示するかどうか
//x,yの位置関係:
//0- 1- 2- 3- 4- 5- 6- 7- 8- 9- 10- 11- 12- 13- 14- 15...
double Vapor::x[VAPOR_NUM][VAPOR_PARTS_NUM];
double Vapor::y[VAPOR_NUM][VAPOR_PARTS_NUM];
int Vapor::Alpha[VAPOR_NUM][VAPOR_PARTS_NUM]; //透明度

bool Vapor::IsMake[VAPOR_NUM];
double Vapor::MakeX[VAPOR_NUM];
double Vapor::MakeY[VAPOR_NUM];
int Vapor::MakeAlpha[VAPOR_NUM];

//初期化
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

//ベイパー生成
int Vapor::Make(int idx, double SetX, double SetY,int SetAlpha){
	if(idx>=VAPOR_NUM){return -1;} //指定したIDが元々の本数より多い
	VisibleAll=true;
	IsMake[idx]=true;
	MakeX[idx]=SetX;
	MakeY[idx]=SetY;
	MakeAlpha[idx]=SetAlpha;
	return 1;
}

//ベイパー動かす
void Vapor::Move(){
	if(VisibleAll==false){
		return;
	} //描画すべき対象がなければ終了
	bool AnyVisible=false;
	//double a=1.0/VAPOR_PARTS_NUM;
	for(int i=0; i<VAPOR_NUM; i++){
		for(int j=VAPOR_PARTS_NUM-1; j>0; j--){
			int k=j-1;
			Visible[i][j]=Visible[i][k];
			x[i][j]=x[i][k];
			y[i][j]=y[i][k]+VAPOR_DIST;//下に向かって伸ばす
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
		return; //描画すべき対象がなければ終了
	}else{
		//描画
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
		if(Frame<=15){ //フェードアウト
			addy=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(mysin(DX_PI_F*Frame/30.0f)*255));
		}else if(Frame<=SHOW_BGM_TITLE_FRM+15){ //通常表示
			addy=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		}else if(Frame<=SHOW_BGM_TITLE_FRM+30){ //フェードイン
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

//クソみたいな関数群

//キー名からキー定数へ
int cfunc::KeyStr2Int(string_t str){
	if(str== "BACK"){
		return(KEY_INPUT_BACK);// バックスペースキー
	}else if(str == "TAB"){
		return(KEY_INPUT_TAB);// タブキー
	}else if(str == "RETURN"){
		return(KEY_INPUT_RETURN);// エンターキー
	}else if(str == "LSHIFT"){
		return(KEY_INPUT_LSHIFT);// 左シフトキー
	}else if(str == "RSHIFT"){
		return(KEY_INPUT_RSHIFT);// 右シフトキー
	}else if(str == "LCONTROL"){
		return(KEY_INPUT_LCONTROL);// 左コントロールキー
	}else if(str == "RCONTROL"){
		return(KEY_INPUT_RCONTROL);// 右コントロールキー
	}else if(str == "ESCAPE"){
		return(KEY_INPUT_ESCAPE);// エスケープキー
	}else if(str == "SPACE"){
		return(KEY_INPUT_SPACE);// スペースキー
	}else if(str == "PGUP"){
		return(KEY_INPUT_PGUP);// ＰａｇｅＵＰキー
	}else if(str == "PGDN"){
		return(KEY_INPUT_PGDN);// ＰａｇｅＤｏｗｎキー
	}else if(str == "END"){
		return(KEY_INPUT_END);// エンドキー
	}else if(str == "HOME"){
		return(KEY_INPUT_HOME);// ホームキー
	}else if(str == "LEFT"){
		return(KEY_INPUT_LEFT);// 左キー
	}else if(str == "UP"){
		return(KEY_INPUT_UP);// 上キー
	}else if(str == "RIGHT"){
		return(KEY_INPUT_RIGHT);// 右キー
	}else if(str == "DOWN"){
		return(KEY_INPUT_DOWN);// 下キー
	}else if(str == "INSERT"){
		return(KEY_INPUT_INSERT);// インサートキー
	}else if(str == "DELETE"){
		return(KEY_INPUT_DELETE);// デリートキー
	}else if(str == "MINUS"){
		return(KEY_INPUT_MINUS);// -キー
	}else if(str == "YEN"){
		return(KEY_INPUT_YEN);// ￥キー
	}else if(str == "PREVTRACK"){
		return(KEY_INPUT_PREVTRACK);// ＾キー
	}else if(str == "PERIOD"){
		return(KEY_INPUT_PERIOD);// ．キー
	}else if(str == "SLASH"){
		return(KEY_INPUT_SLASH);// ／キー
	}else if(str == "LALT"){
		return(KEY_INPUT_LALT);// 左ＡＬＴキー
	}else if(str == "RALT"){
		return(KEY_INPUT_RALT);// 右ＡＬＴキー
	}else if(str == "SCROLL"){
		return(KEY_INPUT_SCROLL);// ScrollLockキー
	}else if(str == "SEMICOLON"){
		return(KEY_INPUT_SEMICOLON);// ；キー
	}else if(str == "COLON"){
		return(KEY_INPUT_COLON);// ：キー
	}else if(str == "LBRACKET"){
		return(KEY_INPUT_LBRACKET);// ［キー
	}else if(str == "RBRACKET"){
		return(KEY_INPUT_RBRACKET);// ］キー
	}else if(str == "AT"){
		return(KEY_INPUT_AT);// ＠キー
	}else if(str == "BACKSLASH"){
		return(KEY_INPUT_BACKSLASH);// ＼キー
	}else if(str == "COMMA"){
		return(KEY_INPUT_COMMA);// ，キー
	}else if(str == "CAPSLOCK"){
		return(KEY_INPUT_CAPSLOCK);// CaspLockキー
	}else if(str == "SYSRQ"){
		return(KEY_INPUT_SYSRQ);// PrintScreenキー
	}else if(str == "PAUSE"){
		return(KEY_INPUT_PAUSE);// PauseBreakキー
	}else if(str == "NUMPAD0"){
		return(KEY_INPUT_NUMPAD0);// テンキー０
	}else if(str == "NUMPAD1"){
		return(KEY_INPUT_NUMPAD1);// テンキー１
	}else if(str == "NUMPAD2"){
		return(KEY_INPUT_NUMPAD2);// テンキー２
	}else if(str == "NUMPAD3"){
		return(KEY_INPUT_NUMPAD3);// テンキー３
	}else if(str == "NUMPAD4"){
		return(KEY_INPUT_NUMPAD4);// テンキー４
	}else if(str == "NUMPAD5"){
		return(KEY_INPUT_NUMPAD5);// テンキー５
	}else if(str == "NUMPAD6"){
		return(KEY_INPUT_NUMPAD6);// テンキー６
	}else if(str == "NUMPAD7"){
		return(KEY_INPUT_NUMPAD7);// テンキー７
	}else if(str == "NUMPAD8"){
		return(KEY_INPUT_NUMPAD8);// テンキー８
	}else if(str == "NUMPAD9"){
		return(KEY_INPUT_NUMPAD9);// テンキー９
	}else if(str == "MULTIPLY"){
		return(KEY_INPUT_MULTIPLY);// テンキー＊キー
	}else if(str == "ADD"){
		return(KEY_INPUT_ADD);// テンキー＋キー
	}else if(str == "SUBTRACT"){
		return(KEY_INPUT_SUBTRACT);// テンキー-キー
	}else if(str == "DECIMAL"){
		return(KEY_INPUT_DECIMAL);// テンキー．キー
	}else if(str == "DIVIDE"){
		return(KEY_INPUT_DIVIDE);// テンキー／キー
	}else if(str == "NUMPADENTER"){
		return(KEY_INPUT_NUMPADENTER);// テンキーのエンターキー
	}else if(str == "F1"){
		return(KEY_INPUT_F1);// Ｆ１キー
	}else if(str == "F2"){
		return(KEY_INPUT_F2);// Ｆ２キー
	}else if(str == "F3"){
		return(KEY_INPUT_F3);// Ｆ３キー
	}else if(str == "F4"){
		return(KEY_INPUT_F4);// Ｆ４キー
	}else if(str == "F5"){
		return(KEY_INPUT_F5);// Ｆ５キー
	}else if(str == "F6"){
		return(KEY_INPUT_F6);// Ｆ６キー
	}else if(str == "F7"){
		return(KEY_INPUT_F7);// Ｆ７キー
	}else if(str == "F8"){
		return(KEY_INPUT_F8);// Ｆ８キー
	}else if(str == "F9"){
		return(KEY_INPUT_F9);// Ｆ９キー
	}else if(str == "F10"){
		return(KEY_INPUT_F10);// Ｆ１０キー
	}else if(str == "F11"){
		return(KEY_INPUT_F11);// Ｆ１１キー
	}else if(str == "F12"){
		return(KEY_INPUT_F12);// Ｆ１２キー
	}else if(str == "A"){
		return(KEY_INPUT_A);// Ａキー
	}else if(str == "B"){
		return(KEY_INPUT_B);// Ｂキー
	}else if(str == "C"){
		return(KEY_INPUT_C);// Ｃキー
	}else if(str == "D"){
		return(KEY_INPUT_D);// Ｄキー
	}else if(str == "E"){
		return(KEY_INPUT_E);// Ｅキー
	}else if(str == "F"){
		return(KEY_INPUT_F);// Ｆキー
	}else if(str == "G"){
		return(KEY_INPUT_G);// Ｇキー
	}else if(str == "H"){
		return(KEY_INPUT_H);// Ｈキー
	}else if(str == "I"){
		return(KEY_INPUT_I);// Ｉキー
	}else if(str == "J"){
		return(KEY_INPUT_J);// Ｊキー
	}else if(str == "K"){
		return(KEY_INPUT_K);// Ｋキー
	}else if(str == "L"){
		return(KEY_INPUT_L);// Ｌキー
	}else if(str == "M"){
		return(KEY_INPUT_M);// Ｍキー
	}else if(str == "N"){
		return(KEY_INPUT_N);// Ｎキー
	}else if(str == "O"){
		return(KEY_INPUT_O);// Ｏキー
	}else if(str == "P"){
		return(KEY_INPUT_P);// Ｐキー
	}else if(str == "Q"){
		return(KEY_INPUT_Q);// Ｑキー
	}else if(str == "R"){
		return(KEY_INPUT_R);// Ｒキー
	}else if(str == "S"){
		return(KEY_INPUT_S);// Ｓキー
	}else if(str == "T"){
		return(KEY_INPUT_T);// Ｔキー
	}else if(str == "U"){
		return(KEY_INPUT_U);// Ｕキー
	}else if(str == "V"){
		return(KEY_INPUT_V);// Ｖキー
	}else if(str == "W"){
		return(KEY_INPUT_W);// Ｗキー
	}else if(str == "X"){
		return(KEY_INPUT_X);// Ｘキー
	}else if(str == "Y"){
		return(KEY_INPUT_Y);// Ｙキー
	}else if(str == "Z"){
		return(KEY_INPUT_Z);// Ｚキー
	}else if(str == "0" ){
		return(KEY_INPUT_0);// ０キー
	}else if(str == "1"){
		return(KEY_INPUT_1);// １キー
	}else if(str == "2"){
		return(KEY_INPUT_2);// ２キー
	}else if(str == "3"){
		return(KEY_INPUT_3);// ３キー
	}else if(str == "4"){
		return(KEY_INPUT_4);// ４キー
	}else if(str == "5"){
		return(KEY_INPUT_5);// ５キー
	}else if(str == "6"){
		return(KEY_INPUT_6);// ６キー
	}else if(str == "7"){
		return(KEY_INPUT_7);// ７キー
	}else if(str == "8"){
		return(KEY_INPUT_8);// ８キー
	}else if(str == "9"){
		return(KEY_INPUT_9);// ９キー
	}
	//PAD
	if(str == "PAD_DOWN"){
		return (0x00000001); // ↓チェックマスク
	}else if(str == "PAD_LEFT"){
		return (0x00000002); // ←チェックマスク
	}else if(str == "PAD_RIGHT"){
		return (0x00000004); // →チェックマスク
	}else if(str == "PAD_UP"){
		return (0x00000008); // ↑チェックマスク
	}else if(str == "PAD_1"){
		return (0x00000010); // Ａボタンチェックマスク
	}else if(str == "PAD_2"){
		return (0x00000020); // Ｂボタンチェックマスク
	}else if(str == "PAD_3"){
		return (0x00000040); // Ｃボタンチェックマスク
	}else if(str == "PAD_4"){
		return (0x00000080); // Ｘボタンチェックマスク
	}else if(str == "PAD_5"){
		return (0x00000100); // Ｙボタンチェックマスク
	}else if(str == "PAD_6"){
		return (0x00000200); // Ｚボタンチェックマスク
	}else if(str == "PAD_7"){
		return (0x00000400); // Ｌボタンチェックマスク
	}else if(str == "PAD_8"){
		return (0x00000800); // Ｒボタンチェックマスク
	}else if(str == "PAD_9"){
		return (0x00001000); // ＳＴＡＲＴボタンチェックマスク
	}else if(str == "PAD_10"){
		return (0x00002000); // Ｍボタンチェックマスク
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
//キーコンフィグ用の、数値から文字列へ変換する関数。
string_t cfunc::KeyInt2Str(int num, bool isPad){
	if(isPad==false){
		switch(num){
			case KEY_INPUT_BACK:
				// バックスペースキー
				return("BACK");
			case KEY_INPUT_TAB:
				// タブキー
				return("TAB");
			case KEY_INPUT_RETURN:
				// エンターキー
				return("RETURN");
			case KEY_INPUT_LSHIFT:
				// 左シフトキー
				return("LSHIFT");
			case KEY_INPUT_RSHIFT:
				// 右シフトキー
				return("RSHIFT");
			case KEY_INPUT_LCONTROL:
				// 左コントロールキー
				return("LCONTROL");
			case KEY_INPUT_RCONTROL:
				// 右コントロールキー
				return("RCONTROL");
			case KEY_INPUT_ESCAPE:
				// エスケープキー
				return("ESCAPE");
			case KEY_INPUT_SPACE:
				// スペースキー
				return("SPACE");
			case KEY_INPUT_PGUP:
				// ＰａｇｅＵＰキー
				return("PGUP");
			case KEY_INPUT_PGDN:
				// ＰａｇｅＤｏｗｎキー
				return("PGDN");
			case KEY_INPUT_END:
				// エンドキー
				return("END");
			case KEY_INPUT_HOME:
				// ホームキー
				return("HOME");
			case KEY_INPUT_LEFT:
				// 左キー
				return("LEFT");
			case KEY_INPUT_UP:
				// 上キー
				return("UP");
			case KEY_INPUT_RIGHT:
				// 右キー
				return("RIGHT");
			case KEY_INPUT_DOWN:
				// 下キー
				return("DOWN");
			case KEY_INPUT_INSERT:
				// インサートキー
				return("INSERT");
			case KEY_INPUT_DELETE:
				// デリートキー
				return("DELETE");
			case KEY_INPUT_MINUS:
				// -キー
				return("MINUS");
			case KEY_INPUT_YEN:
				// ￥キー
				return("YEN");
			case KEY_INPUT_PREVTRACK:
				// ＾キー
				return("PREVTRACK");
			case KEY_INPUT_PERIOD:
				// ．キー
				return("PERIOD");
			case KEY_INPUT_SLASH:
				// ／キー
				return("SLASH");
			case KEY_INPUT_LALT:
				// 左ＡＬＴキー
				return("LALT");
			case KEY_INPUT_RALT:
				// 右ＡＬＴキー
				return("RALT");
			case KEY_INPUT_SCROLL:
				// ScrollLockキー
				return("SCROLL");
			case KEY_INPUT_SEMICOLON:
				// ；キー
				return("SEMICOLON");
			case KEY_INPUT_COLON:
				// ：キー
				return("COLON");
			case KEY_INPUT_LBRACKET:
				// ［キー
				return("LBRACKET");
			case KEY_INPUT_RBRACKET:
				// ］キー
				return("RBRACKET");
			case KEY_INPUT_AT:
				// ＠キー
				return("AT");
			case KEY_INPUT_BACKSLASH:
				// ＼キー
				return("BACKSLASH");
			case KEY_INPUT_COMMA:
				// ，キー
				return("COMMA");
			case KEY_INPUT_CAPSLOCK:
				// CaspLockキー
				return("CAPSLOCK");
			case KEY_INPUT_SYSRQ:
				// PrintScreenキー
				return("SYSRQ");
			case KEY_INPUT_PAUSE:
				// PauseBreakキー
				return("PAUSE");
			case KEY_INPUT_NUMPAD0:
				// テンキー０
				return("NUMPAD0");
			case KEY_INPUT_NUMPAD1:
				// テンキー１
				return("NUMPAD1");
			case KEY_INPUT_NUMPAD2:
				// テンキー２
				return("NUMPAD2");
			case KEY_INPUT_NUMPAD3:
				// テンキー３
				return("NUMPAD3");
			case KEY_INPUT_NUMPAD4:
				// テンキー４
				return("NUMPAD4");
			case KEY_INPUT_NUMPAD5:
				// テンキー５
				return("NUMPAD5");
			case KEY_INPUT_NUMPAD6:
				// テンキー６
				return("NUMPAD6");
			case KEY_INPUT_NUMPAD7:
				// テンキー７
				return("NUMPAD7");
			case KEY_INPUT_NUMPAD8:
				// テンキー８
				return("NUMPAD8");
			case KEY_INPUT_NUMPAD9:
				// テンキー９
				return("NUMPAD9");
			case KEY_INPUT_MULTIPLY:
				// テンキー＊キー
				return("MULTIPLY");
			case KEY_INPUT_ADD:
				// テンキー＋キー
				return("ADD");
			case KEY_INPUT_SUBTRACT:
				// テンキー-キー
				return("SUBTRACT");
			case KEY_INPUT_DECIMAL:
				// テンキー．キー
				return("DECIMAL");
			case KEY_INPUT_DIVIDE:
				// テンキー／キー
				return("DIVIDE");
			case KEY_INPUT_NUMPADENTER:
				// テンキーのエンターキー
				return("NUMPADENTER");
			case KEY_INPUT_F1:
				// Ｆ１キー
				return("F1");
			case KEY_INPUT_F2:
				// Ｆ２キー
				return("F2");
			case KEY_INPUT_F3:
				// Ｆ３キー
				return("F3");
			case KEY_INPUT_F4:
				// Ｆ４キー
				return("F4");
			case KEY_INPUT_F5:
				// Ｆ５キー
				return("F5");
			case KEY_INPUT_F6:
				// Ｆ６キー
				return("F6");
			case KEY_INPUT_F7:
				// Ｆ７キー
				return("F7");
			case KEY_INPUT_F8:
				// Ｆ８キー
				return("F8");
			case KEY_INPUT_F9:
				// Ｆ９キー
				return("F9");
			case KEY_INPUT_F10:
				// Ｆ１０キー
				return("F10");
			case KEY_INPUT_F11:
				// Ｆ１１キー
				return("F11");
			case KEY_INPUT_F12:
				// Ｆ１２キー
				return("F12");
			case KEY_INPUT_A:
				// Ａキー
				return("A");
			case KEY_INPUT_B:
				// Ｂキー
				return("B");
			case KEY_INPUT_C:
				// Ｃキー
				return("C");
			case KEY_INPUT_D:
				// Ｄキー
				return("D");
			case KEY_INPUT_E:
				// Ｅキー
				return("E");
			case KEY_INPUT_F:
				// Ｆキー
				return("F");
			case KEY_INPUT_G:
				// Ｇキー
				return("G");
			case KEY_INPUT_H:
				// Ｈキー
				return("H");
			case KEY_INPUT_I:
				// Ｉキー
				return("I");
			case KEY_INPUT_J:
				// Ｊキー
				return("J");
			case KEY_INPUT_K:
				// Ｋキー
				return("K");
			case KEY_INPUT_L:
				// Ｌキー
				return("L");
			case KEY_INPUT_M:
				// Ｍキー
				return("M");
			case KEY_INPUT_N:
				// Ｎキー
				return("N");
			case KEY_INPUT_O:
				// Ｏキー
				return("O");
			case KEY_INPUT_P:
				// Ｐキー
				return("P");
			case KEY_INPUT_Q:
				// Ｑキー
				return("Q");
			case KEY_INPUT_R:
				// Ｒキー
				return("R");
			case KEY_INPUT_S:
				// Ｓキー
				return("S");
			case KEY_INPUT_T:
				// Ｔキー
				return("T");
			case KEY_INPUT_U:
				// Ｕキー
				return("U");
			case KEY_INPUT_V:
				// Ｖキー
				return("V");
			case KEY_INPUT_W:
				// Ｗキー
				return("W");
			case KEY_INPUT_X:
				// Ｘキー
				return("X");
			case KEY_INPUT_Y:
				// Ｙキー
				return("Y");
			case KEY_INPUT_Z:
				// Ｚキー
				return("Z");
			case KEY_INPUT_0:
				// ０キー
				return("0");
			case KEY_INPUT_1:
				// １キー
				return("1");
			case KEY_INPUT_2:
				// ２キー
				return("2");
			case KEY_INPUT_3:
				// ３キー
				return("3");
			case KEY_INPUT_4:
				// ４キー
				return("4");
			case KEY_INPUT_5:
				// ５キー
				return("5");
			case KEY_INPUT_6:
				// ６キー
				return("6");
			case KEY_INPUT_7:
				// ７キー
				return("7");
			case KEY_INPUT_8:
				// ８キー
				return("8");
			case KEY_INPUT_9:
				// ９キー
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

int cfunc::KeyInt2PadNo(int num){ //キーマッピングされた値からパッドの番号を返す。上下左右は-1、その他は0。
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
	if(Buf[KEY_INPUT_BACK]==1){return(KEY_INPUT_BACK);}	// バックスペースキー
	else if(Buf[KEY_INPUT_TAB]==1){return(KEY_INPUT_TAB);}	// タブキー
	else if(Buf[KEY_INPUT_RETURN]==1){return(KEY_INPUT_RETURN);}	// エンターキー
	else if(Buf[KEY_INPUT_LSHIFT]==1){return(KEY_INPUT_LSHIFT);}	// 左シフトキー
	else if(Buf[KEY_INPUT_RSHIFT]==1){return(KEY_INPUT_RSHIFT);}	// 右シフトキー
	else if(Buf[KEY_INPUT_LCONTROL]==1){return(KEY_INPUT_LCONTROL);}	// 左コントロールキー
	else if(Buf[KEY_INPUT_RCONTROL]==1){return(KEY_INPUT_RCONTROL);}	// 右コントロールキー
	else if(Buf[KEY_INPUT_ESCAPE]==1){return(KEY_INPUT_ESCAPE);}	// エスケープキー
	else if(Buf[KEY_INPUT_SPACE]==1){return(KEY_INPUT_SPACE);}	// スペースキー
	else if(Buf[KEY_INPUT_PGUP]==1){return(KEY_INPUT_PGUP);}	// ＰａｇｅＵＰキー
	else if(Buf[KEY_INPUT_PGDN]==1){return(KEY_INPUT_PGDN);}	// ＰａｇｅＤｏｗｎキー
	else if(Buf[KEY_INPUT_END]==1){return(KEY_INPUT_END);}	// エンドキー
	else if(Buf[KEY_INPUT_HOME]==1){return(KEY_INPUT_HOME);}	// ホームキー
	//else if(Buf[KEY_INPUT_LEFT]==1){return(KEY_INPUT_LEFT);}	// 左キー
	//else if(Buf[KEY_INPUT_UP]==1){return(KEY_INPUT_UP);}	// 上キー
	//else if(Buf[KEY_INPUT_RIGHT]==1){return(KEY_INPUT_RIGHT);}	// 右キー
	//else if(Buf[KEY_INPUT_DOWN]==1){return(KEY_INPUT_DOWN);}	// 下キー
	else if(Buf[KEY_INPUT_INSERT]==1){return(KEY_INPUT_INSERT);}	// インサートキー
	else if(Buf[KEY_INPUT_DELETE]==1){return(KEY_INPUT_DELETE);}	// デリートキー
	else if(Buf[KEY_INPUT_MINUS]==1){return(KEY_INPUT_MINUS);}	// －キー
	else if(Buf[KEY_INPUT_YEN]==1){return(KEY_INPUT_YEN);}	// ￥キー
	else if(Buf[KEY_INPUT_PREVTRACK]==1){return(KEY_INPUT_PREVTRACK);}	// ＾キー
	else if(Buf[KEY_INPUT_PERIOD]==1){return(KEY_INPUT_PERIOD);}	// ．キー
	else if(Buf[KEY_INPUT_SLASH]==1){return(KEY_INPUT_SLASH);}	// ／キー
	else if(Buf[KEY_INPUT_LALT]==1){return(KEY_INPUT_LALT);}	// 左ＡＬＴキー
	else if(Buf[KEY_INPUT_RALT]==1){return(KEY_INPUT_RALT);}	// 右ＡＬＴキー
	else if(Buf[KEY_INPUT_SCROLL]==1){return(KEY_INPUT_SCROLL);}	// ScrollLockキー
	else if(Buf[KEY_INPUT_SEMICOLON]==1){return(KEY_INPUT_SEMICOLON);}	// ；キー
	else if(Buf[KEY_INPUT_COLON]==1){return(KEY_INPUT_COLON);}	// ：キー
	else if(Buf[KEY_INPUT_LBRACKET]==1){return(KEY_INPUT_LBRACKET);}	// ［キー
	else if(Buf[KEY_INPUT_RBRACKET]==1){return(KEY_INPUT_RBRACKET);}	// ］キー
	else if(Buf[KEY_INPUT_AT]==1){return(KEY_INPUT_AT);}	// ＠キー
	else if(Buf[KEY_INPUT_BACKSLASH]==1){return(KEY_INPUT_BACKSLASH);}	// ＼キー
	else if(Buf[KEY_INPUT_COMMA]==1){return(KEY_INPUT_COMMA);}	// ，キー
	else if(Buf[KEY_INPUT_CAPSLOCK]==1){return(KEY_INPUT_CAPSLOCK);}	// CaspLockキー
	else if(Buf[KEY_INPUT_PAUSE]==1){return(KEY_INPUT_PAUSE);}	// PauseBreakキー
	else if(Buf[KEY_INPUT_NUMPAD0]==1){return(KEY_INPUT_NUMPAD0);}	// テンキー０
	else if(Buf[KEY_INPUT_NUMPAD1]==1){return(KEY_INPUT_NUMPAD1);}	// テンキー１
	else if(Buf[KEY_INPUT_NUMPAD2]==1){return(KEY_INPUT_NUMPAD2);}	// テンキー２
	else if(Buf[KEY_INPUT_NUMPAD3]==1){return(KEY_INPUT_NUMPAD3);}	// テンキー３
	else if(Buf[KEY_INPUT_NUMPAD4]==1){return(KEY_INPUT_NUMPAD4);}	// テンキー４
	else if(Buf[KEY_INPUT_NUMPAD5]==1){return(KEY_INPUT_NUMPAD5);}	// テンキー５
	else if(Buf[KEY_INPUT_NUMPAD6]==1){return(KEY_INPUT_NUMPAD6);}	// テンキー６
	else if(Buf[KEY_INPUT_NUMPAD7]==1){return(KEY_INPUT_NUMPAD7);}	// テンキー７
	else if(Buf[KEY_INPUT_NUMPAD8]==1){return(KEY_INPUT_NUMPAD8);}	// テンキー８
	else if(Buf[KEY_INPUT_NUMPAD9]==1){return(KEY_INPUT_NUMPAD9);}	// テンキー９
	else if(Buf[KEY_INPUT_MULTIPLY]==1){return(KEY_INPUT_MULTIPLY);}	// テンキー＊キー
	else if(Buf[KEY_INPUT_ADD]==1){return(KEY_INPUT_ADD);}	// テンキー＋キー
	else if(Buf[KEY_INPUT_SUBTRACT]==1){return(KEY_INPUT_SUBTRACT);}	// テンキー－キー
	else if(Buf[KEY_INPUT_DECIMAL]==1){return(KEY_INPUT_DECIMAL);}	// テンキー．キー
	else if(Buf[KEY_INPUT_DIVIDE]==1){return(KEY_INPUT_DIVIDE);}	// テンキー／キー
	else if(Buf[KEY_INPUT_NUMPADENTER]==1){return(KEY_INPUT_NUMPADENTER);}	// テンキーのエンターキー
	else if(Buf[KEY_INPUT_F1]==1){return(KEY_INPUT_F1);}	// Ｆ１キー
	else if(Buf[KEY_INPUT_F2]==1){return(KEY_INPUT_F2);}	// Ｆ２キー
	//else if(Buf[KEY_INPUT_F3]==1){return(KEY_INPUT_F3);}	// Ｆ３キー
	else if(Buf[KEY_INPUT_F4]==1){return(KEY_INPUT_F4);}	// Ｆ４キー
	else if(Buf[KEY_INPUT_F5]==1){return(KEY_INPUT_F5);}	// Ｆ５キー
	else if(Buf[KEY_INPUT_F6]==1){return(KEY_INPUT_F6);}	// Ｆ６キー
	else if(Buf[KEY_INPUT_F7]==1){return(KEY_INPUT_F7);}	// Ｆ７キー
	else if(Buf[KEY_INPUT_F8]==1){return(KEY_INPUT_F8);}	// Ｆ８キー
	else if(Buf[KEY_INPUT_F9]==1){return(KEY_INPUT_F9);}	// Ｆ９キー
	else if(Buf[KEY_INPUT_F10]==1){return(KEY_INPUT_F10);}	// Ｆ１０キー
	else if(Buf[KEY_INPUT_F11]==1){return(KEY_INPUT_F11);}	// Ｆ１１キー
	else if(Buf[KEY_INPUT_F12]==1){return(KEY_INPUT_F12);}	// Ｆ１２キー
	else if(Buf[KEY_INPUT_A]==1){return(KEY_INPUT_A);}	// Ａキー
	else if(Buf[KEY_INPUT_B]==1){return(KEY_INPUT_B);}	// Ｂキー
	else if(Buf[KEY_INPUT_C]==1){return(KEY_INPUT_C);}	// Ｃキー
	else if(Buf[KEY_INPUT_D]==1){return(KEY_INPUT_D);}	// Ｄキー
	else if(Buf[KEY_INPUT_E]==1){return(KEY_INPUT_E);}	// Ｅキー
	else if(Buf[KEY_INPUT_F]==1){return(KEY_INPUT_F);}	// Ｆキー
	else if(Buf[KEY_INPUT_G]==1){return(KEY_INPUT_G);}	// Ｇキー
	else if(Buf[KEY_INPUT_H]==1){return(KEY_INPUT_H);}	// Ｈキー
	else if(Buf[KEY_INPUT_I]==1){return(KEY_INPUT_I);}	// Ｉキー
	else if(Buf[KEY_INPUT_J]==1){return(KEY_INPUT_J);}	// Ｊキー
	else if(Buf[KEY_INPUT_K]==1){return(KEY_INPUT_K);}	// Ｋキー
	else if(Buf[KEY_INPUT_L]==1){return(KEY_INPUT_L);}	// Ｌキー
	else if(Buf[KEY_INPUT_M]==1){return(KEY_INPUT_M);}	// Ｍキー
	else if(Buf[KEY_INPUT_N]==1){return(KEY_INPUT_N);}	// Ｎキー
	else if(Buf[KEY_INPUT_O]==1){return(KEY_INPUT_O);}	// Ｏキー
	else if(Buf[KEY_INPUT_P]==1){return(KEY_INPUT_P);}	// Ｐキー
	else if(Buf[KEY_INPUT_Q]==1){return(KEY_INPUT_Q);}	// Ｑキー
	else if(Buf[KEY_INPUT_R]==1){return(KEY_INPUT_R);}	// Ｒキー
	else if(Buf[KEY_INPUT_S]==1){return(KEY_INPUT_S);}	// Ｓキー
	else if(Buf[KEY_INPUT_T]==1){return(KEY_INPUT_T);}	// Ｔキー
	else if(Buf[KEY_INPUT_U]==1){return(KEY_INPUT_U);}	// Ｕキー
	else if(Buf[KEY_INPUT_V]==1){return(KEY_INPUT_V);}	// Ｖキー
	else if(Buf[KEY_INPUT_W]==1){return(KEY_INPUT_W);}	// Ｗキー
	else if(Buf[KEY_INPUT_X]==1){return(KEY_INPUT_X);}	// Ｘキー
	else if(Buf[KEY_INPUT_Y]==1){return(KEY_INPUT_Y);}	// Ｙキー
	else if(Buf[KEY_INPUT_Z]==1){return(KEY_INPUT_Z);}	// Ｚキー
	else if(Buf[KEY_INPUT_0]==1){return(KEY_INPUT_0);}	// ０キー
	else if(Buf[KEY_INPUT_1]==1){return(KEY_INPUT_1);}	// １キー
	else if(Buf[KEY_INPUT_2]==1){return(KEY_INPUT_2);}	// ２キー
	else if(Buf[KEY_INPUT_3]==1){return(KEY_INPUT_3);}	// ３キー
	else if(Buf[KEY_INPUT_4]==1){return(KEY_INPUT_4);}	// ４キー
	else if(Buf[KEY_INPUT_5]==1){return(KEY_INPUT_5);}	// ５キー
	else if(Buf[KEY_INPUT_6]==1){return(KEY_INPUT_6);}	// ６キー
	else if(Buf[KEY_INPUT_7]==1){return(KEY_INPUT_7);}	// ７キー
	else if(Buf[KEY_INPUT_8]==1){return(KEY_INPUT_8);}	// ８キー
	else if(Buf[KEY_INPUT_9]==1){return(KEY_INPUT_9);}	// ９キー
	else{return 0;}
	}

void cfunc::KeyInt2Chr(int num){
		switch(num){
			case KEY_INPUT_BACK:
				// バックスペースキー
				KeyName="BACK";
				return;
			case KEY_INPUT_TAB:
				// タブキー
				KeyName="TAB";
				return;
			case KEY_INPUT_RETURN:
				// エンターキー
				KeyName="RETURN";
				return;
			case KEY_INPUT_LSHIFT:
				// 左シフトキー
				KeyName="LSHIFT";
				return;
			case KEY_INPUT_RSHIFT:
				// 右シフトキー
				KeyName="RSHIFT";
				return;
			case KEY_INPUT_LCONTROL:
				// 左コントロールキー
				KeyName="LCONTROL";
				return;
			case KEY_INPUT_RCONTROL:
				// 右コントロールキー
				KeyName="RCONTROL";
				return;
			case KEY_INPUT_ESCAPE:
				// エスケープキー
				KeyName="ESCAPE";
				return;
			case KEY_INPUT_SPACE:
				// スペースキー
				KeyName="SPACE";
				return;
			case KEY_INPUT_PGUP:
				// ＰａｇｅＵＰキー
				KeyName="PGUP";
				return;
			case KEY_INPUT_PGDN:
				// ＰａｇｅＤｏｗｎキー
				KeyName="PGDN";
				return;
			case KEY_INPUT_END:
				// エンドキー
				KeyName="END";
				return;
			case KEY_INPUT_HOME:
				// ホームキー
				KeyName="HOME";
				return;
			case KEY_INPUT_LEFT:
				// 左キー
				KeyName="LEFT";
				return;
			case KEY_INPUT_UP:
				// 上キー
				KeyName="UP";
				return;
			case KEY_INPUT_RIGHT:
				// 右キー
				KeyName="RIGHT";
				return;
			case KEY_INPUT_DOWN:
				// 下キー
				KeyName="DOWN";
				return;
			case KEY_INPUT_INSERT:
				// インサートキー
				KeyName="INSERT";
				return;
			case KEY_INPUT_DELETE:
				// デリートキー
				KeyName="DELETE";
				return;
			case KEY_INPUT_MINUS:
				// -キー
				KeyName="MINUS";
				return;
			case KEY_INPUT_YEN:
				// ￥キー
				KeyName="YEN";
				return;
			case KEY_INPUT_PREVTRACK:
				// ＾キー
				KeyName="PREVTRACK";
				return;
			case KEY_INPUT_PERIOD:
				// ．キー
				KeyName="PERIOD";
				return;
			case KEY_INPUT_SLASH:
				// ／キー
				KeyName="SLASH";
				return;
			case KEY_INPUT_LALT:
				// 左ＡＬＴキー
				KeyName="LALT";
				return;
			case KEY_INPUT_RALT:
				// 右ＡＬＴキー
				KeyName="RALT";
				return;
			case KEY_INPUT_SCROLL:
				// ScrollLockキー
				KeyName="SCROLL";
				return;
			case KEY_INPUT_SEMICOLON:
				// ；キー
				KeyName="SEMICOLON";
				return;
			case KEY_INPUT_COLON:
				// ：キー
				KeyName="COLON";
				return;
			case KEY_INPUT_LBRACKET:
				// ［キー
				KeyName="LBRACKET";
				return;
			case KEY_INPUT_RBRACKET:
				// ］キー
				KeyName="RBRACKET";
				return;
			case KEY_INPUT_AT:
				// ＠キー
				KeyName="AT";
				return;
			case KEY_INPUT_BACKSLASH:
				// ＼キー
				KeyName="BACKSLASH";
				return;
			case KEY_INPUT_COMMA:
				// ，キー
				KeyName="COMMA";
				return;
			case KEY_INPUT_CAPSLOCK:
				// CaspLockキー
				KeyName="CAPSLOCK";
				return;
			case KEY_INPUT_SYSRQ:
				// PrintScreenキー
				KeyName="SYSRQ";
				return;
			case KEY_INPUT_PAUSE:
				// PauseBreakキー
				KeyName="PAUSE";
				return;
			case KEY_INPUT_NUMPAD0:
				// テンキー０
				KeyName="NUMPAD0";
				return;
			case KEY_INPUT_NUMPAD1:
				// テンキー１
				KeyName="NUMPAD1";
				return;
			case KEY_INPUT_NUMPAD2:
				// テンキー２
				KeyName="NUMPAD2";
				return;
			case KEY_INPUT_NUMPAD3:
				// テンキー３
				KeyName="NUMPAD3";
				return;
			case KEY_INPUT_NUMPAD4:
				// テンキー４
				KeyName="NUMPAD4";
				return;
			case KEY_INPUT_NUMPAD5:
				// テンキー５
				KeyName="NUMPAD5";
				return;
			case KEY_INPUT_NUMPAD6:
				// テンキー６
				KeyName="NUMPAD6";
				return;
			case KEY_INPUT_NUMPAD7:
				// テンキー７
				KeyName="NUMPAD7";
				return;
			case KEY_INPUT_NUMPAD8:
				// テンキー８
				KeyName="NUMPAD8";
				return;
			case KEY_INPUT_NUMPAD9:
				// テンキー９
				KeyName="NUMPAD9";
				return;
			case KEY_INPUT_MULTIPLY:
				// テンキー＊キー
				KeyName="MULTIPLY";
				return;
			case KEY_INPUT_ADD:
				// テンキー＋キー
				KeyName="ADD";
				return;
			case KEY_INPUT_SUBTRACT:
				// テンキー-キー
				KeyName="SUBTRACT";
				return;
			case KEY_INPUT_DECIMAL:
				// テンキー．キー
				KeyName="DECIMAL";
				return;
			case KEY_INPUT_DIVIDE:
				// テンキー／キー
				KeyName="DIVIDE";
				return;
			case KEY_INPUT_NUMPADENTER:
				// テンキーのエンターキー
				KeyName="NUMPADENTER";
				return;
			case KEY_INPUT_F1:
				// Ｆ１キー
				KeyName="F1";
				return;
			case KEY_INPUT_F2:
				// Ｆ２キー
				KeyName="F2";
				return;
			case KEY_INPUT_F3:
				// Ｆ３キー
				KeyName="F3";
				return;
			case KEY_INPUT_F4:
				// Ｆ４キー
				KeyName="F4";
				return;
			case KEY_INPUT_F5:
				// Ｆ５キー
				KeyName="F5";
				return;
			case KEY_INPUT_F6:
				// Ｆ６キー
				KeyName="F6";
				return;
			case KEY_INPUT_F7:
				// Ｆ７キー
				KeyName="F7";
				return;
			case KEY_INPUT_F8:
				// Ｆ８キー
				KeyName="F8";
				return;
			case KEY_INPUT_F9:
				// Ｆ９キー
				KeyName="F9";
				return;
			case KEY_INPUT_F10:
				// Ｆ１０キー
				KeyName="F10";
				return;
			case KEY_INPUT_F11:
				// Ｆ１１キー
				KeyName="F11";
				return;
			case KEY_INPUT_F12:
				// Ｆ１２キー
				KeyName="F12";
				return;
			case KEY_INPUT_A:
				// Ａキー
				KeyName="A";
				return;
			case KEY_INPUT_B:
				// Ｂキー
				KeyName="B";
				return;
			case KEY_INPUT_C:
				// Ｃキー
				KeyName="C";
				return;
			case KEY_INPUT_D:
				// Ｄキー
				KeyName="D";
				return;
			case KEY_INPUT_E:
				// Ｅキー
				KeyName="E";
				return;
			case KEY_INPUT_F:
				// Ｆキー
				KeyName="F";
				return;
			case KEY_INPUT_G:
				// Ｇキー
				KeyName="G";
				return;
			case KEY_INPUT_H:
				// Ｈキー
				KeyName="H";
				return;
			case KEY_INPUT_I:
				// Ｉキー
				KeyName="I";
				return;
			case KEY_INPUT_J:
				// Ｊキー
				KeyName="J";
				return;
			case KEY_INPUT_K:
				// Ｋキー
				KeyName="K";
				return;
			case KEY_INPUT_L:
				// Ｌキー
				KeyName="L";
				return;
			case KEY_INPUT_M:
				// Ｍキー
				KeyName="M";
				return;
			case KEY_INPUT_N:
				// Ｎキー
				KeyName="N";
				return;
			case KEY_INPUT_O:
				// Ｏキー
				KeyName="O";
				return;
			case KEY_INPUT_P:
				// Ｐキー
				KeyName="P";
				return;
			case KEY_INPUT_Q:
				// Ｑキー
				KeyName="Q";
				return;
			case KEY_INPUT_R:
				// Ｒキー
				KeyName="R";
				return;
			case KEY_INPUT_S:
				// Ｓキー
				KeyName="S";
				return;
			case KEY_INPUT_T:
				// Ｔキー
				KeyName="T";
				return;
			case KEY_INPUT_U:
				// Ｕキー
				KeyName="U";
				return;
			case KEY_INPUT_V:
				// Ｖキー
				KeyName="V";
				return;
			case KEY_INPUT_W:
				// Ｗキー
				KeyName="W";
				return;
			case KEY_INPUT_X:
				// Ｘキー
				KeyName="X";
				return;
			case KEY_INPUT_Y:
				// Ｙキー
				KeyName="Y";
				return;
			case KEY_INPUT_Z:
				// Ｚキー
				KeyName="Z";
				return;
			case KEY_INPUT_0:
				// ０キー
				KeyName="0";
				return;
			case KEY_INPUT_1:
				// １キー
				KeyName="1";
				return;
			case KEY_INPUT_2:
				// ２キー
				KeyName="2";
				return;
			case KEY_INPUT_3:
				// ３キー
				KeyName="3";
				return;
			case KEY_INPUT_4:
				// ４キー
				KeyName="4";
				return;
			case KEY_INPUT_5:
				// ５キー
				KeyName="5";
				return;
			case KEY_INPUT_6:
				// ６キー
				KeyName="6";
				return;
			case KEY_INPUT_7:
				// ７キー
				KeyName="7";
				return;
			case KEY_INPUT_8:
				// ８キー
				KeyName="8";
				return;
			case KEY_INPUT_9:
				// ９キー
				KeyName="9";
				return;
			}
			KeyName="UNKNOWN";
			return;
}

string_t cfunc::ReplaceKeyNameAll(string_t str){
	//キーボード
	ReplaceKeyName(str,"%KEY_SHOT%",PjSys::key::shot,false); //ショット
	ReplaceKeyName(str,"%KEY_SUB%",PjSys::key::sub,false); //ディフェンダ
	ReplaceKeyName(str,"%KEY_BOMB%",PjSys::key::bomb,false); //ボム
	//パッド
	ReplaceKeyName(str,"%PAD_SHOT%",PjSys::key::shot_p,true); //ショット
	ReplaceKeyName(str,"%PAD_SUB%",PjSys::key::sub_p,true); //ディフェンダ
	ReplaceKeyName(str,"%PAD_BOMB%",PjSys::key::bomb_p,true); //ボム

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