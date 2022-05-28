#include "GamePad.h"

/*
�Q�[���p�b�h�N���X
�Q�[���p�b�h�̋@�\���g�p�ł���
*/

//	�����ݒ�
GamePad::GamePad()
{

}

//	��������
void GamePad::Initia(int InputType)
{
	//	�Q�[���p�b�h������ꍇ
	if (GetJoypadNum() != 0)
	{
		GamePadReady = true;								//	�Q�[���p�b�h�L��
		GamePadNo = InputType;								//	�Q�[���p�b�h�̔ԍ���ݒ�
		SetJoypadDeadZone(GamePadNo, 0.25);					//	�Q�[���p�b�h�̔������Ȃ�������ݒ�
	}
}

//	�X�V����
void GamePad::Update()
{
	GamePadReady = (GetJoypadNum() != 0);					//	�Q�[���p�b�h���L�����ǂ������ב������

	//	�Q�[���p�b�h�������̎��������Ȃ�
	if (!GamePadReady)return;


	GetJoypadXInputState(GamePadNo, &GamePadData);			//	�Q�[���p�b�h�f�[�^�̍X�V

	//	�W���C�X�e�B�b�N�̒l����	-1.0�`1.0
	Joystick[0][0] = ((float)GamePadData.ThumbRX / (float)THUMB_MAX);	//	�E�X�e�B�b�N��X��
	Joystick[0][1] = -((float)GamePadData.ThumbRY / (float)THUMB_MAX);	//	�E�X�e�B�b�N��Y��
	Joystick[1][0] = ((float)GamePadData.ThumbLX / (float)THUMB_MAX);	//	���X�e�B�b�N��X��
	Joystick[1][1] = -((float)GamePadData.ThumbLY / (float)THUMB_MAX);	//	���X�e�B�b�N��Y��

	//	�g���K�[�̒l����	0.0�`1.0
	Trigger[0] = ((float)GamePadData.RightTrigger / (float)TRIGGER_MAX);//	�E�g���K�[
	Trigger[1] = ((float)GamePadData.LeftTrigger / (float)TRIGGER_MAX);	//	���g���K�[
}

//	�ߋ��̍X�V����
void GamePad::OldUpdate()
{
	//	�Q�[���p�b�h�������̎��������Ȃ�
	if (!GamePadReady)return;

	OldGamePadData = GamePadData;							//	�f�[�^���X�V����
}

//	�w��{�^�����L�����m�F
bool GamePad::Button(int XinSet)
{
	//	�Q�[���p�b�h�������̎��������Ȃ�
	if (!GamePadReady)return false;

	return GamePadData.Buttons[XinSet];						//	�w��̃{�^����������Ă����true
}

//	�w��{�^������񉟂��ꂽ���m�F
bool GamePad::OneButton(int XinSet)
{
	//	�Q�[���p�b�h�������̎��������Ȃ�
	if (!GamePadReady)return false;

	//	�ߋ��̃{�^�����L���̎��͔�����
	if (OldGamePadData.Buttons[XinSet])return false;

	//	�ߋ��������Ō��݂��L���̎���true
	return GamePadData.Buttons[XinSet];
}

//	�U������:Power:300�`1000	RorL 1:�E 0:��
void GamePad::Vibrat(int Power, int Time, int RorL)
{
	//	�Q�[���p�b�h�������̎��������Ȃ�
	if (!GamePadReady)return;

	int SetPower = 0;										//	�U����

	//	1000������ɂ��ꂽ��
	if (Power >= 1000)
	{
		SetPower = 1000;									//	1000�Ŋm�肷��
	}

	//	300������Ȃ�
	else if (Power >= 300)
	{
		SetPower = Power;									//	���̂܂ܐݒ肷��(300���������Ƒ΂��ĐU�����Ȃ�����)
	}

	StartJoypadVibration(GamePadNo, SetPower, Time, RorL);	//	�U�����n�߂�
}