#pragma once
#pragma once
#include "SceneBase.h"
#include "GameSource/OptionSG.h"

#define SELECTBUTTON_X 3									//	�{�^���O���[�v
#define SELECTBUTTON_1Y 4									//	�{�^���̉��̐�
#define SELECTBUTTON_2Y 27									//	�{�^���̉��̐�
#define SELECTBUTTON_3Y 1									//	�{�^���̉��̐�

/*
�I����ʃN���X
	�Q�[���̃X�e�[�W��I�����鏈�����s��
*/
class SceneSelect :public SceneBase
{
	enum BUTTON_L
	{
		StageSelect = 0,									//	�X�e�[�W�I��
		Description,										//	�������
		Option,												//	�ݒ�
		GameExit,											//	�Q�[���I��
	};
private:
	SceneBase* pNextSceneSave = this;						//	���̃V�[���ۑ��p
	int BackGraph = 0;										//	�w�i�摜�n���h��
	int TitleGraph = 0;										//	�^�C�g���摜�n���h��
	int ColorBase = 0;										//	��{�I�ȐF(��)
	int ColorMain = 0;										//	��{�I�ȐF(��)
	int ColorSelect = 0;									//	��{�I�ȐF(��)
	UIButton ButtonUI[5] = { UIButton() };						//	�I���V�[���̃{�^��5��
	const char* ButtonText[5] =								//	�{�^���̃e�L�X�g
	{
		"StageSelect",
		"�������",
		"�ݒ�",
		"EXIT",
		"GameStart"
	};
	int MaxClearStageNo = 0;								//	�N���A���Ă���X�e�[�W�̍ő�l
	int SelectStageNo = 0;									//	�I�����Ă���X�e�[�W�̔ԍ�
	int ButtonReturn = 0;									//	�{�^���̏����ŃV�[���J�ڂ���ۂ̒l
	int SelectButtonX = 0;									//	�I�����Ă���{�^���O���[�v
	int SelectButtonL = 0;									//	�I�����Ă��鍶���̃{�^��

	//	�I����ʂ̏���
	int SelectButton();										//	�{�^���̑I������
	void DrawButton();										//	�{�^���̕\������
	void DrawSelectStage();									//	�X�e�[�W��I���̕\������
	void DrawSelectUI();									//	�����p��UI

	OptionSG SelectOption;									//	�ݒ���
	bool OptionFlag = false;								//	�ݒ��ʂ��ǂ���

public:
	SceneSelect();											//	�����ݒ�

	//	�I����ʂ̏���
	void Initia();											//	��������
	SceneBase* Update();									//	�X�V����
	void BaseUpdate();										//	�X�V�����̓��e
	void Draw();											//	�\������
	void Final();											//	�ŏI����

};