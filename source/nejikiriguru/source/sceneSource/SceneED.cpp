#include "SceneED.h"
#include "SceneSelect.h"

/*
�Q�[���̃G���f�B���O��ʃN���X
	�G���f�B���O�A�j���[�V����
*/

//	�����ݒ�
SceneED::SceneED()
{

}

//	��������
void SceneED::Initia()
{
	ColorBase = GetColor(0, 0, 0);							//	�F��ݒ�(��)
	ColorMain = GetColor(255, 255, 255);					//	�F��ݒ�(��)
	ColorSele = GetColor(255, 255, 0);						//	�F��ݒ�(���F)

	//	�w�i��1���ڂ̏��߂̍��W��ݒ�
	BackPos1 = { GAME_WIN_WIDTH / 2,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	�w�i��2���ڂ̏��߂̍��W��ݒ�
	BackPos2 = { GAME_WIN_WIDTH / 2 - ED_BACK_MAX_X ,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	�w�i��3���ڂ̏��߂̍��W��ݒ�
	BackPos3 = { GAME_WIN_WIDTH / 2 + (-ED_BACK_MAX_X * 2) ,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	MAP�̈ʒu�̌��_��ݒ�
	MapPos = { -ED_BACK_MAX_X * 12 ,-ED_BACK_MAX_Y * 12 };
}

//	�ŏI����
void SceneED::Final()
{

}

//	�X�V����
SceneBase* SceneED::Update()
{
	//	�v�Z�������s��
	SceneBase* pNextScene = this;

	//	���݂̃V�[����
	if (TransitionSet == true)
	{
		//	�t�F�[�h�C��
		if (SceneTransition > 0)
		{
			//	0�������܂ŌJ��Ԃ�
			SceneTransition -= 10;
			if (SceneTransition < 0)
			{
				SceneTransition = 0;
			}
		}

		//	��ʓI�ȏ���
		else
		{
			//	��ʂ��A�N�e�B�u����
			if (GetWindowActiveFlag())
			{
				BaseUpdate();								//	�X�V�����̓��e
			}
		}

	}
	//	���̃V�[����
	else
	{
		//	�t�F�[�h�A�E�g
		if (SceneTransition < 255)
		{
			//	255������܂ŌJ��Ԃ�
			SceneTransition += 10;
			if (SceneTransition > 255)
			{
				SceneTransition = 255;
			}
		}
		//	���̃V�[���ɑJ��
		else
		{
			pNextScene = pNextSceneSave;
		}
	}

	return pNextScene;
}

//	�X�V�����̓��e
void SceneED::BaseUpdate()
{
	//	Esc�{�^����start�{�^���������ꂽ��
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectMenu))
	{
		pNextSceneSave = new SceneSelect();					//	�I����ʂɕύX
		TransitionSet = false;								//	�X�V�������~����
	}

	//	���݂̃R�}����1200�������̍�
	if (EDTime < ED_SIZE)
	{
		EDTime++;											//	�G���f�B���O�^�C�����J�E���g�A�b�v

		//	���݂̃R�}����1200������̍�
		if (EDTime > ED_SIZE)
		{
			EDTime = ED_SIZE;								//	���݂̃R�}�����}�b�N�X(1200)�ɂ���
		}
	}

	//	���݂̃R�}����1�̍�
	if (EDTime == 1)
	{
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	���̍Đ�(���̉�BGM)
	}


	//	���`��Ԃ̃A�j���[�V����
	{
		//	�w�i��1���ڂ̏��߂̍��W��ݒ�
		KeyFrame(
			{	//	�ŏ��̍��W 
				GAME_WIN_WIDTH / 2,													//	X���W
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y���W
			{	//	�ŏI���W
				GAME_WIN_WIDTH / 2,													//	X���W
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y* BackPosReverse) },			//	Y���W
				&BackPos1,
				0, 500);										//	�J�n�R�}���ƍŏI�R�}��

			//	�w�i��2���ڂ̏��߂̍��W��ݒ�
		KeyFrame(
			{	//	�ŏ��̍��W
				GAME_WIN_WIDTH / 2 - ED_BACK_MAX_X ,								//	X���W
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y���W
			{	//	�ŏI���W
				GAME_WIN_WIDTH / 2 + (ED_BACK_MAX_X * 4)* BackPosReverse ,			//	X���W
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y)* BackPosReverse },			//	Y���W
				&BackPos2,
				0, 500);										//	�J�n�R�}���ƍŏI�R�}��

			//	�w�i��2���ڂ̏��߂̍��W��ݒ�
		KeyFrame(
			{	//	�ŏ��̍��W
				GAME_WIN_WIDTH / 2 + (-ED_BACK_MAX_X * 2) ,							//	X���W
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y���W
			{	//	�ŏI���W
				GAME_WIN_WIDTH / 2 + (ED_BACK_MAX_X * 4 * 2)* BackPosReverse ,		//	X���W
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y * BackPosReverse) },			//	Y���W
				&BackPos3,
				0, 500);										//	�J�n�R�}���ƍŏI�R�}��

			//	MAP�̈ʒu�̌��_��ݒ�
		KeyFrame(
			{	//	�ŏ��̍��W
				-ED_BACK_MAX_X * 8 ,												//	X���W
				-ED_BACK_MAX_Y * 8 },												//	Y���W
			{	//	�ŏI���W
				WIN_UI_WIDTH,														//	X���W
				WIN_UI_HEIGHT },													//	Y���W
				&MapPos,
				400, 500);										//	�J�n�R�}���ƍŏI�R�}��

			//	WMR�̑傫����ݒ�
		KeyFrameFloat(
			1,												//	�����l
			100,											//	�ŏI�l
			&EDWMRScale,
			600, 700);										//	�J�n�R�}���ƍŏI�R�}��

		//	WMR�̔Z����ݒ�
		KeyFrameFloat(
			1,												//	�����l
			0,												//	�ŏI�l
			&EDWMRAlpha,
			750, 810);										//	�J�n�R�}���ƍŏI�R�}��

		//	�N���A�����̈ʒu��ݒ�
		KeyFrame(
			{	//	�ŏ��̍��W
				0,																	//	X���W
				-100 },																//	Y���W
			{	//	�ŏI���W
				0,																	//	X���W
				GAME_WIN_HEIGHT / 2 },												//	Y���W
				&GameClearPos,
				800, 850);										//	�J�n�R�}���ƍŏI�R�}��
	}

	//	���݂̃R�}����750�ȏ�ŏ���
	if (EDTime > 750)
	{
		BackAngle = 0;										//	�w�i�摜�̊p�x�𐳂���������
		BackPosReverse = -1;								//	�w�i�摜�̈ʒu�𐳂����ꏊ��
	}
}

//	�\������
void SceneED::Draw()
{
	//	�����w�i���o:�c�̂�
	DrawRotaGraph2(
		BackPos1.X, BackPos1.Y,	//	�w�i�̕`��
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackSky], false, false);

	//	�����w�i���o:�x�߂Ɉړ�
	DrawRotaGraph2(
		BackPos2.X, BackPos2.Y, //	�w�i�̕`��
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackBase], true, true);

	//	�����w�i���o:�x�߂Ɉړ�
	DrawRotaGraph2(
		(BackPos2.X - (BACK_GRAPH_SIZE_X * 4 * BackPosReverse)), BackPos2.Y, //	�w�i�̕`��
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackBase], true, true);


	//	�����w�i���o:����1
	DrawRotaGraph2(
		BackPos3.X, BackPos3.Y, //	�w�i�̕`��
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackMove], true, true);

	//	�����w�i���o:����2
	DrawRotaGraph2(
		(BackPos3.X - (BACK_GRAPH_SIZE_X * 4 * BackPosReverse)), BackPos3.Y, //	�w�i�̕`��
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4�{
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackMove], true, true);

	//	���݂̃R�}����750�������ŏ�������
	if (EDTime < 750)
	{
		//	��ʉE���瓃���f��悤��5�d�˂Ĉړ������ĕ\������
		DrawMap(MapPos.X, MapPos.Y, 0);							//	���]�p�̈�ԉ��̃}�b�v�\��
		for (int DrawMapNum = 1; DrawMapNum < 5; DrawMapNum++)
		{
			//	�����}�b�v��1�}�b�v���ς��ɂ��炵��4��\��
			DrawMap(MapPos.X, MapPos.Y + (MAP_CHIP_SIZE * 2) * (15 * DrawMapNum), 1);
		}

		//	�ҋ@���[�V�����̃v���C���[��\������
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 15,
			16, 32,
			2, 0,
			pSceneDataLoad->GraphPL[GRAPH::PL_GRAPH::Wait][PLGraph], true, true);


		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, (int)(EDWMRAlpha * 255));	//	�u�����h���[�h��ύX���ĕω�����l(���񂾂񔖂�)�ɂ���

		//	�G���f�B���O�p��WMR�̕\��
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 11,
			32, 32,
			2 * EDWMRScale, 0,								//	4�{
			pSceneDataLoad->GraphEDWMR, true, true);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);		//	�u�����h���[�h��ʏ�ɒ���
	}

	//	���݂̃R�}����750�ȏ�ŏ�������
	else
	{
		DrawMap(MapPos.X, MapPos.Y, 2);						//	���]�����}�b�v�̕\��
		DrawMap(MapPos.X, MapPos.Y - (MAP_CHIP_SIZE * 2) * 15, 1);	//	���E�ۂ��Ɣ��]�����悤�Ɍ����邽�߃}�b�v�̈��ɕ\��

		//	�G���f�B���O�p��WMR�̔Z����0�o�Ȃ��Ƃ���
		if (EDWMRAlpha != 0)
		{
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, (int)(EDWMRAlpha * 255));	//	�u�����h���[�h��ύX���ĕω�����l(���񂾂񔖂�)�ɂ���

			//	�G���f�B���O�p��WMR�̕\��
			DrawRotaGraph2(
				MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
				MapPos.Y + (MAP_CHIP_SIZE * 2) * 11,
				32, 32,
				2 * EDWMRScale, 0,							//	4�{
				pSceneDataLoad->GraphEDWMR, true, true);

			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);	//	�u�����h���[�h��ʏ�ɒ���
		}

		pSceneUI->TextOutlLine(								//	�Q�[���N���A�Əォ�牺�낵�ĕ\��
			GAME_WIN_WIDTH / 2,								//	��ʒ���
			GameClearPos.Y,									//	�ω�����l
			FONT_SIZE::Big, "�Q�[���N���A", 6,				//	�傫���T�C�Y�̃t�H���g�Q�[���N���A�ƕ\��
			4, ColorMain, ColorBase);						//	�A�E�g���C���̕��ƐF�̎w��

		//	�ҋ@���[�V�����̃v���C���[��\������
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 12,
			16, 32,
			2, 0,
			pSceneDataLoad->GraphPL[GRAPH::PL_GRAPH::Move][0], true, true);

	}



	//	���݂̃V�[����
	if (TransitionSet == true)
	{
		//	�t�F�[�h�C��
		if (SceneTransition > 0)
		{
			pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
				GetColor(0, 0, 0), SceneTransition);
		}

	}
	//	���̃V�[����
	else
	{
		//	�t�F�[�h�A�E�g
		pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
			GetColor(0, 0, 0), SceneTransition);
	}
}

