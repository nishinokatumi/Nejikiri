#include "GimmickAll.h"
#include "DxLib.h"

/*------------------------------WMR-------------------------------*/

//�@��������
GimmickWMR::GimmickWMR()
{

}

//	�M�~�b�N�̍X�V����
void GimmickWMR::Update()
{
	//�@WMR�̃}�[�N�����̓_��
	GimmickLightNum += GimmickConvequan;

	if (GimmickLightNum > 255 || GimmickLightNum <= 100)
	{
		//�@�_�ł����邽�߂ɐF�̕ω��ʂ𔽓]������
		GimmickConvequan = -GimmickConvequan;
	}

	//�@����̈��p��
	if (GimmickIsValidOld != GimmickIsValid)
	{
		GimmickIsValidOld = GimmickIsValid;
	}
}

//	�M�~�b�N�̕\������
void GimmickWMR::Draw()
{
	float Angle = 0;										//	�\���p�x

	//	�M�~�b�N���c����
	if (GimmickVecXorY == 1)
	{
		//	�������i���K�v�Ȏ�
		if (GimmickSize > 1)
		{
			//	�������i�̕\���J��Ԃ�
			for (int size_num = 0; size_num < GimmickSize; size_num++)
			{
				DrawRotaGraph2(
					(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH					//�@��ʏ�ł̉摜�̒��S��X���W
					, ((int)GimmickPos.Y + size_num) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT	//�@��ʏ�ł̉摜�̒��S��Y���W
					, 4, 0																	//�@�摜��ł̉摜�̒��S��X���W, Y���W
					, 2, 0																	//	�T�C�Y�Ɗp�x
					, *pGimmickGraNo[GRAPH::WMR_PARTS::Extend]								//	�\������摜
					, true, false);															//	�\������摜�̓��߂Ɣ��]
			}

			//	���[���i�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//�@��ʏ�ł̉摜�̒��S��X���W
				, ((int)GimmickPos.Y + GimmickSize) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT		//�@��ʏ�ł̉摜�̒��S��Y���W
				, 6, 0																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	���[���i�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//�@��ʏ�ł̉摜�̒��S��X���W
				, ((int)GimmickPos.Y) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//�@��ʏ�ł̉摜�̒��S��Y���W
				, 6, 0																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, 0																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]
		}

		//	��{���i�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickCenterPos.Y + WIN_UI_HEIGHT										//�@��ʏ�ł̉摜�̒��S��Y���W
			, 6, 16																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRBase]										//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]

		//�@�ʓd���Ă��邩�ǂ���
		if (GimmickIsEnergization == true)
		{
			//�@�M�~�b�N�̐F�ƃ`�����l���̐F���ꏏ���ǂ���
			if ((GimmickColor == 0) ||
				(GimmickColor == 1 && GimmickYellow == true) ||
				(GimmickColor == 2 && GimmickBlue == true) ||
				(GimmickColor == 3 && GimmickWhite == true))
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, GimmickLightNum);						//�@�摜�̃O���t�B�b�N��Z������

				//	���s���i�̕\��
				DrawRotaGraph2(
					(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH					//�@��ʏ�ł̉摜�̒��S��X���W
					, (int)GimmickCenterPos.Y + WIN_UI_HEIGHT								//�@��ʏ�ł̉摜�̒��S��Y���W
					, 3, 10																	//�@�摜��ł̉摜�̒��S��X���W, Y���W
					, 2, Angle																//	�T�C�Y�Ɗp�x
					, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRLight]							//	�\������摜
					, true, false);															//	�\������摜�̓��߂Ɣ��]

				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);								//�@���ʂ̉摜�ɂ���
			}
		}
	}

	//	�M�~�b�N��������
	else
	{
		Angle = -PI / 2.0f;									//	�\���p�x������

		//	�������i���K�v�Ȏ�
		if (GimmickSize > 1)
		{
			//	�������i�̕\���J��Ԃ�
			for (int size_num = 0; size_num < GimmickSize; size_num++)
			{
				DrawRotaGraph2(
					((int)GimmickPos.X + size_num) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH		//�@��ʏ�ł̉摜�̒��S��X���W
					, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//�@��ʏ�ł̉摜�̒��S��Y���W
					, 4, 0																	//�@�摜��ł̉摜�̒��S��X���W, Y���W
					, 2, -PI / 2.0															//	�T�C�Y�Ɗp�x
					, *pGimmickGraNo[GRAPH::WMR_PARTS::Extend]								//	�\������摜
					, true, false);															//	�\������摜�̓��߂Ɣ��]
			}

			//	���[���i�̕\��
			DrawRotaGraph2(
				((int)GimmickPos.X + GimmickSize) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH		//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 6, 0																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI / 2.0f																//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	���[���i�̕\��
			DrawRotaGraph2(
				((int)GimmickPos.X) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 6, 0																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, -PI / 2.0f																//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	�\������摜
				, true, false);
		}

		//	��{���i�̕\��
		DrawRotaGraph2(
			(int)GimmickCenterPos.X + WIN_UI_WIDTH										//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 6, 16																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRBase]										//	�\������摜		
			, true, false);																	//	�\������摜�̓��߂Ɣ��]

		//�@�ʓd���Ă��邩�ǂ���
		if (GimmickIsEnergization == true)
		{
			//�@�M�~�b�N�̐F�ƃ`�����l���̐F���ꏏ���ǂ���
			if ((GimmickColor == 0) ||
				(GimmickColor == 1 && GimmickYellow == true) ||
				(GimmickColor == 2 && GimmickBlue == true) ||
				(GimmickColor == 3 && GimmickWhite == true))
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, GimmickLightNum);						//�@�摜�̃O���t�B�b�N��Z������

				//	���s���i�̕\��
				DrawRotaGraph2(
					(int)GimmickCenterPos.X + WIN_UI_WIDTH								//�@��ʏ�ł̉摜�̒��S��X���W
					, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//�@��ʏ�ł̉摜�̒��S��Y���W
					, 3, 10																	//�@�摜��ł̉摜�̒��S��X���W, Y���W
					, 2, Angle																//	�T�C�Y�Ɗp�x
					, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRLight]							//	�\������摜
					, true, false);															//	�\������摜�̓��߂Ɣ��]

				SetDrawBlendMode(DX_BASEIMAGE_FORMAT_NORMAL, 0);							//�@���ʂ̉摜�ɂ���
			}
		}
	}
}

