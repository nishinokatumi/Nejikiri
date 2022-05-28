#include "CharaPL.h"
#include "DxLib.h"


/*
�v���C���[�̏����N���X
�W�����v�◎����������̐ݒ肩��A�v���C���[�̃��C�����[�v���s���Ă���N���X
*/

//	�����ݒ�FPos��0�ɃZ�b�g
CharaPL::CharaPL()
{
	GraphNo = 0;											//	�������F�v���C���[�̌����ڎ��
	GraphNow = GRAPH::PL_GRAPH::Wait;						//	�������F�摜�f�[�^�̃R�}�w��
	PosX = 0;												//	�������F�v���C���[�̃|�W�V����:X
	PosY = 0;												//	�������F�v���C���[�̃|�W�V����:Y
	ProgressVec.Zero();										//	�������F�v���C���[�i�s�x�N�g��
	Buoyancy = 3;											//	�������F�v���C���[�̃W�����v�ɂ�镂��
	VecX = 1;												//	�������F�v���C���[�̐i�ݕ��̌���:X
	VecY = 1;												//	�������F�v���C���[�̐i�ݕ��̌���:Y
	Time = GetNowCount();									//	�������F���ݎ���

	//	�摜����
	for (int GraphX = 0; GraphX < GRAPH::PL_GRAPH::PLLength; GraphX++)
	{
		//	�摜�̍������珈��

		for (int GraphY = 0; GraphY < 4; GraphY++)
		{
			//	�摜�̏㑤���珈��
			*pPLGraph[GraphX][GraphY] = 0;							//	�������F�v���C���[�̃O���t
		}
	}
}

//	�����ݒ�FPos���w��
CharaPL::CharaPL(int SetPosX, int SetPosY)
{
	GraphNo = 0;											//	�������F�v���C���[�̌����ڎ��
	GraphNow = GRAPH::PL_GRAPH::Wait;							//	�������F�摜�f�[�^�̃R�}�w��
	PosX = SetPosX;											//	�������F�v���C���[�̃|�W�V����:X
	PosY = SetPosY;											//	�������F�v���C���[�̃|�W�V����:Y
	ProgressVec.Zero();										//	�������F�v���C���[�i�s�x�N�g��
	Buoyancy = 3;											//	�������F�v���C���[�̃W�����v�ɂ�镂��
	VecX = 1;												//	�������F�v���C���[�̐i�ݕ��̌���:X
	VecY = 1;												//	�������F�v���C���[�̐i�ݕ��̌���:Y
	Time = GetNowCount();									//	�������F���ݎ���
}

//	�x�N�g���̏���
void CharaPL::Vector()
{
	//	�W�����v���Ă��ĕ��͂�����Ƃ�
	if (Buoyancy > 0)
	{
		Buoyancy -= 1;									//	���͂����Ȃ����Ă���
	}

	ProgressVec.Add(Vector2D(0.0f, (float)((PL_GRAPHVITY - Buoyancy) * VecY)));
}

