#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"


/*
�}�b�v�̕\���N���X
	�}�b�v�f�[�^(CSV����ϊ���������)��ǂݍ��݉摜�Ƃ��ĕ\��
	�����ڂ̕\������{
*/
class DrawMAP
{
private:

	//	�ϐ�
	int MapPosX = 0;										//	�}�b�v�̌��_�̈ʒuX
	int MapPosY = 0;										//	�}�b�v�̌��_�̈ʒuY
	int MapNo = 0;											//	�\������X�e�[�W�i���o�[
	MAP_INFO::Stage NowMapData = { 0 };						//	���݂̃X�e�[�W�̃}�b�v�f�[�^

public:
	//	�ϐ�
	int* pMapGraph[GRAPH::BLOCK::BlockLength - 1][4] = { 0 };	//	�摜��蕪���p�z��
	int* pGimmickGraph = 0;									//	�M�~�b�N�摜��蕪���p

	DrawMAP();												//	�����ݒ�

	//	����
	void Update();											//	�J��Ԃ����s�F�p�l���̑���̔��f�ƌv�Z
	void DrawMap();											//	�\������
	void DataRoad(MAP_INFO::Stage MapData, int MapDataNo);	//	�X�e�[�W�ύX���̏����l�ǂݍ���
};