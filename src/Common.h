#pragma once
#pragma warning(disable:4996) //Secure Warningを無視する

#include "DxLib.h"
//DxLibのマニュアル: http://homepage2.nifty.com/natupaji/DxLib/dxfunc.html

#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <tchar.h>
#include <boost/foreach.hpp>
#include <boost/swap.hpp>
#include <boost/lexical_cast.hpp>
#ifdef _UNICODE
	typedef std::wstring string_t;
#else
	typedef std::string string_t;
#endif
typedef long int int_score; //スコア

#define ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING 42 //生命、宇宙、そして万物についての究極の疑問の答え=42
#define foreach BOOST_FOREACH

#define PJVERSION _T("ver. 0.7.0.0 alpha")
#define PJTITLE _T("Al-Nasl "##PJVERSION##" (DxLib: "##DXLIB_VERSION_STR##")") //タイトル
#define DEBUG_COMMAND //デバッグコマンド

#define MBCAP 500 //自弾上限
#define EBCAP 10000 //敵弾の上限
#define INVFRAME 60*2 //無敵秒数
#define BMBFRAME 60*1 //ボム秒数
#define SUBFRAMECNT 60 //サブウェポン秒数(incl.無敵時間)
#define SUBINVFRAME 60*1 //サブウェポン無敵時間
#define SUBFRAMEMIN 30 //サブウェポン２
#define BUZZSUBRATE 4 //バズった時のサブウェポンゲージ加算倍率
#define BUZZSCORE 2 //1フレーム辺りのバズ加算スコア
#define BUZZMAX 5 //同時にバズる最高弾数
#define BUZZ_FRAME_MAX 30 //バズレベルが残留するframe数
#define BUZZ_REGION_DEFAULT 32 //デフォのバズり半径
#define BMB_DMG_PER_FRAME 0 //1フレーム当りのボムダメージ
#define SHOW_CHIP_TIME 64 //チップを表示する時間
#define COUNT_STOP_SCORE 999999999 //カンスト：9億9999万9999点
//#define SUB_MAX 256 //サブウェポンのマックスポイント

#define LASER_MAX 32 //レーザーの最大数
#define LASER_TRACE_MAX 16 //レーザー軌跡の最大数
//#define LASER_POWER 256 //レーザーの威力
#define LASER_SCORE 10 //レーザー素点

#define EXPLODE_MAX 16 //爆発の最大数

#define MAXLEFT 30 //残機の最大数
#define MAXBOMB 7 //ボムの最大数
#define SUB_LEVEL 5 //サブウェポンのレベル
#define IRODORI_RATE 1.1 //彩モードの倍速
#define ACCELERATOR_RATE 1.01 //加速モードの倍速
#define ENEMY_INV -127 //敵が無敵になる特殊定数
#define MY_MODEL_EXP 1.3f //デフォルトの自機モデル拡大率

using namespace std; //スタンダードライブラリ名前空間を使用

#include "SettingIni.h" //INI
extern SettingIni Setting;

#include "Fps.h" //FPS関係
#include "Chore.h" //雑用関数群
#include "BgmTitle.h" //BGMのタイトル
#include "CommandInput.h" //コマンド入力関係
#include "MathFunc.h" //数学関係
#include "Global.h" //グローバル変数
#include "BackGround.h" //背景関係
#include "Player.h" //自機・自弾関係
#include "EnemyBullet.h" //敵弾関係
#include "Enemy.h" //敵関係
#include "StageManager.h" //ステージ進行
//#include "Ranking.h" //ランキング
//extern RankAll gRank;
extern StageManager stage;
extern Player gPlayer;
extern Enemy e1;