//�@�f�[�^���[�h�̊Ǘ�
void GimmickWMR::DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color)
{
	GimmickPos.Set((float)PosX, (float)PosY);				//	���W�w��
	GimmickVecXorY = VecXorY;								//	�����w��	X:0	Y:1
	GimmickSize = Size;										//	�傫��
	GimmickColor = Color;									//�@�F

	//�@�t���O���I�t�ɂ���
	GimmickIsEnergization = false;							//�@�ʓd���Ă��邩�ǂ���
	GimmickIsValid = false;									//�@�M�~�b�N�̔��]
	GimmickIsValidOld = false;								//�@�O��̔���

	//�@WMR�M�~�b�N�̌��������̏ꍇ
	if (GimmickVecXorY == 0)
	{
		//�@�M�~�b�N���S���W�����߂�
		GimmickCenterPos.Set(
			((GimmickPos.X + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2),
			GimmickPos.Y * MAP_CHIP_SIZE * 2);
	}

	//�@WMR�M�~�b�N�̌������c�̏ꍇ
	else
	{
		//�@�M�~�b�N���S���W�����߂�
		GimmickCenterPos.Set(
			GimmickPos.X * MAP_CHIP_SIZE * 2,
			((GimmickPos.Y + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2));
	}
}

//�@�Փ˔���
bool GimmickWMR::ReverseMove(int* PLPosX, int* PLPosY, Vector2D PLVec, int PLSize)
{
	//	�v���C���[���M�~�b�N�ɓ������Ă��邩�̔���
	if (ReverseCheck(*PLPosX + (int)PLVec.X, *PLPosY + (int)PLVec.Y, PLSize))
	{
		Vector2D Difference = Vector2D(0, 0);												//�@Difference�ɍ��W(0, 0)����

		Difference.Set(GimmickCenterPos.X - *PLPosX, GimmickCenterPos.Y - *PLPosY);			//	���S�ƃv���C���[�̋��������߂�

		*PLPosX = (int)GimmickCenterPos.X + (int)Difference.X;								//	�v���C���[�̈ʒu�𔽓]������
		*PLPosY = (int)GimmickCenterPos.Y + (int)Difference.Y;								//	�v���C���[�̈ʒu�𔽓]������
		return true;																		//	���茋�ʁF�������Ă���
	}
	return false;																			//	���茋�ʁF������Ȃ�
}

//�@�M�~�b�N�̓��쏈��
bool GimmickWMR::ReverseCheck(int PLPosX, int PLPosY, int PLSize)
{

	//�@�ʓd���Ă��Ȃ��Ƃ�
	if (GimmickIsEnergization == false)
	{
		//�@WMR�M�~�b�N�̔��]�𖳌���
		GimmickIsValid = false;
		return false;
	}

	//	WMR�M�~�b�N�̌��������̏ꍇ
	if (GimmickVecXorY == 0)
	{
		//	�M�~�b�N��Y���̔���O��������O���
		if ((((int)GimmickPos.Y * MAP_CHIP_SIZE + 8) * 2) < PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE - 8) * 2) > PLPosY)
		{
			GimmickIsValid = false;															//	�M�~�b�N�̓����t��
			return false;
		}


		int PLIntXLeft = (int)(PLPosX - (PLSize / 2) + 16) / (MAP_CHIP_SIZE * 2);			//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu
		int PLIntXRight = (int)(PLPosX + (PLSize / 2) - 16) / (MAP_CHIP_SIZE * 2);			//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu



		//	�M�~�b�N��X���̔���O��������O���
		if ((int)GimmickPos.X > PLIntXLeft || ((int)GimmickPos.X + GimmickSize - 1) < PLIntXRight)
		{
			GimmickIsValid = false;															//	�M�~�b�N�̓����t��
			return false;
		}
	}

	//	WMR�M�~�b�N�̌������c�̏ꍇ
	else
	{
		//	�M�~�b�N��Y���̔���O��������O���
		if ((((int)GimmickPos.X * MAP_CHIP_SIZE + 8) * 2) < PLPosX ||
			(((int)GimmickPos.X * MAP_CHIP_SIZE - 8) * 2) > PLPosX)
		{
			GimmickIsValid = false;															//	�M�~�b�N�̓����t��
			return false;
		}


		int PLIntYTop = (int)(PLPosY - ((int)PLSize / 2) - 2) / (MAP_CHIP_SIZE * 2);		//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu
		int PLIntYBottom = (int)(PLPosY + ((int)PLSize / 2)) / (MAP_CHIP_SIZE * 2);			//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu



		//	�M�~�b�N��X���̔���O��������O���
		if ((int)GimmickPos.Y > PLIntYTop || ((int)GimmickPos.Y + GimmickSize - 1) < PLIntYBottom)
		{
			GimmickIsValid = false;															//	�M�~�b�N�̓����t��
			return false;
		}
	}

	//	�����܂�
	//	�������Ă��鎞

	//�@WMR�M�~�b�N�̔��]��L����
	GimmickIsValid = true;

	//�@�O��̔��肪true�̂Ƃ�
	if (GimmickIsValidOld == true)
	{
		return false;
	}

	return true;
}

