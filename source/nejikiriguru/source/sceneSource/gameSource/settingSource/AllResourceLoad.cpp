#include "AllResourceLoad.h"
#include "DxLib.h"


/*
�摜���\�[�X�Ǘ��N���X
	�摜��ǂݍ��݃n���h���ɂ��ĕۑ���
	���̃N���X���Q�Ƃ��Ďg�p���Ă��炤
*/

//	���߂ɓǂݍ��݉摜��z��ɃZ�b�g����
void DataLoadResource::Initia()
{
	//	�t�H���g���t�H���g�̎�ޕ��ǂݍ��ݐݒ肷��
	for (int FontNum = 0; FontNum < FontLength; FontNum++)
	{
		FontSet[FontNum] =
			CreateFontToHandle(
				0,											//	�f�t�H���g�̃t�H���g���g��
				SetFontStat[FontNum].Size,					//	�t�H���g�̑傫����ݒ肷��
				SetFontStat[FontNum].Thick,					//	�t�H���g�̑�����ݒ肷��
				DX_FONTTYPE_NORMAL);						//	�m�[�}���t�H���g
	}

	//	�摜�̖��������J��Ԃ�
	for (int GraphNum = 0; GraphNum < GRAPH::HANDLE::GameLength; GraphNum++)
	{
		GraphGame[GraphNum] = LoadGraph(GraphPath[GraphNum]);	//	�摜�̓ǂݍ���
	}
}

//	���߂ɓǂݍ���PL�摜��z��ɃZ�b�g����
void DataLoadResource::InitiaPL()
{
	//	�摜�̍������珈���F���̉摜����
	for (int GraphNumX = 0; GraphNumX < GRAPH::PL_GRAPH::PLLength; GraphNumX++)
	{
		//	�摜�̏㑤���珈���F�c�̉摜����
		for (int GraphNumY = 0; GraphNumY < 4; GraphNumY++)
		{
			GraphPL[GraphNumX][GraphNumY]					//	�v���C���[�̉摜�z��ɑ��
				= DerivationGraph(							//	�摜�̈ꕔ��V�����摜�ɕϊ�
					PL_GRAPH_SIZE * GraphNumX,				//	���o�������̍��̍��W�����
					PL_GRAPH_SIZE * GraphNumY,				//	���o�������̏�̍��W�����
					PL_GRAPH_SIZE, PL_GRAPH_SIZE,			//	���o��������X��Y�̃s�N�Z���������
					GraphGame[GRAPH::HANDLE::PLHandle]);	//	���o���摜���w��
		}
	}
}

//	���߂ɓǂݍ��݃u���b�N�摜��z��ɃZ�b�g����
void DataLoadResource::InitiaBlock()
{
	//	�摜�̏㑤���珈���F�c�̉摜����
	for (int GraphNumY = 0; GraphNumY < GRAPH::BLOCK::BlockLength; GraphNumY++)
	{
		//	�摜�̍������珈���F���̉摜����
		for (int GraphNumX = 0; GraphNumX < PL_MAX_GRAPH_WIDTH; GraphNumX++)
		{

			GraphBlock[GraphNumY][GraphNumX]				//	�u���b�N�̉摜�z��ɑ��
				= DerivationGraph(							//	�摜�̈ꕔ��V�����摜�ɕϊ�
					MAP_CHIP_SIZE * GraphNumX,				//	���o�������̍��̍��W�����
					MAP_CHIP_SIZE * GraphNumY,				//	���o�������̏�̍��W�����
					MAP_CHIP_SIZE, MAP_CHIP_SIZE,			//	���o��������X��Y�̃s�N�Z���������
					GraphGame[GRAPH::HANDLE::PanelHandle]);	//	���o���摜���w��
		}
	}
	//	�j���̓ǂݍ���
	GraphBlockGimmickWire = DerivationGraph(
		64, 0, 4, 32,
		GraphGame[GRAPH::HANDLE::GimmickHandle]);

	//	�G���f�B���O�pWMR�̓ǂݍ���
	GraphEDWMR = DerivationGraph(
		0, 64, 64, 64,
		GraphGame[GRAPH::HANDLE::GimmickHandle]);
}

//	���߂ɓǂݍ��݃M�~�b�N�摜��z��ɃZ�b�g����
void DataLoadResource::InitiaGimmick()
{
	//	WMR ���� �ʓd�̂R��
	for (int GimmickGraphNum = 0; GimmickGraphNum < 3; GimmickGraphNum++)
	{
		//	WMR ���� �ʓd���ꂼ��̃p�[�c�̐���
		for (int GimmickPartsNum = 0; GimmickPartsNum < GimmickGraphSetNum[GimmickGraphNum]; GimmickPartsNum++)
		{
			InitiaGimmickSet(GimmickGraphNum, GimmickPartsNum);	//	�摜��ǂݍ���
		}
	}
}

