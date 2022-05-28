#include "SceneGame.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneED.h"
/*
�Q�[���V�[��
*/

//	�����ݒ�
SceneGame::SceneGame()
{

}

//	��������
void SceneGame::Initia()
{
	//	�|�C���^���p��
	SceneGameManager.pGameManagerOperation = pSceneOperation;	//	�Q�[���p�b�h�N���X���Q�Ƃ�����
	SceneGameManager.pGameManagerGameUI = pSceneGameUI;		//	�Q�[��UI�N���X���Q�Ƃ�����
	SceneGameManager.pGameManagerSE = pSceneSE;				//	���̊Ǘ��N���X���Q�Ƃ�����
	SceneGameManager.pGameManagerUI = pSceneUI;				//	�\��UI�N���X���Q�Ƃ�����
	SceneGameManager.pGameManagerDataLoad = pSceneDataLoad;	//	���\�[�X�Ǘ��N���X���Q�Ƃ�����

	//	�����̐���������
	for (int Num = 0; Num < FONT_SIZE::FontLength; Num++)
	{
		//	�����f�[�^���Q�Ƃ�����
		SceneGameManager.pGameManagerFONT[Num] = &pSceneDataLoad->FontSet[Num];
		ScenePause.pPauseFont[Num] = &pSceneDataLoad->FontSet[Num];
	}

	//	�w�i�摜���Q�Ƃ�����
	ScenePause.pPauseBackGrahandle = &pSceneDataLoad->GraphGame[GRAPH::BackGround];
	ScenePause.pPauseOperation = pSceneOperation;				//	�Q�[���p�b�h�N���X���Q�Ƃ�����
	ScenePause.pPauseGameUI = pSceneGameUI;					//	�Q�[��UI�N���X���Q�Ƃ�����
	ScenePause.pPauseSE = pSceneSE;							//	���̊Ǘ����Q�Ƃ�����
	ScenePause.pPauseUI = pSceneUI;							//	�\��UI�N���X���Q�Ƃ�����
	ScenePause.pPauseDataLoad = pSceneDataLoad;				//	�摜�Ǘ��N���X���Q�Ƃ�����
	ScenePause.pPauseGameData = pSceneGameData;				//	�Q�[���Z�[�u�f�[�^���Q�Ƃ�����
	ScenePause.Initia();									//	�|�[�Y��ʂ̏�������

	SceneGameManager.Initia();								//	�Q�[���}�l�[�W����������
	NowStat = PlayGame;										//	�v���C�Q�[����Ԃɂ���
}

//	�ŏI����
void SceneGame::Final()
{
	pSceneSE->SoundFinal(SOUND_NAME::Wind);					//	���̒�~(���̉�BGM)
}