/*------------------------------����-------------------------------*/

//�@��������
GimmickPres::GimmickPres()
{

}

//	�M�~�b�N�̍X�V����
void GimmickPres::Update()
{
	//�@����̈��p��
	if (GimmickIsValidOld != GimmickStep)
	{
		GimmickIsValidOld = GimmickStep;
	}
}

//	�M�~�b�N�̕\������
void GimmickPres::Draw()
{
	float Angle = 0;										//	�\���p�x
	const int ButtonDown = 4;								//	�{�^���̒��݋1�`4

	//�@�M�~�b�N�������
	if (GimmickVecXorY == 0)
	{
		//�@�����M�~�b�N���I�t�̂Ƃ�
		if (GimmickIsValid == false)
		{
			//	�{�^�����i�̕\��
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH												//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 2 * ButtonDown	//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 5																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]
		}

		//�@�����M�~�b�N���I���̂Ƃ�
		else
		{
			//	�{�^�����i�̕\��
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH														//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 2 * (ButtonDown - 3)		//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 5																				//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																			//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]										//	�\������摜
				, true, false);																		//	�\������摜�̓��߂Ɣ��]
		}

		//	��{���i�̕\��
		DrawRotaGraph2(
			GimmickCenterPos + WIN_UI_WIDTH													//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 16, 4																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::PRES_PARTS::PresBase]									//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]

		//	��{���i�̏ォ��\��
		if (GimmickIsValid == true)
		{
			//	�������i�̕\��(��)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH - (2 * 3)									//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 1, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�������i�̕\��(�E)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH + (2 * 3)									//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 1, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�d�g1�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18				//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal1]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�d�g2�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18 - 8			//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal2]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�d�g3�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18 - 8 * 2		//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, Angle																	//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal3]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]
		}
	}

	//�@�M�~�b�N��������
	else
	{
		//�@�����M�~�b�N���I�t�̂Ƃ�
		if (GimmickIsValid == false)
		{
			//	�{�^�����i�̕\��
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH												//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 2 * ButtonDown	//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 5																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]
		}

		//�@�����M�~�b�N���I���̂Ƃ�
		else
		{
			//	�{�^�����i�̕\��
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH														//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 2 * (ButtonDown - 3)		//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 5																				//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																				//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]										//	�\������摜
				, true, false);																		//	�\������摜�̓��߂Ɣ��]
		}

		//	��{���i�̕\��
		DrawRotaGraph2(
			GimmickCenterPos + WIN_UI_WIDTH													//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 16, 4																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, PI																			//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::PRES_PARTS::PresBase]									//	�\������摜
			, true, true);																	//	�\������摜�̓��߂Ɣ��]

		//	��{���i�̏ォ��\��
		if (GimmickIsValid == true)
		{
			//	�������i�̕\��(��)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH - (2 * 3)									//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 1, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�������i�̕\��(�E)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH + (2 * 3)									//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//�@��ʏ�ł̉摜�̒��S��Y���W
				, 1, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]

			//	�d�g1�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16				//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18				//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal1]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]


			//	�d�g2�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16					//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18 + 8			//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal2]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]


			//	�d�g3�̕\��
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16					//�@��ʏ�ł̉摜�̒��S��X���W
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18 + 8 * 2		//�@��ʏ�ł̉摜�̒��S��Y���W
				, 16, 4																		//�@�摜��ł̉摜�̒��S��X���W, Y���W
				, 2, PI																		//	�T�C�Y�Ɗp�x
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal3]								//	�\������摜
				, true, false);																//	�\������摜�̓��߂Ɣ��]
		}
	}
}

