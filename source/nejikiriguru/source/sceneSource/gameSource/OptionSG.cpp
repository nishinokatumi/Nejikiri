#include "OptionSG.h"
#include "PauseSG.h"
#include "DxLib.h"

//	�����ݒ�
OptionSG::OptionSG()
{

}

//	�ꎞ��~��ʂ̏�������
void OptionSG::Initia()
{
	//	�^�u�{�^����������
	{
		//�@�^�u�̐������J��Ԃ�
		for (int Num = 0; Num < OPTION_TAB::OptionTabLength; Num++)
		{
			OptionTab[Num].ButtonNo = Num;								//�@�{�^���̔ԍ�
			OptionTab[Num].ColorBase = ColorBase;						//�@�{�^���̐F(��)
			OptionTab[Num].ColorMain = ColorMain;						//�@�{�^���̐F(��)
			OptionTab[Num].ColorSelect = ColorSelect;					//�@�{�^���̐F(��)
		}

		//	�I���^�u
		//	���ʐݒ�
		{
			OptionTab[OPTION_TAB::VolumeSetting].PosX = (CENTER_SCREEN_POS_X - OPTION_TAB_WIDTH) - 5;		//�@X���W
			OptionTab[OPTION_TAB::VolumeSetting].PosY = CENTER_SCREEN_POS_Y - 300;							//�@Y���W
			OptionTab[OPTION_TAB::VolumeSetting].Width = OPTION_TAB_WIDTH;									//�@�{�^���̑傫��(��)
			OptionTab[OPTION_TAB::VolumeSetting].Height = OPTION_TAB_HEIGHT;								//�@�{�^���̑傫��(�c)
		}

		//	����ݒ�
		{
			OptionTab[OPTION_TAB::Operation].PosX = CENTER_SCREEN_POS_X + 5;								//�@X���W
			OptionTab[OPTION_TAB::Operation].PosY = CENTER_SCREEN_POS_Y - 300;								//�@Y���W
			OptionTab[OPTION_TAB::Operation].Width = OPTION_TAB_WIDTH;										//�@�{�^���̑傫��(��)
			OptionTab[OPTION_TAB::Operation].Height = OPTION_TAB_HEIGHT;									//�@�{�^���̑傫��(�c)
		}

		//	�~(����)
		{
			OptionTab[OPTION_TAB::OptionClose].PosX = (CENTER_SCREEN_POS_X + 5) + OPTION_TAB_WIDTH + 10;	//�@X���W
			OptionTab[OPTION_TAB::OptionClose].PosY = CENTER_SCREEN_POS_Y - 300 + 10;						//�@Y���W
			OptionTab[OPTION_TAB::OptionClose].Width = OPTION_CLOSE_TAB;									//�@�{�^���̑傫��(��)
			OptionTab[OPTION_TAB::OptionClose].Height = OPTION_CLOSE_TAB;									//�@�{�^���̑傫��(�c)
		}
	}
	
	//	���ʐݒ�{�^����������
	{
		//�@�{�^���̐������J��Ԃ�
		for (int Num = 0; Num < VOLUME_BUTTON::VolumeButtonLength; Num++)
		{
			VolumeButton[Num].ButtonNo = Num + 1;								//�@�{�^���̔ԍ�
			VolumeButton[Num].ColorBase = ColorBase;							//�@�{�^���̐F(��)
			VolumeButton[Num].ColorMain = ColorMain;							//�@�{�^���̐F(��)
			VolumeButton[Num].ColorSelect = ColorSelect;						//�@�{�^���̐F(��)
		}

		//	���ʐݒ�{�^��
		//	BGM
		{
			VolumeButton[VOLUME_BUTTON::BGM].PosX = CENTER_SCREEN_POS_X - 450;	//�@X���W
			VolumeButton[VOLUME_BUTTON::BGM].PosY = CENTER_SCREEN_POS_Y;		//�@Y���W
			VolumeButton[VOLUME_BUTTON::BGM].Width = VOLUME_BUTTON_WIDTH;		//�@�{�^���̑傫��(��)
			VolumeButton[VOLUME_BUTTON::BGM].Height = VOLUME_BUTTON_HEIGHT;		//�@�{�^���̑傫��(�c)
		}

		//	SE
		{
			VolumeButton[VOLUME_BUTTON::SE].PosX = CENTER_SCREEN_POS_X - 450;	//�@X���W
			VolumeButton[VOLUME_BUTTON::SE].PosY = CENTER_SCREEN_POS_Y + 100;	//�@Y���W
			VolumeButton[VOLUME_BUTTON::SE].Width = VOLUME_BUTTON_WIDTH;		//�@�{�^���̑傫��(��)
			VolumeButton[VOLUME_BUTTON::SE].Height = VOLUME_BUTTON_HEIGHT;		//�@�{�^���̑傫��(�c)
		}

		//	UI
		{
			VolumeButton[VOLUME_BUTTON::UI].PosX = CENTER_SCREEN_POS_X - 450;	//�@X���W
			VolumeButton[VOLUME_BUTTON::UI].PosY = CENTER_SCREEN_POS_Y + 200;	//�@Y���W
			VolumeButton[VOLUME_BUTTON::UI].Width = VOLUME_BUTTON_WIDTH;		//�@�{�^���̑傫��(��)
			VolumeButton[VOLUME_BUTTON::UI].Height = VOLUME_BUTTON_HEIGHT;		//�@�{�^���̑傫��(�c)
		}

		//	Save
		{
			VolumeButton[VOLUME_BUTTON::Save].PosX = CENTER_SCREEN_POS_X + 400;	//�@X���W
			VolumeButton[VOLUME_BUTTON::Save].PosY = CENTER_SCREEN_POS_Y + 300;	//�@Y���W
			VolumeButton[VOLUME_BUTTON::Save].Width = SAVE_WIDTH;				//�@�{�^���̑傫��(��)
			VolumeButton[VOLUME_BUTTON::Save].Height = SAVE_HEIGHT;				//�@�{�^���̑傫��(�c)
		}
	}
	
	//	����ݒ�{�^����������
	{
		//�@�{�^���̐������J��Ԃ�
		for (int Num = 0; Num < OPRATION_BUTTON::OprationButtonLength; Num++)
		{
			OprationButton[Num].ButtonNo = Num + 1;								//�@�{�^���̔ԍ�
			OprationButton[Num].ColorBase = ColorBase;							//�@�{�^���̐F(��)
			OprationButton[Num].ColorMain = ColorMain;							//�@�{�^���̐F(��)
			OprationButton[Num].ColorSelect = ColorSelect;						//�@�{�^���̐F(��)
		}

		//	���ʐݒ�{�^��
		//	�W�����v����ύX
		{
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].PosX = CENTER_SCREEN_POS_X - 500;		//�@X���W
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].PosY = CENTER_SCREEN_POS_Y + 50;		//�@Y���W
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].Width = OPRATION_BUTTON_WIDTH;		//�@�{�^���̑傫��(��)
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].Height = OPRATION_BUTTON_HEIGHT;		//�@�{�^���̑傫��(�c)
		}

		//	�ړ�����ύX
		{
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].PosX = CENTER_SCREEN_POS_X - 500;		//�@X���W
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].PosY = CENTER_SCREEN_POS_Y + 270;		//�@Y���W
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].Width = OPRATION_BUTTON_WIDTH;		//�@�{�^���̑傫��(��)
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].Height = OPRATION_BUTTON_HEIGHT;		//�@�{�^���̑傫��(�c)
		}
	}

	//	���u��
	LoadOption();
}

