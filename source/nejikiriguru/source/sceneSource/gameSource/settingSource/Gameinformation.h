#pragma once
#include "Vector2D.h"
//�Q�[���v���O�����̒萔�E�`

// �E�B���h�E�̃T�C�Y
#define GAME_WIN_WIDTH	1920								//	�Q�[���̉�ʃT�C�Y:��
#define GAME_WIN_HEIGHT	1080								//	�Q�[���̉�ʃT�C�Y:�c

#define WIN_PL_WIDTH		1280								//	�v���C��ʃT�C�Y:��
#define WIN_PL_HEIGHT		960									//	�v���C��ʃT�C�Y:�c
#define MAP_CHIP_SIZE 	32									//	��̃`�b�v�̃T�C�Y
#define MAP_NUM			27									//	�X�e�[�W��

#define MAP_WIDTH		(WIN_PL_WIDTH / (MAP_CHIP_SIZE*2))	//	�}�b�v�̉���
#define MAP_HEIGHT		(WIN_PL_HEIGHT / (MAP_CHIP_SIZE*2))	//	�}�b�v�̏c��
#define	WIN_UI_WIDTH		((GAME_WIN_WIDTH - WIN_PL_WIDTH)/2)		//	UI�̉���
#define	WIN_UI_HEIGHT		((GAME_WIN_HEIGHT - WIN_PL_HEIGHT)/2)		//	UI�̏c��

//	�v���C���[�̐ݒ�
#define PL_MAX_GRAPH_WIDTH 4									//	�v���C���[�e�N�X�`���[�̓���ő吔(X)
#define PL_MAX_GRAPH_HEIGHT 4									//	�v���C���[�e�N�X�`���[�̓����̐�(Y)
#define PL_GRAPH_SIZE 32										//	�v���C���[�e�N�X�`���[�̈�Ӄs�N�Z����

#define PL_MOV_SPEED 6										//	�v���C���[�̓�������
#define PL_GRAPHVITY	32										//	�v���C���[�̏d�͒l(�ꍇ�ɂ��-��t���Ďg��)


#define GIMMICK_WMR_MAX_NUM 12								//	WMR�̍ő吔
#define GIMMICK_PRES_MAX_NUM 3								//	WMR�̍ő吔
#define GIMMICK_ENER_MAX_NUM 6								//	WMR�̍ő吔

//	�摜�Ȃǂ̗񋓌^�̖��O���
namespace GRAPH
{
	//	�摜�n���h��
	enum HANDLE
	{
		BackGround = 0,										//	�o�b�N�X�N���[���摜
		BackBase,											//	�o�b�N�X�N���[�������摜
		BackMove,											//	�o�b�N�X�N���[���߂������摜
		BackSky,											//	�o�b�N�X�N���[����摜
		PanelHandle,										//	�p�l���摜
		GimmickHandle,										//	�M�~�b�N�摜
		PLHandle,											//	�L�����摜
		TitlLogo,											//	�^�C�g�����S
		GamePadUI,											//	�Q�[���p�b�h�摜
		Manual,												//	�����摜
		ManualKey,											//	�����摜�L�[�{�[�h����
		GameLength,											//	�񋓐�
	};

	//	�v���C���[�̉摜�̏�Ԏ��
	enum PL_GRAPH
	{
		Wait = 0,											//	�ҋ@
		Move,												//	�ړ�
		Jump,												//	����
		Action,												//	�s��
		PLLength,											// �񋓐�
	};

	// �}�b�v�摜�̗�
	enum BLOCK
	{
		Ear = 0,											// ��
		Pne,												// �p�l��
		Wal,												// ��
		AuxiMate,											// �⏕��
		BlockLength,										// �񋓐�
	};

	//	WMR�̕��i
	enum WMR_PARTS
	{
		WMRBase = 0,										//	��{���i
		WMRLight,											//	�������i
		Extend,												//	�������i
		EndPoint,											//	�[�_���i
		WMRLength,											//	���i����
	};

