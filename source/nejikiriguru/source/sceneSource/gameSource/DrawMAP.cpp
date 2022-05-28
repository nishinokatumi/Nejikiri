#include "DrawMAP.h"


/*
�}�b�v�̕\�������N���X
�}�b�v�̉摜�����H���ă`�b�v�ŕ\������N���X

*/

//	�����ݒ�
DrawMAP::DrawMAP()
{

}

//	�J��Ԃ����s�F�p�l���̑���̔��f�ƌv�Z
void DrawMAP::Update()
{

}

//	�\������
void DrawMAP::DrawMap()
{
	//	�}�b�v�̕`��
	{
		//	�}�b�v�f�[�^��MapY���̏ォ�牺�܂�
		for (int MapY = 0; MapY < MAP_HEIGHT; MapY++)
		{
			//	�}�b�v�f�[�^��MapX���̍�����E�܂�
			for (int MapX = 0; MapX < MAP_WIDTH; MapX++)
			{
				//	�S�[���̐j��
				if (MapY == 0 && MapX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	�\������E���X���W
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	�\������E���Y���W
						, 2, 0															//	�\������摜�̒��S�ʒu()
						, 2, -PI / 2													//	�T�C�Y�Ɗp�x
						, *pGimmickGraph												//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}

				//	�S�[���̐j��
				if (MapY == MAP_HEIGHT - 1 && MapX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	�\������E���X���W
						, (MapY + 1) * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	�\������E���Y���W
						, 2, 0															//	�\������摜�̒��S�ʒu()
						, 2, -PI / 2													//	�T�C�Y�Ɗp�x
						, *pGimmickGraph												//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}



				// �u���b�N�̕\��
				if (NowMapData.BlockData[MapY][MapX] == GRAPH::BLOCK::Pne)
				{

					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	�\������E���X���W
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	�\������E���Y���W
						, 0, 0															//	�\������摜�̒��S�ʒu()
						, 2, 0															//	�T�C�Y�Ɗp�x
						, *pMapGraph[GRAPH::BLOCK::Pne - 1][NowMapData.MapPanelNo]		//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]


					//	�u���b�N�ׂ̗𔻒f���⏕���i��t����
					{
						if (MapX < MAP_WIDTH - 1 && NowMapData.BlockData[MapY][MapX + 1] != 1)	//�u���b�N�E��
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	�\������E���X���W
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	�\������E���Y���W
								, 0, 0						//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]				//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}

						if (MapX > 0 && NowMapData.BlockData[MapY][MapX - 1] != 1)		//	�u���b�N�E��
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	�\������E���X���W
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	�\������E���Y���W
								, 0, 0						//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]				//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}

						if (MapY < MAP_HEIGHT - 1 && NowMapData.BlockData[MapY + 1][MapX] != 1)	//	�u���b�N�㕔
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	�\������E���X���W
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	�\������E���Y���W
								, 0, 0						//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][1]				//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}

						if (MapY > 0 && NowMapData.BlockData[MapY - 1][MapX] != 1)		//	�u���b�N����
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	�\������E���X���W
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	�\������E���Y���W
								, 0, 0													//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][0]				//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}
					}
				}
				else if (NowMapData.BlockData[MapY][MapX] == GRAPH::BLOCK::Wal)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	�\������E���X���W
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, *pMapGraph[GRAPH::BLOCK::Wal - 1][NowMapData.MapWallNo]		//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]

					//	�u���b�N�E����
					{
						DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)		//	�\������E���X���W
							, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	�\������E���Y���W
							, 0, 0														//	�\�����鍶���̍��W
							, 2, 0														//	�T�C�Y�Ɗp�x
							, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]					//	�\������摜
							, true, false);												//	�\������摜�̓��߂Ɣ��]

						DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)		//	�\������E���X���W
							, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	�\������E���Y���W
							, 0, 0														//	�\�����鍶���̍��W
							, 2, 0														//	�T�C�Y�Ɗp�x
							, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]					//	�\������摜
							, true, false);												//	�\������摜�̓��߂Ɣ��]
					}
				}
			}
		}

		//	�㉺�̕ǂ̒[�̏���
		for (int MapY = 0; MapY < MAP_HEIGHT + 2; MapY += 16)
		{
			if (MapY >= 16 && MapNo == 0)break;
			//	�}�b�v�f�[�^��MapY���̏ォ�牺�܂�

			//	���E�̕ǂ̒[�̏���
			for (int MapX = 0; MapX < MAP_WIDTH; MapX += 19)
			{
				//	�}�b�v�f�[�^��MapX���̍�����E�܂�
				DrawRotaGraph2(MapX* MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)					//	�\������E���X���W
					, MapY* MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)		//	�\������E���Y���W
					, 0, 0																//	�\�����鍶���̍��W
					, 2, 0																//	�T�C�Y�Ɗp�x
					, *pMapGraph[GRAPH::BLOCK::Wal - 1][NowMapData.MapWallNo]			//	�\������摜
					, true, false);														//	�\������摜�̓��߂Ɣ��]

				//	�u���b�N�E����
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)				//	�\������E���X���W
						, MapY * MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)	//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]						//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]

					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)				//	�\������E���X���W
						, MapY * MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)	//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]						//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}

			}
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//	�u�����h���[�h�ύX�w��̐��l180�̔Z��

		//	�Ԃ��j���ɂ��邽�߂ɐԂ��l�p��킹��
		DrawBox(MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)
			, ((WIN_UI_HEIGHT)) - 4
			, (MAP_WIDTH - 1)*MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)
			, ((WIN_UI_HEIGHT)) + 4, GetColor(255, 0, 0), true);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);		//	�u�����h���[�h�ύX�ʏ��
	}
}

//	�X�e�[�W�ύX���̏����l�ǂݍ���
void DrawMAP::DataRoad(MAP_INFO::Stage MapData, int MapDataNo)
{
	NowMapData = MapData;					//	�\������X�e�[�W�f�[�^��ǂݍ���
	MapNo = MapDataNo;							//	�\������X�e�[�W�i���o�[�ǂݍ���
}