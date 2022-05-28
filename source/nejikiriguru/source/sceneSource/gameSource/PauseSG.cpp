#include "PauseSG.h"
#include "DxLib.h"

//	�����ݒ�
PauseSG::PauseSG()
{

}

//	�ꎞ��~��ʂ̏�������
void PauseSG::Initia()
{
	static int ColorBase = GetColor(0, 0, 0);							//�@���F
	static int ColorMain = GetColor(255, 255, 255);						//�@���F
	static int ColorSelect = GetColor(255, 255, 0);						//�@���F

	static int PauseButtonPosX = GAME_WIN_WIDTH / 2;					//�@PauseButton��X���W
	static int PauseButtonPosY = GAME_WIN_HEIGHT / 2;					//�@PauseButton��Y���W

	static int PauseButtonWidth = 200;									//�@PauseButton�̉���
	static int PauseButtonHeight = 30;									//�@PauseButton�̏c�̒���

	//�@�{�^���̐������J��Ԃ�
	for (int Num = 0; Num < PAUSEBUTTON::PauseLength; Num++)
	{
		PauseButton[Num].ButtonNo = Num;								//�@�{�^���̔ԍ�
		PauseButton[Num].ColorBase = ColorBase;							//�@�{�^���̐F(��)
		PauseButton[Num].ColorMain = ColorMain;							//�@�{�^���̐F(��)
		PauseButton[Num].ColorSelect = ColorSelect;						//�@�{�^���̐F(��)
	}

	//	�X�e�[�W�Z���N�g�{�^��
	{
		PauseButton[PAUSEBUTTON::Back].PosX = PauseButtonPosX;			//�@X���W
		PauseButton[PAUSEBUTTON::Back].PosY = PauseButtonPosY;			//�@Y���W
		PauseButton[PAUSEBUTTON::Back].Width = PauseButtonWidth;		//�@�{�^���̑傫��(��)
		PauseButton[PAUSEBUTTON::Back].Height = PauseButtonHeight;		//�@�{�^���̑傫��(�c)
	}

	//	�����{�^��
	{
		PauseButton[PAUSEBUTTON::Retry].PosX = PauseButtonPosX;			//�@X���W
		PauseButton[PAUSEBUTTON::Retry].PosY = PauseButtonPosY + 100;	//�@Y���W
		PauseButton[PAUSEBUTTON::Retry].Width = PauseButtonWidth;		//�@�{�^���̑傫��(��)
		PauseButton[PAUSEBUTTON::Retry].Height = PauseButtonHeight;		//�@�{�^���̑傫��(�c)
	}

	//	�ݒ�{�^��
	{
		PauseButton[PAUSEBUTTON::Option].PosX = PauseButtonPosX;		//�@X���W
		PauseButton[PAUSEBUTTON::Option].PosY = PauseButtonPosY + 200;	//�@Y���W
		PauseButton[PAUSEBUTTON::Option].Width = PauseButtonWidth;		//�@�{�^���̑傫��(��)
		PauseButton[PAUSEBUTTON::Option].Height = PauseButtonHeight;	//�@�{�^���̑傫��(�c)
	}

	//	�Q�[���I���{�^��
	{
		PauseButton[PAUSEBUTTON::Select].PosX = PauseButtonPosX + 585;	//�@X���W
		PauseButton[PAUSEBUTTON::Select].PosY = PauseButtonPosY + 400;	//�@Y���W
		PauseButton[PAUSEBUTTON::Select].Width = PauseButtonWidth;		//�@�{�^���̑傫��(��)
		PauseButton[PAUSEBUTTON::Select].Height = PauseButtonHeight;	//�@�{�^���̑傫��(�c)
	}

	PauseOption.pOptionBackGrahandle = pPauseBackGrahandle;
	PauseOption.pOptionOperation = pPauseOperation;				//	�Q�[���p�b�h�N���X���Q�Ƃ�����
	PauseOption.pOptionGameUI = pPauseGameUI;					//	�Q�[��UI�N���X���Q�Ƃ�����
	PauseOption.pOptionSE = pPauseSE;							//	���̊Ǘ����Q�Ƃ�����
	PauseOption.pOptionUI = pPauseUI;							//	�\��UI�N���X���Q�Ƃ�����
	PauseOption.pOptionDataLoad = pPauseDataLoad;				//	�摜�Ǘ��N���X���Q�Ƃ�����
	PauseOption.pOptionGameDate = pPauseGameData;				//	�Q�[���Z�[�u�f�[�^���Q�Ƃ�����
	PauseOption.Initia();									//	�|�[�Y��ʂ̏�������

}

