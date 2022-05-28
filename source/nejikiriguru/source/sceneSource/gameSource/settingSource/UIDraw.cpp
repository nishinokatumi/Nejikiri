#include "UIDraw.h"
#include "DxLib.h"

/*
UI�̕\���N���X
	���p����UI���܂Ƃ߂ĊȒP�Ɏg����悤�ɂ���
*/

//	�����ݒ�
UIDraw::UIDraw()
{
}

//	�{�b�N�X�ō��E�B���h�E�̕\��
void UIDraw::BoxWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor)
{
	//	�{�b�N�X�̕\��
	DrawBox(
		WindowPosX, WindowPosY,								//	�{�b�N�X����
		WindowPosX + WindowWidth, WindowPosY + WindowHeight,//	�{�b�N�X�E��
		WindowColor, true);									//	�F��I�����ēh��Ԃ�
}

//	����{�b�N�X�ō��E�B���h�E�̕\��
void UIDraw::BoxLineWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor,
	float WindowLineTin)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blend���[�h��؂�ւ�180�f���ݒ������

	//	�e�L�X�g�{�b�N�X�̕\��
	DrawBox(
		WindowPosX + (int)WindowLineTin,					//	��
		WindowPosY + (int)WindowLineTin,					//	��
		WindowPosX + WindowWidth - (int)WindowLineTin,		//	�E
		WindowPosY + WindowHeight - (int)WindowLineTin,		//	��
		GetColor(0, 0, 0), true);							//	���F��I�����ēh��Ԃ�

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	�ʏ��blend���[�h��؂�ւ���

	//	�e�L�X�g�{�b�N�X�̘g�̕\��
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	��
		(float)WindowPosY + WindowLineTin,					//	��
		(float)(WindowPosX + WindowWidth) - WindowLineTin,	//	�E
		(float)(WindowPosY + WindowHeight) - WindowLineTin,	//	��
		WindowColor, false, WindowLineTin);					//	�F��I�����Ē��S��h��Ԃ��Ȃ�
}

