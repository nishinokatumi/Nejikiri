#include "SceneSelect.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneGame.h"

/*
�Q�[���V�[��
*/

//	�����ݒ�
SceneSelect::SceneSelect()
{

}

//	��������
void SceneSelect::Initia()
{
	static int ZeroX = 32;									//�@�{�^���O���[�v�̌��_��X���W
	static int MaxmX = (GAME_WIN_WIDTH / 2) - (64 * 5);		//�@�X�e�[�W�Z���N�g�{�^���̍��[��X���W
	static int MaxpX = (GAME_WIN_WIDTH / 2) + (64 * 5);		//�@�X�e�[�W�Z���N�g�{�^���̉E�[��X���W
	static int ZeroY = 64;									//�@�{�^���O���[�v�̌��_��Y���W
	static int Gap = 32;									//�@�{�^�����m�̋󔒋���
	static int SelectStageHeight = 64 * 6;					//�@

	pSceneDataLoad->InitiaGame();							//�@�Q�[���摜�̏����������s��
	MaxClearStageNo = pSceneDataLoad->MaxStageNo;			//�@���݃N���A�����X�e�[�W�ԍ��̑��
	SelectStageNo = pSceneDataLoad->StageSet;					//�@�I�����ꂽ�X�e�[�W�ԍ���ۑ�

	ColorBase = GetColor(0, 0, 0);							//�@���F
	ColorMain = GetColor(255, 255, 255);					//�@���F
	ColorSelect = GetColor(255, 255, 0);					//�@���F

	//�@�{�^��UI�̐������J��Ԃ�
	for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
	{
		//�@���
		ButtonUI[ButtonUINum].ButtonNo = ButtonUINum;
		ButtonUI[ButtonUINum].ColorBase = ColorBase;
		ButtonUI[ButtonUINum].ColorMain = ColorMain;
		ButtonUI[ButtonUINum].ColorSelect = ColorSelect;
	}

	//	�X�e�[�W�Z���N�g�{�^��
	{
		//�@X���W, Y���W, ����, �c��
		ButtonUI[BUTTON_L::StageSelect].PosX = ZeroX + Gap;
		ButtonUI[BUTTON_L::StageSelect].PosY = ZeroY + Gap;
		ButtonUI[BUTTON_L::StageSelect].Width = MaxmX - ButtonUI[StageSelect].PosX - Gap;
		ButtonUI[BUTTON_L::StageSelect].Height = SelectStageHeight;
	}

	//	�����{�^��
	{
		//�@X���W, Y���W, ����, �c��
		ButtonUI[BUTTON_L::Description].PosX = ButtonUI[StageSelect].PosX;
		ButtonUI[BUTTON_L::Description].PosY = ButtonUI[StageSelect].PosY + ButtonUI[StageSelect].Height + Gap;
		ButtonUI[BUTTON_L::Description].Width = ButtonUI[StageSelect].Width;
		ButtonUI[BUTTON_L::Description].Height = ButtonUI[StageSelect].Height / 2;
	}

	//	�ݒ�{�^��
	{
		//�@X���W, Y���W, ����, �c��
		ButtonUI[BUTTON_L::Option].PosX = ButtonUI[StageSelect].PosX;
		ButtonUI[BUTTON_L::Option].PosY = ButtonUI[Description].PosY + ButtonUI[Description].Height + Gap;
		ButtonUI[BUTTON_L::Option].Width = (ButtonUI[Description].Width - Gap) / 2;
		ButtonUI[BUTTON_L::Option].Height = ButtonUI[Description].Height;
	}

	//	�Q�[���I���{�^��
	{
		//�@X���W, Y���W, ����, �c��
		ButtonUI[BUTTON_L::GameExit].PosX = ButtonUI[Option].PosX + ButtonUI[Option].Width + Gap;
		ButtonUI[BUTTON_L::GameExit].PosY = ButtonUI[Option].PosY;
		ButtonUI[BUTTON_L::GameExit].Width = ButtonUI[Option].Width;
		ButtonUI[BUTTON_L::GameExit].Height = ButtonUI[Option].Height;
	}

	//	�Q�[���X�^�[�g�{�^��
	{
		//�@X���W, Y���W, ����, �c��
		ButtonUI[4].PosX = MaxpX + Gap;
		ButtonUI[4].PosY = (GAME_WIN_HEIGHT - ButtonUI[StageSelect].Height) / 2;
		ButtonUI[4].Width = ButtonUI[StageSelect].Width;
		ButtonUI[4].Height = ButtonUI[StageSelect].Height;
	}

	SelectOption.pOptionBackGrahandle = &pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround];
	SelectOption.pOptionOperation = pSceneOperation;				//	�Q�[���p�b�h�N���X���Q�Ƃ�����
	SelectOption.pOptionGameUI = pSceneGameUI;					//	�Q�[��UI�N���X���Q�Ƃ�����
	SelectOption.pOptionSE = pSceneSE;							//	���̊Ǘ����Q�Ƃ�����
	SelectOption.pOptionUI = pSceneUI;							//	�\��UI�N���X���Q�Ƃ�����
	SelectOption.pOptionGameDate = pSceneGameData;				//	�Q�[���Z�[�u�f�[�^���Q�Ƃ�����
	SelectOption.pOptionDataLoad = pSceneDataLoad;				//	�摜�Ǘ��N���X���Q�Ƃ�����
	SelectOption.Initia();										//	�|�[�Y��ʂ̏�������
}

