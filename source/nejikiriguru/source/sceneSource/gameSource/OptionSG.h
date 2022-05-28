#pragma once
#include "DxLib.h"
#include "SettingSource/OperationManager.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/UIDraw.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/SEManager.h"
#include "SettingSource/AllResourceLoad.h"
#include "SettingSource/CSVHeader.h"

#define CENTER_SCREEN_POS_X			(GAME_WIN_WIDTH / 2)	//�@��ʒ�����X���W
#define CENTER_SCREEN_POS_Y			(GAME_WIN_HEIGHT / 2)	//�@��ʒ�����Y���W

#define BACK_GROUND_FRAME_WIDTH		1280					//�@OptionTab�̉���
#define BACK_GROUND_FRAME_HEIGHT	640						//�@OptionTab�̏c�̒���

#define OPTION_TAB_WIDTH			400						//�@OptionTab�̉���
#define OPTION_TAB_HEIGHT			60						//�@OptionTab�̏c�̒���
#define OPTION_CLOSE_TAB			50						//�@����{�^���̑傫��
#define SAVE_WIDTH					100
#define SAVE_HEIGHT					50

#define VOLUME_BAR_WIDTH			600						//�@���ʃo�[�̉���
#define VOLUME_BAR_HEIGHT			24						//�@���ʃo�[�̏c��

#define VOLUME_BUTTON_WIDTH			100						//�@���ʃ{�^���̉���
#define VOLUME_BUTTON_HEIGHT		50						//�@���ʃ{�^���̏c��

#define OPRATION_BUTTON_WIDTH		300						//�@����ݒ�{�^���̉���
#define OPRATION_BUTTON_HEIGHT		40						//�@����ݒ�{�^���̏c��

#define TRIVIABOX_SIDE				10						//�@TRIVIABOX�̂P��

#define PERCENT_MAX					100						//	�o�[�̃}�b�N�X


/*
�ꎞ��~�N���X
	�Q�[�����ꎞ��~���{�^���ɐݒ肳�ꂽ���������s
*/
class OptionSG
{
	//�@�I�v�V�����^�u�̎��
	enum OPTION_TAB
	{
		VolumeSetting = 0,									//�@���ʐݒ�
		Operation,											//�@����ݒ�
		OptionClose,										//�@�~(����)
		OptionTabLength										//�@����
	};

	//	�ꎞ��~��ʂ̃{�^���̎��
	enum VOLUME_BUTTON
	{
		BGM = 0,											//	�Q�[���ɖ߂�
		SE,													//	���g���C����
		UI,													//	�ݒ��ʂ�
		Save,												//�@�ۑ�
		VolumeButtonLength									//	����
	};

	//�@����ݒ�̃{�^���̎��
	enum OPRATION_BUTTON
	{
		ArrowKeyJump = 0,
		ArrowKeyMove,
		OprationButtonLength
	};

	//�@���m���̎��
	enum TRIVIA
	{
		Trivia0 = 0,
		Trivia1,
		Trivia2,
		Trivia3,
		Trivia4,
		Trivia5,
		Trivia6,
		Trivia7,
		Trivia8,
		Trivia9,
		TriviaLength
	};


private:
	const int TabButtonMaxNum[OPTION_TAB::OptionTabLength] =	//	�I�v�V�����^�u���ꂼ��̃{�^���̍ő吔
	{ VOLUME_BUTTON::VolumeButtonLength,OPRATION_BUTTON::OprationButtonLength,0 };

	const int ColorBase = GetColor(0, 0, 0);				//�@���F
	const int ColorMain = GetColor(255, 255, 255);			//�@���F
	const int ColorSelect = GetColor(255, 255, 0);			//�@���F

	const char* TabTextString[OPTION_TAB::OptionTabLength] =				//	�^�u�̃e�L�X�g�̓��e
	{
		{"     ����"},
		{"     ����"},
		{"�~"}
	};

	const char* VolumeTextString[VOLUME_BUTTON::VolumeButtonLength] =		//	���ʐݒ�̃e�L�X�g�̓��e
	{
		{"BGM"},
		{"SE"},
		{"UI"},
		{"�ۑ�"},
	};

	const char* OprationTextString[OPRATION_BUTTON::OprationButtonLength] =	//	����ݒ�̃e�L�X�g�̓��e
	{
		{"�W�����v����ύX"},
		{"�ړ�����ύX"},
	};

	const char* TriviaTextString[TRIVIA::TriviaLength] =	//	���m���̓��e
	{
		{"     �^��ɃW�����v���Ă�Œ���"},
		{"�ړ��L�[�������Ă��W�����v�ړ��ł����"},

		{"�X�e�[�W24"},
		{"�����̃��[�g�͂P�ł͂Ȃ�!?"},

		{"�X�e�[�W10"},
		{"�X�^�[�g�ʒu����"},
		{"D�L�[�������Ɖ����Ă���Ɓc"},

		{"���̃Q�[���ɂ͗l�X�ȍU���@������B"},
		{"�S�N������ǂ�ȍU���@������̂�"},
		{"�����ȃX�e�[�W�Ŏ����Ă݂悤�I"},
	};