//	���߂ɓǂݍ��݃M�~�b�N�摜��z��ɃZ�b�g����
void DataLoadResource::InitiaGimmickSet(int GimmickNo, int PartsNo)
{
	//	WMR�؂�o��
	if (GimmickNo == 0)
	{
		GraphGimmickWMR[PartsNo] = DerivationGraph(			//	�؂�o�������̂���
			GimmickWMRGraphStatSet[PartsNo].GraphPosX,		//	�E�̒l
			GimmickWMRGraphStatSet[PartsNo].GraphPosY,		//	��̒l
			GimmickWMRGraphStatSet[PartsNo].GraphWidth,		//	�����̒l
			GimmickWMRGraphStatSet[PartsNo].GraphHeight,	//	�c���̒l
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	�؂�o���摜
	}

	//	�����؂�o��
	else if (GimmickNo == 1)
	{
		GraphGimmickPres[PartsNo] = DerivationGraph(		//	�؂�o�������̂���
			GimmickPresGraphStatSet[PartsNo].GraphPosX,		//	�E�̒l
			GimmickPresGraphStatSet[PartsNo].GraphPosY,	//	��̒l
			GimmickPresGraphStatSet[PartsNo].GraphWidth,	//	�����̒l
			GimmickPresGraphStatSet[PartsNo].GraphHeight,	//	�c���̒l
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	�؂�o���摜
	}

	//	�ʓd�؂�o��
	else if (GimmickNo == 2)
	{
		GraphGimmickEner[PartsNo] = DerivationGraph(		//	�؂�o�������̂���
			GimmickEnerGraphStatSet[PartsNo].GraphPosX,		//	�E�̒l
			GimmickEnerGraphStatSet[PartsNo].GraphPosY,		//	��̒l
			GimmickEnerGraphStatSet[PartsNo].GraphWidth,	//	�����̒l
			GimmickEnerGraphStatSet[PartsNo].GraphHeight,	//	�c���̒l
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	�؂�o���摜
	}
}

//	�Ō�ɓǂݍ��񂾂��ׂẲ摜������
void DataLoadResource::Final()
{
	int GraphNum = 0;										//	�摜�̐�
	int PieceNum = 0;										//	�R�}��

	//	�摜�̐�������������
	for (GraphNum = 0; GraphNum < GRAPH::HANDLE::GameLength; GraphNum++)
	{
		DeleteGraph(GraphGame[GraphNum]);
	}

	//	�����̐�������������
	for (GraphNum = 0; GraphNum < FONT_SIZE::FontLength; GraphNum++)
	{
		DeleteFontToHandle(FontSet[GraphNum]);
	}

	//	�Q�[�����v���C���Ă�����
	if (FinalGameGraph)
	{
		//	�v���C���[�̉摜�̐�������������
		for (GraphNum = 0; GraphNum < GRAPH::PL_GRAPH::PLLength; GraphNum++)
		{
			//	�R�}�̐�������������
			for (PieceNum = 0; PieceNum < 4; PieceNum++)
			{
				DeleteGraph(GraphPL[GraphNum][PieceNum]);
			}
		}

		//	�u���b�N�̉摜�̐�������������
		for (GraphNum = 0; GraphNum < GRAPH::BLOCK::BlockLength; GraphNum++)
		{
			//	�R�}�̐�������������
			for (PieceNum = 0; PieceNum < 4; PieceNum++)
			{
				DeleteGraph(GraphBlock[GraphNum][PieceNum]);
			}
		}

		DeleteGraph(GraphBlockGimmickWire);					//	���C���[������
		DeleteGraph(GraphEDWMR);							//	�G���f�B���O�p��WMR������

		//	�M�~�b�N�̐���������
		for (int GimmickGraphNum = 0; GimmickGraphNum < 3; GimmickGraphNum++)
		{
			//	���i�̐���������
			for (GraphNum = 0; GraphNum < GimmickGraphSetNum[GimmickGraphNum]; GraphNum++)
			{
				if (GimmickGraphNum == 0)DeleteGraph(GraphGimmickWMR[GraphNum]);		//	WMR
				else if (GimmickGraphNum == 1)DeleteGraph(GraphGimmickPres[GraphNum]);	//	����
				else if (GimmickGraphNum == 2)DeleteGraph(GraphGimmickEner[GraphNum]);	//	�ʓd
			}
		}
	}
}