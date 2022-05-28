#pragma once
#include "SettingSource/Gameinformation.h"

/*
WMR�̓���N���X
	���[�v���r�E�X�����O�̔����\�����s��
	�v���C���[�̏d�͂⑀��𔽓]������
*/
class GimmickWMR
{
private:
	//	�ϐ�
	Vector2D GimmickPos = Vector2D(0, 0);					//	�M�~�b�N�̃`�b�v���W
	Vector2D GimmickCenterPos = Vector2D(0, 0);				//	�M�~�b�N���S�ʒu
	int GimmickSize = 0;									//	�傫��
	int GimmickLightNum = 255;								//	���C�g�̃u�����h�0�`255;
	int GimmickConvequan = 10;								//	���C�g�̕ω���
	bool GimmickIsValid = false;							//	�M�~�b�N�̔��]���L����
	bool GimmickIsValidOld = false;							//	�O��̔���

public:
	//	�ϐ�
	int* pGimmickGraNo[GRAPH::WMR_PARTS::WMRLength] = { 0 };	//	�M�~�b�N�̉摜�n���h��
	int GimmickVecXorY = 0;									//	�M�~�b�N�̌���	0:X	1:Y
	bool GimmickIsEnergization = true;						//	�ʓd���Ă��邩
	bool GimmickYellow = false;								//	�`�����l�����F
	bool GimmickBlue = false;								//	�`�����l���F
	bool GimmickWhite = false;								//	�`�����l�����F
	int GimmickColor = 0;									//�@�F �@�S���_��:0 ��:1 ��:2 ��:3


	GimmickWMR();											//	�����ݒ�

	//	WMR�̏���
	void Update();											//	�M�~�b�N�̍X�V����
	void Draw();											//	�M�~�b�N�̕\������
	void DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color);	//	vecXorY:X��Y�̃v���X�����ɐL�΂� X:0 Y:1
	bool ReverseMove(int* PLPosX, int* PLPosY, Vector2D PLVec, int PLSize);	//	WMR�̒��S���甽�]������
	bool ReverseCheck(int PLPosX, int PLPosY, int PLSize);	//	���]���L�����ǂ���
};

/*
�����̓���N���X
	WMR��ONOFF�؂�ւ���ۂɎg��
	�`�����l�����Ƃɐ؂�ւ���
*/
class GimmickPres
{
private:
	//	�ϐ�
	Vector2D GimmickPos = Vector2D(0, 0);					//	�M�~�b�N�̃`�b�v���W
	int GimmickCenterPos = 0;								//	�M�~�b�N���S�ʒu
	int GimmickInitia = 0;									//	�傫��
	bool GimmickStep = false;								//�@�����𓥂񂾂�

public:
	//	�ϐ�
	int* pGimmickGraNo[GRAPH::PRES_PARTS::PresLength] = { 0 };//	�M�~�b�N�̉摜�n���h��
	int GimmickVecXorY = 0;									//	�M�~�b�N�̌���	0:X �����	1:Y ������
	bool GimmickIsEnergization = false;						//	�ʓd���Ă���
	bool GimmickIsValid = false;							//	�����M�~�b�N���L����
	bool GimmickIsValidOld = false;							//	�O��̔���
	bool GimmickYellow = false;								//	�`�����l�����F
	bool GimmickBlue = false;								//	�`�����l���F
	bool GimmickWhite = false;								//	�`�����l�����F
	int GimmickColor = 0;									//�@�F �@�S���_��:0 ��:1 ��:2 ��:3


	GimmickPres();											//	�����ݒ�

	//	�����̏���
	void Update();											//	�M�~�b�N�̍X�V����
	void Draw();											//	�M�~�b�N�̕\������
	void DataRoad(int PosX, int PosY, int VecXorY, int Initia, int Color);	//	vecXorY:X��Y�̃v���X�����ɐL�΂� X:0 Y:1
	bool ReverseCheck(int PLPosX, int PLPosY, int PLSize);	//	�����M�~�b�N���L�����ǂ���
};

/*
�ʓd�̓���N���X
	�Ȃ����Ă��銴����WMR�𕪂���₷����������
*/
class GimmickEner
{
private:
	//	�ϐ�
	Vector2D GimmickPos = Vector2D(0, 0);					//	�M�~�b�N�̃`�b�v���W
	int GimmickCenterPos = 0;								//	�M�~�b�N���S�ʒu
	float Angle = 0;										//	�\���p�x
	int GimmickSize = 0;									//	�傫��
	int GimmickKind = 0;									//	��� �o��:0 ����:1

public:
	//	�ϐ�
	int* pGimmickGraNo[GRAPH::ENER_PARTS::EnerLength] = { 0 };//	�M�~�b�N�̉摜�n���h��
	int GimmickVecXorY = 0;									//	�M�~�b�N�̌���	0:�� 1:�� 2:�� 3:�E
	bool GimmickYellow = false;								//	�`�����l�����F
	bool GimmickBlue = false;								//	�`�����l���F
	bool GimmickWhite = false;								//	�`�����l�����F
	int GimmickColor = 0;									//�@�F �@�S���_��:0 ��:1 ��:2 ��:3

	GimmickEner();											//	�����ݒ�

	//	�ʓd�̏���
	void Draw();											//	�M�~�b�N�̕\������
	void DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color, int Kind);	//	vecXorY:X��Y�̃v���X�����ɐL�΂� X:0 Y:1
};