#include "CommandInput.h"

bool CommandInput::Check(){
	//各ビットに各ボタンの入力状態が格納される
	InputData=GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	if(InputData == OldInputData ){ //前回と状態が変わってない
		return false; //コマンド入力失敗として終了
	}

	bool status = false;
	if(InputData != 0){ //何か押されている
		//現在のフェーズがコマンドの要素数以下かつコマンド入力が一致
		if(Cmd.size() > Phase && (InputData & Cmd[Phase]) !=0){
			Phase++; //フェーズを進める
			if(Cmd.size() == Phase){ //コマンド入力完了！
				status = true;
				Phase = 0;
			}
		}else{ //コマンドを間違えていたら、フェーズを初期化
			Phase=0;
		}
	}
	OldInputData = InputData;
	return status;
}