//�@�ꎞ��~��ʂ̍X�V����
int OptionSG::Update()
{
	int Returning = 0;										//�@�e�̉�ʂɕԂ��l��0�ɂ���

		//�@���݂̃V�[����
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

		//	��ʂ��A�N�e�B�u����
		if (GetWindowActiveFlag())
		{
			ReturningSave = 0;								//�@�e�̉�ʂɕԂ��l��0�ɂ���

			//	��{�I�ȌJ��Ԃ�����
			TabButton();

			if (ReturningSave == 3)
				TransitionSet = false;						//	�X�V�����̒�~(false)
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
			Returning = ReturningSave;
		}
	}

	//	�����܂�
	return Returning;
}

//	�{�^���̍X�V����
void OptionSG::TabButton()
{
	//	�^�u�̍X�V����
	//�@�^�u�̐������J��Ԃ�
	for (int TabNum = 0; TabNum < OPTION_TAB::OptionTabLength; TabNum++)
	{
		//	�{�^���̑I���I���̓��I�ȐF�̕ω�
		OptionTab[TabNum].UpdateBlend();

		//�@�{�^�����I�𒆂�������
		if (OptionTab[TabNum].ButtonNo == SelectTab)
		{
			//�@�{�^���I�𒆂̃t���O��true�ɂ���
			OptionTab[TabNum].Valid = true;
		}

		//�@�{�^�����I�𒆂���Ȃ�������
		else
		{
			//�@�{�^���I�𒆂̃t���O��false�ɂ���
			OptionTab[TabNum].Valid = false;
		}
	}

	//	�{�^���̏����F�^�u������ȊO
	if (SelectTab != OPTION_TAB::OptionClose)
	{
		//	�{�^���̍X�V����
		//�@�{�^���̐������J��Ԃ�
		for (int ButtonNum = 0; ButtonNum < TabButtonMaxNum[SelectTab]; ButtonNum++)
		{
			//	�I�v�V�����^�u�����ʐݒ�̎�
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	�{�^���̑I���I���̓��I�ȐF�̕ω�
				VolumeButton[ButtonNum].UpdateBlend();

				//�@�{�^�����I�𒆂�������
				if (VolumeButton[ButtonNum].ButtonNo == SelectButtons)
				{
					//�@�{�^���I�𒆂̃t���O��true�ɂ���
					VolumeButton[ButtonNum].Valid = true;
				}

				//�@�{�^�����I�𒆂���Ȃ�������
				else
				{
					//�@�{�^���I�𒆂̃t���O��false�ɂ���
					VolumeButton[ButtonNum].Valid = false;
				}
			}

			//	�I�v�V�����^�u�����ʐݒ�̎�
			if (SelectTab == OPTION_TAB::Operation)
			{
				//	�{�^���̑I���I���̓��I�ȐF�̕ω�
				OprationButton[ButtonNum].UpdateBlend();

				//�@�{�^�����I�𒆂�������
				if (OprationButton[ButtonNum].ButtonNo == SelectButtons)
				{
					//�@�{�^���I�𒆂̃t���O��true�ɂ���
					OprationButton[ButtonNum].Valid = true;
				}

				//�@�{�^�����I�𒆂���Ȃ�������
				else
				{
					//�@�{�^���I�𒆂̃t���O��false�ɂ���
					OprationButton[ButtonNum].Valid = false;
				}
			}
		}
	}

	
	//	�I���̏�
	if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
	{
		//	�I���{�^�������
		SelectButtons--;
		if (SelectButtons < 0)
		{
			SelectButtons = TabButtonMaxNum[SelectTab];		//	�{�^����1�ԉ���
		}
		pOptionSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
		pOptionSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�
	}

	//	�I���̉�
	if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
	{
		//	�I���{�^��������
		SelectButtons++;
		if (SelectButtons > TabButtonMaxNum[SelectTab])
		{
			SelectButtons = 0;								//	�{�^����1�ԏ��
		}
		pOptionSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
		pOptionSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�
	}



	//	�I���{�^�����^�u�̎�
	if (SelectButtons == 0)
	{
		//	�I���̍�
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Select);		//	���ʉ��̒�~
			pOptionSE->SoundPlay(SOUND_NAME::Select);		//	���ʉ��̍Đ�
			//	�I���^�u������
			SelectTab--;
			if (SelectTab < 0)
			{
				SelectTab = OPTION_TAB::OptionTabLength -1;	//	�^�u��1�ԉE��
			}

			SaveFlag = false;								//�@�ۑ������̃e���b�v���\���ɂ���
		}

		//	�I���̉E
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Select);		//	���ʉ��̒�~
			pOptionSE->SoundPlay(SOUND_NAME::Select);		//	���ʉ��̍Đ�
			//	�I���^�u������
			SelectTab++;
			if (SelectTab >= OPTION_TAB::OptionTabLength)
			{
				SelectTab = 0;								//	�^�u��1�ԍ���
			}

			SaveFlag = false;								//�@�ۑ������̃e���b�v���\���ɂ���
		}

		//	����L�[�I��
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Enter);		//	���ʉ��̒�~
			pOptionSE->SoundPlay(SOUND_NAME::Enter);		//	���ʉ��̍Đ�

			//	����^�u�̎�
			if (SelectTab == OPTION_TAB::OptionClose)
			{
				ReturningSave = 3;							//	�ݒ��ʂ���؂�ւ�
			}

			//	����ȊO
			else
			{
				SelectButtons = 1;							//	�I�𕔂��^�u�̈�ԍŏ��ɐݒ�
			}
		}

		//	�������L�[�I��
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			ReturningSave = 3;								//	�ݒ��ʂ���؂�ւ�
			pOptionSE->SoundFinal(SOUND_NAME::Jump);		//	���ʉ��̒�~
			pOptionSE->SoundPlay(SOUND_NAME::Jump);			//	���ʉ��̍Đ�
		}
	}

	//	����ȊO�̎�
	else
	{
		//	�I���̍�
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
		{
			//�@���ʐݒ�
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	�{�^���I�𕔂��o�[�̎�
				if (SelectButtons == VOLUME_BUTTON::BGM + 1 || SelectButtons == VOLUME_BUTTON::SE + 1
					|| SelectButtons == VOLUME_BUTTON::UI + 1)
				{
					pOptionSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
					pOptionSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�

					//�@���ʒ������ɃQ�[�W�X�L�b�v����
					if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectSkip))
					{
						VolumePercent[SelectButtons - 1] -= 10;			//	�w�艹�ʊ�����10������������
					}

					else
					{
						VolumePercent[SelectButtons - 1]--;				//	�w�艹�ʊ�����1������������
					}

					//	�w�艹�ʊ�����0�����ł����
					if (VolumePercent[SelectButtons - 1] < 0)
					{
						VolumePercent[SelectButtons - 1] = 0;			//	0�ɒ���
					}
				}
			}
		}

		//	�I���̉E
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	�{�^���I�𕔂��o�[�̎�
				if (SelectButtons == VOLUME_BUTTON::BGM + 1 || SelectButtons == VOLUME_BUTTON::SE + 1
					|| SelectButtons == VOLUME_BUTTON::UI + 1)
				{
					pOptionSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
					pOptionSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�

					//�@���ʒ������ɃQ�[�W�X�L�b�v����
					if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectSkip))
					{
						VolumePercent[SelectButtons - 1] += 10;			//	�w�艹�ʊ���������������
					}

					else
					{
						VolumePercent[SelectButtons - 1]++;				//	�w�艹�ʊ������㏸������
					}

					//	�w�艹�ʊ�����100��葽���̂ł����
					if (VolumePercent[SelectButtons - 1] > PERCENT_MAX)
					{
						VolumePercent[SelectButtons - 1] = PERCENT_MAX;	//	100�ɒ���
					}
				}
			}
		}

		//	�������L�[�I��
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			SelectButtons = 0;									//	�I�𕔂��^�u�ɐݒ�
			pOptionSE->SoundFinal(SOUND_NAME::Jump);			//	���ʉ��̒�~
			pOptionSE->SoundPlay(SOUND_NAME::Jump);				//	���ʉ��̍Đ�
		}

		//	����L�[�I��
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			//�@���ʐݒ�
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	�{�^���I�𕔂�Save�̎�
				if (SelectButtons == VOLUME_BUTTON::Save + 1)
				{
					//	�ۑ�����
					pOptionGameDate->SaveSoundVolume(
						VolumePercent[VOLUME_BUTTON::SE],
						VolumePercent[VOLUME_BUTTON::BGM],
						VolumePercent[VOLUME_BUTTON::UI]);

					//�@���ʂ�K������
					pOptionSE->SettingVolume(
						(float)VolumePercent[VOLUME_BUTTON::SE] / 100.0f,
						(float)VolumePercent[VOLUME_BUTTON::BGM] / 100.0f,
						(float)VolumePercent[VOLUME_BUTTON::UI] / 100.0f);

					SaveFlag = true;							//�@�ۑ�����
					CountSave = 0;								//�@�ۑ������̃e���b�v�̕\�����Ԃ�������

					pOptionSE->SoundFinal(SOUND_NAME::Enter);	//	���ʉ��̒�~
					pOptionSE->SoundPlay(SOUND_NAME::Enter);	//	���ʉ��̍Đ�

				}
			}

			//�@����ݒ�
			else if (SelectTab == OPTION_TAB::Operation)
			{
				pOptionSE->SoundFinal(SOUND_NAME::Enter);		//	���ʉ��̒�~
				pOptionSE->SoundPlay(SOUND_NAME::Enter);		//	���ʉ��̍Đ�

				//�@����ݒ�̗L���̐؂�ւ�
				*pOperationSetting[SelectButtons - 1] =! *pOperationSetting[SelectButtons - 1];

			}
		}
	}


	//	�����ݒ�̎�
	if (SelectTab == OPTION_TAB::VolumeSetting)
	{
		//�@3��J��Ԃ�
		for (int BarNo = 0; BarNo < VOLUME_BUTTON::VolumeButtonLength - 1; BarNo++)
		{
			//	���ʃo�[�̒����ݒ�
			VolumeBar[BarNo] = (VOLUME_BAR_WIDTH / 100) * (VolumePercent[BarNo]);
		}
	}
}