//	�ŏI����
void SceneSelect::Final()
{
	//	�摜���J��
	pSceneSE->SoundFinal(SOUND_NAME::Wind);
}

//	�X�V����
SceneBase* SceneSelect::Update()
{
	//	�v�Z�������s��
	SceneBase* nextScene = this;

	//�@���݂̃V�[����
	if (TransitionSet == true)
	{
		//	�t�F�[�h�C��
		if (SceneTransition > 0)
		{
			//	0�������܂ŌJ��Ԃ�
			SceneTransition -= 10;
			if (SceneTransition < 0)
			{
				SceneTransition = 0;
			}
		}

		//	��ʓI�ȏ���
		else
		{
			//	��ʂ��A�N�e�B�u����
			if (GetWindowActiveFlag())
			{
				//	��{�I�ȌJ��Ԃ�����
				BaseUpdate();
			}
		}
	}

	//	���̃V�[����
	else
	{
		//	�t�F�[�h�A�E�g
		if (SceneTransition < 255)
		{
			//	255������܂ŌJ��Ԃ�
			SceneTransition += 10;
			if (SceneTransition > 255)
			{
				SceneTransition = 255;
			}
		}
		//	���̃V�[���ɑJ��
		else
		{
			nextScene = pNextSceneSave;
		}
	}

	//	�����܂�
	return nextScene;
}

//	��{�I�ȌJ��Ԃ�����
void SceneSelect::BaseUpdate()
{
	//	�ŏ�����
	if (InitiaBool == false)
	{
		InitiaBool = true;

		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	BGM�Đ�
	}

	//	�ݒ��ʂ̏���
	if (OptionFlag == true)
	{
		//�@SelectOption.Update����Ԃ��Ă����l��3�̂Ƃ�
		if (SelectOption.Update() == 3)
		{
			//�@�I�v�V�����t���O��false
			OptionFlag = false;

			//	�X�V�����̍Đ�(true)
			SelectOption.TransitionSet = true;
		}
	}
	else
	{
		//	��{�I�Ȍv�Z����
		ButtonReturn = SelectButton();

		//�@�{�^��UI�̐������J��Ԃ�
		for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
		{
			ButtonUI[ButtonUINum].UpdateBlend();				//�@�I������Ă���{�^���̐F��ς���
		}

		//�@�{�^���̑I����
		switch (ButtonReturn)
		{
		case 1:	//	�Q�[���X�^�[�g�������ꂽ
			//	�n��
			pSceneDataLoad->StageSet = SelectStageNo;			//�@�I�����ꂽ�X�e�[�W��ۑ�
			pNextSceneSave = new SceneGame();					//�@�Q�[���V�[���ɑJ�ڂ���
			TransitionSet = false;								//�@�X�V�������~
			break;

		case 2:	//	�I�v�V�����������ꂽ
			OptionFlag = true;									//�@�I�v�V�����t���O��true
			SelectOption.Initia();								//�@�I�v�V������������
			break;

		case 3:	//	�Q�[���I���������ꂽ
			//	�Z�[�u

			*pSceneGameExit = true;								//�@�Q�[�������
			break;

		default:
			break;
		}
	}
}