//	Text������E�B���h�E��\��
void UIDraw::TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString)
{
	//	���������邽�߂̃{�b�N�X�̉E���̈ʒu(���������E��)
	int BoxX = WindowPosX + (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	���������邽�߂̃{�b�N�X�̉����̈ʒu
	int BoxY = WindowPosY + SetFontStat[FontType].Size + ((15 + (int)WindowLineTin) * 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blend���[�h��؂�ւ�180�f���ݒ������

	//	�e�L�X�g�{�b�N�X�̕\��
	DrawBox(
		WindowPosX, WindowPosY,								//	����
		BoxX, BoxY,											//	�E��(���������E��)
		WindowColor, true);									//	�F��I�����ēh��Ԃ�


	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	�ʏ��blend���[�h��؂�ւ���

	//	�e�L�X�g�{�b�N�X�̉��̕\��
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	��
		(float)WindowPosY + WindowLineTin,					//	��
		(float)BoxX - WindowLineTin,						//	�E(���������E��)
		(float)BoxY - WindowLineTin,						//	��
		StringColor, false, WindowLineTin);					//	�F��I�����Ē��S��h��Ԃ��Ȃ�


	//	�e�L�X�g�̕\��
	DrawStringToHandle(
		WindowPosX + (int)WindowLineTin + 15,				//	��
		WindowPosY + (int)WindowLineTin + 15,				//	��
		WindowTextString, StringColor, *FontSet[FontType]);	//	�F��I�����Ďw��t�H���g�Ńe�L�X�g��\��

}

//	Text������E�B���h�E��\��:�����s
void UIDraw::TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString[], int WindowTextNum)
{
	//	���������邽�߂̃{�b�N�X�̉E���̈ʒu(���������E��)
	int BoxX = WindowPosX + (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	���������邽�߂̃{�b�N�X�̉����̈ʒu(�s����������)
	int BoxY = WindowPosY + (SetFontStat[FontType].Size * WindowTextNum) + ((15 + (int)WindowLineTin) * 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blend���[�h��؂�ւ�180�f���ݒ������

	//	�e�L�X�g�{�b�N�X�̕\��
	DrawBox(
		WindowPosX, WindowPosY,								//	����
		BoxX, BoxY,											//	�E��(���������E��)
		WindowColor, true);									//	�F��I�����ēh��Ԃ�

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	�ʏ��blend���[�h��؂�ւ���

	//	�e�L�X�g�{�b�N�X�̉��̕\��
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	��
		(float)WindowPosY + WindowLineTin,					//	��
		(float)BoxX - WindowLineTin,						//	�E(���������E��)
		(float)BoxY - WindowLineTin,						//	��
		StringColor, false, WindowLineTin);					//	�F��I�����Ďw��t�H���g�Ńe�L�X�g��\��

	//	�e�L�X�g�̕\���F�s��
	for (int LineCount = 0; LineCount < WindowTextNum; LineCount++)
	{
		//	�e�L�X�g�̕\��
		DrawStringToHandle(
			WindowPosX + (int)WindowLineTin + 10,			//	��
			WindowPosY + (int)WindowLineTin + 10 + (LineCount * SetFontStat[FontType].Size),//	��(�s����������)
			WindowTextString[LineCount], StringColor, *FontSet[FontType]);	//	�F��I�����Ďw��t�H���g�Ńe�L�X�g��\��
	}
}

//	���S����{�b�N�X�ō��E�B���h�E�̕\��
void UIDraw::BoxWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor)
{
	//	���S����ɕϊ�
	BoxWindow(
		WindowPosX - (WindowWidth / 2),						//	�����牡���̔�������
		WindowPosY - (WindowHeight / 2),					//	�ォ��c���̔������
		WindowWidth, WindowHeight,							//	�c�����ꂼ��̕�
		WindowColor);										//	�F�̑I��
}

//	���S���璆��{�b�N�X�ō��E�B���h�E�̕\��
void UIDraw::BoxLineWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor, float WindowLineTin)
{
	//	���S����ɕϊ�
	BoxLineWindow(
		WindowPosX - (WindowWidth / 2),						//	�����牡���̔�������
		WindowPosY - (WindowHeight / 2),					//	�ォ��c���̔������
		WindowWidth, WindowHeight,							//	�c�����ꂼ��̕�
		WindowColor, WindowLineTin);						//	���̐F�ƕ��̑I��
}

//	���S����Text������E�B���h�E��\��
void UIDraw::TextBoxWindowCenter(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString)
{
	//	TextBoxWindow�Ɠ����悤�Ɍv�Z
	int BoxX = (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	TextBoxWindow�Ɠ����悤�Ɍv�Z
	int BoxY = (SetFontStat[FontType].Size) + ((15 + (int)WindowLineTin) * 2);

	//	���S����ɕϊ�
	TextBoxWindow(
		WindowPosX - (BoxX / 2),							//	�����牡���̔�������
		WindowPosY - (BoxY / 2),							//	�ォ��c���̔������
		TextStringNum, StringColor,							//	�������ƕ����̐F
		WindowColor, WindowLineTin,							//	�E�B���h�E�̐F�ƃE�B���h�E�̉��̕�
		FontType, WindowTextString);						//	�����̎�ނƃe�L�X�g
}

//	�A�E�g���C��������e�L�X�g:�^�C�g�����Ԃ�`����Ƃ��Ȃ�
void UIDraw::TextOutlLine(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int TextStringNum,
	int OutLineWidth, int StringColor, int OutLineColor)
{
	int FontSize = SetFontStat[FontType].Size;				//	�����̐F
	int StringX = StringPosX - (FontSize * TextStringNum / 2);	//	�����̉�����(���S�ɂ��邽��)
	int StringY = StringPosY - (FontSize / 2);				//	�����̏c����(���S�ɂ��邽��)

	//	�A�E�g�J���[�\��
	DrawStringToHandle(StringX + OutLineWidth, StringY + OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	���������E���ɕ\��

	DrawStringToHandle(StringX + OutLineWidth, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	�������������ɕ\��

	DrawStringToHandle(StringX - OutLineWidth, StringY + OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	���������E��ɕ\��

	DrawStringToHandle(StringX - OutLineWidth, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	������������ɕ\��


	DrawStringToHandle(StringX + OutLineWidth, StringY, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	�����������ɕ\��

	DrawStringToHandle(StringX, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	�����������ɕ\��

	DrawStringToHandle(StringX - OutLineWidth, StringY, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	����������ɕ\��

	DrawStringToHandle(StringX, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	���������E�ɕ\��


	//	������\��(���S)
	DrawStringToHandle(StringX, StringY, WindowTextString, StringColor, *FontSet[FontType]);
}

//	�A�E�g���C��������e�L�X�g�E�ォ��:�^�C�g�����Ԃ�`����Ƃ��Ȃ�
void UIDraw::TextOutlLineFormat(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int StringInt,
	int OutLineWidth, int StringColor, int OutLineColor)
{
	//	�A�E�g�J���[�\��
	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY + OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	���������E���ɕ\��
	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	�������������ɕ\��
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY + OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	���������E��ɕ\��
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	������������ɕ\��



	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	�����������ɕ\��
	DrawFormatStringToHandle(StringPosX, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	�����������ɕ\��
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	����������ɕ\��
	DrawFormatStringToHandle(StringPosX, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	���������E�ɕ\��




	//	������\��
	DrawFormatStringToHandle(StringPosX, StringPosY, StringColor, *FontSet[FontType], WindowTextString, StringInt);
}

//	�u���b�N�A�E�g
void UIDraw::DarkenScreen(int WindowPosX, int WindowPosY,
	int WindowWidth, int WindowHeight, int WindowColor, int WindowDarken)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, WindowDarken);					//	���u�����h
	BoxWindow(WindowPosX, WindowPosY, WindowWidth, WindowHeight, WindowColor);	//	�w��̐F�Ɣ͈͂Ƀ{�b�N�X�ŕ\��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//	��{�ɖ߂�
}