//	�ꎞ��~��ʂ̕\������
void OptionSG::Draw()
{
	// �V�[�����̕`�揈�����s��
	DrawRotaGraph2(											//	�w�i�̕`��
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64		//�@��ʏ�ł̉摜�̒��S��X���W
		, WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4				//�@��ʏ�ł̉摜�̒��S��Y���W
		, 3.5, 0											//	�T�C�Y, �p�x
		, *pOptionBackGrahandle, false, false);				//	�\������摜, �\������摜�̓���, ���]

	int ColorGray = GetColor(160, 160, 160);				//�@�D�F

		//�@�w�i�g
	pOptionGameUI->DrawMenuWindowPos(
		CENTER_SCREEN_POS_X - (BACK_GROUND_FRAME_WIDTH / 2),			//�@�����X���W
		CENTER_SCREEN_POS_Y - (BACK_GROUND_FRAME_HEIGHT / 2) + 113,		//�@�����Y���W
		CENTER_SCREEN_POS_X + (BACK_GROUND_FRAME_WIDTH / 2),			//�@�E����X���W
		CENTER_SCREEN_POS_Y + (BACK_GROUND_FRAME_HEIGHT / 2) + 113,		//�@�E����Y���W
		8, ColorGray, 0);												//�@�T�C�Y, �F, �^�C�v

	//�@�^�C�g���g
	pOptionGameUI->DrawMenuWindowOrigin(
		CENTER_SCREEN_POS_X - 250, CENTER_SCREEN_POS_Y - 150,			//�@�����X���W, Y���W
		500, 64,														//�@����, �c��
		4, ColorBase,													//�@�T�C�Y, �F
		MENU_TYPE::FullDraw);											//�@�\�����, �w�i�̓����x


//�@�{�^���̐������J��Ԃ�
	for (int Num = 0; Num < OPTION_TAB::OptionTabLength; Num++)
	{
		//	�I���{�^���̕\��
		SelectTabDraw(Num, TabTextString[Num]);
	}


	switch (SelectTab)
	{
	case 0:	//�@���ʐݒ�

		//�@�{�^���̐������J��Ԃ�
		for (int Num = 0; Num < VOLUME_BUTTON::VolumeButtonLength; Num++)
		{
			//	�I���{�^���̕\��
			VolumeButtonDraw(Num, VolumeTextString[Num]);
		}

		VolumeDraw();										//�@���ʐݒ��ʂ̕`�揈��
		break;

	case 1:	//�@����ݒ�

		//�@�{�^���̐������J��Ԃ�
		for (int Num = 0; Num < OPRATION_BUTTON::OprationButtonLength; Num++)
		{
			//	�I���{�^���̕\��
			OprationButtonDraw(Num, OprationTextString[Num]);
		}

		OperationDraw();									//�@����ݒ��ʂ̕`�揈��
		break;

	case 2:	//�@����
		CloseDraw();										//�@����{�^���̉�ʂ̕`�揈��
		break;

	default:
		break;
	}


	if (TransitionSet == true)
	{
		//	�t�F�[�h�C��
		if (SceneTransition > 0)
		{
			pOptionUI->DarkenScreen
			(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//�@X���W, Y���W, ����, �c��
				, GetColor(0, 0, 0), SceneTransition);		//�@�F, �t�F�[�h�C��
		}
	}

	//	���̃V�[����
	else
	{
		//	�t�F�[�h�A�E�g
		pOptionUI->DarkenScreen(
			0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//�@X���W, Y���W, ����, �c��
			, GetColor(0, 0, 0), SceneTransition);			//�@�F, �t�F�[�h�A�E�g
	}
}