	//	PRES�̕��i
	enum PRES_PARTS
	{
		PresBase = 0,										//	��{���i
		PresLight,											//	�������i
		PresButton,											//	�{�^�����i
		Signal1,											//�@�d�g1
		Signal2,											//�@�d�g2
		Signal3,											//�@�d�g3
		PresLength											//	���i����
	};

	//�@ENER�̕��i
	enum ENER_PARTS
	{
		OutPut = 0,											//�@�o�͑��u
		InPut,												//�@���͑��u
		LightYellow,										//	�������i(���F)
		LightBlue,											//	�������i(�F)
		LightWhite,											//	�������i(���F)
		EnerLength											//	���i����
	};
}


//	�}�b�v�̌^�̖��O���
namespace MAP_INFO
{
	// �X�e�[�W�̍\����
	struct Stage
	{
		int MapPanelNo;										//	�p�l���̎��
		int MapWallNo;										//	�ǂ̎��
		int BlockData[MAP_HEIGHT][MAP_WIDTH];					// �}�b�v
	};
	//	WMR�M�~�b�N�̍\����
	struct GimmickDataWMR
	{
		int GimmickWMRNum;									//	WMR�̐�
		int GimmickWMR[GIMMICK_WMR_MAX_NUM][5];				//	WMR�̃f�[�^�@���݂̃M�~�b�N�̐ݒ��� X:Y:�c��:����:�`�����l��
	};

	//	�����M�~�b�N�̍\����
	struct GimmickDataPres
	{
		int GimmickPresNum;									//	�����̐�
		int GimmickPres[GIMMICK_PRES_MAX_NUM][5];			//	�����̃f�[�^�@���݂̃M�~�b�N�̐ݒ��� X:Y:�㉺:�����l:�`�����l��
	};

	//	�ʓd�M�~�b�N�̍\����
	struct GimmickDataEner
	{
		int GimmickEnerNum;									//	�ʓd�̐�
		int GimmickEner[GIMMICK_ENER_MAX_NUM][6];			//	�ʓd�̃f�[�^�@���݂̃M�~�b�N�̐ݒ��� X:Y:����:�T�C�Y:�`�����l��:���
	};

	//	�M�~�b�N�̍\���̂��܂Ƃ߂��\����
	struct GimmickData
	{
		GimmickDataWMR	StageWMRData;						//	�X�e�[�W��WMR�̃f�[�^
		GimmickDataPres StagePresData;						//	�X�e�[�W�̊����̃f�[�^
		GimmickDataEner StageEnerData;						//	�X�e�[�W�̒ʓd�̃f�[�^
	};
}


//	�v���C���[��������������
enum class HIT_RESULT
{
	None = 0,												// ������Ȃ�����
	Left,													// ���ӂɓ�������
	Right,													// �E�ӂɓ�������
	Top,													// ��ӂɓ�������
	Bottom,													// ���ӂɓ�������
};

//	�t�H���g�̎��
enum FONT_SIZE
{
	Normal = 0,												//	�ʏ�T�C�Y�̃t�H���g
	PicUp,													//	�����ڗ�������T�C�Y�̃t�H���g
	Big,													//	�傫���T�C�Y�̃t�H���g
	GameStat,												//	���������T�C�Y�̃t�H���g
	Tab,													//	�^�u������
	Explanation,											//�@����
	FontLength,												//	�񋓐�
};

//	�t�H���g�̏��̍\����
struct FontStat
{
	int Size;												//	�傫��
	int Thick;												//	�t�H���g�̑���
};

//	�t�H���g�̏��
const FontStat SetFontStat[FONT_SIZE::FontLength] =
{
	{16,-1},												//	�m�[�}��
	{32,-1},												//	�ڗ�����
	{128,5},												//	�傫��
	{40,-1},												//	��������
	{55,-1},												//	�^�u����
	{24,-1},												//�@����
};