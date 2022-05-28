#include "GameUI.h"
#include "DxLib.h"

/*
�Q�[��UI�̊Ǘ��N���X
	�Q�[��UI�𕪊����I��ŕ\������
*/

//	�����ݒ�
GameUI::GameUI()
{
}

//	�Q�[��UI�̏���
void GameUI::Initia(int GameUIGraphNo)
{
	//	���i�̐������J��Ԃ�
	for (int PartsNum = 0; PartsNum < UILength; PartsNum++)
	{
		//	�p�[�c�̐؂�o��
		GameUIGraph[PartsNum]								//	�M�~�b�N�̉摜�z��ɑ��
			= DerivationGraph(								//	�摜�̈ꕔ��V�����摜�ɕϊ�
				UIGraphPos[PartsNum][0], UIGraphPos[PartsNum][1],	//	���o�������̍���̍��W�����
				UIGraphSize[PartsNum][0], UIGraphSize[PartsNum][1],	//	���o��������X��Y�̃s�N�Z���������
				GameUIGraphNo);								//	���o���摜���w��

	}

	//	���i�̐������J��Ԃ�
	for (int PartsNum = 0; PartsNum < UIMenuLength; PartsNum++)
	{
		GameUIFrame[PartsNum]								//	�M�~�b�N�̉摜�z��
			= DerivationGraph(								//	�摜�̈ꕔ��V�����摜�ɕϊ�
				UIFramePos[PartsNum][0], UIFramePos[PartsNum][1],	//	���o�������̍���̍��W�����
				UIFrameSize[PartsNum][0], UIFrameSize[PartsNum][1],	//	���o��������X��Y�̃s�N�Z���������
				GameUIGraphNo);								//	���o���摜���w��
	}

	//	�F�̎擾
	UIColorWhite = GetColor(250, 250, 250);				//	��
	UIColorBlack = GetColor(0, 0, 0);					//	��
}

//	�ŏI����
void GameUI::Final()
{
	//	�Q�[��UI�̐����J��Ԃ�
	for (int UINum = 0; UINum < UI_PARTS::UILength; UINum++)
	{
		DeleteGraph(GameUIGraph[UINum]);					//	UI�̉摜�폜
	}
}

//	�Q�[���̉摜��I�����\������
void GameUI::Draw(int UIPosX, int UIPosY, float Size, int SetUIParts, int VecPadSet)
{
	float Angle = 0;										//	�\���p�x

	//	�����L�[�̍ۂ�
	if (SetUIParts == UI_PARTS::VecPad || SetUIParts == UI_PARTS::LightVec)
	{
		Angle = PI * (float)VecPadSet / 2.0f;				//	�摜�̌�����ύX
	}

	//	�Q�[���̉摜�\��
	DrawRotaGraph2(
		UIPosX, UIPosY,										//	�摜�̈ʒu
		UIGraphCenterPos[SetUIParts][0], UIGraphCenterPos[SetUIParts][1],	//	���S�ʒu�̐ݒ�
		Size, Angle,										//	�T�C�Y�Ɗp�x
		GameUIGraph[SetUIParts],							//	�\������摜
		true, false);										//	�\������摜�̓��߂Ɣ��]
}