//�@���ʐݒ�̕\��
void OptionSG::VolumeDraw()
{
	//�@�^�C�g������
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 66, CENTER_SCREEN_POS_Y - 135,				//�@�����X���W, Y���W
		"���ʐݒ�", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F

	//�@�{�^���̐������J��Ԃ�
	for (int VolumeButtonNum = 0; VolumeButtonNum < VOLUME_BUTTON::VolumeButtonLength - 1; VolumeButtonNum++)
	{
		//�@���ʐݒ�̐���
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 200, CENTER_SCREEN_POS_Y - 40,			//�@�����X���W, Y���W
			"���@���@�łP,�@+�@Shift�L�[��10�ړ�", ColorBase,				//�@�\�����镶��, �F
			*pOptionUI->FontSet[FONT_SIZE::Explanation]);					//�@�t�H���g�̎�ށ@


		//�@BGM�Q�[�W�̘g�̐F(���F)
		DrawBox(
			CENTER_SCREEN_POS_X + (VOLUME_BAR_WIDTH / 2) + 1,										//�@�����X���W
			(CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100)) - 1,								//�@�����Y���W
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2) - 1,										//�@�E����X���W
			(CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100) + 1,	//�@�E����Y���W
			ColorBase, true);																		//�@�F, �h��Ԃ����ǂ���


		//�@BGM�Q�[�W�̐F(���F)
		DrawBox(
			CENTER_SCREEN_POS_X + (VOLUME_BAR_WIDTH / 2),											//�@�����X���W
			CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100),										//�@�����Y���W
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2),											//�@�E���X���W
			CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100,			//�@�E���Y���W
			ColorBase, true);																		//�@�F, �h��Ԃ����ǂ���

		//�@BGM�Q�[�W�̐F(���F)
		DrawBox(
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2),											//�@�����X���W
			CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100),										//�@�����Y���W
			(CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2)) + VolumeBar[VolumeButtonNum],			//�@�E���X���W
			CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100,			//�@�E���Y���W
			ColorSelect, true);																		//�@�F, �h��Ԃ����ǂ���


		//�@���ʂ̐��l�̘g(���F)
		DrawBox(
			CENTER_SCREEN_POS_X + 350 - 3,								//�@�����X���W
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100) - 3,			//�@�����Y���W
			CENTER_SCREEN_POS_X + 450 + 3,								//�@�E���X���W
			CENTER_SCREEN_POS_Y + 50 + (VolumeButtonNum * 100) + 3,		//�@�E���Y���W
			ColorMain, true);											//�@�F, �h��Ԃ����ǂ���

		//�@���ʂ̐��l�̔w�i(���F)
		DrawBox(
			CENTER_SCREEN_POS_X + 350,									//�@�����X���W
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100),				//�@�����Y���W
			CENTER_SCREEN_POS_X + 450,									//�@�E���X���W
			CENTER_SCREEN_POS_Y + 50 + (VolumeButtonNum * 100),			//�@�E���Y���W
			ColorBase, true);											//�@�F, �h��Ԃ����ǂ���

		//�@���ʂ̐��l�̕\��
		pOptionUI->TextOutlLineFormat(
			CENTER_SCREEN_POS_X + 380,									//�@�����X���W
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100) + 5,			//�@�����Y���W
			FONT_SIZE::GameStat,										//�@�t�H���g�^�C�v
			"%d", VolumePercent[VolumeButtonNum], 2,					//�@�\�����镶���̃|�C���^, �\�����镶��, �T�C�Y
			ColorMain, ColorBase);										//�@�F, �A�E�g���C���̐F
	
		//�@�ۑ�����,�e���b�v�̕\���J�E���g��500�ȉ��̂Ƃ��ɕ\��
		if (SaveFlag && CountSave <= 500)
		{
			//�@�g
			pOptionGameUI->DrawMenuWindowOrigin(
				CENTER_SCREEN_POS_X - 200, CENTER_SCREEN_POS_Y + 305,			//�@������X���W, Y���W
				400, 80,														//�@����, �c��
				2, ColorBase,													//�@�T�C�Y, �F
				MENU_TYPE::CenterNone);											//�@�\�����, �w�i�̓����x

			//�@�ۑ������̃e���b�v
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 100, CENTER_SCREEN_POS_Y + 328,			//�@�����X���W, Y���W
				"�ۑ����܂���", ColorMain,										//�@�\�����镶��, �F
				*pOptionUI->FontSet[FONT_SIZE::PicUp]);							//�@�t�H���g�̎��
		
			CountSave++;									//�@�\�����鎞�Ԃ̃J�E���g

			if (CountSave == 500)							//�@�\�����Ԃ��I�������
				SaveFlag = false;							//�@�ۑ������̃e���b�v���\���ɂ���
		}

	}

}