//�@�f�[�^���[�h�̊Ǘ�
void GimmickPres::DataRoad(int PosX, int PosY, int VecXorY, int Initia, int Color)
{
	GimmickPos.Set((float)PosX, (float)PosY);										//	���W�w��
	GimmickVecXorY = VecXorY;														//	�����w��	X:0	Y:1
	GimmickInitia = Initia;															//	����
	GimmickColor = Color;															//�@�F

	GimmickCenterPos = (int)((GimmickPos.X + 0.5)* MAP_CHIP_SIZE * 2);				//	�M�~�b�N���S���W�����߂�

	GimmickIsValid = (bool)Initia;													//�@�M�~�b�N�̗L�����ǂ����������ɂ���
}

//�@�M�~�b�N�̓��쏈��
bool GimmickPres::ReverseCheck(int PLPosX, int PLPosY, int PLSize)
{

	int PLIntXLeft = (int)(PLPosX - (PLSize / 2) + 16);						//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu
	int PLIntXRight = (int)(PLPosX + (PLSize / 2) - 16);						//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu

		//	�M�~�b�N��X���̔���O��������O���
	if (
		((((int)GimmickPos.X * MAP_CHIP_SIZE) + 4) * 2) > PLIntXLeft ||
		((((int)GimmickPos.X * MAP_CHIP_SIZE) + 4 + 24) * 2) < PLIntXRight
		)
	{
		//�@�����M�~�b�N�𓥂�ł��Ȃ�
		GimmickStep = false;
		return false;
	}

	int PL_int_y_up = (int)(PLPosY - (PLSize / 2));								//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu
	int PL_int_y_down = (int)(PLPosY + (PLSize / 2));							//	�`�b�v�v�Z�p�ɂ����ۂ�Y�̈ʒu

	//�@�M�~�b�N�������
	if (GimmickVecXorY == 0)
	{
		//	�M�~�b�N��Y���̔���O��������O���
		if (
			(((int)GimmickPos.Y * MAP_CHIP_SIZE) * 2) < PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE - 20) * 2) > PLPosY
			)
		{
			//�@�����M�~�b�N�𓥂�ł��Ȃ�
			GimmickStep = false;
			return false;
		}
	}

	//�@�M�~�b�N��������
	else
	{
		//	�M�~�b�N��Y���̔���O��������O���
		if (
			(((int)GimmickPos.Y * MAP_CHIP_SIZE) * 2) > PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE + 20) * 2) < PLPosY
			)
		{
			//�@�����M�~�b�N�𓥂�ł��Ȃ�
			GimmickStep = false;
			return false;
		}
	}

	//�@�����M�~�b�N�𓥂�ł���
	GimmickStep = true;

	//�@�����M�~�b�N�𓥂�ł��� �� �O��̔��肪false
	if (GimmickStep == true && GimmickIsValidOld == false)
	{
		GimmickIsValid = !GimmickIsValid;											//	���΂ɂ���
		return true;
	}
	return false;
}