//	�\������
void SceneSelect::Draw()
{
	//	�ݒ��ʂ̏���
	if (OptionFlag == true)
	{
		//�@�I�v�V������ʂ̕`�揈��
		SelectOption.Draw();
	}

	else
	{
		//	�`�揈�����s��
		DrawRotaGraph2(														//	�w�i�̕`��
			GAME_WIN_WIDTH / 2												//�@��ʏ�ł̉摜�̒��S��X���W
			, GAME_WIN_HEIGHT												//�@��ʏ�ł̉摜�̒��S��Y���W
			, WIN_PL_WIDTH / 4, 0											//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 4, PI															//	�T�C�Y�Ɗp�x
			, pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround]			//�@�\������摜
			, false, false);												//	�\������摜�̓��߂Ɣ��]

		DrawButton();											//�@�{�^���̕\������
		DrawSelectStage();										//	�X�e�[�W��I���̕\������
		DrawSelectUI();											//�@�����p��UI

		if (TransitionSet == true)
		{
			//	�t�F�[�h�C��
			if (SceneTransition > 0)
			{
				pSceneUI->DarkenScreen
				(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//�@X���W, Y���W, ����, �c��
					, GetColor(0, 0, 0), SceneTransition);		//�@�F, �t�F�[�h�C��
			}
		}
		//	���̃V�[����
		else
		{
			//	�t�F�[�h�A�E�g
			pSceneUI->DarkenScreen(
				0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//�@X���W, Y���W, ����, �c��
				, GetColor(0, 0, 0), SceneTransition);			//�@�F, �t�F�[�h�A�E�g
		}
	}
}

