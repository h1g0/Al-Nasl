#ifndef __BGMTITLE
#define __BGMTITLE

#define BGM_PRE _T("♪ ") //日本語環境下のプレフィクス

#define BGM_PRE_E _T("BGM: \"") //英語環境下のプレフィクス
#define BGM_POST_E _T("\"") //英語環境下のサフィックス
/*===========================
BGM曲名リスト(日本語)
============================*/
#define BGM_DEPARTURE _T(BGM_PRE##"") //出撃

#define BGM_STG1 _T(BGM_PRE##"") //1面
#define BGM_STG2 _T(BGM_PRE##"") //2面

#define BGM_BOSS1 _T(BGM_PRE##"") //ボス1
/*============================
英語
============================*/
#define BGM_DEPARTURE_E _T(BGM_PRE_E##""##BGM_POST_E) //出撃

//============================
#define SHOW_BGM_TITLE_FRM 60*5 //BGMタイトルを表示する秒数(w/oフェードインアウト)
#define SHOW_BGM_TITLE_X 520 //BGMタイトルを表示するX座標(右端基準)
#define SHOW_BGM_TITLE_Y 460 //BGMタイトルを表示するY座標(下端基準)
#define SHOW_BGM_TITLE_SIZE 12 //フォントサイズ

/*===========================
ステージタイトルリスト(英語)
============================*/
#define TITLE_PROROGUE _T("Will to the future")

#define TITLE_STG1 _T("Over the devastated earth")
#define TITLE_STG2 _T("Betrayer's faith")
#define TITLE_STG3 _T("Alas for her homeland")
#define TITLE_STG4 _T("Foes performing a fantasia")
#define TITLE_STG5 _T("G")
#define TITLE_STGF _T("K")

#define TITLE_END2 _T("M")
/*============================
日本語
============================*/
#define TITLE_PROROGUE_J _T("未来への意思")

#define TITLE_STG1_J _T("荒れ果てた大地を超えて")
#define TITLE_STG2_J _T("背信者の忠誠")
#define TITLE_STG3_J _T("哀しきかな、かの祖国")
#define TITLE_STG4_J _T("幻想曲を奏でる仇敵")
#define TITLE_STG5_J _T("G")
#define TITLE_STGF_J _T("K")

#define TITLE_END2_J _T("M")

//============================

#endif