//�@����ݒ�̕\��
void OptionSG::OperationDraw()
{
	//�@�^�C�g������
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 65, CENTER_SCREEN_POS_Y - 135,			//�@�����X���W, Y���W
		"����ݒ�", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);	//�@�\�����镶��, �F, �t�H���g�̎��

	//�@2��J��Ԃ�
	for (int BackGroundNum = 0; BackGroundNum < OPRATION_BUTTON::OprationButtonLength; BackGroundNum++)
	{
		pOptionGameUI->DrawMenuWindowOrigin(
			CENTER_SCREEN_POS_X - 150,									//�@������X���W
			CENTER_SCREEN_POS_Y - 24 + (BackGroundNum * 230),			//�@������Y���W
			700, 180,													//�@����, �c��
			2, ColorBase,												//�@�T�C�Y, �F
			MENU_TYPE::CenterNone);										//�@�\�����
	}

	//�@����
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 26,			//�@�����X���W, Y���W
		"W�L�[,���L�[(���]���FS�L�[,���L�[)�ł�",						//�@�\�����镶��
		ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);				//�@�F, �t�H���g�̎��

	//�@����
	if (*pOperationSetting[ArrowKeyJump])
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 76,		//�@�����X���W, Y���W
			"�W�����v�����L�������܂����B",							//�@�\�����镶��
			ColorSelect, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�F, �t�H���g�̎��
	}

	//�@����
	else
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 76,		//�@�����X���W, Y���W
			"�W�����v����𖳌������܂����B",							//�@�\�����镶��
			ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//�@�F, �t�H���g�̎��
	}

	//�@����
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 256,			//�@�����X���W, Y���W
		"�����L�[�ł�",													//�@�\�����镶��
		ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);				//�@�F, �t�H���g�̎��

	//�@����
	if (*pOperationSetting[ArrowKeyMove])
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 306,		//�@�����X���W, Y���W
			"�ړ������L�������܂����B",								//�@�\�����镶��
			ColorSelect, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�F, �t�H���g�̎��
	}
	
	//�@����
	else
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 306,		//�@�����X���W, Y���W
			"�ړ�����𖳌������܂����B",								//�@�\�����镶��
			ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//�@�F, �t�H���g�̎��
	}

}