//	�{�^���̑I������
int SceneSelect::SelectButton()
{
	//�@1�ԍ����̃{�^���O���[�v
	if (SelectButtonX == 0)
	{
		//�@DOWN�L�[
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//�@�I�𒆂̉�����~
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//�@�I�𒆂̉����Đ�

			SelectButtonL++;								//�@1���̑I���{�^����

			//�@�J�[�\�����P�ԉ��̑I�����̂Ƃ�
			if (SelectButtonL >= SELECTBUTTON_1Y)
			{
				//�@�J�[�\����1�ԏ�̑I�����ɂ���
				SelectButtonL = 0;
			}
		}

		//�@UP�L�[
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//�@�I�𒆂̉�����~
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//�@�I�𒆂̉����Đ�

			SelectButtonL--;								//�@1��̑I���{�^����

			//�@�J�[�\����1�ԏ�̑I�����̂Ƃ�
			if (SelectButtonL < 0)
			{
				//�@�J�[�\����1�ԉ��̑I�����ɂ���
				SelectButtonL = 3;
			}
		}

		//�@�{�^��UI�̐������J��Ԃ�
		for (int ButtonUINum = 0; ButtonUINum < 4; ButtonUINum++)
		{
			//�@1�ԍ����̃{�^���O���[�v���I�𒆂�������
			if (ButtonUI[ButtonUINum].ButtonNo == SelectButtonL)
			{
				//�@�I�𒆂̃{�^���O���[�v�̃t���O��true�ɂ���
				ButtonUI[ButtonUINum].Valid = true;
			}

			//�@1�ԍ����̃{�^���O���[�v���I�𒆂���Ȃ�������
			else
			{
				//�@�I�𒆂̃{�^���O���[�v�̃t���O��false�ɂ���
				ButtonUI[ButtonUINum].Valid = false;
			}
		}

		//	�����̃{�^���̎��̔���
		switch (SelectButtonL)
		{
		case BUTTON_L::StageSelect:							//�@�X�e�[�W�I��

			//	RIGHT�L�[������{�^��
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight) ||
				pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//�@���艹����~
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//�@���艹���Đ�

				SelectButtonX = 1;							//�@�J�[�\�����X�e�[�W�Z���N�g�{�^���Ɉړ�����
			}
			break;

		case BUTTON_L::Description:							//�@�������

			//	����{�^��
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//�@���艹����~
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//�@���艹���Đ�
				SelectButtonX = -1;							//�@���������ʂ��o��
			}
			break;

		case BUTTON_L::Option:							//�@�ݒ�

			//�@
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Select);			//�@�I�𒆂̉�����~
				pSceneSE->SoundPlay(SOUND_NAME::Select);			//�@�I�𒆂̉����Đ�
				SelectButtonL = BUTTON_L::GameExit;
			}

			//�@
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);			//�@���艹����~
				pSceneSE->SoundPlay(SOUND_NAME::Enter);				//�@���艹���Đ�
				return 2;
			}
			break;

		case BUTTON_L::GameExit:							//�@�Q�[���I��

			//	LEFT�L�[
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Select);	//�@�I�𒆂̉����~
				pSceneSE->SoundPlay(SOUND_NAME::Select);	//�@�I�𒆂̉����Đ�

				SelectButtonL = BUTTON_L::Option;
			}

			//	����{�^��
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//�@���艹����~
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//�@���艹���Đ�
				return 3;
			}
			break;

		default:
			break;
		}
	}

	//�@�����̃{�^���O���[�v(�X�e�[�W�Z���N�g�{�^��)
	else if (SelectButtonX == 1)
	{
		//	�����̃X�e�[�W�Z���N�g�{�^���̃X���b�g

		//�@DOWN�L�[
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//�@�I�𒆂̉����~
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//�@�I�𒆂̉����Đ�

			SelectStageNo--;								//�@�J�[�\����1�O�̃X�e�[�W�ԍ��ɖ߂�

			//�@�J�[�\�����X�e�[�W�ԍ���0�����������
			if (SelectStageNo < 0)
			{
				SelectStageNo = MaxClearStageNo;			//�@�J�[�\�������݃N���A�ς݂�MAX�X�e�[�W�ԍ��ɂ���
			}
		}

		//�@UP�L�[
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//�@�I�𒆂̉����~
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//�@�I�𒆂̉����Đ�

			SelectStageNo++;								//�@�J�[�\�������̃X�e�[�W�ԍ��ɂ���

			//�@�J�[�\�������݃N���A�ς݂�MAX�X�e�[�W�ԍ�����������
			if (SelectStageNo > MaxClearStageNo)
			{
				SelectStageNo = 0;							//�@�J�[�\����1�ԍŏ��̃X�e�[�W�ԍ��ɂ���
			}
		}

		//	����{�^����RIGHT�L�[
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Enter);		//�@���艹����~
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//�@���艹���Đ�

			SelectButtonX = 2;								//�@�J�[�\�����Q�[���X�^�[�g�{�^���Ɉړ�����
			ButtonUI[4].Valid = true;						//�@�Q�[���X�^�[�g�{�^���̑I���t���O��true�ɂ���
		}

		//	LEFT�L�[���߂�
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//�@�W�����v������~
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//�@�W�����v�����Đ�

			SelectButtonX = 0;								//�@�J�[�\����1�ԍ����̃{�^���O���[�v�Ɉړ�����
		}
	}

	//�@1�ԉE���̃{�^���O���[�v(�Q�[���X�^�[�g�{�^��)
	else if (SelectButtonX == 2)
	{
		//	�Q�[���X�^�[�g�������ꂽ
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Enter);		//�@���艹����~
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//�@���艹���Đ�
			return 1;										//�@case1�ɂ���
		}

		//	LEFT�L�[���߂�
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//�@�W�����v������~
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//�@�W�����v�����Đ�

			SelectButtonX = 1;								//�@�J�[�\����1�ԉE�̃{�^���O���[�v�Ɉړ�����
			ButtonUI[4].Valid = false;						//�@�Q�[���X�^�[�g�{�^���̑I���t���O��false�ɂ���
		}
	}

	//�@����������
	else if (SelectButtonX == -1)
	{
		//�@����{�^�����߂�@
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//�@�W�����v������~
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//�@�W�����v�����Đ�

			SelectButtonX = 0;								//�@�J�[�\����1�ԉE�̃{�^���O���[�v�Ɉړ�����
		}

	}

	return 0;
}

//	�{�^���̕\������
void SceneSelect::DrawButton()
{
	//�@�{�^��UI�̐������J��Ԃ�
	for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
	{
		//�@���������ʂ�I�����ɑ�������̃{�^�������F�ɂ���
		ButtonUI[ButtonUINum].Draw((SelectButtonX == -1 && ButtonUINum == Description) || (SelectButtonX > 0 && ButtonUINum == StageSelect));

		//�@�I�𒆂̃{�^��
		if (ButtonUI[ButtonUINum].Valid == true)
		{
			//�����̐F�����F�ɂ���
			DrawStringToHandle(ButtonUI[ButtonUINum].PosX + 15, ButtonUI[ButtonUINum].PosY + 15,
				ButtonText[ButtonUINum], ButtonUI[ButtonUINum].ColorBase, *pSceneFont[PicUp]);
		}

		//�@�I���O�̃{�^��
		else
		{
			//�����̐F�𔒐F�ɂ���
			DrawStringToHandle(ButtonUI[ButtonUINum].PosX + 15, ButtonUI[ButtonUINum].PosY + 15,
				ButtonText[ButtonUINum], ButtonUI[ButtonUINum].ColorMain, *pSceneFont[PicUp]);
		}
	}
}