//	�}�b�v�̕\������
void SceneED::DrawMap(int MapPosX, int MapPosY, int MapNum)
{
	//	�}�b�v�̕`��
	{
		//	�}�b�v�f�[�^��PosY���̏ォ�牺�܂�
		for (int PosY = 0; PosY < MAP_HEIGHT; PosY++)
		{
			//	�}�b�v�f�[�^��PosX���̍�����E�܂�
			for (int PosX = 0; PosX < MAP_WIDTH; PosX++)
			{
				//	�S�[���̐j��
				if (PosY == 0 && PosX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	�\������E���Y���W
						, 2, 0															//	�\������摜�̒��S�ʒu()
						, 2, -PI / 2													//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlockGimmickWire							//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}

				//	�S�[���̐j��
				if (PosY == MAP_HEIGHT - 1 && PosX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, (PosY + 1) * MAP_CHIP_SIZE * 2 + (MapPosY)					//	�\������E���Y���W
						, 2, 0															//	�\������摜�̒��S�ʒu()
						, 2, -PI / 2													//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlockGimmickWire							//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}



				// �u���b�N�̕\��
				if (NowMapData[MapNum].BlockData[PosY][PosX] == GRAPH::BLOCK::Pne)
				{

					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	�\������E���Y���W
						, 0, 0															//	�\������摜�̒��S�ʒu()
						, 2, 0															//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Pne - 1][NowMapData[MapNum].MapPanelNo]	//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]


					//	�u���b�N�ׂ̗𔻒f���⏕���i��t����
					{
						if (PosX < MAP_WIDTH - 1 && NowMapData[MapNum].BlockData[PosY][PosX + 1] != 1)	//	�u���b�N�E��
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	�\������E���X���W
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	�\������E���Y���W
								, 0, 0						//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]	//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}

						if (PosX > 0 && NowMapData[MapNum].BlockData[PosY][PosX - 1] != 1)	//	�u���b�N�E��
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	�\������E���X���W
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	�\������E���Y���W
								, 0, 0													//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]	//	�\������摜
								, true, false);												//	�\������摜�̓��߂Ɣ��]
						}

						if (PosY < MAP_HEIGHT - 1 && NowMapData[MapNum].BlockData[PosY + 1][PosX] != 1)	//	�u���b�N�㕔
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	�\������E���X���W
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	�\������E���Y���W
								, 0, 0													//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][1]	//	�\������摜
								, true, false);												//	�\������摜�̓��߂Ɣ��]
						}

						if (PosY > 0 && NowMapData[MapNum].BlockData[PosY - 1][PosX] != 1)	//	�u���b�N����
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	�\������E���X���W
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	�\������E���Y���W
								, 0, 0													//	�\�����鍶���̍��W
								, 2, 0													//	�T�C�Y�Ɗp�x
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][0]	//	�\������摜
								, true, false);											//	�\������摜�̓��߂Ɣ��]
						}
					}
				}
				else if (NowMapData[MapNum].BlockData[PosY][PosX] == GRAPH::BLOCK::Wal)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Wal - 1][NowMapData[MapNum].MapWallNo]	//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]

					//	�u���b�N�E����
					{
						DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)				//	�\������E���X���W
							, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)						//	�\������E���Y���W
							, 0, 0														//	�\�����鍶���̍��W
							, 2, 0														//	�T�C�Y�Ɗp�x
							, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]	//	�\������摜
							, true, false);												//	�\������摜�̓��߂Ɣ��]

						DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)				//	�\������E���X���W
							, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)						//	�\������E���Y���W
							, 0, 0														//	�\�����鍶���̍��W
							, 2, 0														//	�T�C�Y�Ɗp�x
							, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]	//	�\������摜
							, true, false);												//	�\������摜�̓��߂Ɣ��]
					}
				}
			}
		}

		//	�}�b�v�f�[�^��PosY���̏ォ�牺�܂�
		for (int PosY = 0; PosY < MAP_HEIGHT + 2; PosY += 16)
		{
			//	�}�b�v�f�[�^��PosX���̍�����E�܂�
			for (int PosX = 0; PosX < MAP_WIDTH; PosX += 19)
			{
				DrawRotaGraph2(PosX* MAP_CHIP_SIZE * 2 + (MapPosX)						//	�\������E���X���W
					, PosY* MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)			//	�\������E���Y���W
					, 0, 0																//	�\�����鍶���̍��W
					, 2, 0																//	�T�C�Y�Ɗp�x
					, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Wal - 1][NowMapData[MapNum].MapWallNo]	//	�\������摜
					, true, false);														//	�\������摜�̓��߂Ɣ��]

				//	�u���b�N�E����
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, PosY * MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)		//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]		//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]

					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	�\������E���X���W
						, PosY * MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)		//	�\������E���Y���W
						, 0, 0															//	�\�����鍶���̍��W
						, 2, 0															//	�T�C�Y�Ɗp�x
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]		//	�\������摜
						, true, false);													//	�\������摜�̓��߂Ɣ��]
				}

			}
		}
	}
}