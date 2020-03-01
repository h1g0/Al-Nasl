//FPS����
#ifndef FPS_H
#define FPS_H

/*DxLib���g�킸�A���̃��C�u�������g�p����ꍇ��
#define FPS_USE_DXLIB
���R�����g�A�E�g���A
�ȉ��̊֐����`���ĉ�����
inline int GetNowCount(); //�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
inline int	WaitTimer( int WaitTime ) ; //�w��̎��Ԃ����������Ƃ߂�
*/
#define FPS_USE_DXLIB

#ifdef FPS_USE_DXLIB
	#include "DxLib.h"
#else
	#include "hoge.h"
	inline int GetNowCount(); //�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
	inline int	WaitTimer( int WaitTime ) ; //�w��̎��Ԃ����������Ƃ߂�
#endif

/*
�g����:
���C�����[�v�J�n�O�ɐ錾����(�܂�������O����)
��
FPS��`�悷��^�C�~���O��GetFPS()���Ă�(���C�����[�v�̂Ȃ�ׂ��Ō�̕����D�܂���)
��
FixFPS()�ŋ����I�ɌŒ肷��
*/

//FPS�ݒ�
class FPS{
	bool IsFixFPS; //FPS���Œ肷�邩�H
	bool ShowFPS; //FPS��\�����邩�H
	int DefaultFPS; //�f�t�H���g��FPS
public:
	/*�R���X�g���N�^
	����: IsFixFps: FPS���Œ肷�邩�H IsShowFps: FPS��\�����邩�H FixedFPS: FPS����ɌŒ肷�邩�H
	*/
	FPS(bool IsFixFps = true, bool IsShowFps = true, int FixedFPS = 60);
	//�f�X�g���N�^
	~FPS();

	//FPS�������I�ɌŒ肷��
	void Fix();
	//FPS��Ԃ�(�Ԃ�l: FPS)
	int Get();
	//�f�t�H���g��FPS��Ԃ�
	int GetDefaultFPS(){
		return DefaultFPS;
	}
};

#endif