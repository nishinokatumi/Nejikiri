#pragma once

#include "CharaPL.h"
#include "DrawMAP.h"
#include "GimmickAll.h"
#include "SettingSource/CSVHeader.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/AllResourceLoad.h"
#include "SettingSource/UIDraw.h"
#include "PauseSG.h"

/*
�Q�[������N���X
	�}�b�v��v���C���[�A�M�~�b�N������萧�䂷��
	�Q�[���̊�{����𐧌�
*/
class GameManager
{
	//	�Q�[���̏�Ԏ��
	enum GAMESTATE
	{
		Normal = 0,												//	�ʏ�i�s
		Clear,													//	�N���A��
		TimeUP,													//	�Q�[���I�[�o�[��
	};
private:

	//	�ϐ�
	DrawMAP GameManagerMap = DrawMAP();						//	�}�b�v�N���X�쐬
	UIDraw GameManagerUI;									//	UI�p�N���X�쐬
	CSVLoad GameManagerCSV = CSVLoad();						//	�ǂݍ��݃N���X�쐬

	MAP_INFO::Stage			MapNow;							//	���܂̃X�e�[�W�f�[�^

	MAP_INFO::GimmickData GimmiDataNow;						//	���܂̃M�~�b�N�f�[�^

	int GameTime = 0;										//	�Q�[���̎���
	int GameRemainingTime = 0;								//	�Q�[���̎c�莞��
	int GameStartTime = 0;									//	�Q�[�����n�߂�����
	int GameState = 0;										//	�Q�[���̏��

	//	WMR�M�~�b�N
	GimmickWMR WMR[GIMMICK_WMR_MAX_NUM] = { GimmickWMR() };

	//	PRES�M�~�b�N
	GimmickPres Pres[GIMMICK_PRES_MAX_NUM] = { GimmickPres() };

	//	ENER�M�~�b�N
	GimmickEner Ener[GIMMICK_ENER_MAX_NUM] = { GimmickEner() };

	bool GimmickYellow = false;								//�@�M�~�b�N(��)���A�����Ă邩
	bool GimmickBlue = false;								//�@�M�~�b�N(��)���A�����Ă邩
	bool GimmickWhite = false;								//�@�M�~�b�N(��)���A�����Ă邩

	bool MoveFlag = false;									//	�Q�[���̏�Ԃ𑱂��邩
	bool LastStageClear = false;							//	�ŏI�X�e�[�W�N���A


	//	����
	void UpdateNormal();									//	�Q�[���̒ʏ�^�s���̏����̍X�V
	void UpdateClear();										//	�X�e�[�W�N���A���̏����̍X�V
	void UpdateTimeUP();									//	�^�C���A�b�v���̏����̍X�V
	void DrawNormal();										//	�Q�[���̒ʏ�^�s���̕\������
	void DrawClear();										//	�X�e�[�W�N���A���̕\������
	void DrawTimeUP();										//	�^�C���A�b�v���̕\������
	void DrawUI();											//	UI�̕\������

public:

	//	�ϐ�
	UIDraw*				pGameManagerUI;						//	UI�p�N���X�|�C���^�쐬
	OperationManager*	pGameManagerOperation;				//	�Q�[���p�b�h�N���X�|�C���^����
	GameUI*				pGameManagerGameUI;					//	�Q�[��UI�|�C���^����
	SEManager*			pGameManagerSE;						//	SE�|�C���^�Ǘ�����
	DataLoadResource*	pGameManagerDataLoad;				//	�f�[�^�|�C���^����
	int*				pGameManagerFONT[FONT_SIZE::FontLength];//	�g�p�t�H���g
	int StageNo = 0;										//	���܂̃X�e�[�W
	int GameStopTime = 0;									//	�Q�[�����~�߂�����
	CharaPL GameManagerPL = CharaPL(200, 200);				//	�v���C���[�N���X�쐬


	GameManager();											//	��������

	//	����
	void Initia();											//	���߂ɓǂݍ��݃Q�[���̉摜��z��ɕ�������
	void Update();											//	�J��Ԃ����s�F�Q�[���̑���̔��f�ƌv�Z
	void Draw();											//	�\������
	void ChangeStage(int NextStageNo);						//	�N���A���ȂǂɃX�e�[�W�̕ϊ����s��

	//	�Ō�̃X�e�[�W���N���A������
	bool MAXStageClear()
	{
		return (LastStageClear == true);
	}
};