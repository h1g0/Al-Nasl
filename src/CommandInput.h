#pragma once
#include "Common.h"
/*
#include <vector>
#include "DxLib.h"
using namespace std;
//*/
/*########################################################################

						コマンド入力クラス

########################################################################*/

/*=======================================================================
使い方:

あらかじめ下みたいな感じで宣言しといてやる
↓
コマンド入力されてるかチェックしたいときにCheck()を呼ぶ。
↓
Check()でtrueが帰ってくればコマンド入力成功

サンプルコード
--------------------------------------------------------------------------
//コマンドの宣言(例として「↑↑↓↓←→←→BA」のコ○ミコマンド)
int KC[] = {PAD_INPUT_UP, PAD_INPUT_UP, PAD_INPUT_DOWN, PAD_INPUT_DOWN,
			PAD_INPUT_LEFT, PAD_INPUT_RIGHT, PAD_INPUT_LEFT, PAD_INPUT_RIGHT,
			PAD_INPUT_2, PAD_INPUT_1};

//配列の要素数
const int KCNum = sizeof KC / sizeof KC[0];

//クラスの宣言
CommandInput KonantokaCommand(KC,KCNum);
----------------------------------------------------------------------------
==============================================================================*/

class CommandInput{
	vector<int> Cmd; //コマンド
	unsigned int Phase;
	int InputData;
	int OldInputData; // ひとつ前のキー入力データ
public:
	//コンストラクタ
	CommandInput(const vector<int>& Command){
		Cmd=Command;
		InputData=0;
		OldInputData=0;
		Phase=0;
	}
	//コマンドが入った配列のポインタ
	CommandInput(int* Command, int ElementNum){
		Cmd.assign(&Command[0], &Command[ElementNum]);
		InputData=0;
		OldInputData=0;
		Phase=0;
	}

	bool Check(); //コマンドチェック
};