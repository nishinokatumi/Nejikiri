#include "SceneManager.h"
#include "SceneBase.h"

/*
�V�[���Ǘ��N���X
�V�[���̐؂�ւ�������S��

*/

SceneManager::SceneManager(SceneBase* initScene)
{
	//	���̃V�[���͋��
	pNowScene = nullptr;

	//	���̃V�[���ɍŏ��̃V�[��������
	pNextScene = initScene;

	// initScene�Ŏ󂯎�����V�[�����N������
	SetNextScene();
}

void SceneManager::SetNextScene()
{
	//	�A�h���X�n��
	pNextScene->pSceneGameExit = &SceneManagerGameExit;
	pNextScene->pSceneOperation = &SceneManagerOperation;
	pNextScene->pSceneGameData = &SceneManagerGameData;
	pNextScene->pSceneUI = &SceneManagerUI;
	pNextScene->pSceneSE = &SceneManagerSE;
	pNextScene->pSceneGameUI = &SceneManagerGameUI;
	pNextScene->pSceneDataLoad = &SceneManagerDataLoad;
	for (int num = 0; num < FontLength; num++)
	{
		pNextScene->pSceneFont[num] = &SceneManagerDataLoad.FontSet[num];
	}

	//	�J�ڐ�V�[���̏�����
	pNextScene->Initia();

	//	�V�[���؂�ւ����s��
	SwitchPhase = SwitchScene;
}

void SceneManager::Initia()
{
	//	�Q�[���̃Z�[�u�f�[�^�ǂݍ���
	SceneManagerGameData.Load();

	//	������
	int uifghun = LoadGraph("resource/texture/UI32pix.png");
	SceneManagerDataLoad.Initia();

	//	���̊Ǘ�������
	SceneManagerSE.SoundLoad(
		(float)SceneManagerGameData.GameSaveData.SaveSEVolume / 100.0f,
		(float)SceneManagerGameData.GameSaveData.SaveBGMVolume / 100.0f,
		(float)SceneManagerGameData.GameSaveData.SaveUIVolume / 100.0f);
	
	//	�Q�[��UI�̏�����(UI�p�̉摜�n��)
	SceneManagerGameUI.Initia(uifghun);

	//	�t�H���g�����ׂĎ擾
	for (int fnum = 0; fnum < FontLength; fnum++)
	{
		SceneManagerUI.FontSet[fnum] = &SceneManagerDataLoad.FontSet[fnum];
	}

	//	UI�̏��n��
	SceneManagerGameUI.pGameUIDraw = &SceneManagerUI;

	//	�Q�[���p�b�h�̏����ݒ�(��Ԗڂ̃Q�[���p�b�h���g�p)
	SceneManagerOperation.Initia(DX_INPUT_PAD1);

	//	����ς݃X�e�[�W��ǂݍ���
	SceneManagerDataLoad.MaxStageNo = SceneManagerGameData.GameSaveData.ReleaseStage;

	//	��ʂ�����
	ClearDrawScreen();
}

void SceneManager::Update()
{
	//	�S�V�[���Ŏg���N���X�̍X�V����
	SceneManagerOperation.Update();

	//	�V�[���J�ڂ̃t�F�[�Y�ɂ���ď�����؂�ւ���
	switch (SwitchPhase)
	{
		//	���s��
	case PHASE::Run:

		//	���݂̃V�[���̍X�V����
		pNextScene = pNowScene->Update();

		//	���̃V�[�������̃V�[���ƈ���Ă����ꍇ
		if (pNextScene != pNowScene)
		{
			SetNextScene();
		}
		break;

		//	�V�[���؂�ւ�
	case PHASE::SwitchScene:
		//	���ݎ��s���̃V�[���̏I�������Ɖ�����s��
		//	�Q�[���J�n����͌��ݎ��s���̃V�[�������݂��Ȃ��̂�if()�ň͂��Ă���
		if (pNowScene)
		{
			pNowScene->Final();
			delete pNowScene;
			pNowScene = nullptr;
		}

		//	�J�ڐ�V�[�������ݎ��s���̃V�[���ɂ���
		pNowScene = pNextScene;

		//	pNextScene�̏��L����pNowScene�ɓn�����̂ŁApNextScene��delete���Ȃ�
		//	pNextScene�̃|�C���^�������ɗ��߂�
		pNextScene = nullptr;

		//	�t�F�[�Y�i�s
		SwitchPhase = Run;
		break;
	}

	//	�ŏI�I�ȏ����̌�ɖ���s������
	SceneManagerOperation.OldUpdate();
}

void SceneManager::Draw()
{
	//	�t�F�[�Y���ɕ`�悷����̂�؂�ւ���
	switch (SwitchPhase)
	{
	case PHASE::Run:
		if (pNowScene)
		{
			pNowScene->Draw();								//	���̉�ʂ̕\������
		}
		break;
	}
}

void SceneManager::Final()
{
	//	����ς݃X�e�[�W��ۑ�����
	SceneManagerGameData.SaveStageNo(SceneManagerDataLoad.MaxStageNo);

}