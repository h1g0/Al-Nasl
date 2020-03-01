#include "CommandInput.h"

bool CommandInput::Check(){
	//�e�r�b�g�Ɋe�{�^���̓��͏�Ԃ��i�[�����
	InputData=GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	if(InputData == OldInputData ){ //�O��Ə�Ԃ��ς���ĂȂ�
		return false; //�R�}���h���͎��s�Ƃ��ďI��
	}

	bool status = false;
	if(InputData != 0){ //����������Ă���
		//���݂̃t�F�[�Y���R�}���h�̗v�f���ȉ����R�}���h���͂���v
		if(Cmd.size() > Phase && (InputData & Cmd[Phase]) !=0){
			Phase++; //�t�F�[�Y��i�߂�
			if(Cmd.size() == Phase){ //�R�}���h���͊����I
				status = true;
				Phase = 0;
			}
		}else{ //�R�}���h���ԈႦ�Ă�����A�t�F�[�Y��������
			Phase=0;
		}
	}
	OldInputData = InputData;
	return status;
}