//�@����{�^���̉�ʂ̕`�揈��
void OptionSG::CloseDraw()
{
	if (CountDraw <= 1200)
		CountDraw++;										//�@�����ʂŕ`�悳��Ă��ʂ̕\�����Ԃ̃J�E���g
	else
		CountDraw = 1;

	//�@�^�C�g������
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 66, CENTER_SCREEN_POS_Y - 135,				//�@�����X���W, Y���W
		" ����", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F

	//�@���̃Q�[���̓��m��
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 160, CENTER_SCREEN_POS_Y - 40,								//�@�����X���W, Y���W
		" ������Ƃ������m��", ColorBase, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//�@�\�����镶��, �F, �t�H���g�^�C�v

	//�@�g
	pOptionGameUI->DrawMenuWindowOrigin(
		CENTER_SCREEN_POS_X - 400, CENTER_SCREEN_POS_Y + 40,			//�@������X���W, Y���W
		800, 320,														//�@����, �c��
		2, ColorBase,													//�@�T�C�Y, �F
		MENU_TYPE::CenterNone);											//�@�\�����, �w�i�̓����x

	//�@���m���̐�
	for (int TriviaBoxNum = 0; TriviaBoxNum < 4; TriviaBoxNum++)
	{
		//�@������
		DrawBox(
			CENTER_SCREEN_POS_X - 120 + (TriviaBoxNum * 80),								//�@�����X���W
			CENTER_SCREEN_POS_Y + 100,														//�@�����Y���W
			(CENTER_SCREEN_POS_X - 120 + (TriviaBoxNum * 80)) - TRIVIABOX_SIDE,				//�@�E���X���W
			(CENTER_SCREEN_POS_Y + 100) - TRIVIABOX_SIDE,									//�@�E���Y���W
			ColorMain, true);																//�@�F, �h��Ԃ����ǂ���

	//�@���F����
		DrawBox(
			CENTER_SCREEN_POS_X - 120 + (TriviaNum * 80),									//�@�����X���W
			CENTER_SCREEN_POS_Y + 100,														//�@�����Y���W
			(CENTER_SCREEN_POS_X - 120 + (TriviaNum * 80)) - TRIVIABOX_SIDE,				//�@�E���X���W
			(CENTER_SCREEN_POS_Y + 100) - TRIVIABOX_SIDE,									//�@�E���Y���W
			ColorSelect, true);																//�@�F, �h��Ԃ����ǂ���

	}

	//�@�J�E���g�@0�`300
	if ((0 < CountDraw) && (CountDraw <= 300))
	{
		//�@���m�������J��Ԃ�
		for (int TriviaNum = 0; TriviaNum < 2; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 320, CENTER_SCREEN_POS_Y + 170 + (TriviaNum * 50),			//�@�����X���W, Y���W
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F, �t�H���g�^�C�v
		}

		TriviaNum = 0;										//�@���m���̔ԍ��F0
	}

	//�@�J�E���g�@300�`600
	else if ((300 < CountDraw) && (CountDraw <= 600))
	{
		//�@���m�������J��Ԃ�
		for (int TriviaNum = 2; TriviaNum < 4; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 240, CENTER_SCREEN_POS_Y + 170 + ((TriviaNum - 2) * 50),		//�@�����X���W, Y���W
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F, �t�H���g�^�C�v
		}

		TriviaNum = 1;										//�@���m���̔ԍ��F1
	}

	//�@�J�E���g�@600�`900
	else if ((600 < CountDraw) && (CountDraw <= 900))
	{
		//�@���m�������J��Ԃ�
		for (int TriviaNum = 4; TriviaNum < 7; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 240, CENTER_SCREEN_POS_Y + 160 + ((TriviaNum - 4) * 50),		//�@�����X���W, Y���W
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F, �t�H���g�^�C�v
		}

		TriviaNum = 2;										//�@���m���̔ԍ��F2
	}

	//�@�J�E���g�@900�`1200
	else if ((900 < CountDraw) && (CountDraw <= 1200))
	{
		//�@���m�������J��Ԃ�
		for (int TriviaNum = 7; TriviaNum < OptionSG::TriviaLength; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 280, CENTER_SCREEN_POS_Y + 160 + ((TriviaNum - 7) * 50),		//�@�����X���W, Y���W
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//�@�\�����镶��, �F, �t�H���g�^�C�v
		}

		TriviaNum = 3;										//�@���m���̔ԍ��F3
	}

}

