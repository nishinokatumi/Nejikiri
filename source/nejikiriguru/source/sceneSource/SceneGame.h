#pragma once
#include "SceneBase.h"
#include "GameSource/GameManager.h"
#include "GameSource/PauseSG.h"

/*
�Q�[����ʃN���X
	�Q�[����ʂ�ꎞ��~��ʂ̏����ƕ\�����s��
*/

//	�Q�[���̏��
enum SCENE_GAME_STAT
{
	PlayGame = 0,											//	�v���C�Q�[��
	PauseScene,												//	�ꎞ��~
	OptionScene,
};

class SceneGame : public SceneBase
{
private:
	//	�ϐ�
	SceneBase* pNextSceneSave = this;						//	���̃V�[���ۑ��p
	GameManager SceneGameManager = GameManager();			//	�Q�[���}�l�[�W���[�N���X
	PauseSG	ScenePause = PauseSG();							//	�ꎞ��~�N���X
	int TimeStart = 0;										//	�n�߂̎���
	int TimePause = 0;										//	�ꎞ��~��������

public:
	SceneGame();											//	�����ݒ�

	//	�Q�[����ʂ̏���
	void Initia();											//	��������
	void Final();											//	�ŏI����
	SceneBase* Update();									//	�X�V����
	void BaseUpdate();										//	�X�V�����̓��e
	void Draw();											//	�\������

	int NowStat = 0;										//	���݂̏��(�ꎞ��~���Q�[���v���C��)
	int SeleStage = 0;										//	�I�����Ă���X�e�[�W
};