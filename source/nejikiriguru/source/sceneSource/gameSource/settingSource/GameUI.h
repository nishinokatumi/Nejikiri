#pragma once
#include "Gameinformation.h"
#include "UIDraw.h"

//	UI�̕��i
enum UI_PARTS
{
	A = 0,			//�@A
	B,				//�@B
	X,				//�@X
	Y,				//�@Y
	L,				//�@L
	R,				//�@R
	Button,			//�@�{�^��
	Stick,			//�@�X�e�B�b�N
	VecPad,			//�@�����p�b�h
	LightVec,		//�@�����p�b�h(����)
	Trigger,		//�@�g���K�[
	Shoulder,		//�@�V�����_�{�^��
	Key,			//	�L�[�{�[�h�̃L�[
	EnterKey,		//	�G���^�[�L�[
	UILength,		//	���i����
};

//	Menu�̕��i
enum MENU_PARTS
{
	GoldFrame = 0,	//	���̘g
	GoldEndoint,	//	���̒[�_
	LineCenter,		//	�g�̒���
	UIMenuLength,	//	���i����
};

//	Menu�̕\�����
enum MENU_TYPE
{
	FullDraw = 0,	//	�S�\��
	CenterNone,		//	�g�������i����
	BackTransparency,//	�w�i������
};

//	UI���i�̌��_(����)
static const int UIGraphPos[UI_PARTS::UILength][2] =
{
	{96,32},		//	A
	{112,32},		//	B
	{96,46},		//	X
	{112,46},		//	Y
	{104,0},		//	L
	{104,16},		//	R
	{0,48},			//	�{�^��
	{32,32},		//	�X�e�B�b�N
	{0,32},			//	�����p�b�h
	{16,32},		//	�����p�b�h�i�����j
	{64,48},		//	�g���K�[
	{64,32},		//	�V�����_�{�^��
	{48,0},			//	�L�[�{�[�h�̃L�[
	{64,0}			//	�G���^�[�L�[
};

//	UI���i�̕�(XY)
static const int UIGraphSize[UI_PARTS::UILength][2] =
{
	{16,16},		//	A
	{16,16},		//	B
	{16,16},		//	X
	{16,16},		//	Y
	{16,16},		//	L
	{16,16},		//	R
	{16,16},		//	�{�^��
	{32,32},		//	�X�e�B�b�N
	{16,10},		//	�����p�b�h
	{16,10},		//	�����p�b�h�i�����j
	{32,16},		//	�g���K�[
	{32,16},		//	�V�����_�{�^��
	{16,16},		//	�L�[�{�[�h�̃L�[
	{32,32}			//	�G���^�[�L�[
};

//	UI���i�̒��S�ʒu
static const int UIGraphCenterPos[UI_PARTS::UILength][2] =
{
	{8,8},			//	A
	{8,8},			//	B
	{8,8},			//	X
	{8,8},			//	Y
	{8,8},			//	L
	{8,8},			//	R
	{8,8},			//	�{�^��
	{16,16},		//	�X�e�B�b�N
	{16,5},			//	�����p�b�h
	{16,5},			//	�����p�b�h�i�����j
	{16,8},			//	�g���K�[
	{16,8},			//	�V�����_�{�^��
	{8,8},			//	�L�[�{�[�h�̃L�[
	{16,16}			//	�G���^�[�L�[
};

//	UI���i�̌��_(����)
static const int UIFramePos[MENU_PARTS::UIMenuLength][2] =
{
	{0 ,16},			//	GoldFrame
	{0 ,0 },			//	GoldEndoint
	{32,0 },			//	LineCenter
};

//	UI���i�̕�(XY)
static const int UIFrameSize[MENU_PARTS::UIMenuLength][2] =
{
	{4 ,16},			//	GoldFrame
	{16,16},			//	GoldEndoint
	{16,32},			//	LineCenter
};

//	UI���i�̒��S�ʒu
static const int UIFrameCenterPos[MENU_PARTS::UIMenuLength][2] =
{
	{2 ,8 },			//	GoldFrame
	{8 ,8 },			//	GoldEndoint
	{8 ,16},			//	LineCenter
};

enum GameSenenUIPosition
{
	SpaceAX = 360,
	SpaceBX = 630,
	SpaceCX = 900,
	SpaceDX = 1170,
	SpaceAY = 1030,
	SpaceC = 0
};

/*
�Q�[��UI�̊Ǘ��N���X
	�Q�[��UI�𕪊����I��ŕ\������
*/
class GameUI
{
private:
	int GameUIGraph[UI_PARTS::UILength] = { 0 };			//	�Q�[���p�b�h�̉摜�n���h��
	int GameUIFrame[MENU_PARTS::UIMenuLength] = { 0 };		//	�Q�[��UI�̉摜�n���h��

	int FontThrty;											//�@�t�H���g�T�C�Y30

	int UIColorWhite;										//	��
	int UIColorBlack;										//	��

public:
	int*	pGameUIFont[FONT_SIZE::FontLength] = { 0 };		//	�g�p�t�H���g
	UIDraw* pGameUIDraw = new UIDraw();						//	UI�\���Ǘ�

	GameUI();												//	�����ݒ�

	//	�Q�[��UI�̏���
	void Initia(int GameUIGraphNo);					    	//	��������
	void Final();								    		//	�ŏI����

	//	�Q�[���̉摜��I�����\������
	void Draw(int UIPosX, int UIPosY, float Size, int SetUIParts, int VecPadSet = -1);	//	UI�̕\������
	void DrawpadUI(bool GamePadReady);						//	�Q�[�����̑������

	//	���j���[�E�B���h�E��\������(���W��)PV���ɂȂ�c��(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowPos(int MenuPosX1, int MenuPosY1, int MenuPosX2, int MenuPosY2, int Size, int BackColor, int MenuType, int Transparency = 0);

	//	���j���[�E�B���h�E��\������(���_��)PV���ɂȂ�c��(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowOrigin(int MenuPosX, int MenuPosY, int MenuWidth, int MenuHeight, int Size, int BackColor, int MenuType, int Transparency = 0)
	{
		//	���_��������W���ɕϊ�
		DrawMenuWindowPos(MenuPosX, MenuPosY, MenuPosX + MenuWidth, MenuPosY + MenuHeight, Size, BackColor, MenuType, Transparency);
	}

	//	���j���[�E�B���h�E��\������(���S��)PV���ɂȂ�c��(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowCenter(int MenuCenterPosX, int MenuCenterPosY, int MenuWidth, int MenuHeight, int Size, int BackColor, int MenuType, int Transparency = 0)
	{
		//	���S��������W���ɕϊ�
		DrawMenuWindowPos(MenuCenterPosX - (MenuWidth / 2), MenuCenterPosY - (MenuHeight / 2),
			MenuCenterPosX + (MenuWidth / 2), MenuCenterPosY + (MenuHeight / 2), Size, BackColor, MenuType, Transparency);
	}
};