#pragma once
#include "Common.h"

/******************************************************************
　　　　　　　　　　　　　　メイン
******************************************************************/
StageManager stage;
Player gPlayer;
Enemy e1;

SettingIni Setting;
//RankAll gRank;
FPS gFPS;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
	int ExitCnt=0;

	SetAlwaysRunFlag(TRUE);
	SetMainWindowText( PJTITLE ) ;
	SetUseDXArchiveFlag(true) ;
	SetDXArchiveExtension("aln") ;
	SetDXArchiveKeyString( "pjflora");

	if(Setting.General.ColorBit!=32 && Setting.General.ColorBit!=16){
		Setting.General.ColorBit=32;
	}
	SetGraphMode( 640, 480 , Setting.General.ColorBit );
	int f;

	if(Setting.General.VSync==0){
		f=FALSE;
	}else{
		Setting.General.VSync=1;
		f=TRUE;
	}
	SetWaitVSyncFlag(f) ;//垂直同期するか？

	if(Setting.Debug.OutputLog==1){
		f=TRUE;
	}else{
		Setting.Debug.OutputLog=0;
		f=FALSE;
	}
	SetOutApplicationLogValidFlag(f);

	if(Setting.General.Window==1){
		f=TRUE;
	}else{
		Setting.General.Window=0;
		f=FALSE;
	}
	ChangeWindowMode( f ); //ウィンドウモード
	SetWindowSizeExtendRate(Setting.General.WindowExtendRate);

	if(Setting.General.SoftwareSound==1){
		f=TRUE;
	}else{
		Setting.General.SoftwareSound=0;
		f=FALSE;
	}

	SetUseSoftwareMixingSoundFlag(Setting.General.SoftwareSound); //サウンド処理をソフトウェアでやるか？

	//アンチエイリアス。重い割にメリットもないのであんまり使いたくない…
	switch(Setting.General.AntiAliasing){
		case 0:
			break;
		case 1:
			SetFullSceneAntiAliasingMode( 4 , 8 ) ;
			break;
		case 2:
			SetFullSceneAntiAliasingMode( 8 , 8 ) ;
			break;
		case 3:
			SetFullSceneAntiAliasingMode( 8 , 12 ) ;
			break;
		default:
			break;
	}

	if( DxLib_Init() == -1 ){		// ＤＸライブラリ初期化処理
		return -1 ;			// エラーが起きたら直ちに終了
	}
	stage.setstage(0x0a);
	ErrorLogAdd("***********************\n");
	ErrorLogAdd(PJTITLE);
	ErrorLogAdd(" has started...\n");
	ErrorLogAdd("***********************\n");
	//***********************************************************
	//メインループ
	while(ProcessMessage() == 0){
		if(((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::exit_p) != 0 && PjSys::CanExit==true)){
			break;
			/*//長押ししないと終了しない
			ExitCnt++;
			if(ExitCnt>60){
				break;
			}
		}else{
			if(ExitCnt!=0){
				InitGraph() ;
				InitSoundMem();
				stage.setstage(0);
			}
			ExitCnt=0;
			//*/
		}
		if(PjSys::Exit){break;}
		SetDrawScreen( DX_SCREEN_BACK ) ; // 描画先画面を裏にする
		ClsDrawScreen() ; //画面の初期化
		//if(PjSys::Invert){SetDrawBlendMode(DX_BLENDMODE_INVSRC, 256 ) ;}
		stage.move();//ステージの描画

		//FPS描画
		PjSys::DrawFPS(550,464,gFPS.Get(),gFPS.GetDefaultFPS());
		if(PjSys::Scr::AvaliableShake){PjSys::Scr::Shake();}
		//PjSys::Scr::Arcade_Like();
		PjSys::ScreenShot();
		ScreenFlip(); //フリップ

		//FPS補正
		gFPS.Fix();
	}
	InitGraph();
	InitSoundMem();
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了
}