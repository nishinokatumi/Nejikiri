#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/UIDraw.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/SEManager.h"
#include "OptionSG.h"

/*
�ꎞ��~�N���X
	�Q�[�����ꎞ��~���{�^���ɐݒ肳�ꂽ���������s
*/
class PauseSG
{
	//	�ꎞ��~��ʂ̃{�^���̎��
	enum PAUSEBUTTON
	{
		Back = 0,										//	�Q�[���ɖ߂�
		Retry,											//	���g���C����
		Option,											//	�ݒ��ʂ�
		Select,											//	�I����ʂ�
		PauseLength										//	����
	};
private:

	//	�ϐ�
	UIButton PauseButton[PauseLength + 1] = { UIButton() };	//	�{�^��
	OptionSG PauseOption;

	void SelectButtonDraw(								//	�I���{�^���̕\��
		int FontNo, const char* PText);
public:

	//	�ϐ�
	int* pPauseFont[FONT_SIZE::FontLength];				//	�g�p�t�H���g
	int* pPauseBackGrahandle;							//	�w�i�摜�n���h��
	int* pPauseGrahandle;								//	�^�C�g���摜�n���h��
	DataLoadResource*	pPauseDataLoad;					//	�摜���\�[�X�|�C���^
	GameUI*				pPauseGameUI;					//	�Q�[���p�b�h��UI�\��
	OperationManager*	pPauseOperation;				//	�Q�[���p�b�h�N���X�|�C���^
	GameData*			pPauseGameData;					//	�Q�[���Z�[�u�f�[�^�|�C���^
	UIDraw*				pPauseUI;						//	UI�̕\��
	SEManager*			pPauseSE;						//	���ʉ��N���X�|�C���^
	int SelectButton = 0;								//	�I�𒆂̃{�^��

	//	�����ݒ�
	PauseSG();											//	�����ݒ�

	//	�ꎞ��~��ʂ̏���
	void Initia();										//	�ꎞ��~��ʂ̏�������
	int Update();										//	�ꎞ��~��ʂ̍X�V����
	void Draw();										//	�ꎞ��~��ʂ̕\������

	void OptionUpdate();

	bool OptionFlag = false;
};