//	�v���C���[�̉摜��ω�������
void CharaPL::GraphChange()
{
	//	�v���C���[�̃��[�V�����Ŏg�p����
	int GraOld = GraphNo;

	//	�v���C���[�̏d�͂��ʏ�(������)�̎���
	if (VecY == 1)
	{
		//	��ɐi��ł��鎞��
		if (ProgressVec.Y < 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Jump;					//	�v���C���[�̉摜���W�����v�ɕύX
		}

		//	�v���C���[�����ɐi��ł��Ȃ�����
		else if (ProgressVec.X == 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Wait;					//	�v���C���[�̉摜��ҋ@�ɕύX
		}

		//	�v���C���[�����ɐi��ł���̎���
		else if (ProgressVec.X != 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Move;					//	�v���C���[�̉摜���ړ��ɕύX
		}
	}

	//	�v���C���[�̏d�͂����](�����)�̎���
	else
	{
		//	���ɐi��ł��鎞��
		if (ProgressVec.Y > 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Jump;					//	�v���C���[�̉摜���W�����v�ɕύX
		}

		//	�v���C���[�����ɐi��ł��Ȃ�����
		else if (ProgressVec.X == 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Wait;					//	�v���C���[�̉摜��ҋ@�ɕύX
		}

		//	�v���C���[�����ɐi��ł���̎���
		else if (ProgressVec.X != 0)
		{
			GraphNo = GRAPH::PL_GRAPH::Move;					//	�v���C���[�̉摜���ړ��ɕύX
		}
	}

	//	�Ⴄ�s���̏ꍇ�ŏ��̃R�}�Ɏw��
	if (GraphNo != GraOld)
	{
		Time = GetNowCount();								//	�Q�Ƃ��鎞�Ԃ�������
		GraphNow = 0;										//	�R�}���ŏ���
	}

	//�@��~��
	if (GraphNo == GRAPH::PL_GRAPH::Wait && JumpFlag == false)
	{
		//	�O�̎��Ԃ���0.25�b��ɏ���
		if (GetNowCount() - Time > 150)
		{
			Time = GetNowCount();							//	�Q�Ƃ��鎞�Ԃ�������
			GraphNow++;										//	�摜�̃R�}��i�߂�

			//	�ő�l�𒴂��Ȃ��悤�Ƀ��[�v������
			if (GraphNow >= (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = 0;		//	0�ɐݒ�(���[�v����)
			}
		}
	}

	//	�W�����v��
	else if (GraphNo == GRAPH::PL_GRAPH::Jump)
	{
		//	�O�̎��Ԃ���0.25�b��ɏ���
		if (GetNowCount() - Time > 250)
		{
			Time = GetNowCount();							//	�Q�Ƃ��鎞�Ԃ�������
			GraphNow++;										//	�摜�̃R�}��i�߂�

			//	�ő�l�Ŏ~�߂�
			if (GraphNow > (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = GRAPH::PL_GRAPH::PLLength - 1;		//	�Ō�̒l�Ŏ~�߂�
			}
		}
	}

	//	�����Ƃ�
	else if (GraphNo == GRAPH::PL_GRAPH::Move)
	{
		//	�O�̎��Ԃ���0.1�b��ɏ���
		if (GetNowCount() - Time > 100)
		{
			Time = GetNowCount();							//	�Q�Ƃ��鎞�Ԃ�������
			GraphNow++;										//	�摜�̃R�}��i�߂�

			//	�ő�l�𒴂��Ȃ��悤�Ƀ��[�v������
			if (GraphNow >= (GRAPH::PL_GRAPH::PLLength - 1))
			{
				GraphNow = 0;		//	0�ɐݒ�(���[�v����)
			}
		}
	}
}


//	�J��Ԃ����s�F�v���C���[�̑���̔��f�ƌv�Z
void CharaPL::Update()
{
	ProgressVec.Zero();										//	�i�s�x�N�g�����[���ɐݒ�

	KeyboardOperation();

	////	���͂��Q�[���p�b�h�������̎�
	//if (pPLOperation->GamePadReady == false) { KeyboardOperation(); }	//	�L�[�{�[�h�ő��삷��
	//
	////	���͂��Q�[���p�b�h���L���̎�
	//else { GamePadOperation(); }								//	�Q�[���p�b�h�ő��삷��

	Vector();												//	�x�N�g���̏���
	GraphChange();											//	�v���C���[�̉摜��ω�����
}

//	�\������
void CharaPL::Draw()
{
	//	�v���C���[�̏d�͂��ʏ�(������)�̎���
	if (VecY == 1)
	{
		ExtRate = 0;										//	��]��ʏ�
	}

	//	�v���C���[�̏d�͂����](�����)�̎���
	else
	{
		ExtRate = 1;										//	180�x��]������
	}

	//	�v���C���[�̌����̐ݒ�
	if (ProgressVec.X != 0)
	{
		//	�}�C�i�X�����ł����
		if (ProgressVec.X < 0)
		{
			//	�v���C���[�̏d�͂��ʏ킩
			if (VecY == 1)
			{
				PLToFace = true;						//	��
			}
			else
			{
				PLToFace = false;						//	�E
			}
		}

		//	�v���X�����ł����
		else
		{
			//	�v���C���[�̏d�͂��ʏ킩
			if (VecY == 1)
			{
				PLToFace = false;						//	�E
			}
			else
			{
				PLToFace = true;						//	��
			}
		}
	}
	//	�v���C���[�̕\��
	DrawRotaGraph2(
		PosX + WIN_UI_WIDTH,								//	�Q�[����ʂɎ��܂�悤��X�����߂�
		PosY + WIN_UI_HEIGHT,								//	�Q�[����ʂɎ��܂�悤��Y�����߂�
		PL_GRAPH_SIZE / 2, PL_GRAPH_SIZE / 2,				//	���S�ʒu�͉摜�̒���
		PLSize, PI * ExtRate,							//	�傫���E�������w��
		*pPLGraph[GraphNow][GraphNo], true, PLToFace);	//	�\������摜����ށE�R�}����Q��
}

//	�X�V������i�K��	�v���C���[�̈ʒu���m�F���Ȃ���
void CharaPL::DataRoad(MAP_INFO::Stage MapData, Vector2D PLPos)
{
	PosX = (int)PLPos.X;									//	�v���C���[��X����ݒ�
	PosY = (int)PLPos.Y;									//	�v���C���[��Y����ݒ�
	Buoyancy = PL_GRAPHVITY;									//	�d�͂𑊎E����0��
	VecX = 1;												//	�i�ވӎ��̕�����ʏ��
	VecY = 1;												//	�d�͂̕�����ʏ��
	NowMapData = MapData;									//	���肷��X�e�[�W�f�[�^��ǂݍ���
}

//	�v���C���[�𔽓]������ X:0 Y:1
void CharaPL::PLAnti(int XorY)
{
	//	X�̔��]���w�肳�ꂽ�ꍇ
	if (XorY == 0) { VecX *= -1; }							//	�i��X�𔽓]

	//	Y�̔��]���w�肳�ꂽ�ꍇ
	else if (XorY == 1) { VecY *= -1; }						//	�d��Y�𔽓]
}

//	//	�L�[�{�[�h�ł̑���
void CharaPL::KeyboardOperation()
{
	//	�v���C���[���W�����v�ł��邩�ǂ���
	if (JumpFlag == false && (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaJump)
		|| (VecY > 0 && pPLOperation->GetOperation(OPERATION_CATEGORY::CharaUP))
		|| (VecY < 0 && pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDown))))
	{
		//	�W�����v���Ă��Ȃ��ăX�y�[�X�L�[�������Ă���
		Buoyancy = PL_GRAPHVITY + 13;						//	�W�����v�́F1.5�u���b�N�����
		JumpFlag = true;									//	�W�����v������
		pPLSE->SoundPlay(SOUND_NAME::Jump);					//	�����Đ�(�W�����v)
		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	�����~(������)
	}

	//	�i�s����:�E����������:�Ȃ�
	if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaLeft) &&
		pPLOperation->GetOperation(OPERATION_CATEGORY::CharaRight))
	{
		pPLSE->SoundFinal(SOUND_NAME::FootStep);		//	�����~(������)
	}

	//	�i�s����:���E�ǂ��炩�ňړ�
	else if (pPLOperation->Joystick[1][0] >= 0.25 || pPLOperation->Joystick[1][0] <= -0.25)
	{
		ProgressVec.Add(Vector2D(
			(PL_MOV_SPEED * pPLOperation->Joystick[1][0] * VecX),	//	�W���C�X�e�B�b�N�̌X����Ńv���C���[�̑��x���ω�
			0.0));											//	�����̕ύX�͂Ȃ�

		//	�W�����v���Ă��Ȃ���:�����Đ�(������)
		if (JumpFlag == false)pPLSE->SoundPlay(SOUND_NAME::FootStep);

		//	�W�����v���Ă��鎞:�����~(������)
		else pPLSE->SoundFinal(SOUND_NAME::FootStep);
	}
	//	�i�s����:���{�^������
	else if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaLeft))
	{
		//	�_�b�V����
		if (!pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDash))
		{
			ProgressVec.Add(Vector2D((float)(-PL_MOV_SPEED * VecX), 0.0));			//	�i�s�x�N�g���ɃX�s�[�h���ǉ�
		}
		else
		{
			ProgressVec.Add(Vector2D((float)(-PL_MOV_SPEED * VecX) / 2, 0.0f));				//	�i�s�x�N�g���ɃX�s�[�h���ǉ�
		}
		//	�W�����v���Ă��Ȃ���
		if (JumpFlag == false) {
			pPLSE->SoundPlay(SOUND_NAME::FootStep);			//	�����Đ�(������)
		}

	}
	//	�i�s����:�E�{�^������
	else if (pPLOperation->GetOperation(OPERATION_CATEGORY::CharaRight))
	{
		//	�_�b�V����
		if (!pPLOperation->GetOperation(OPERATION_CATEGORY::CharaDash))
		{
			ProgressVec.Add(Vector2D((float)(PL_MOV_SPEED * VecX), 0.0f));				//	�i�s�x�N�g���ɃX�s�[�h���ǉ�
		}
		else
		{
			ProgressVec.Add(Vector2D((float)(PL_MOV_SPEED * VecX) / 2, 0.0f));				//	�i�s�x�N�g���ɃX�s�[�h���ǉ�
		}
		//	�W�����v���Ă��Ȃ���
		if (JumpFlag == false) {
			pPLSE->SoundPlay(SOUND_NAME::FootStep);			//	�����Đ�(������)
		}

	}
	//	�������Ă��Ȃ�
	else
	{
		ProgressVec.Zero();									//	�i�s�x�N�g����0�x�N�g����
		ExtRate = 0;										//	��]�����Ă��Ȃ��悤��
		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	�����~(������)
	}
}

