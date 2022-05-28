#pragma once
#include "Gameinformation.h"

//	�摜�f�[�^�̑��΃p�X
static const char* GraphPath[GRAPH::HANDLE::GameLength] =
{
	"resource/texture/background.png",							//	�Q�[���w�i�摜
	"resource/texture/backbase.png",						//	�Q�[�������w�i��b�摜
	"resource/texture/backmove.png",						//	�Q�[�������w�i�ߏ�摜
	"resource/texture/backsky.png",							//	�Q�[�������w�i�[��摜
	"resource/texture/panel32pix.png",						//	�u���b�N�̉摜
	"resource/texture/gimmick32pix.png",					//	�M�~�b�N�̉摜
	"resource/texture/player32pix.png",						//	�v���C���[�̉摜
	"resource/texture/titlelog.png",						//	�^�C�g�����S�摜
	"resource/texture/ui32pix.png",							//	�Q�[���p�b�hUI�摜
	"resource/texture/manualpad.png",							//	��������摜
	"resource/texture/manualkey.png"						//	��������摜�L�[�{�[�h����
};

//	�M�~�b�N���ꂼ��̕��i�̐�
static const int GimmickGraphSetNum[3] =
{ GRAPH::WMRLength,GRAPH::PresLength,GRAPH::EnerLength };

//	�摜�𕪊�����M�~�b�N�̏��ݒ�
struct GimmickGraphStat
{
	int GraphPosX = 0;										//	�摜�̎Q�Ƃ���E�̒l
	int GraphPosY = 0;										//	�摜�̎Q�Ƃ����̒l
	int GraphWidth = 0;										//	�摜�̎Q�Ƃ��鉡���̒l
	int GraphHeight = 0;									//	�摜�̎Q�Ƃ���c���̒l
};

//	�摜�𕪊�����WMR�M�~�b�N�̏��
static const GimmickGraphStat GimmickWMRGraphStatSet[GRAPH::WMRLength] =
{
	{ 0, 0,12,32},											//	��{���i
	{16, 6, 6,20},											//	�������i
	{24, 0, 8,32},											//	�������i
	{ 0,32,12, 6}											//	�[�_���i
};

//	�摜�𕪊����銴���M�~�b�N�̏��
static const GimmickGraphStat GimmickPresGraphStatSet[GRAPH::PresLength] =
{
	{32,28,32, 4},											//	��{���i
	{48, 4, 2, 4},											//	�������i
	{32,16,32, 5},											//	�{�^�����i
	{48,32,16, 8},											//	�d�g1
	{32,32,16, 8},											//	�d�g2
	{16,32,16, 8}											//	�d�g3
};

//	�摜�𕪊�����ʓd�M�~�b�N�̏��
static const GimmickGraphStat GimmickEnerGraphStatSet[GRAPH::EnerLength] =
{
	{35, 0,10, 8},											//	�o�͑��u
	{35, 8,10, 8},											//	���͑��u
	{48, 4, 2, 4},											//	�������i(���F)
	{48, 8, 2, 4},											//	�������i(�F)
	{48,12, 2, 4}											//	�������i(���F)
};


/*
�摜���\�[�X�Ǘ��N���X
	�摜��ǂݍ��݃n���h���ɂ��ĕۑ���
	���̃N���X���Q�Ƃ��Ďg�p���Ă��炤
*/
class DataLoadResource
{
private:
	bool FinalGameGraph = false;								//	�Q�[���������ɏI������Ƃ��p�̔���

public:

	//	�ϐ�
	/*----------------------�摜------------------------*/
	int GraphGame[GRAPH::HANDLE::GameLength] = { 0 };				//	�Q�[���̉摜
	int GraphPL[GRAPH::PL_GRAPH::PLLength][PL_MAX_GRAPH_WIDTH] = { 0 };	//	�v���C���[�̉摜
	int GraphBlock[GRAPH::BLOCK::BlockLength - 1][4] = { 0 };		//	�u���b�N�̉摜
	int GraphBlockGimmickWire = 0;								//	�X�e�[�W�㉺�̐j���̉摜
	int GraphEDWMR = 0;											//	�G���f�B���O�Ŏg�p�����pWMR�̉摜
	int	GraphGimmickWMR[GRAPH::WMR_PARTS::WMRLength] = { 0 };		//	WMR�̉摜
	int GraphGimmickPres[GRAPH::PRES_PARTS::PresLength] = { 0 };	//	�����̉摜
	int GraphGimmickEner[GRAPH::ENER_PARTS::EnerLength] = { 0 };	//	�ʓd�̉摜

	/*----------------------����------------------------*/
	int FontSet[FONT_SIZE::FontLength] = { 0 };				//	�g�p�t�H���g

	int MaxStageNo = 0;										//	����ςݍő�̃X�e�[�W�ԍ�
	int StageSet = 0;										//	�I�������X�e�[�W

	DataLoadResource() {}									//	�����ݒ�

	//	�摜���\�[�X�Ǘ��N���X�̏���
	void Initia();											//	���߂ɓǂݍ��݉摜��z��ɃZ�b�g����
	void InitiaGame()										//	�Q�[�����������܂Ƃ� 
	{
		//	��x���ǂݍ���łȂ�
		if (FinalGameGraph == false) {

			InitiaPL();										//	�v���C���[�̉摜���[�h
			InitiaBlock();									//	�u���b�N�̉摜���[�h
			InitiaGimmick();								//	�M�~�b�N�̉摜���[�h
			FinalGameGraph = true;							//	�Q�[���̉摜�̓��[�h�����B
		}
	}
	void InitiaPL();										//	���߂ɓǂݍ���PL�摜��z��ɃZ�b�g����
	void InitiaBlock();										//	���߂ɓǂݍ��݃u���b�N�摜��z��ɃZ�b�g����
	void InitiaGimmick();									//	���߂ɓǂݍ��݃M�~�b�N�摜��z��ɃZ�b�g����
	void InitiaGimmickSet(int GimmickNo, int PartsNo);		//	���߂ɓǂݍ��݃M�~�b�N�摜��z��ɃZ�b�g����
	void Final();											//	�Ō�ɓǂݍ��񂾂��ׂẲ摜������
};