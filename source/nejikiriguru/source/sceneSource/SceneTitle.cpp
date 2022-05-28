#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneSelect.h"

/*
�^�C�g���V�[��
*/

//	�����ݒ�
SceneTitle::SceneTitle()
{

}

//	��������
void SceneTitle::Initia()
{
}

//	�ŏI����
void SceneTitle::Final()
{
	pSceneSE->SoundFinal(SOUND_NAME::Wind);					//	���̒�~(���̉�BGM)
}

//	��������
SceneBase* SceneTitle::Update()
{
	// �V�[�����̌v�Z����
	SceneBase* pNextScene = this;

	//	���݂̃V�[����
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
				BaseUpdate();								//	��{�I�ȍX�V����
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
			pNextScene = pNextSceneSave;
		}
	}

	return pNextScene;
}

//	�X�V�����̓��e
void SceneTitle::BaseUpdate()
{
	//	�ŏ�����
	if (InitiaBool == false)
	{
		InitiaBool = true;
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	���̍Đ�(���̉�BGM)
	}

	// Z�L�[�������ꂽ��Q�[���V�[���ɑJ�ڂ���CheckDownKey(KEY_INPUT_RETURN) || (pSceneGamePad->OneButton(XINPUT_BUTTON_B))
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
	{
		pSceneSE->SoundFinal(SOUND_NAME::Enter);			//	���̒�~(����)
		pSceneSE->SoundPlay(SOUND_NAME::Enter);				//	���̍Đ�(����)
		pNextSceneSave = new SceneSelect();					//	���̃V�[����I����ʂ�
		TransitionSet = false;								//	���̃V�[����
	}
}

//	�\������
void SceneTitle::Draw()
{
	// �V�[�����̕`�揈�����s��

	//	�w�i�̕`��
	DrawRotaGraph2(
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64,		//	�\��������W
		WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4,				//	�摜�̔����̈ʒu
		3.5, 0,												//	3.5�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround], false, false);

	//	�w�i�̕`��
	DrawRotaGraph2(
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 200,		//	�\��������W
		96, 34,												//	�摜�̔����̈ʒu
		4, 0,												//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::TitlLogo], true, false);

	int Tin = 4;											//	�E�B���h�E�̉��̕�
	int WindowBoxY = GAME_WIN_HEIGHT / 2 + 128;					//	�E�B���h�E�̈ʒuY


	//	�hB�h�Ŏ��ւƕ\��
	pSceneUI->TextBoxWindowCenter(
		GAME_WIN_WIDTH / 2, WindowBoxY, 15,		//	���W�ƕ�����
		GetColor(255, 255, 255), GetColor(0, 0, 0),			//	�����̐F,�E�B���h�E�̐F
		(float)Tin, FONT_SIZE::PicUp, "�@�@\"�@�@�@\"�Ŏ���");	//	�E�B���h�E�̉��̕�,�����̎��,�e�L�X�g

	//	�Q�[���p�b�h���L����
	if (pSceneOperation->GamePadReady)
	{
		//	B�{�^���̕\��
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 3, UI_PARTS::Button);
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 3, UI_PARTS::B);
	}

	//	�L�[�{�[�h���쎞
	else
	{
		//�@EnterKey��\��
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 2, UI_PARTS::EnterKey);
		pSceneUI->TextOutlLine(GAME_WIN_WIDTH / 2 - (88 - 18), WindowBoxY - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
	}

	//	���݂̃V�[����
	if (TransitionSet == true)
	{
		//	�t�F�[�h�C��
		if (SceneTransition > 0)
		{
			pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
				GetColor(0, 0, 0), SceneTransition);
		}

	}
	//	���̃V�[����
	else
	{
		//	�t�F�[�h�A�E�g
		pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
			GetColor(0, 0, 0), SceneTransition);
	}
}