	//	�ϐ�
	int SelectTab = 0;										//	�I�𒆂̃^�u
	int SelectButtons = 0;									//	�I�𒆂̃{�^���ԍ�
	int VolumeBar[VolumeButtonLength - 1];					//�@���ʃo�[�̔z��
	int VolumePercent[VolumeButtonLength - 1];				//�@���ʃo�[�̊���
	int Percent = 100;										//�@����
	int CountSave = 0;										//�@�\�����Ԃ̃J�E���g
	int CountDraw = 1;										//�@�����ʂŕ`�悳��Ă��ʂ̕\�����Ԃ̃J�E���g
	int DrawNum = 0;										//�@�����ʂŕ`�悳��Ă��ʂ̔ԍ�
	int TriviaNum = 0;										//�@���m���̔ԍ�

	bool SaveFlag = false;									//�@�ۑ����ꂽ���ǂ���
	bool* pOperationSetting[OprationButtonLength] = { new bool };			//	����ݒ�̓��e

	UIButton OptionTab[OptionTabLength + 1] = { UIButton() };				//	�^�u
	UIButton VolumeButton[VolumeButtonLength + 1] = { UIButton() };			//	���ʐݒ�{�^��
	UIButton OprationButton[OprationButtonLength + 1] = { UIButton() };		//	����ݒ�{�^��



	bool InitiaBool = false;								//	���߂̏���
	int ReturningSave = 0;									//�@�e�̉�ʂɕԂ��l
	int	SceneTransition = 255;								//	��ʑJ�ڂ̃t�F�[�h�C���t�F�[�h�A�E�g0~255

	void SelectTabDraw(										//	�I���^�u�̕\��
		int FontNo, const char* PText);

	void VolumeButtonDraw(									//	���ʐݒ�{�^���̕\��
		int FontNo, const char* PText);

	void OprationButtonDraw(								//	����ݒ�{�^���̕\��
		int FontNo, const char* PText);

public:

	//	�ϐ�
	int* pOptionFont[FONT_SIZE::FontLength];				//	�g�p�t�H���g
	int* pOptionBackGrahandle;								//	�w�i�摜�n���h��
	int* pOptionGrahandle;									//	�^�C�g���摜�n���h��
	DataLoadResource*	pOptionDataLoad;
	GameUI*				pOptionGameUI;						//	�Q�[���p�b�h��UI�\��
	OperationManager*	pOptionOperation;					//	�Q�[���p�b�h�N���X�|�C���^
	UIDraw*				pOptionUI;							//	UI�̕\��
	SEManager*			pOptionSE;							//	���ʉ��N���X�|�C���^
	GameData*			pOptionGameDate;					//	�Q�[���Z�[�u�f�[�^�|�C���^
	bool TransitionSet = true;								//	�X�V�����̍Đ�(true)�ƒ�~(false)
	OptionSG();												//	�����ݒ�

	//	�ꎞ��~��ʂ̏���
	void Initia();											//	�ꎞ��~��ʂ̏�������
	void TabButton();										//	�{�^���̍X�V����
	void Draw();											//	�ꎞ��~��ʂ̕\������
	void VolumeDraw();										//�@���ʐݒ��ʂ̕`�揈��
	void OperationDraw();									//�@����ݒ��ʂ̕`�揈��
	void CloseDraw();										//�@����{�^���̉�ʂ̕`�揈��
	int Update();											//	�ꎞ��~��ʂ̍X�V����

	//	�ݒ�ǂݍ���0�`100
	void LoadOption()
	{
		VolumePercent[SE] = pOptionGameDate->GameSaveData.SaveSEVolume;				//	���ʂ�K�p
		VolumePercent[BGM] = pOptionGameDate->GameSaveData.SaveBGMVolume;			//	���ʂ�K�p
		VolumePercent[UI] = pOptionGameDate->GameSaveData.SaveUIVolume;				//	���ʂ�K�p
		pOperationSetting[ArrowKeyJump] = &pOptionOperation->ArrowKeyJumpActive;	//	�\���L�[�ɂ��W�����v���L����
		pOperationSetting[ArrowKeyMove] = &pOptionOperation->ArrowKeyMoveActive;	//	�\���L�[�ɂ��ړ����L����
		SelectTab = OPTION_TAB::VolumeSetting;										//	�^�u�J�[�\������
		SelectButtons = 0;															//	�{�^���I���^�u
	}
};