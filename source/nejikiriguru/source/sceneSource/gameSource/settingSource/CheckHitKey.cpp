/*
�L�[���͂Ɋւ���⏕�֐�
DXLib�ɑ��݂��Ȃ��̂Ŏ���

*/
#include "CheckHitKey.h"
#include "DxLib.h"

namespace CheckKey
{
	int DownBuffer[256];	// CheckDownKey�p�̃L�[�o�b�t�@
	int UpBuffer[256];		// CheckUpKey�p�̃L�[�o�b�t�@
};

// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��� 1 ��Ԃ��֐�
int CheckDownKey(int KeyCode)
{
	// �߂�l�p�̕ϐ���p��
	int Result = 0;

	// �w��L�[�̌��݂̏�Ԃ��擾
	int KeyState = CheckHitKey(KeyCode);

	// �O��L�[��������Ă��炸�A���A���݃L�[��������Ă�����u�L�[���������u�ԁv�Ƃ���
	if (CheckKey::DownBuffer[KeyCode] == 0 && KeyState == 1)
	{
		Result = 1;
	}

	// ���݂̃L�[��Ԃ��o�b�t�@�Ɋi�[
	CheckKey::DownBuffer[KeyCode] = KeyState;

	return Result;
}

// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��� 1 ��Ԃ��֐�
int CheckUpKey(int KeyCode)
{
	// �߂�l�p�̕ϐ���p��
	int Result = 0;

	// �w��L�[�̌��݂̏�Ԃ��擾
	int KeyState = CheckHitKey(KeyCode);

	// �O��L�[��������Ă���A���A���݃L�[��������Ă��Ȃ�������u�L�[�𗣂����u�ԁv�Ƃ���
	if (CheckKey::UpBuffer[KeyCode] == 1 && KeyState == 0)
	{
		Result = 1;
	}

	// ���݂̃L�[��Ԃ��o�b�t�@�Ɋi�[
	CheckKey::UpBuffer[KeyCode] = KeyState;

	return Result;
}