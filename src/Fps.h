//FPS制御
#ifndef FPS_H
#define FPS_H

/*DxLibを使わず、他のライブラリを使用する場合は
#define FPS_USE_DXLIB
をコメントアウトし、
以下の関数を定義して下さい
inline int GetNowCount(); //ミリ秒単位の精度を持つカウンタの現在値を得る
inline int	WaitTimer( int WaitTime ) ; //指定の時間だけ処理をとめる
*/
#define FPS_USE_DXLIB

#ifdef FPS_USE_DXLIB
	#include "DxLib.h"
#else
	#include "hoge.h"
	inline int GetNowCount(); //ミリ秒単位の精度を持つカウンタの現在値を得る
	inline int	WaitTimer( int WaitTime ) ; //指定の時間だけ処理をとめる
#endif

/*
使い方:
メインループ開始前に宣言する(まぁ当たり前だね)
↓
FPSを描画するタイミングでGetFPS()を呼ぶ(メインループのなるべく最後の方が好ましい)
↓
FixFPS()で強制的に固定する
*/

//FPS設定
class FPS{
	bool IsFixFPS; //FPSを固定するか？
	bool ShowFPS; //FPSを表示するか？
	int DefaultFPS; //デフォルトのFPS
public:
	/*コンストラクタ
	引数: IsFixFps: FPSを固定するか？ IsShowFps: FPSを表示するか？ FixedFPS: FPSを幾つに固定するか？
	*/
	FPS(bool IsFixFps = true, bool IsShowFps = true, int FixedFPS = 60);
	//デストラクタ
	~FPS();

	//FPSを強制的に固定する
	void Fix();
	//FPSを返す(返り値: FPS)
	int Get();
	//デフォルトのFPSを返す
	int GetDefaultFPS(){
		return DefaultFPS;
	}
};

#endif