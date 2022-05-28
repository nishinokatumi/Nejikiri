#pragma once
#include "SceneBase.h"
#include "GameSource/SettingSource/CSVHeader.h"

/*
�V�[���̊Ǘ��N���X
	�V�[���J�ڂ��邽�߂̏������s��
*/
class SceneManager
{
private:
	// �V�[���J�ڂ̃t�F�[�Y���
	enum PHASE
	{
		Run = 0,											//	���s��
		SwitchScene,										//	�V�[���؂�ւ�
	};

	//	�ϐ�
	PHASE				SwitchPhase;									//	�V�[���J�ڂ̃t�F�[�Y
	SceneBase*			pNowScene;										//	���݂̃V�[��
	SceneBase*			pNextScene;										//	�J�ڐ�̃V�[��
	GameData			SceneManagerGameData = GameData();				//	�Q�[���f�[�^�̓ǂݍ���
	OperationManager	SceneManagerOperation = OperationManager();		//	����̊Ǘ��N���X����	
	SEManager			SceneManagerSE = SEManager();					//	SE�Ǘ�����
	UIDraw				SceneManagerUI = UIDraw();						//	UI�p�N���X����
	GameUI				SceneManagerGameUI = GameUI();					//	gameUI�p�N���X����
	DataLoadResource	SceneManagerDataLoad = DataLoadResource();		//	�f�[�^�Ǘ��N���X����
	int					SceneManagerFont[FONT_SIZE::FontLength] = { 0 };//	�g�p�t�H���g

	// �V�[���J�ڏ���
	void SetNextScene();
public:
	bool				SceneManagerGameExit = false;					//	�Q�[���I���^�U�l

	SceneManager(SceneBase* InitScene);									//	�����ݒ�


	//	�V�[���Ǘ��̏���
	void Initia();														//	��������
	void Update();														//	�X�V����
	void Draw();														//	�\������
	void Final();														//	�ŏI����
};