//	�Q�[�����̑������
void GameUI::DrawpadUI(bool GamePadReady)
{
	//�@UI�E�B���h�E�̉��̑���
	const float LineTin = 3.0f;

	//	�O���t�̊g��x����
	const int GraphScale = 3;


	//�@�������
	DrawStringToHandle(
		SpaceAX + (int)LineTin,
		SpaceAY + (int)LineTin,
		"�������", UIColorWhite, *pGameUIDraw->FontSet[FONT_SIZE::GameStat]);

	pGameUIDraw->TextOutlLine(
		SpaceAX + (int)LineTin,
		SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
		FONT_SIZE::GameStat, "�������", 0,
		2, UIColorWhite, UIColorBlack);


	//�@�ړ�
	pGameUIDraw->TextOutlLine(
		SpaceBX + 50 + (int)LineTin,
		SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
		FONT_SIZE::GameStat, ":�ړ�", 0,
		2, UIColorWhite, UIColorBlack);


	//	�Q�[���p�b�h���L����
	if (GamePadReady)
	{
		//�@L�X�e�B�b�N
		Draw(SpaceBX + 25, SpaceAY + 20, 1.5f, UI_PARTS::Stick);
		Draw(SpaceBX + 25, SpaceAY + 18, 2, UI_PARTS::L);

		//�@A�{�^��
		Draw(SpaceCX, SpaceAY + 20, (float)GraphScale, UI_PARTS::Button);
		Draw(SpaceCX, SpaceAY + 20, (float)GraphScale, UI_PARTS::A);

		//�@�W�����v
		pGameUIDraw->TextOutlLine(
			SpaceCX + 24 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":�W�����v", 0,
			2, UIColorWhite, UIColorBlack);

		//�@�|�[�Y��ʂ�
		pGameUIDraw->TextOutlLine(
			1170 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, "start�{�^��:�|�[�Y", 0,
			2, UIColorWhite, UIColorBlack);
	}
	//	�L�[�{�[�h���쎞
	else
	{
		//�@�W�����v
		pGameUIDraw->TextOutlLine(
			SpaceCX + 24 + 180 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":�W�����v", 0,
			2, UIColorWhite, UIColorBlack);

		//�@AKey
		Draw(SpaceBX + (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) + 1, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX + 32, SpaceAY + 18, FONT_SIZE::PicUp, "D", 1, 1, UIColorWhite, UIColorBlack);

		//�@DKey
		Draw(SpaceBX - (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) - 1, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX - 18, SpaceAY + 18, FONT_SIZE::PicUp, "A", 1, 1, UIColorWhite, UIColorBlack);

		//�@BKey
		Draw(SpaceBX - (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) + 250, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX - 18 + 250, SpaceAY + 18, FONT_SIZE::PicUp, "B", 1, 1, UIColorWhite, UIColorBlack);

		//�@SpaceKey
		Draw(SpaceCX + 180, SpaceAY + 18, 3, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceCX + 16 + 180, SpaceAY + 18, FONT_SIZE::Normal, "Space", 5, 1, UIColorWhite, UIColorBlack);

		//�@�|�[�Y��ʂ�
		Draw(SpaceDX + 180, SpaceAY + 18, 3, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceDX + 12 + 180, SpaceAY + 18, FONT_SIZE::Normal, "Esc", 3, 1, UIColorWhite, UIColorBlack);

		//�@�|�[�Y��ʂ�
		pGameUIDraw->TextOutlLine(
			SpaceDX + 18 + 180 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":�|�[�Y", 0,
			2, UIColorWhite, UIColorBlack);

		//�@����
		pGameUIDraw->TextOutlLine(
			SpaceBX + 250 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":����", 0,
			2, UIColorWhite, UIColorBlack);
	}
}