//	�I���^�u�̕\��
void OptionSG::SelectTabDraw(int FontNo, const char* pText)
{
	//�@�{�^���̕\������
	OptionTab[FontNo].Draw(SelectButtons != 0 && FontNo == SelectTab);

	//�@�I��
	if (OptionTab[FontNo].Valid)
	{
		DrawStringToHandle(
			OptionTab[FontNo].PosX							//�@�������`�悷��N�_���W(X���W)
			, OptionTab[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, OptionTab[FontNo].ColorBase			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::Tab]			//�@�`�悷�镶����
		);
	}

	//�@�I���O
	else
	{
		DrawStringToHandle(
			OptionTab[FontNo].PosX							//�@�������`�悷��N�_���W(X���W)
			, OptionTab[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, OptionTab[FontNo].ColorMain			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::Tab]			//�@�`�悷�镶����
		);
	}

}

//	���ʃ{�^���̕\��
void OptionSG::VolumeButtonDraw(int FontNo, const char* pText)
{
	//�@�{�^���̕\������
	VolumeButton[FontNo].Draw(false);

	//�@�I��
	if (VolumeButton[FontNo].Valid)
	{
		DrawStringToHandle(
			VolumeButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, VolumeButton[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, VolumeButton[FontNo].ColorBase			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//�@�`�悷�镶����
		);
	}

	//�@�I���O
	else
	{
		DrawStringToHandle(
			VolumeButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, VolumeButton[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, VolumeButton[FontNo].ColorMain			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//�@�`�悷�镶����
		);
	}
}

//�@����ݒ�{�^���̕\��
void OptionSG::OprationButtonDraw(int FontNo, const char* pText)
{
	//�@�{�^���̕\������
	OprationButton[FontNo].Draw(false);

	//�@�I��
	if (OprationButton[FontNo].Valid)
	{
		DrawStringToHandle(
			OprationButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, OprationButton[FontNo].PosY + 1				//�@�������`�悷��N�_���W(Y���W)
			, pText, OprationButton[FontNo].ColorBase		//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//�@�`�悷�镶����
		);
	}

	//�@�I���O
	else
	{
		DrawStringToHandle(
			OprationButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, OprationButton[FontNo].PosY + 1				//�@�������`�悷��N�_���W(Y���W)
			, pText, OprationButton[FontNo].ColorMain		//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//�@�`�悷�镶����
		);
	}

}