//	�X�e�[�W��I���̕\������
void SceneSelect::DrawSelectStage()
{
	static int CentX = GAME_WIN_WIDTH / 2;					//�@��ʒ�����X���W
	static int CentY = GAME_WIN_HEIGHT / 2;					//�@��ʒ�����Y���W
	static int SelectStageWidth = 64 * 10;					//�@�X�e�[�W�Z���N�g�{�^���̉���
	static int SelectStageHeight = 64 * 8;					//�@�X�e�[�W�Z���N�g�{�^���̏c��

	//	��
	if (SelectStageNo != 0)
	{
		////�@�w�ʂ̐F(���F)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorBase, true);

		////�@�g�̐F(���F)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false);

		////�@�O�g�̐F(���F)
		//DrawBoxAA(
		//	(float)(CentX - (SelectStageWidth / 2)), (float)(CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	(float)(CentX + (SelectStageWidth / 2)), (float)(CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false, 4);

		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::CenterNone, 180);


		//�@����
		//DrawFormatStringToHandle(CentX, (CentY + SelectStageHeight), ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", (SelectStageNo - 1));
		pSceneUI->TextOutlLineFormat(CentX - 10, (CentY + SelectStageHeight), FONT_SIZE::Big, "No.%d", (SelectStageNo - 1), 2, ColorBase, ColorMain);
	}

	//	��
	if (SelectStageNo != (SELECTBUTTON_2Y - 1))
	{
		////�@�w�ʂ̐F(���F)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorBase, true);

		////�@�g�̐F(���F)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false);

		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::CenterNone, 180);

		//�@����
		//DrawFormatStringToHandle(CentX, (CentY - SelectStageHeight), ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", (SelectStageNo + 1));
		pSceneUI->TextOutlLineFormat(CentX - 10, (CentY - SelectStageHeight), FONT_SIZE::Big, "No.%d", (SelectStageNo + 1), 2, ColorBase, ColorMain);

		//�@�N���A�ς݂̃X�e�[�W�ԍ�������̔ԍ��̂Ƃ�
		if (SelectStageNo + 1 > MaxClearStageNo)
		{
			//�@�F���Â�����
			pSceneUI->DarkenScreen(
				CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
				SelectStageWidth, SelectStageHeight, ColorBase, 200);
		}
	}

	{
		//�@�w�ʂ̐F�����F�ɂ���
		/*DrawBox(
			CentX - (SelectStageWidth / 2), CentY - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), CentY + (SelectStageHeight / 2),
			ColorBase, true);*/


		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), CentY - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), CentY + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::FullDraw, 180);

		//�@�X�e�[�W�Z���N�g�{�^���܂��̓Q�[���X�^�[�g�{�^���̂Ƃ�
		if (SelectButtonX > 0)
		{
			//�@�I�𒆂̃{�^���̘g�̐F�����F�ɂ���
			DrawBoxAA(
				(float)CentX - (SelectStageWidth / 2), (float)CentY - (SelectStageHeight / 2),
				(float)CentX + (SelectStageWidth / 2), (float)CentY + (SelectStageHeight / 2),
				ColorSelect, false, 2);

			//�@�����̐F�����F�ɂ���
			//DrawFormatStringToHandle(CentX, CentY, ColorSelect, *pSceneFont[FONT_SIZE::Big], "No.%d", SelectStageNo);
			pSceneUI->TextOutlLineFormat(CentX - 10, CentY, FONT_SIZE::Big, "No.%d", SelectStageNo, 2, ColorSelect, ColorMain);

		}

		//�@1�ԍ����̃{�^���O���[�v�̂Ƃ�
		else
		{
			//�@�{�^���̘g�̐F�𔒐F�ɂ���
			DrawBoxAA(
				(float)CentX - (SelectStageWidth / 2), (float)CentY - (SelectStageHeight / 2),
				(float)CentX + (SelectStageWidth / 2), (float)CentY + (SelectStageHeight / 2),
				ColorMain, false, 2);

			//�@�����̐F�𔒐F�ɂ���
			//DrawFormatStringToHandle(CentX, CentY, ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", SelectStageNo);
			pSceneUI->TextOutlLineFormat(CentX - 10, CentY, FONT_SIZE::Big, "No.%d", SelectStageNo, 2, ColorBase, ColorMain);

		}
	}
}

