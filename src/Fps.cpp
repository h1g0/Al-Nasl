//FPS制御
#pragma once
#include "Fps.h"

//=================================================================================================
//コンストラクタ
//=================================================================================================
FPS::FPS(bool IsFixFps, bool IsShowFps, int FixedFPS){
	IsFixFPS = IsFixFps;
	ShowFPS = IsShowFps;
	DefaultFPS = FixedFPS;
}

//=================================================================================================
//デストラクタ
//=================================================================================================
FPS::~FPS(){}

//=================================================================================================
//FPSを強制的に固定する
//=================================================================================================
void FPS::Fix(){
	//フラグが立っていなければ抜ける
	if(IsFixFPS == false){return;}

	int nowtime = GetNowCount(); //今回の時間
	static int oldtime = 0; //前回の時間
	static int frametime = 1000 / DefaultFPS;	//１フレームの時間

	//１フレームの時間と現在の経過時間を比較
	int diftime = nowtime - oldtime;	//差分

	for(;;){
		if(diftime >= frametime){ //時間が過ぎているか？
			oldtime = nowtime;	//次の計測のため今回の時間を保存
			return;
		}else{ //時間が余ったら待機
			WaitTimer(1);
			nowtime = GetNowCount();
			diftime = nowtime - oldtime;
		}
	}
}

/*===============================================================
FPSを取得する
=================================================================*/
int FPS::Get(){
	//FPSを表示しない？
	if(ShowFPS == false){return -1;}

	static int oldtime = GetNowCount(); //前回の時間を保存
	static int fpscount = 0;  //FPSをカウント
	static int fps = 0; //表示用
	int nowtime = GetNowCount(); //今回の時間

	fpscount++;

	//1000ms過ぎたか？
	if((nowtime - oldtime) >= 1000){
		int dif = ((nowtime - oldtime) - 1000);
		//今回の時間を保存
		oldtime = nowtime - dif;	//経過しすぎた分を引く
		//FPSを保存
		fps = fpscount;
		//カウンタを初期化
		fpscount = 0;
	}
	return fps;
}