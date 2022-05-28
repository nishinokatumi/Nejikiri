#pragma once
#include "DxLib.h"
#include "GameSource/SettingSource/Gameinformation.h"
#include "GameSource/SettingSource/CSVHeader.h"
#include "GameSource/SettingSource/GameUI.h"
#include "GameSource/SettingSource/OperationManager.h"
#include "GameSource/SettingSource/SEManager.h"
#include "GameSource/SettingSource/UIDraw.h"
#include "GameSource/SettingSource/CheckHitKey.h"
#include "GameSource/SettingSource/AllResourceLoad.h"

/*
�V�[�����N���X
*/
class SceneBase
{
public:
	SceneBase() {};														//	�����ݒ�
	virtual ~SceneBase() {};											//	�����ۂ̏���

	virtual void Initia() = 0;											//	�V�[���̏�������
	virtual void Final() = 0;											//	�V�[���̍ŏI����
	virtual SceneBase* Update() = 0;									//	�V�[���̍X�V����
	virtual void Draw() = 0;											//	�V�[���̕\������

	bool*				pSceneGameExit = new bool;						//	�Q�[���I���^�U�l�|�C���^����
	UIDraw*				pSceneUI = new UIDraw;							//	UI�p�N���X�|�C���^�쐬
	GameData*			pSceneGameData = new GameData;					//	�Q�[���̃Z�[�u�f�[�^�|�C���^����
	OperationManager*	pSceneOperation = new OperationManager;			//	����Ǘ��N���X�|�C���^�쐬
	SEManager*			pSceneSE = new SEManager;						//	SE�|�C���^����
	GameUI*				pSceneGameUI = new GameUI;						//	�Q�[��UI�N���X�|�C���^����
	DataLoadResource*	pSceneDataLoad = new DataLoadResource;			//	�f�[�^�Ǘ��|�C���^����
	int*				pSceneFont[FONT_SIZE::FontLength] = { new int };//	�g�p�t�H���g

protected:
	bool InitiaBool = false;											//	���߂̏���
	bool TransitionSet = true;											//	�X�V�����̍Đ�(true)�ƒ�~(false)
	int	SceneTransition = 255;											//	��ʑJ�ڂ̃t�F�[�h�C���t�F�[�h�A�E�g0~255
};