/*------------------------------�ʓd-------------------------------*/

//�@��������
GimmickEner::GimmickEner()
{

}

//	�M�~�b�N�̕\������
void GimmickEner::Draw()
{
	//�@�o�͑��u
	if (GimmickKind == 0)
	{
		//�@�o�͑��u�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 5, 8																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::ENER_PARTS::OutPut]										//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]
	}

	//�@���͑��u
	else
	{
		//	���͑��u�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 5, 8																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::ENER_PARTS::InPut]										//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]
	}

	//�@�ʓd(��)
	if (GimmickYellow == true)
	{
		//	�����p�[�c(���F)�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 1, 4																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightYellow]								//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]
	}

	//�@�ʓd(��)
	if (GimmickBlue == true)
	{
		//	�����p�[�c(�F)�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 1, 4																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightBlue]									//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]
	}

	//�@�ʓd(��)
	if (GimmickWhite == true)
	{
		//	�����p�[�c(���F)�̕\��
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//�@��ʏ�ł̉摜�̒��S��X���W
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//�@��ʏ�ł̉摜�̒��S��Y���W
			, 1, 4																			//�@�摜��ł̉摜�̒��S��X���W, Y���W
			, 2, Angle																		//	�T�C�Y�Ɗp�x
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightWhite]									//	�\������摜
			, true, false);																	//	�\������摜�̓��߂Ɣ��]
	}
}

//�@�f�[�^���[�h�̊Ǘ�
void GimmickEner::DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color, int Kind)
{
	GimmickPos.Set((float)PosX, (float)PosY);										//	���W�w��
	GimmickVecXorY = VecXorY;														//	�����w��	X:0	Y:1
	GimmickSize = Size;																//	�傫��
	GimmickColor = Color;															//�@�F
	GimmickKind = Kind;																//�@���

	switch (GimmickVecXorY)
	{
	case 1:		//	��
		Angle = PI;
		break;
	case 2:		//	��
		Angle = PI * (3.0f / 2.0f);
		break;
	case 3:		//	�E
		Angle = PI * (1.0f / 2.0f);
		break;
	default:	//	��
		Angle = 0;
		break;
	}

	//�@������̏ꍇ
	if (GimmickVecXorY == 0)
	{
		//	�M�~�b�N���S���W�����߂�
		GimmickCenterPos = (int)((GimmickPos.X + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2);
	}
	else
	{
		//	�M�~�b�N���S���W�����߂�
		GimmickCenterPos = (int)((GimmickPos.Y + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2);
	}
}