//	�����p��UI
void SceneSelect::DrawSelectUI()
{
	static int UIWidth = GAME_WIN_WIDTH - (64 * 2);			//�@UI�̉���
	static int UIHeight = 64;								//�@UI�̏c��

	static int UIPosX = 64;									//�@UI��X���W
	static int UIPosY = GAME_WIN_HEIGHT - 32 - UIHeight;	//�@UI��Y���W

	////�@�������̔w�i
	//DrawBox(UIPosX, UIPosY, UIPosX + UIWidth, UIPosY + UIHeight, ColorBase, true);

	////�@���������͂��Ă���g
	//DrawBox(UIPosX, UIPosY, UIPosX + UIWidth, UIPosY + UIHeight, ColorMain, false);

	////�@���������͂��Ă���O�g
	//DrawBoxAA((float)UIPosX, (float)UIPosY, (float)UIPosX + (float)UIWidth, (float)UIPosY + (float)UIHeight, ColorMain, false, 4);

	pSceneGameUI->DrawMenuWindowOrigin
	(UIPosX, UIPosY, UIWidth, UIHeight, 4, ColorBase, MENU_TYPE::BackTransparency, 180);


	//	�Q�[���p�b�h���L����
	if (pSceneOperation->GamePadReady)
	{
		//�@������
		DrawStringToHandle(
			UIPosX,
			UIPosY + 15,
			"\"�@�@\"�őI����\"�@�@\"�Ō���\"�@�@\"�ŃL�����Z��", ColorMain, *pSceneFont[PicUp]);

		//	���L�[(4����)��\��
		for (int VecSelect = 0; VecSelect < 4; VecSelect++)
		{
			//�@���L�[��\��
			pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 2, UI_PARTS::VecPad, VecSelect);
			pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 2, UI_PARTS::LightVec, VecSelect);
		}

		//�@B�{�^����\��
		pSceneGameUI->Draw(UIPosX + 304, UIPosY + (UIHeight / 2), 3, UI_PARTS::Button);
		pSceneGameUI->Draw(UIPosX + 304, UIPosY + (UIHeight / 2), 3, UI_PARTS::B);

		//�@A�{�^����\��
		pSceneGameUI->Draw(UIPosX + 516, UIPosY + (UIHeight / 2), 3, UI_PARTS::Button);
		pSceneGameUI->Draw(UIPosX + 516, UIPosY + (UIHeight / 2), 3, UI_PARTS::A);
	}

	//	�L�[�{�[�h���쎞
	else
	{
		//�@������
		DrawStringToHandle(
			UIPosX,
			UIPosY + 15,
			"\"�@�@�@�@�@�@\"�őI����\"�@�@\"�Ō���\"�@�@\"�ŃL�����Z��", ColorMain, *pSceneFont[PicUp]);

		//	���L�[(�����)��\��
		pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + 48, UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "��", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	���L�[(������)��\��
		pSceneGameUI->Draw(UIPosX + (48 * 2), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 2), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "��", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	���L�[(�E����)��\��
		pSceneGameUI->Draw(UIPosX + (48 * 3), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 3), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "��", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	���L�[(������)��\��
		pSceneGameUI->Draw(UIPosX + (48 * 4), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 4), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "��", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//�@EnterKey��\��
		pSceneGameUI->Draw(UIPosX + 436, UIPosY + (UIHeight / 2), 2, UI_PARTS::EnterKey);
		pSceneUI->TextOutlLine(UIPosX + 454, UIPosY + (UIHeight / 2) - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//�@SpaceKey��\��
		pSceneGameUI->Draw(UIPosX + 656, UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + 674, UIPosY + (UIHeight / 2), FONT_SIZE::Normal, "Space", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
	}

	//�@��������{�^�������莞
	if (SelectButtonX == -1)
	{
		int ManualGraph = 0;									//	�����摜

		//	�Q�[���p�b�h���L����
		if (pSceneOperation->GamePadReady)ManualGraph = pSceneDataLoad->GraphGame[GRAPH::HANDLE::Manual];
		else ManualGraph = pSceneDataLoad->GraphGame[GRAPH::HANDLE::ManualKey];


		//�@���������ʂ�\��
		DrawRotaGraph2(
			GAME_WIN_WIDTH / 2, 32								//�@��ʏ�ł̉摜�̒��S��X���W, Y���W
			, 1556 / 2, 0										//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 0.8, 0											//	0.8�{, �p�x
			, ManualGraph										//�@�\������摜
			, true, false);										//�@�\������摜�̓��߂Ɣ��]
	}
}