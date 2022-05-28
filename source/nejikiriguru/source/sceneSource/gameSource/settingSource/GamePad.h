#pragma once
#include "DxLib.h"
#include "CheckHitKey.h"

/*
�Q�[���p�b�h�N���X
�Q�[���p�b�h�̋@�\���g�p�ł���
*/

#define THUMB_MAX 32767										//	�X�e�B�b�N�̍ő�l
#define THUMB_MIN -32768									//	�X�e�B�b�N�̍ŏ��l
#define TRIGGER_MAX 255										//	�g���K�[�̍ő�l

/*
�Q�[���p�b�h�̊Ǘ��N���X
	�Q�[���p�b�h�̏��Ǘ�
	XInput�̃Q�[���p�b�h�̂ݎg����
*/
class GamePad
{
private:
	XINPUT_STATE OldGamePadData = { 0 };					//	�Q�[���p�b�h�̉ߋ��̓��̓f�[�^
	int GamePadNo = 0;										//	�v���C���[�̑���ł���Q�[���p�b�h

public:
	XINPUT_STATE GamePadData;								//	�Q�[���p�b�h�̓��̓f�[�^

	float Joystick[2][2] = { 0.0f };						//	�W���C�X�e�B�b�N�̒l-1�`1�܂� 0:�E 1:��0:X 1:Y 
	float Trigger[2] = { 0 };								//	�g���K�[�̒l0�`255�܂� 0:�E 1:��
	bool GamePadReady = false;								//	�Q�[���p�b�h���L����

	GamePad();												//	�����ݒ�

	//	�Q�[���p�b�h�̏���
	void Initia(int InputType);								//	��������
	void Update();											//	�X�V����
	void OldUpdate();										//	�ߋ��̍X�V����
	bool Button(int XinSet);								//	�w��{�^�����L�����m�F
	bool OneButton(int XinSet);								//	�w��{�^������񉟂��ꂽ���m�F
	void Vibrat(int Power, int Time, int RorL);				//	�U������:Power:300�`1000	RorL 1:�E 0:��
};