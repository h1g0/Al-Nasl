#ifndef __BGMTITLE
#define __BGMTITLE

#define BGM_PRE _T("�� ") //���{������̃v���t�B�N�X

#define BGM_PRE_E _T("BGM: \"") //�p������̃v���t�B�N�X
#define BGM_POST_E _T("\"") //�p������̃T�t�B�b�N�X
/*===========================
BGM�Ȗ����X�g(���{��)
============================*/
#define BGM_DEPARTURE _T(BGM_PRE##"") //�o��

#define BGM_STG1 _T(BGM_PRE##"") //1��
#define BGM_STG2 _T(BGM_PRE##"") //2��

#define BGM_BOSS1 _T(BGM_PRE##"") //�{�X1
/*============================
�p��
============================*/
#define BGM_DEPARTURE_E _T(BGM_PRE_E##""##BGM_POST_E) //�o��

//============================
#define SHOW_BGM_TITLE_FRM 60*5 //BGM�^�C�g����\������b��(w/o�t�F�[�h�C���A�E�g)
#define SHOW_BGM_TITLE_X 520 //BGM�^�C�g����\������X���W(�E�[�)
#define SHOW_BGM_TITLE_Y 460 //BGM�^�C�g����\������Y���W(���[�)
#define SHOW_BGM_TITLE_SIZE 12 //�t�H���g�T�C�Y

/*===========================
�X�e�[�W�^�C�g�����X�g(�p��)
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
���{��
============================*/
#define TITLE_PROROGUE_J _T("�����ւ̈ӎv")

#define TITLE_STG1_J _T("�r��ʂĂ���n�𒴂���")
#define TITLE_STG2_J _T("�w�M�҂̒���")
#define TITLE_STG3_J _T("���������ȁA���̑c��")
#define TITLE_STG4_J _T("���z�Ȃ�t�ł�w�G")
#define TITLE_STG5_J _T("G")
#define TITLE_STGF_J _T("K")

#define TITLE_END2_J _T("M")

//============================

#endif