//	�Q�[���p�b�h�ł̑���
//void CharaPL::GamePadOperation()
//{
//	//	�v���C���[���W�����v�ł��邩�ǂ���
//	if (pPLGamePad->OneButton(XINPUT_BUTTON_A) && JumpFlag == false)
//	{
//		//	�W�����v���Ă��Ȃ��ăX�y�[�X�L�[�������Ă���
//		Buoyancy = PL_GRAPHVITY + 13;						//	�W�����v�́F1.5�u���b�N�����
//		JumpFlag = true;									//	�W�����v������
//		pPLSE->SoundPlay(SOUND_NAME::Jump);					//	�����Đ�(�W�����v)
//	}
//
//	//	�i�s����:���E�ǂ��炩�ňړ�
//	if (pPLGamePad->Joystick[1][0] >= 0.25 || pPLGamePad->Joystick[1][0] <= -0.25)
//	{
//		ProgressVec.Add(Vector2D(
//			(PL_MOV_SPEED * pPLGamePad->Joystick[1][0] * VecX),	//	�W���C�X�e�B�b�N�̌X����Ńv���C���[�̑��x���ω�
//			0.0));											//	�����̕ύX�͂Ȃ�
//
//		//	�W�����v���Ă��Ȃ���:�����Đ�(������)
//		if (JumpFlag == false)pPLSE->SoundPlay(SOUND_NAME::FootStep);
//		
//		//	�W�����v���Ă��鎞:�����~(������)
//		else pPLSE->SoundFinal(SOUND_NAME::FootStep);
//	}
//
//	//	�������Ă��Ȃ�
//	else
//	{
//		ProgressVec.Zero();									//	�i�s�x�N�g����0�x�N�g����
//		ExtRate = 0;										//	��]�����Ă��Ȃ��悤��
//		pPLSE->SoundFinal(SOUND_NAME::FootStep);			//	�����~(������)
//	}
//}


