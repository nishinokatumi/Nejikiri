#include "GameManager.h"

//�@��������
GameManager::GameManager()
{
}

//�@�ǂݍ��񂾃Q�[���̉摜��z��ɕ�������
void GameManager::Initia()
{
	GameManagerPL.pPLOperation = pGameManagerOperation;			//�@�Q�[���p�b�h�̃|�C���^����
	GameManagerPL.pPLSE = pGameManagerSE;					//�@SE�̃|�C���^����
	int GraphNum = 0;										//�@�摜�̐�
	int PieceNum = 0;										//�@�R�}�̐�

	//	WMR
	for (int Num = 0; Num < GIMMICK_WMR_MAX_NUM; Num++)
	{
		//	�摜�n���h���|�C���^�n��
		for (GraphNum = 0; GraphNum < GRAPH::WMRLength; GraphNum++)
		{
			WMR[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickWMR[GraphNum];
		}
	}

	//	����
	for (int Num = 0; Num < GIMMICK_PRES_MAX_NUM; Num++)
	{
		//	�摜�n���h���|�C���^�n��
		for (GraphNum = 0; GraphNum < GRAPH::PresLength; GraphNum++)
		{
			Pres[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickPres[GraphNum];
		}
	}

	//	�ʓd
	for (int Num = 0; Num < GIMMICK_ENER_MAX_NUM; Num++)
	{
		//	�摜�n���h���|�C���^�n��
		for (GraphNum = 0; GraphNum < GRAPH::EnerLength; GraphNum++)
		{
			Ener[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickEner[GraphNum];
		}
	}

	//	�j��
	GameManagerMap.pGimmickGraph = &pGameManagerDataLoad->GraphBlockGimmickWire;

	//	�p�l��
	for (GraphNum = 0; GraphNum < GRAPH::BlockLength; GraphNum++)
	{
		//	�摜�n���h���|�C���^�n��
		for (PieceNum = 0; PieceNum < 4; PieceNum++)
		{
			GameManagerMap.pMapGraph[GraphNum][PieceNum] = &pGameManagerDataLoad->GraphBlock[GraphNum][PieceNum];
		}
	}

	//	�v���C���[
	for (GraphNum = 0; GraphNum < GRAPH::PLLength; GraphNum++)
	{
		//	�摜�n���h���|�C���^�n��
		for (PieceNum = 0; PieceNum < 4; PieceNum++)
		{
			GameManagerPL.pPLGraph[GraphNum][PieceNum] = &pGameManagerDataLoad->GraphPL[GraphNum][PieceNum];
		}
	}

	StageNo = pGameManagerDataLoad->StageSet;				//�@�I�������X�e�[�W�����̃X�e�[�W�ɃZ�b�g

	ChangeStage(StageNo);									//	�X�e�[�W�ɃZ�b�g
	GameTime = GetTickCount();								//	���Ԃ̓ǂݍ���
	GameStartTime = GameTime;								//	�ŏ��̎��Ԑݒ�
}

//	�J��Ԃ����s�F�Q�[���̑���̔��f�ƌv�Z
void GameManager::Update()
{
	GameTime = GetTickCount();								//	���Ԃ̓ǂݍ���



	switch (GameState)
	{
	case GAMESTATE::Normal:									//	�Q�[���v���C��
		UpdateNormal();
		break;

	case GAMESTATE::Clear:									//	�X�e�[�W�N���A��
		UpdateClear();
		break;

	case GAMESTATE::TimeUP:									//	�^�C���A�b�v��
		UpdateTimeUP();
		break;

	default:
		break;
	}
}

//	�\������
void GameManager::Draw()
{
	//	���ɍs���قǉ�ʎ�O�ɂȂ�

	//	�Q�[���̊�{�`��
	{
		//	�w�i�̕`��
		DrawRotaGraph2(GAME_WIN_WIDTH / 2					//�@��ʏ�ł̉摜�̒��S��X���W
			, GAME_WIN_HEIGHT / 2 - 64 * 6 + (StageNo * 32)	//�@��ʏ�ł̉摜�̒��S��Y���W
			, WIN_PL_WIDTH / 4								//�@�摜��ł̉摜�̒��S��X���W
			, WIN_PL_HEIGHT / 4								//�@�摜��ł̉摜�̒��S��Y���W
			, 4, PI											//	�T�C�Y, �p�x
			, pGameManagerDataLoad->GraphGame[GRAPH::HANDLE::BackGround]	//�@�\������摜
			, false, false);								//�@�\������摜�̓��߂Ɣ��]

		GameManagerMap.DrawMap();							//	�}�b�v�`��
		GameManagerPL.Draw();								//	�v���C���[�`��

		//	WMR�M�~�b�N�̐������\���������s��
		for (int WMRNum = 0; WMRNum < GimmiDataNow.StageWMRData.GimmickWMRNum; WMRNum++)
		{
			WMR[WMRNum].Draw();
		}

		//	�����M�~�b�N�̐������\���������s��
		for (int PresNum = 0; PresNum < GimmiDataNow.StagePresData.GimmickPresNum; PresNum++)
		{
			Pres[PresNum].Draw();
		}

		//	�ʓd�M�~�b�N�̐������\���������s��
		for (int EnerNum = 0; EnerNum < GimmiDataNow.StageEnerData.GimmickEnerNum; EnerNum++)
		{
			Ener[EnerNum].Draw();
		}
	}

	DrawUI();												//	UI�̕`��
}

//	UI�̕\������
void GameManager::DrawUI()
{
	int UIColorWhite = GetColor(250, 250, 250);				//��
	int UIColorRed = GetColor(255, 0, 0);                 //��
	int UIColorBlack = GetColor(0, 0, 0);					//��

	//	����	0 �` WIN_UI_WIDTH
	{

		float LineTin = 3.0f;								//	UI�E�B���h�E�̉��̑���


		//	UI�E�B���h�E�̕\��
		pGameManagerUI->BoxLineWindow(0, 0, WIN_UI_WIDTH, GAME_WIN_HEIGHT, UIColorWhite, LineTin);


		//	���݂̎c�莞�ԕ\��
		//�@�c�莞�Ԃ�11�b�ȏゾ�����玞�Ԃ𔒐F�ŕ\��
		if (GameRemainingTime > 10)
		{
			pGameManagerUI->TextOutlLineFormat(5 + 425 + (int)LineTin,
				5 + (int)LineTin,
				FONT_SIZE::GameStat, "�c�莞��:%d", GameRemainingTime, 2, UIColorWhite, UIColorBlack);
		}

		//�@�c�莞�Ԃ�10�b�ȓ��������玞�Ԃ�ԐF�ŕ\��
		else
		{
			pGameManagerUI->TextOutlLineFormat(5 + 425 + (int)LineTin,
				5 + (int)LineTin,
				FONT_SIZE::GameStat, "�c�莞��:%d", GameRemainingTime, 2, UIColorRed, UIColorBlack);
		}

		//	���݂̃X�e�[�W�\��
		pGameManagerUI->TextOutlLineFormat(
			5 + 1295 + (int)LineTin,
			50 - 45 + (int)LineTin,
			FONT_SIZE::GameStat, "�X�e�[�W:%d", StageNo, 2, UIColorWhite, UIColorBlack);
	}

	//	�E��	WIN_UI_WIDTH + WIN_PL_WIDTH �` GAME_WIN_WIDTH
	{
		float LineTin = 3.0f;								//	UI�E�B���h�E�̉��̑���

		//	UI�E�B���h�E�̕\��
		pGameManagerUI->BoxLineWindow(WIN_UI_WIDTH + WIN_PL_WIDTH, 0, WIN_UI_WIDTH, GAME_WIN_HEIGHT, UIColorWhite, LineTin);

	}

	//	GameUI�̕\��
	pGameManagerGameUI->DrawpadUI(pGameManagerOperation->GamePadReady);

	switch (GameState)
	{
	case GAMESTATE::Normal:									//	�Q�[���v���C��
		DrawNormal();
		break;

	case GAMESTATE::Clear:									//	�X�e�[�W�N���A��
		DrawClear();
		break;

	case GAMESTATE::TimeUP:									//	�^�C���A�b�v��
		DrawTimeUP();
		break;

	default:
		break;
	}
}

//	�Q�[���̒ʏ�^�s���̏����̍X�V
void GameManager::UpdateNormal()
{
	//	�Q�[���̊�{����
	{
		GameManagerMap.Update();							//	�}�b�v�̌v�Z�������s��
		GameManagerPL.Update();								//	�v���C���[�̌v�Z�������s��



		//�����M�~�b�N�̌v�Z�������s��
		for (int PresNum = 0; PresNum < GimmiDataNow.StagePresData.GimmickPresNum; PresNum++)
		{
			Pres[PresNum].Update();							//	�����̌J��Ԃ�����

			//	�����ɐG�ꂽ���ǂ���
			if (Pres[PresNum].ReverseCheck(GameManagerPL.PosX, GameManagerPL.PosY, (MAP_CHIP_SIZE - 8) * 2))
			{
				pGameManagerSE->SoundFinal(SOUND_NAME::Switch);			//	���ʉ��̒�~
				pGameManagerSE->SoundPlay(SOUND_NAME::Switch);			//	���ʉ��̍Đ�

				pGameManagerSE->SoundFinal(SOUND_NAME::Electricity);	//	���ʉ��̒�~
				pGameManagerSE->SoundPlay(SOUND_NAME::Electricity);		//	���ʉ��̍Đ�
			}

			//�@�����F�̃M�~�b�N������@
			//�@�M�~�b�N(��)
			if (Pres[PresNum].GimmickColor == 1)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	�M�~�b�N�̃X�C�b�`���L����
				{
					GimmickYellow = true;					//�@�M�~�b�N���A�����Ă���
					Pres[PresNum].GimmickYellow = true;
				}
				else
				{
					GimmickYellow = false;					//�@�M�~�b�N���A�����Ă��Ȃ�
					Pres[PresNum].GimmickYellow = false;
				}
			}

			//�@�M�~�b�N(��)
			if (Pres[PresNum].GimmickColor == 2)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	�M�~�b�N�̃X�C�b�`���L����
				{
					GimmickBlue = true;						//�@�M�~�b�N���A�����Ă���
					Pres[PresNum].GimmickBlue = true;
				}
				else
				{
					GimmickBlue = false;					//�@�M�~�b�N���A�����Ă��Ȃ�
					Pres[PresNum].GimmickBlue = false;
				}
			}

			//�@�M�~�b�N(��)
			if (Pres[PresNum].GimmickColor == 3)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	�M�~�b�N�̃X�C�b�`���L����
				{
					GimmickWhite = true;					//�@�M�~�b�N���A�����Ă���
					Pres[PresNum].GimmickWhite = true;
				}
				else
				{
					GimmickWhite = false;					//�@�M�~�b�N���A�����Ă��Ȃ�
					Pres[PresNum].GimmickWhite = false;
				}
			}
		}

		//�ʓd�M�~�b�N�̌v�Z�������s��
		for (int EnerNum = 0; EnerNum < GimmiDataNow.StageEnerData.GimmickEnerNum; EnerNum++)
		{
			//�@�t���O�̎󂯓n��
			//�@�M�~�b�N(��)
			if (Ener[EnerNum].GimmickColor == 1)
				Ener[EnerNum].GimmickYellow = true;

			//�@�M�~�b�N(��)�������Ă��Ȃ��Ƃ�
			else
				Ener[EnerNum].GimmickYellow = false;

			//�@�M�~�b�N(��)
			if (Ener[EnerNum].GimmickColor == 2)
				Ener[EnerNum].GimmickBlue = true;

			//�@�M�~�b�N(��)�������Ă��Ȃ��Ƃ�
			else
				Ener[EnerNum].GimmickBlue = false;

			//�@�M�~�b�N(��)
			if (Ener[EnerNum].GimmickColor == 3)
				Ener[EnerNum].GimmickWhite = true;

			//�@�M�~�b�N(��)�������Ă��Ȃ��Ƃ�
			else
				Ener[EnerNum].GimmickWhite = false;
		}

		//	WMR�M�~�b�N�̌v�Z�������s��
		for (int WMRNum = 0; WMRNum < GimmiDataNow.StageWMRData.GimmickWMRNum; WMRNum++)
		{
			//�@WMR�M�~�b�N���S���_�����Ă��Ȃ��Ƃ�
			if (WMR[WMRNum].GimmickColor != 0)
			{
				//�@�����F�̃t���O���I���ɂ��đ���2�̃t���O���I�t�ɂ���
				//�@�M�~�b�N(��)�̂Ƃ�
				if (WMR[WMRNum].GimmickColor == 1)
				{
					//�@�M�~�b�N(��)���A��
					if (GimmickYellow == true)
					{
						//�@�M�~�b�N(��)���N��
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickYellow = true;
					}

					//�@�M�~�b�N(��)���A�����Ă��Ȃ�
					else
					{
						//�@�M�~�b�N(��)���~
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickYellow = false;
					}
				}

				//�@�M�~�b�N(��)�̂Ƃ�
				if (WMR[WMRNum].GimmickColor == 2)
				{
					//�@�M�~�b�N(��)���A��
					if (GimmickBlue == true)
					{
						//�@�M�~�b�N(��)���N��
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickBlue = true;
					}

					//�@�M�~�b�N(��)���A�����Ă��Ȃ�
					else
					{
						//�@�M�~�b�N(��)���~
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickBlue = false;
					}
				}

				//�@�M�~�b�N(��)�̂Ƃ�
				if (WMR[WMRNum].GimmickColor == 3)
				{
					//�@�M�~�b�N(��)���A��
					if (GimmickWhite == true)
					{
						//�@�M�~�b�N(��)���N��
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickWhite = true;
					}

					//�@�M�~�b�N(��)���A�����Ă��Ȃ�
					else
					{
						//�@�M�~�b�N(��)���~
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickWhite = false;
					}
				}
			}

			//	�v���C���[��WMR�ɐG�ꂽ���ǂ���
			if (WMR[WMRNum].ReverseMove(&GameManagerPL.PosX, &GameManagerPL.PosY, GameManagerPL.ProgressVec, (MAP_CHIP_SIZE - 8) * 2))
			{
				pGameManagerSE->SoundFinal(SOUND_NAME::WMRdown);		//	���ʉ��̒�~
				pGameManagerSE->SoundPlay(SOUND_NAME::WMRdown);			//	���ʉ��̍Đ�
				GameManagerPL.PLAnti(WMR[WMRNum].GimmickVecXorY);		//	�v���C���[�̌����𔽓]
			}
			WMR[WMRNum].Update();							//	WMR�̌J��Ԃ�����
		}

		GameManagerPL.SetMove();							//	�v���C���[�̓����𔽉f

		//�@�v���C���[��Y���W��0�������̂Ƃ�
		if (GameManagerPL.PosY < 0)
		{
			pGameManagerSE->SoundFinal(SOUND_NAME::FootStep);			//�@���������~

			GameState = GAMESTATE::Clear;								//	�X�e�[�W�N���A
			pGameManagerSE->SoundFinal(SOUND_NAME::Gole);				//�@�S�[�������~
			pGameManagerSE->SoundPlay(SOUND_NAME::Gole);				//�@�S�[�������Đ�
		}
	}

	//	�Q�[���󋵔���
	{
		GameTime = GetTickCount();							//	�Q�[���̎��Ԃ�ǂ݂���

		//	�ꎞ��~�̎��Ԃ�����ꍇ���ԕ����Z����
		if (GameStopTime > 0)
		{
			GameStartTime += GameStopTime;
			GameStopTime = 0;
		}

		//	�c�莞�Ԍv�Z:60
		GameRemainingTime = 60 - ((GameTime - GameStartTime) / 1000);


		//	�c��̎��Ԃ��Ȃ��Ȃ�����
		if (GameRemainingTime <= 0)
		{
			pGameManagerSE->SoundFinal(SOUND_NAME::FootStep);			//�@���������~

			GameState = GAMESTATE::TimeUP;								//	�^�C���A�b�v
			pGameManagerSE->SoundFinal(SOUND_NAME::GameOver);			//�@�Q�[���I�[�o�[�����~
			pGameManagerSE->SoundPlay(SOUND_NAME::GameOver);			//�@�Q�[���I�[�o�[�����Đ�
		}
	}
}

//	�X�e�[�W�N���A���̏����̍X�V
void GameManager::UpdateClear()
{
	//	�󋵂̓ǂݍ���
	if (MoveFlag == false)
	{
		//�@�ŏI�X�e�[�W�ł͂Ȃ� �� �܂����̃X�e�[�W���������Ă��Ȃ�������
		if (StageNo < MAP_NUM - 1 && pGameManagerDataLoad->MaxStageNo < StageNo + 1)
		{
			pGameManagerDataLoad->MaxStageNo = (StageNo + 1);			//�@���̃X�e�[�W�����
		}

		GameStartTime = GameTime;							//	�ŏ��̎��Ԑݒ�
		MoveFlag = true;									//	Clear��Ԃ�L��
	}

	//	�X�y�[�X�L�[(B�{�^��)��0.5�b��
	if (0.5f < (float)(GameTime - GameStartTime) / 1000.0f
		&& (pGameManagerOperation->GetOperation(OPERATION_CATEGORY::SelectEnter)))
	{
		//�@�S�[��������I����Ă��邩�ǂ���
		if (pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
		{
			MoveFlag = false;								//	Clear��Ԃ𖳌����̃X�e�[�W��
		}

	}

	//	��Ԃ𑱂��Ȃ����N���A�󋵂�10�b��
	if (MoveFlag == false)
	{
		//	�X�e�[�W�������E
		if (StageNo >= MAP_NUM - 1)
		{
			LastStageClear = true;							//�@�ŏI�X�e�[�W�̏ꍇ Flag��true
			return;
		}
		ChangeStage(StageNo + 1);							//�@���̃X�e�[�W��
	}

}

//	�^�C���A�b�v���̏����̍X�V
void GameManager::UpdateTimeUP()
{

	//	�󋵂̓ǂݍ���
	if (MoveFlag == false)
	{
		GameStartTime = GameTime;							//	�ŏ��̎��Ԑݒ�
		MoveFlag = true;									//	Clear��Ԃ�L��
	}

	//	�X�y�[�X�L�[(B�{�^��)��0.5�b��
	if (0.5f < (float)(GameTime - GameStartTime) / 1000.0f
		&& (CheckHitKey(KEY_INPUT_SPACE) ||
			pGameManagerOperation->GetOperation(OPERATION_CATEGORY::SelectEnter)))
	{
		MoveFlag = false;									//	Clear��Ԃ𖳌����̃X�e�[�W��
	}

	//	��Ԃ𑱂��Ȃ����^�C���A�b�v�󋵂�10�b��
	if (MoveFlag == false || 10 < (GameTime - GameStartTime) / 1000)
	{
		ChangeStage(StageNo);								//�@���g���C��Ԃɂ���
		MoveFlag = false;									//�@�v���C���[�̓������~�߂�
	}
}

//	�Q�[���̒ʏ�^�s���̕\������
void GameManager::DrawNormal()
{

}

//	�X�e�[�W�N���A���̕\������
void GameManager::DrawClear()
{
	int Tin = 3;											//�@�����̑���

	//	��ʂ𖾂邭����
	pGameManagerUI->DarkenScreen(WIN_UI_WIDTH, 0, WIN_PL_WIDTH, GAME_WIN_HEIGHT, GetColor(255, 255, 255), 160);


	//	�^�񒆂ɃX�e�[�W�N���A�Əo��
	pGameManagerUI->TextOutlLine(
		GAME_WIN_WIDTH / 2, (GAME_WIN_HEIGHT / 2) - 100,	//�@X���W, Y���W
		FONT_SIZE::Big, "�X�e�[�W�N���A", 7, Tin,			//�@�t�H���g�T�C�Y, �X�e�[�W�N���A, ������, �����̑���
		GetColor(250, 250, 250), GetColor(0, 0, 0));		//�@�����̐F, �A�E�g���C���̐F

	//	�X�e�[�W�������E
	if (StageNo >= MAP_NUM - 1)
	{
		//�@�S�[��������~�����
		if (pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
		{
			//	�uB�{�^���Ŏ��̃V�[���ցv�ƕ\������
			pGameManagerUI->TextBoxWindowCenter(
				GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 10,		//�@X���W, Y���W, ������
				GetColor(255, 255, 255), GetColor(0, 0, 0),				//�@�����̐F, WindowColor
				4.0, Normal, "\"�@�@\"�Ŏ��̃V�[����");					//�@WindowLine�̑���, �����̎��, �e�L�X�g


			//	�Q�[���p�b�h���L�������
			if (pGameManagerOperation->GamePadReady == true)
			{

				//�@B�{�^����UI��\��
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
			}
			//	�����łȂ����
			else
			{
				//	�G���^�[�L�[
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
				pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 50 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
			}
		}
	}

	//	�N���A�󋵂�1�b��
	else if (MoveFlag == true && pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
	{
		//	�uB�{�^���Ŏ��ցv�ƕ\������
		pGameManagerUI->TextBoxWindowCenter(
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 6,			//�@X���W, Y���W, ������
			GetColor(255, 255, 255), GetColor(0, 0, 0),					//�@�����̐F, WindowColor
			4.0, Normal, "\"�@�@\"�Ŏ���");								//�@WindowLine�̑���, �����̎��, �e�L�X�g



		//	�Q�[���p�b�h���L�������
		if (pGameManagerOperation->GamePadReady == true)
		{
			//�@B�{�^����UI��\��
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
		}
		//	�����łȂ����
		else
		{
			//	�G���^�[�L�[
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
			pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 20 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
		}
	}
}

//	�^�C���A�b�v���̕\������
void GameManager::DrawTimeUP()
{
	int Tin = 3;											//�@�����̑���

	//	��ʂ��Â�����
	pGameManagerUI->DarkenScreen(WIN_UI_WIDTH, 0, WIN_PL_WIDTH, GAME_WIN_HEIGHT, GetColor(0, 0, 0), 200);


	//	�^�񒆂Ƀ^�C���A�b�v�Əo��
	pGameManagerUI->TextOutlLine(
		GAME_WIN_WIDTH / 2, (GAME_WIN_HEIGHT / 2) - 100,	//�@X���W, Y���W
		FONT_SIZE::Big, "�^�C���A�b�v", 6, Tin,				//�@�t�H���g�T�C�Y, �X�e�[�W�N���A, ������, �����̑���
		GetColor(150, 0, 0), GetColor(255, 0, 0));			//�@�����̐F, �A�E�g���C���̐F

	//	�N���A�󋵂�1�b��
	if (MoveFlag == true && 2 < (GameTime - GameStartTime) / 1000)
	{
		//	�uB�{�^���Ŏ��ցv�ƕ\������
		pGameManagerUI->TextBoxWindowCenter(
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 6,			//�@X���W, Y���W, ������
			GetColor(255, 255, 255), GetColor(0, 0, 0),					//�@�����̐F, WindowColor
			4.0, Normal, "\"�@�@\"�Ŏ���");								//�@WindowLine�̑���, �����̎��, �e�L�X�g


		//	�Q�[���p�b�h���L�������
		if (pGameManagerOperation->GamePadReady == true)
		{
			//�@B�{�^����UI��\��
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
		}
		//	�����łȂ����
		else
		{
			//	�G���^�[�L�[
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
			pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 20 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
		}
	}
}

//	�N���A���ȂǂɃX�e�[�W�̕ϊ�
void GameManager::ChangeStage(int NextStageNo)
{
	StageNo = NextStageNo;									//	�X�e�[�W�̕ύX

	//�@CSV�t�@�C���̓ǂݍ���
	GameManagerCSV.StageDataLoad(StageNo, &MapNow, &GimmiDataNow);

	GimmickYellow = false;                                  //�@�M�~�b�N(��)���A�����Ă邩
	GimmickBlue = false;									//�@�M�~�b�N(��)���A�����Ă邩
	GimmickWhite = false;                                   //�@�M�~�b�N(��)���A�����Ă邩

	GameManagerMap.DataRoad(MapNow, StageNo);				//	�}�b�v�̃f�[�^�ǂݍ���

	Vector2D PLPosSet = Vector2D(96, 928);					//�@�Q�[���J�n���̃v���C���[�̍��W

	//�@�ŏ��̃X�e�[�W�̂Ƃ�
	if (StageNo == 0)
	{
		PLPosSet.Set(96, 200);								//�@�v���C���[��(96, 200)�̍��W����X�^�[�g
	}

	GameManagerPL.DataRoad(MapNow, PLPosSet);				//	�}�b�v�̃f�[�^�ǂݍ���
	GameManagerPL.ProgressVec.X = 0.1f;						//�@�Q�[���J�n���̃v���C���[�̌������E�����ɂ���

	//�@WMR�M�~�b�N�̐������J��Ԃ��������s��
	for (int Num = 0; Num < GimmiDataNow.StageWMRData.GimmickWMRNum; Num++)
	{
		//	�f�[�^�̓ǂݍ���
		WMR[Num].DataRoad(
			GimmiDataNow.StageWMRData.GimmickWMR[Num][0],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][1],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][2],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][3],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][4]);

		//�@�Q�[���J�n���ɃM�~�b�N�̃t���O��S�ăI���ɂ���
		if (WMR[Num].GimmickColor == 0) { WMR[Num].GimmickIsEnergization = true; }
	}

	//�@�����M�~�b�N�̐������J��Ԃ��������s��
	for (int Num = 0; Num < GimmiDataNow.StagePresData.GimmickPresNum; Num++)
	{
		//	�f�[�^�̓ǂݍ���
		Pres[Num].DataRoad(
			GimmiDataNow.StagePresData.GimmickPres[Num][0],
			GimmiDataNow.StagePresData.GimmickPres[Num][1],
			GimmiDataNow.StagePresData.GimmickPres[Num][2],
			GimmiDataNow.StagePresData.GimmickPres[Num][3],
			GimmiDataNow.StagePresData.GimmickPres[Num][4]);
	}

	//�@�ʓd�M�~�b�N�̐������J��Ԃ��������s��
	for (int Num = 0; Num < GimmiDataNow.StageEnerData.GimmickEnerNum; Num++)
	{
		//	�f�[�^�̓ǂݍ���
		Ener[Num].DataRoad(
			GimmiDataNow.StageEnerData.GimmickEner[Num][0],
			GimmiDataNow.StageEnerData.GimmickEner[Num][1],
			GimmiDataNow.StageEnerData.GimmickEner[Num][2],
			GimmiDataNow.StageEnerData.GimmickEner[Num][3],
			GimmiDataNow.StageEnerData.GimmickEner[Num][4],
			GimmiDataNow.StageEnerData.GimmickEner[Num][5]);
	}



	GameTime = GetTickCount();								//	���Ԃ̓ǂݍ���
	GameStartTime = GameTime;								//	�ŏ��̎��Ԑݒ�
	GameState = GAMESTATE::Normal;							//	�ʏ�^�s
	GameStopTime = 0;										//�@�Q�[�����~�߂����Ԃ�0�ɂ���
	GameRemainingTime = 60;									//	��������
	pGameManagerSE->SoundFinal(SOUND_NAME::Gole);			//	�~�߂�
	pGameManagerSE->SoundFinal(SOUND_NAME::GameOver);		//	�~�߂�
}