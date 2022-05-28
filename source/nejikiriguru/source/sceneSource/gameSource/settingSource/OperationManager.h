#pragma once
#include "GamePad.h"
#include "CheckHitKey.h"

//	����̎��
enum class OPERATION_CATEGORY
{
	CharaUP = 0,											//	�L�����ړ�:��
	CharaDown,												//	�L�����ړ�:��
	CharaLeft,												//	�L�����ړ�:��
	CharaRight,												//	�L�����ړ�:�E
	CharaDash,												//	�L�����ړ�:����
	CharaJump,												//	�L�����ړ�:�W�����v
	SelectUP,												//	�I���ړ�:��
	SelectDown,												//	�I���ړ�:��
	SelectLeft,												//	�I���ړ�:��
	SelectRight,											//	�I���ړ�:�E
	SelectEnter,											//	�I������
	SelectCancel,											//	�I��������
	SelectMenu,												//	�I�����j���[
	SelectSkip,												//�@���ʒ������̃Q�[�W�X�L�b�v
	OperationLength											//	����
};

//	����Ǘ��N���X
class OperationManager :public GamePad
{
public:
	OperationManager() {}									//	��������

	bool ArrowKeyJumpActive = true;							//	�\���L�[�ɂ��W�����v���L����
	bool ArrowKeyMoveActive = true;							//	�\���L�[�ɂ��ړ����L����


	//	���쏈��
	bool GetOperation(OPERATION_CATEGORY Set) {

		bool Returning = false;								//	�Ԃ��l���`		

		//	����̎�ނɂ���Ĕ���ύX
		switch (Set)
		{
		case OPERATION_CATEGORY::CharaUP:					//	�L�����ړ���
			Returning = ArrowKeyJumpActive && (CheckHitKey(KEY_INPUT_UP) || Button(XINPUT_BUTTON_DPAD_UP) ||
				CheckHitKey(KEY_INPUT_W));
			break;
		case OPERATION_CATEGORY::CharaDown:					//	�L�����ړ���
			Returning = ArrowKeyJumpActive && (CheckHitKey(KEY_INPUT_DOWN) || Button(XINPUT_BUTTON_DPAD_DOWN) ||
				CheckHitKey(KEY_INPUT_S));
			break;
		case OPERATION_CATEGORY::CharaLeft:					//	�L�����ړ���
			Returning = ((ArrowKeyMoveActive && (CheckHitKey(KEY_INPUT_LEFT) || Button(XINPUT_BUTTON_DPAD_LEFT))) ||
				CheckHitKey(KEY_INPUT_A));
			break;
		case OPERATION_CATEGORY::CharaRight:				//	�L�����ړ��E
			Returning = ((ArrowKeyMoveActive && (CheckHitKey(KEY_INPUT_RIGHT) || Button(XINPUT_BUTTON_DPAD_RIGHT))) ||
				CheckHitKey(KEY_INPUT_D));
			break;
		case OPERATION_CATEGORY::CharaDash:					//	�L�����_�b�V��
			Returning = (CheckHitKey(KEY_INPUT_B) || Button(XINPUT_BUTTON_B));
			break;
		case OPERATION_CATEGORY::CharaJump:					//	�L�����W�����v
			Returning = (CheckDownKey(KEY_INPUT_SPACE) || OneButton(XINPUT_BUTTON_A));
			break;
		case OPERATION_CATEGORY::SelectUP:					//	�I����
			Returning = (CheckDownKey(KEY_INPUT_UP) || OneButton(XINPUT_BUTTON_DPAD_UP));
			break;
		case OPERATION_CATEGORY::SelectDown:				//	�I����
			Returning = (CheckDownKey(KEY_INPUT_DOWN) || OneButton(XINPUT_BUTTON_DPAD_DOWN));
			break;
		case OPERATION_CATEGORY::SelectLeft:				//	�I����
			Returning = (CheckDownKey(KEY_INPUT_LEFT) || OneButton(XINPUT_BUTTON_DPAD_LEFT));
			break;
		case OPERATION_CATEGORY::SelectRight:				//	�I���E
			Returning = (CheckDownKey(KEY_INPUT_RIGHT) || OneButton(XINPUT_BUTTON_DPAD_RIGHT));
			break;
		case OPERATION_CATEGORY::SelectEnter:				//	�I������
			Returning = (CheckDownKey(KEY_INPUT_RETURN) || OneButton(XINPUT_BUTTON_B));
			break;
		case OPERATION_CATEGORY::SelectCancel:				//	�I��������
			Returning = (CheckDownKey(KEY_INPUT_SPACE) || OneButton(XINPUT_BUTTON_A));
			break;
		case OPERATION_CATEGORY::SelectMenu:				//	�I�����j���[
			Returning = (CheckDownKey(KEY_INPUT_ESCAPE) || OneButton(XINPUT_BUTTON_START));
			break;
		case OPERATION_CATEGORY::SelectSkip:				//	�I�����X�L�b�v
			Returning = (CheckHitKey(KEY_INPUT_LSHIFT));
		default:
			break;
		}
		return Returning;									//	���茋�ʂ�Ԃ�
	}
};