void CharaPL::SetMove()
{
	// �ړ��ʂɊ�Â��ăv���C���[�N�^�̍��W���ړ�
	CharMove(&PosX, &PosY,
		&Buoyancy,
		(int)ProgressVec.X, (int)ProgressVec.Y,
		PL_GRAPH_SIZE * 2, &JumpFlag);
}

// �}�b�v�Ƃ̓����蔻��
int CharaPL::CharMove(int* pPosX, int* pPosY, int* pDownSP, int MoveX, int MoveY, int Size, bool* pJumpFlag)
{
	int Dummy = 0;
	int PLMoveSize = Size / 2;

	//	�d�͂ɑΉ�������
	int PLMoveTop, PLMoveBottom;

	//	���ɗ�����
	if (VecY == 1)
	{
		PLMoveTop = *pPosY - PLMoveSize + 24;
		PLMoveBottom = *pPosY + PLMoveSize;
	}

	//	��ɗ�����
	else
	{
		PLMoveTop = *pPosY - PLMoveSize - 1;
		PLMoveBottom = *pPosY + PLMoveSize - 25;
	}

	// �v���C���[�̍���A�E��A�����A�E�������������蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

	// �悸�㉺�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveBottom, &Dummy, &MoveY) == HIT_RESULT::Top)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveBottom, &Dummy, &MoveY) == HIT_RESULT::Top)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveTop, &Dummy, &MoveY) == HIT_RESULT::Bottom)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveTop, &Dummy, &MoveY) == HIT_RESULT::Bottom)
		{
			*pDownSP = PL_GRAPHVITY;
		}

		// �㉺�ړ����������Z
		*pPosY += MoveY;
	}

	// ��ɍ��E�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N
		MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveBottom, &MoveX, &Dummy);

		// �E���̃`�F�b�N
		MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveBottom, &MoveX, &Dummy);

		// ����̃`�F�b�N
		MapHitCheck(*pPosX - PLMoveSize + 10, PLMoveTop, &MoveX, &Dummy);

		// �E��̃`�F�b�N
		MapHitCheck(*pPosX + PLMoveSize - 10, PLMoveTop, &MoveX, &Dummy);

		// ���E�ړ����������Z
		*pPosX += MoveX;
	}

	// �ڒn����
	{
		if (VecY == 1)
		{
			// �v���C���[�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
			if (GetChipParam(*pPosX - (Size * 0.5f) + 10, *pPosY + (Size * 0.5f) + 1) == 0 &&
				GetChipParam(*pPosX + (Size * 0.5f) - 10, *pPosY + (Size * 0.5f) + 1) == 0)
			{
				// ���ꂪ����������W�����v���ɂ���
				*pJumpFlag = true;
			}
			else
			{
				// ���ꂪ�݂�����ڒn���ɂ���
				*pJumpFlag = false;

			}
		}

		//	��ɗ�����
		else
		{
			// �v���C���[�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
			if (GetChipParam(*pPosX - (Size * 0.5f) + 10, *pPosY + -(Size * 0.5f) - 2) == 0 &&
				GetChipParam(*pPosX + (Size * 0.5f) - 10, *pPosY + -(Size * 0.5f) - 2) == 0)
			{
				// ���ꂪ����������W�����v���ɂ���
				*pJumpFlag = true;
			}
			else
			{
				// ���ꂪ�݂�����ڒn���ɂ���
				*pJumpFlag = false;

			}
		}
	}

	// �I��
	return 0;
}

