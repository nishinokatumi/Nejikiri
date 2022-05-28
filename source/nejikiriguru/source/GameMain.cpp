#include "GameMain.h"
#include "DxLib.h"
#include "sceneSource/SceneManager.h"
#include "sceneSource/SceneTitle.h"


/*
�Q�[�����C���N���X
DXLib��V�[���Ǘ��N���X���̏����������n����A�Q�[���̃��C�����[�v
*/

GameMain::GameMain()
{
	// DXLib �O����
	SetMainWindowText("�˂�����");							// �E�B���h�E�^�C�g��
	SetAlwaysRunFlag(true);									// ��A�N�e�B�u���ɂ�����
	ChangeWindowMode(false);								// Window Mode
	SetGraphMode(GAME_WIN_WIDTH, GAME_WIN_HEIGHT, 32);		// �E�B���h�E�T�C�Y

	// DXLib������
	DxLib_Init();

	// �V�[���Ǘ��N���X�쐬�@�^�C�g���V�[�����N��
	GameMainSceneManager = new SceneManager(new SceneTitle());

	// �o�b�N�X�N���[���ɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

}

//	�Q�[�������ۂ̏���
GameMain::~GameMain()
{
	// new�����N���X��delete
	delete GameMainSceneManager;

	//�@�V�[���N���X����ɂ���
	GameMainSceneManager = nullptr;

	// DXLib �I��
	DxLib_End();
}

void GameMain::Run()
{
	//	FPS�p�Ɏg�p���鎞��
	int time = 0;
	
	// �����������@SE���̏�Ɏg�����̓ǂݍ���
	GameMainSceneManager->Initia();

	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		//	FPS�p�̏����J�n���Ԃ��擾
		time = GetTickCount();

		// �Q�[���I�����Ă΂ꂽ��I��
		if ((GameMainSceneManager->SceneManagerGameExit))
		{
			break;
		}

		// �X�V����
		GameMainSceneManager->Update();

		// �`�悷��
		ClearDrawScreen();
		GameMainSceneManager->Draw();

		// ��ʍX�V
		ScreenFlip();

		//	17������܂ŌJ��Ԃ���60FPS�ɌŒ�
		while (GetTickCount() - time < 15);
	}

	// �����������@�Z�[�u��
	GameMainSceneManager->Final();
}