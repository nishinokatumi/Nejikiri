#pragma once
#include "DxLib.h"
#include "Gameinformation.h"
#include <stdio.h>
#include <string.h>

#define	MAP_WIDTH_NUM		20								//	�}�b�v�`�b�v�̉��̐�
#define	MAP_HEIGHT_NUM		15								//	�}�b�v�`�b�v�̏c�̐�
#define CSV_MAX_COMMA	19									//	�X�e�[�WCSV�t�H���_�̃J���}�̍ő吔
#define	CSV_STAGE_NUM	27

static const char* CSVFilePath = "resource/csvdata/stage_%d.csv";	//	�ǂݍ���CSV�t�@�C���̑��΃p�X
static const char* GameFile = "resource/GameData.dat";		//	�ǂݍ���Dat�t�@�C���̑��΃p�X

//	�Q�[���̃Z�[�u�f�[�^�̍\����
struct GameSaveData
{
	int ReleaseStage = 0;									//	����ς݂̃X�e�[�W�̔ԍ�
	int SaveSEVolume = 100;										//	���ʉ��̐ݒ�
	int SaveBGMVolume = 100;									//	�w�i���̐ݒ�
	int SaveUIVolume = 100;										//	�V�X�e�����̐ݒ�
};

/*
�X�e�[�W�̓ǂݍ��݃N���X
	CSV�t�@�C������X�e�[�W�f�[�^(�u���b�N�̔z�u���ށE�M�~�b�N�̔z�u����)��ǂݍ���
*/
class CSVLoad
{
public:
	CSVLoad() {};											//	�����ݒ�

	//	�X�e�[�W�̃f�[�^��CSV�t�@�C������ǂݍ��݃|�C���^�Œl��n��
	void StageDataLoad(int StageNo, MAP_INFO::Stage* pStageData, MAP_INFO::GimmickData* pGimmickData);
};

/*
�X�e�[�W�̏������݃N���X
	CSV�t�@�C���ɃX�e�[�W�f�[�^(�u���b�N�̔z�u���ށE�M�~�b�N�̔z�u����)����������
*/
class CSVWrite
{
public:
	CSVWrite() {};											//	�����ݒ�

	//	�X�e�[�W�̃f�[�^��CSV�t�@�C���ɍ��킹�ď�������
	void StageDataWrite(int StageNo, MAP_INFO::Stage StageData, MAP_INFO::GimmickData GimmickData);
};

/*
�X�e�[�W�̓ǂݍ��݃N���X
	dat�t�@�C������Q�[���̃Z�[�u�f�[�^����������
*/
class GameData
{
private:
	bool LoadDone = false;									//	�Q�[���̃Z�[�u�f�[�^��ǂݍ��ݍς݂��ǂ���
	bool LoadDoneSE = false;								//	���̐ݒ��ǂݍ��ݍς݂��ǂ���

public:
	GameSaveData GameSaveData = { 0 };						//	�Q�[���̃Z�[�u�f�[�^

	GameData() {};											//	�����ݒ�

	void Load();											//	dat�t�@�C������Z�[�u�f�[�^��ǂݍ���
	void SaveStageNo(int SetNo);							//	dat�t�@�C���ɃQ�[���̃Z�[�u�f�[�^����������
	void SaveSoundVolume(int SEVolume, int BGMVolume, int UIVolume);	//	dat�t�@�C���ɉ��̃Z�[�u�f�[�^����������
	void LoadSoundVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume);	//	���ʃZ�[�u�f�[�^���
};