#pragma once
#include "Common.h"
/*#############################################################

					ステージ進行管理クラス

##############################################################*/
//ヘルプとか表示する小窓
class SmallWindow{
	int width;
	int height;
	int flg;
	int dialog; //ダイアログの選択肢の種類
	int dialog_selected; //どの選択肢が選ばれているか？
	int status; //状態
	int SndOpen; //開くときの音
	int SndClose;//閉じるときの音
	int ImgSelected;
	vector<string_t> DialogSelect; //ダイアログの選択肢文章

	static const int FadeFrm = 20; //フェードインアウトに要するフレーム
	static const int ShowingFrm = FadeFrm+1; //表示中のフレーム
	static const int FontSize = 14; //フォントサイズ
	vector<string_t> Str; //表示する文字列
	void AnalyzeStr(string_t& String); //文字列を改行で分割する
	void SwitchDialog(int DialogType); //ダイアログの選択肢ぶんの配列を確保
public:
	static const int DialogOK = 0; //<OK>
	static const int DialogYesNo = 1; //<YES> <NO>

	//コンストラクタ
	SmallWindow(int Width=320,int Height=240, string_t String="",int DialogType = 0){
		width=Width;
		height=Height;
		flg=0;
		AnalyzeStr(String);
		dialog=DialogType;
		dialog_selected=0;
		SwitchDialog(dialog); //文字列ぶんのベクタを確保
	}
	void SetWH(int Width,int Height){
		width=Width;
		height=Height;
	}
	//文字列を設定
	void SetString(string_t String, int DialogType = DialogOK){
		AnalyzeStr(String);
		dialog=DialogType;
		dialog_selected=0;
		SwitchDialog(dialog); //文字列ぶんのベクタを確保
	}
	void SetDialogString(string_t String,int Idx =0){
		if((int)DialogSelect.size()<Idx+1){return;}
		DialogSelect[Idx]=String;
	}
	//サウンドファイルを読み込む
	void SetSound(string_t OpenSndFile, string_t CloseSndFile){
		SndOpen = LoadSoundMem( OpenSndFile.c_str() );
		ChangeVolumeSoundMem( Setting.General.SEVolume , SndOpen );
		SndClose = LoadSoundMem( CloseSndFile.c_str() );
		ChangeVolumeSoundMem( Setting.General.SEVolume , SndClose );
	}
	void SetImg(const int& Selected){
		ImgSelected = Selected;
	}
		//表示フラグを立てる
	void SetFlag(){
		flg=1;
	}
	int GetStatus(){
		return status;
	}
	/*描画。
	戻り値:
	-2: 描画対象が存在しない
	-1: 描画中、もしくは待機中
	0: OK、YES等が押された
	1: NO等が押された

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
	int ImgLoadStr; //「Loading...」の画像
	int warn();
	int result();
	int ShowStageTitle(int phase); //ステージタイトルを表示
	void stgmove(); //メインのステージ管理
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

//最初の表示
	int StgNotice();
//メニュー
	int stg00(); //メインメニューロード
	int stg01();
	int stg08(); //フレームワークロード
//レベルメニュー
	int stg80(); //メニューロード
	int stg81(); //レベルメニュー

	int stg90(); //設定メニューロード
	int stg91(); //設定メニュー

	int stg92(); //キーコンフィグ1ロード
	int stg93(); //キーコンフィグ1

	int stg94(); //キーコンフィグ2ロード
	int stg95(); //キーコンフィグ2

	int stg96(); //設定1ロード
	int stg97(); //設定1

	int stg98(); //設定2ロード
	int stg99(); //設定2

	void KeyConfig1(); //キーコンフィグ1の実体
	void KeyConfig2(); //キーコンフィグ2の実体

	int stgA0(); //ランキングロード
	int stgA1(); //ランキング

//ステージ1
	int stg10(); //Stg1ロード
	int stg11(); //Stg1本番
	int stg12(); //Stg1Warning
	int stg13(); //Stg1ボス
	int stg14(); //リザルト
	int stg18(); //出撃シーン

//ステージ2
	int stg20(); //Stg2ロード
	int stg21(); //Stg2本番
	int stg22(); //Stg2Warning
	int stg23(); //Stg2ボス
//ステージ3
	int stg30(); //Stg3ロード
	int stg31(); //Stg3本番
	int stg32(); //Stg3Warning
	int stg33(); //Stg3ボス

public:
	int stage, GOimg,PauseImg,LoadImg,ResultImg,ResultSound;
	int Enum[10];//ボスの敵番号管理

	//int WSmoke[4],GSmoke[4];
	int GrPlane[3];

	int SmallEnmImg[8];
	int BigEnmImg[8];
	int BossImg[8];
	int SmallExplode[16]; //爆発エフェクト(小)
	int InvImg,BornEff;//エフェクト
	StageManager(){}
	void setstage(int stg){stage=stg;phase=-1;}
	void move(); //統合管理
};