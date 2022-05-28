#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/OperationManager.h"
#include "SettingSource/SEManager.h"

/*
�v���C���[�Ǘ��N���X
	�v���C���[�̈ʒu��摜�Ȃǂ𓮂������߂̃N���X
*/
class CharaPL
{
private:

	//	�ϐ�
	double PLSize = 2;										//	�v���C���[�̉摜�̑傫�����ʂ��P
	double ExtRate = 0;										//	�v���C���[�̉�]�p�x�F���W�A���ŉ~����������
	int GraphNo = 0;										//	�v���C���[�摜�̎�ރi���o�[
	int GraphNow = 0;										//	�v���C���[�摜�̌��݃i���o�[
	int Time = 0;											//	���ݎ����F�摜�؂�ւ��Ŏg��
	int VecX = 1;											//	�v���C���[�̐i�ވӎ��̌���X
	int VecY = 1;											//	�v���C���[�̏d�͂̌���Y
	int Buoyancy = 3;										//	�v���C���[�̃W�����v�̍ۂ̕���
	bool JumpFlag = false;									//	�v���C���[�̃W�����v�̏��
	bool PLToFace = false;									//	�v���C���[�̌����Ă������ false:�E�@true:��
	MAP_INFO::Stage NowMapData{ 0 };							//	���݂̃}�b�v�f�[�^

	//	����ʂ̏���
	void KeyboardOperation();								//	�L�[�{�[�h�ł̑���
	void GamePadOperation();									//	�Q�[���p�b�h�ł̑���

	//	�v���C���[�ƃ}�b�v�̓����蔻�菈��
	int CharMove(int* pPosX, int* pPosY, int* pDownSP			//	�����ɂ��}�b�v�Ƃ̓����蔻��
		, int MoveX, int MoveY, int Size, bool* pJumpFlag);
	HIT_RESULT MapHitCheck									//	�v���C���[�̃}�b�v�Ƃ̓����蔻��
	(int PosX, int PosY, int* pMoveX, int* pMoveY);
	int GetChipParam(float ParamX, float ParamY);			//	���W�ɂ�铖���蔻��

public:

	//	�ϐ�
	int* pPLGraph[GRAPH::PL_GRAPH::PLLength][PL_MAX_GRAPH_WIDTH] = { new int };	//	�v���C���[�摜�ۑ��z��F�R�}���Ə�Ԏ�ނ��琶��
	int PosX = 0;											//	�v���C���[�̒��S�|�W�V����X
	int PosY = 0;											//	�v���C���[�̒��S�|�W�V����Y
	Vector2D ProgressVec = Vector2D(0, 0);					//	�v���C���[�̐i�s�x�N�g��
	int PLGamePadNum = 0;									//	�Q�[���p�b�h�̐�

	OperationManager* pPLOperation = new OperationManager();//	�v���C���[�𑀍�ł���Q�[���p�b�h
	SEManager* pPLSE = new SEManager();						//	�v���C���[�̉�

	//	�����ݒ�
	CharaPL();												//	�N���X�����FPos��0�ɃZ�b�g	
	CharaPL(int SetPosX, int SetPosY);						//	�N���X�����FPos���w��

	//	�v���C���[����
	void Vector();											//	�x�N�g���̏���
	void GraphChange();										//	�v���C���[�̉摜��ω�������
	void Update();											//	�J��Ԃ����s�F�v���C���[�̑���̔��f�ƌv�Z
	void Draw();											//	�\������
	void SetMove();											//	�X�V������i�K��	�v���C���[�̈ʒu���m�F���Ȃ���
	void DataRoad(MAP_INFO::Stage MapData, Vector2D PLPos);	//	�X�e�[�W�ύX���̏����l�ǂݍ���
	void PLAnti(int XorY);									//	�v���C���[�𔽓]������ X:0 Y:1
};