//	�ꎞ��~��ʂ̍X�V����
int PauseSG::Update()
{
	//	�ݒ��ʂ̏���
	if (OptionFlag == true)
	{
		//�@PauseOption.Update����Ԃ��Ă����l��3�̂Ƃ�
		if (PauseOption.Update() == 3)
		{
			//�@�I�v�V�����t���O��false
			OptionFlag = false;

			//	�X�V�����̍Đ�(true)
			PauseOption.TransitionSet = true;
		}
	}

	//	�ꎞ��~��ʂ̏���
	else
	{
		//�@�{�^���̐������J��Ԃ�
		for (int ButtonNum = 0; ButtonNum < PAUSEBUTTON::PauseLength; ButtonNum++)
		{
			//	�{�^���̑I���I���̓��I�ȐF�̕ω�
			PauseButton[ButtonNum].UpdateBlend();

			//�@�{�^�����I�𒆂�������
			if (PauseButton[ButtonNum].ButtonNo == SelectButton)
			{
				//�@�{�^���I�𒆂̃t���O��true�ɂ���
				PauseButton[ButtonNum].Valid = true;
			}

			//�@�{�^�����I�𒆂���Ȃ�������
			else
			{
				//�@�{�^���I�𒆂̃t���O��false�ɂ���
				PauseButton[ButtonNum].Valid = false;
			}
		}

		//�@DOWN�L�[
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
			pPauseSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�

			SelectButton++;										//�@���̑I���{�^����

			//�@�J�[�\�����Ō�̑I�����̂Ƃ�
			if (SelectButton >= PAUSEBUTTON::PauseLength)
			{
				//�@�J�[�\����1�ԍŏ��̑I�����ɂ���
				SelectButton = 0;
			}
		}

		//�@UP�L�[
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Select);			//	���ʉ��̒�~
			pPauseSE->SoundPlay(SOUND_NAME::Select);			//	���ʉ��̍Đ�
			SelectButton--;										//�@1�O�̑I���{�^����

			//�@�J�[�\�����ŏ��̑I�����̂Ƃ�
			if (SelectButton < 0)
			{
				//�@�J�[�\����1�ԍŌ�̑I�����ɂ���
				SelectButton = PAUSEBUTTON::PauseLength - 1;
			}
		}


		//	����{�^��
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Enter);			//	���ʉ��̒�~
			pPauseSE->SoundPlay(SOUND_NAME::Enter);				//	���ʉ��̍Đ�
			//�@1�Q�[���ɖ߂�
			//�@2���g���C
			//�@3�ݒ���
			//�@4�^�C�g��

			if (SelectButton == PAUSEBUTTON::Option)
			{
				PauseOption.Initia();							//	�ݒ��ʏ�����
			}

			return (SelectButton + 1);							//�@�I�����ꂽ�{�^���̏������s��
		}


	}
	return 0;												//�@���������Ȃ�
}

//	�ꎞ��~��ʂ̕\������
void PauseSG::Draw()
{
	if (OptionFlag == true)
	{
		PauseOption.Draw();
	}

	else
	{
		// �V�[�����̕`�揈�����s��
		DrawRotaGraph2(											//	�w�i�̕`��
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64		//�@��ʏ�ł̉摜�̒��S��X���W
			, WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4				//�@��ʏ�ł̉摜�̒��S��Y���W
			, 3.5, 0											//	�T�C�Y, �p�x
			, *pPauseBackGrahandle, false, false);				//	�\������摜, �\������摜�̓���, ���]

		int Tin = 4;											//�@�����̑���

		const char* TextString[PAUSEBUTTON::PauseLength] =		//	�e�L�X�g�̓��e : Back
		{
			{"            Back"},
			{"            Retry"},
			{"            Option"},
			{"      Select"}
		};

		//�@�{�^���̐������J��Ԃ�
		for (int Num = 0; Num < PAUSEBUTTON::PauseLength; Num++)
		{
			//	�I���{�^���̕\��
			SelectButtonDraw(Num, TextString[Num]);
		}
	}
}

//	�I���{�^���̕\��
void PauseSG::SelectButtonDraw(int FontNo, const char* pText)
{
	//�@�{�^���̕\������
	PauseButton[FontNo].Draw(false);

	//�@�I��
	if (PauseButton[FontNo].Valid)
	{
		DrawStringToHandle(
			PauseButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, PauseButton[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, PauseButton[FontNo].ColorBase			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pPauseFont[FONT_SIZE::Normal]				//�@�`�悷�镶����
		);
	}

	//�@�I���O
	else
	{
		DrawStringToHandle(
			PauseButton[FontNo].PosX						//�@�������`�悷��N�_���W(X���W)
			, PauseButton[FontNo].PosY + 1					//�@�������`�悷��N�_���W(Y���W)
			, pText, PauseButton[FontNo].ColorMain			//�@�`�悷�镶����̃|�C���^, �����̐F
			, *pPauseFont[FONT_SIZE::Normal]				//�@�`�悷�镶����
		);
	}
}

//�@�ݒ��ʂ̏���
void PauseSG::OptionUpdate()
{
	if (OptionFlag == true)
		PauseOption.Update();
}