//	�������Ă���u���b�N����
HIT_RESULT CharaPL::MapHitCheck(int PosX, int PosY, int* pMoveX, int* pMoveY)
{
	int AfterX, AfterY;

	// �ړ��ʂ𑫂�
	AfterX = PosX + *pMoveX;
	AfterY = PosY + *pMoveY;

	// �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N
	if (GetChipParam((float)AfterX, (float)AfterY) != GRAPH::BLOCK::Ear)
	{
		float BlockLeftX, BlockTopY, BlockRightX, BlockBottomY;

		// �������Ă�����ǂ��痣���������s��

		// �u���b�N�̏㉺���E�̍��W���Z�o
		BlockLeftX = (float)((int)AfterX / (MAP_CHIP_SIZE * 2)) * MAP_CHIP_SIZE * 2;			// ���ӂ� X ���W
		BlockRightX = (float)(((int)AfterX / (MAP_CHIP_SIZE * 2)) + 1) * MAP_CHIP_SIZE * 2;	// �E�ӂ� X ���W

		BlockTopY = (float)((int)AfterY / (MAP_CHIP_SIZE * 2)) * MAP_CHIP_SIZE * 2;			// ��ӂ� Y ���W
		BlockBottomY = (float)(((int)AfterY / (MAP_CHIP_SIZE * 2)) + 1) * MAP_CHIP_SIZE * 2;	// ���ӂ� Y ���W


		// ��ӂɓ������Ă����ꍇ
		if (*pMoveY > 0)
		{
			// �ړ��ʂ�␳����
			*pMoveY = (int)(BlockTopY - PosY - 1);

			// ��ӂɓ��������ƕԂ�
			return HIT_RESULT::Top;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*pMoveY < 0)
		{
			// �ړ��ʂ�␳����
			*pMoveY = (int)(BlockBottomY - PosY + 0);

			// ���ӂɓ��������ƕԂ�
			return HIT_RESULT::Bottom;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*pMoveX > 0)
		{
			// �ړ��ʂ�␳����
			*pMoveX = (int)(BlockLeftX - PosX - 1);

			// ���ӂɓ��������ƕԂ�
			return HIT_RESULT::Left;
		}

		// �E�ӂɓ������Ă� ���ꍇ
		if (*pMoveX < 0)
		{
			// �ړ��ʂ�␳����
			*pMoveX = (int)(BlockRightX - PosX + 1);

			// �E�ӂɓ��������ƕԂ�
			return HIT_RESULT::Right;
		}

		// �����ɗ�����K���Ȓl��Ԃ�
		return HIT_RESULT::Bottom;
	}

	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return HIT_RESULT::None;
}

// �}�b�v���璊�o
int CharaPL::GetChipParam(float ParamX, float ParamY)
{
	// �����l�֕ϊ�
	int IntX = (int)(ParamX) / (MAP_CHIP_SIZE * 2);
	int IntY = (int)(ParamY) / (MAP_CHIP_SIZE * 2);

	// �}�b�v����͂ݏo�Ă����� 1 ��Ԃ�
	if (IntX >= MAP_WIDTH || IntY >= MAP_HEIGHT || IntX < 0 || IntY < 0)
	{
		return 1;
	}

	// �w��̍��W�ɊY������}�b�v�̏���Ԃ�
	return NowMapData.BlockData[IntY][IntX];
}