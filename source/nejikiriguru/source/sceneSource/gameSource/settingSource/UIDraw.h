#pragma once
#include "Gameinformation.h"
#include "DxLib.h"


/*
UI�̕\���N���X
	���p����UI���܂Ƃ߂ĊȒP�Ɏg����悤�ɂ���
*/
class UIDraw
{
public:
	/*----------------------����------------------------*/
	int* FontSet[FONT_SIZE::FontLength] = { new int };		//	�g�p�t�H���g 

	UIDraw();												//	�����ݒ�

	//	�{�b�N�X�ō��E�B���h�E�̕\��
	void BoxWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor);

	//	����{�b�N�X�ō��E�B���h�E�̕\��
	void BoxLineWindow(int WindowPosX, int WindowPosY, int WindowWidth,
		int WindowHeight, int WindowColor, float WindowLineTin);

	//	Text������E�B���h�E��\��
	void TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString);

	//	Text������E�B���h�E��\��:�����s
	void TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString[], int WindowTextNum);

	//	���S����{�b�N�X�ō��E�B���h�E�̕\��
	void BoxWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor);

	//	���S���璆��{�b�N�X�ō��E�B���h�E�̕\��
	void BoxLineWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor,
		float WindowLineTin);

	//	���S����Text������E�B���h�E��\��
	void TextBoxWindowCenter(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString);

	//	�A�E�g���C��������e�L�X�g:�^�C�g�����Ԃ�`����Ƃ��Ȃ�
	void TextOutlLine(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int TextStringNum, int OutLineWidth, int StringColor, int OutLineColor);

	//	�A�E�g���C��������e�L�X�g�E�ォ��:�^�C�g�����Ԃ�`����Ƃ��Ȃ�
	void TextOutlLineFormat(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int StringInt, int OutLineWidth, int StringColor, int OutLineColor);

	//	�u���b�N�A�E�g
	void DarkenScreen(int WindowPosX, int WindowPosY,
		int WindowWidth, int WindowHeight,
		int WindowColor, int WindowDarken);
};

#define PLUSPER 20											//	�{�^���F�؂�ւ��̕ω���

/*
�{�^���̏����\���N���X
	�{�^���̓��I�I�𓙂̕\���\���̏����Ȃǂ��s��
*/
class UIButton :public UIDraw
{
public:
	bool Valid = false;										//	�{�^���I��
	int ButtonNo = 0;										//	�{�^���̃i���o�[
	int PosX = 0;											//	�{�^�����̍��W
	int PosY = 0;											//	�{�^����̍��W
	int Width = 0;											//	�{�^������
	int Height = 0;											//	�{�^���c��
	int ColorBase = 0;										//	�{�^���F(��I����)
	int ColorSelect = 0;									//	�{�^���F(�I���ς�)
	int ColorMain = 0;										//	�{�^���F(�I����)

	int ColorPercent = 0;									//	�d�˂�F�̃p�[�Z���g0�`255
	int Perplus = 0;										//	�p�[�Z���g��ς���l


	UIButton() {}											//	�����ݒ�

	//	�{�^���̑I���I���̓��I�ȐF�̕ω�
	void UpdateBlend()
	{
		Perplus = 0;										//	�ω����Ȃ��ۂɗ]�v�ȏ��������Ȃ����߂�0�ɂ���

		//	�L���̎�
		if (Valid)
		{
			//	�F�����łɍő�łȂ����
			if (ColorPercent < 255)
			{
				Perplus = PLUSPER;							//	�ω��ʂ�ݒ�
			}

			//	�F�����łɍő�ł����
			else
			{
				ColorPercent = 255;							//	�d�˂�F���ő�l�ɐݒ�
			}
		}

		//	�����̎�
		else
		{
			//	�F�����łɍŏ��łȂ����
			if (ColorPercent > 0)
			{
				Perplus = -PLUSPER;							//	�ω��ʂ�ݒ�
			}

			//	�F�����łɍŏ��ł����
			else
			{
				ColorPercent = 0;							//	�d�˂�F���ő�l�ɐݒ�
			}
		}

		//	�ω��ʂ��ς���Ă����
		if (Perplus != 0)
		{
			ColorPercent += Perplus;						//	�ω��̏���������
		}
	}

	//	�{�^���̕\���@sele:�I���ς݂̘_���l
	void Draw(bool Sele)
	{
		int WindowLineTin = 4;								//	�E�B���h�E�̐��̑���

		//	�{�^���̃{�b�N�X
		DrawBox(
			PosX, PosY,
			PosX + Width, PosY + Height,
			ColorBase, true);

		//	���_�l���L���������ꍇ
		if (Sele)
		{
			//	�{�b�N�X��I���ς݂̐F��
			DrawBox(
				PosX, PosY,
				PosX + Width, PosY + Height,
				ColorSelect, true);
		}

		//	���_�l�������������ꍇ
		else
		{
			//	blend���[�h��؂�ւ��ǂ̈ʉf�����ݒ肷��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ColorPercent);

			//	�{�b�N�X�ɑI��F��킹��
			DrawBox(
				PosX, PosY,
				PosX + Width, PosY + Height,
				ColorMain, true);

			//	�ʏ��blend���[�h��؂�ւ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//	�e�L�X�g�{�b�N�X�̉��̕\��
		DrawBoxAA((float)PosX, (float)PosY,
			(float)(PosX + Width), (float)(PosY + Height),
			ColorMain, false, (float)WindowLineTin);
	}
};