//	�X�V����
SceneBase* SceneGame::Update()
{
	//	�v�Z�������s��
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
			BaseUpdate();											//	�X�V�����̓��e
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
void SceneGame::BaseUpdate()
{
	//	�ŏ�����
	if (InitiaBool == false)
	{
		InitiaBool = true;
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	���̍Đ�(���̉�BGM)
	}

	//	�X�^�[�g�{�^���������ꂽ��|�[�Y���j���[�ɑJ�ڂ���
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectMenu))
	{
		//	�|�[�Y��ʂ̎��ɃQ�[����ʂ�
		if (NowStat == PauseScene)
		{
			NowStat = PlayGame;								//	�v���C�Q�[����Ԃɂ���
			SceneGameManager.GameStopTime = TimePause - TimeStart;	//	�ꎞ��~���Ă��������Ԃ�����Ȃ��悤�ɂ���

			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//	���̒�~(�W�����v)
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//	���̍Đ�(�W�����v)
		}
		//	�Q�[����ʂ̎��Ƀ|�[�Y��ʂ�
		else {
			//	���̉�ʂ��v���C�Q�[���̎�
			if (NowStat == PlayGame)
			{
				ScenePause.SelectButton = 0;					//	�{�^���̑I���ʒu������
				TimeStart = GetTickCount();					//	�n�߂鎞�Ԃ̏�����

				//	���ʉ��̒�~(���[�v��h��)
				pSceneSE->SoundFinal(SOUND_NAME::Jump);		//	���̒�~(�W�����v)
				pSceneSE->SoundFinal(SOUND_NAME::FootStep);	//	���̒�~(������)
				pSceneSE->SoundFinal(SOUND_NAME::Timelimit);//	���̒�~(��������)

				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//	���̒�~(����)
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//	���̍Đ�(����)
			}
			NowStat = PauseScene;							//	�ꎞ��~��Ԃɂ���
		}
	}

	//	��ʂ���A�N�e�B�u����
	if (!(GetWindowActiveFlag()))
	{
		//	���̉�ʂ��v���C�Q�[���̎�
		if (NowStat == PlayGame)
		{
			ScenePause.SelectButton = 0;
			TimeStart = GetTickCount();

			//	���ʉ��̒�~(���[�v��h��)
			pSceneSE->SoundFinal(SOUND_NAME::Jump);		//	���̒�~(�W�����v)
			pSceneSE->SoundFinal(SOUND_NAME::FootStep);	//	���̒�~(�W�����v)
			pSceneSE->SoundFinal(SOUND_NAME::Timelimit);//	���̒�~(�W�����v)

			pSceneSE->SoundFinal(SOUND_NAME::Enter);	//	���̒�~(�W�����v)
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//	���̒�~(�W�����v)
		}
		NowStat = PauseScene;								//	�ꎞ��~��Ԃɂ���
	}

	//	���̉�ʂ��v���C�Q�[���̎�
	if (NowStat == PlayGame)
	{
		SceneGameManager.Update();							//	�Q�[���}�l�[�W���[�̍X�V����

		//	�Ō�̃X�e�[�W���N���A������
		if (SceneGameManager.MAXStageClear())
		{
			pNextSceneSave = new SceneED();					//	�Q�[���G���f�B���O��ʂ�
			TransitionSet = false;							//	���̉�ʂ�
		}

	}

	//	�|�[�Y��ʂ̎��ɃQ�[����ʂ�
	else if (NowStat == PauseScene)
	{
		TimePause = GetTickCount();							//	�ꎞ��~���Ă��錻�ݎ��Ԃ̍X�V
		int Set = ScenePause.Update();						//	�ꎞ��~��ʂ̍X�V����

		//	�ꎞ��~��ʂ���A���Ă����l���ȉ��̒l�̎��̏���
		switch (Set)
		{
		case 1: //�@�Q�[���ɖ߂�
			NowStat = PlayGame;								//	�v���C�Q�[����Ԃɂ���
			SceneGameManager.GameStopTime = (TimePause - TimeStart);	//	�Q�[�����~�߂����Ԃ���
			break;

		case 2: //�@���g���C
			NowStat = PlayGame;								//	�v���C�Q�[����Ԃɂ���
			SceneGameManager.ChangeStage(SceneGameManager.StageNo);		//	�Q�[�����~�߂����Ԃ���
			break;

		case 3: //�@�ݒ���

			ScenePause.OptionFlag = true;
			break;

		case 4: //�@�I���V�[��
			pNextSceneSave = new SceneSelect();				//	�I����ʂ�
			TransitionSet = false;							//	���̉�ʂ�
			break;

		default:
			break;
		}
	}
}

//	�\������
void SceneGame::Draw()
{
	//	�`�揈�����s��

	//	���̉�ʂ��v���C�Q�[���̎�
	if (NowStat == PlayGame)
	{
		SceneGameManager.Draw();								//	�Q�[���}�l�[�W���[�̕\������
	}

	//	�|�[�Y��ʂ̎��ɃQ�[����ʂ�
	else if (NowStat == PauseScene)
	{
		ScenePause.Draw();									//	�ꎞ��~��ʂ̕\������
	}

	//	���݂̉�ʂ�
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