//	���j���[�E�B���h�E��\������(���W��)
void GameUI::DrawMenuWindowPos(int MenuPosX1, int MenuPosY1, int MenuPosX2, int MenuPosY2, int Size, int BackColor, int MenuType, int Transparency)
{
	//	���j���[�^�C�v�������ł����
	if (MenuType == MENU_TYPE::BackTransparency)
	{
		//	�w�i�̂ݎw��ʂœ�����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Transparency);
		DrawBox(MenuPosX1, MenuPosY1, MenuPosX2, MenuPosY2, BackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//	�łȂ����
	else
	{
		DrawBox(MenuPosX1, MenuPosY1, MenuPosX2, MenuPosY2, BackColor, true);
	}
	int MenuWidth = MenuPosX2 - MenuPosX1;					//	����
	int MenuHeight = MenuPosY2 - MenuPosY1;					//	�c��

	//	�g�̕\���㉺
	{
		//	��̘g
		DrawRotaGraph3(
			MenuPosX1, MenuPosY1,								//	��ʂ̌��_
			0, 0,												//	�摜�̌��_
			(float)Size, (1.0 / 16.0)* MenuWidth,				//	�g��x��
			PI * (float)3 / 2.0f, GameUIFrame[MENU_PARTS::GoldFrame], false, true, false);

		//	��̘g
		DrawRotaGraph3(
			MenuPosX1, MenuPosY2,								//	��ʂ̌��_
			4, 0,												//	�摜�̌��_
			(float)Size, (1.0 / 16.0)* MenuWidth,				//	�g��x��
			PI * (float)3 / 2.0f, GameUIFrame[MENU_PARTS::GoldFrame], false, false, false);
	}

	//	���j���[�^�C�v�����S���i��\���ł��胁�j���[�̍��������̒��S���i�̑傫�������傫�����
	if ((MenuType == MENU_TYPE::CenterNone) ||
		(MenuHeight / 2) + (UIFrameSize[MENU_PARTS::GoldFrame][0] * Size) >
		((UIFrameSize[MENU_PARTS::LineCenter][1] / 2) - 4)  * Size)
	{
		//	�g�̕\�����E
		{
			//	���̘g
			DrawRotaGraph3(
				MenuPosX1, MenuPosY1,								//	��ʂ̌��_
				4, 0,												//	�摜�̌��_
				(float)Size, (1.0f / 16.0f)* MenuHeight,			//	�g��x��
				0, GameUIFrame[MENU_PARTS::GoldFrame], false, false, false);

			//	�E�̘g
			DrawRotaGraph3(
				MenuPosX2, MenuPosY1,								//	��ʂ̌��_
				0, 0,												//	�摜�̌��_
				(float)Size, (1.0f / 16.0f)* MenuHeight,			//	�g��x��
				0, GameUIFrame[MENU_PARTS::GoldFrame], false, true, false);

		}

		//	�g�̒[�̕\��
		{
			//	����
			DrawRotaGraph2(
				MenuPosX1, MenuPosY1,							//	��ʍ��W
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	�摜���S�ʒuX
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	�摜���S�ʒuY
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	����
			DrawRotaGraph2(
				MenuPosX1, MenuPosY2,							//	��ʍ��W
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	�摜���S�ʒuX
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	�摜���S�ʒuY
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	�E��
			DrawRotaGraph2(
				MenuPosX2, MenuPosY1,							//	��ʍ��W
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	�摜���S�ʒuX
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	�摜���S�ʒuY
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	�E��
			DrawRotaGraph2(
				MenuPosX2, MenuPosY2,							//	��ʍ��W
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	�摜���S�ʒuX
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	�摜���S�ʒuY
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

		}
	}

	//	�g�̒��S���i��\������Ƃ�
	if (MenuType != MENU_TYPE::CenterNone)
	{
		//	��
		DrawRotaGraph2(
			MenuPosX1, MenuPosY1 + MenuHeight / 2,			//	��ʍ��W
			UIFrameCenterPos[MENU_PARTS::LineCenter][0] - 1,	//	�摜���S�ʒuX
			UIFrameCenterPos[MENU_PARTS::LineCenter][1],	//	�摜���S�ʒuY
			Size, 0, GameUIFrame[MENU_PARTS::LineCenter], true, false);

		//	��
		DrawRotaGraph2(
			MenuPosX2, MenuPosY1 + MenuHeight / 2,			//	��ʍ��W
			UIFrameCenterPos[MENU_PARTS::LineCenter][0] + 1,	//	�摜���S�ʒuX
			UIFrameCenterPos[MENU_PARTS::LineCenter][1],	//	�摜���S�ʒuY
			Size, 0, GameUIFrame[MENU_PARTS::LineCenter], true, true);
	}
}