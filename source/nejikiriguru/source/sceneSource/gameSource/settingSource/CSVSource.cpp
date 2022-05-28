#include "CSVHeader.h"


/*
�X�e�[�W�̓ǂݍ��݃N���X
	CSV�t�@�C������X�e�[�W�f�[�^(�u���b�N�̔z�u���ށE�M�~�b�N�̔z�u����)��ǂݍ���
*/

//	�X�e�[�W�̃f�[�^��CSV�t�@�C������ǂݍ��݃|�C���^�Œl��n��
void CSVLoad::StageDataLoad(int StageNo, MAP_INFO::Stage* pStageData, MAP_INFO::GimmickData* pGimmickData)
{
	FILE* CSVDataFile;

	//	�}�b�v�`�b�v�t�@�C���̎w��
	char FilePathBuffer[255] = { "" };						//	�t�@�C���̑��΃p�X�p�̃o�b�t�@
	sprintf_s(FilePathBuffer, CSVFilePath, StageNo);		//	�t�@�C���̑��΃p�X�̃o�b�t�@���X�e�[�W�ԍ��������
	fopen_s(&CSVDataFile, FilePathBuffer, "r");				//	�ǂݍ��ރt�@�C�����w��

	char* ConText;											//	�ʒu���̊i�[
	char Buffer[1024] = { "" };								//	�ǂݍ��݃o�b�t�@

	/*--------------��������t�@�C���̓ǂݍ���-----------*/

	//	�}�b�v�̃u���b�N�̎�ނ̓ǂݍ���
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	��s�ǂݍ���
	char* DividedNum = strtok_s(Buffer, ",", &ConText);		//	����

	pStageData->MapPanelNo = atoi(DividedNum);				//	�p�l���Z�b�g
	DividedNum = strtok_s(NULL, ",", &ConText);				//	���̗v�f
	pStageData->MapWallNo = atoi(DividedNum);				//	�ǃZ�b�g

	//	�}�b�v�`�b�v�̓ǂݍ���
	for (int YNum = 0; YNum < MAP_HEIGHT_NUM; YNum++)
	{
		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	��s�ǂݍ���
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	����
		pStageData->BlockData[YNum][0] = atoi(DividedNum);	//	�}�b�v�`�b�v�̍ŏ����Z�b�g

		//	�c�����
		for (int XNum = 1; XNum < MAP_WIDTH_NUM; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	����
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	����������I���
			if (strlen(DividedNum) <= 0)break;						//	�v�f������������I���
			pStageData->BlockData[YNum][XNum] = atoi(DividedNum);	//	����ȊO����
		}

	}

	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	�ǂݍ��݂̉��s

	int GimmickNum = 0;										//	�J��Ԃ��g�p


	/*--------------��������WMR�M�~�b�N�̓ǂݍ���-----------*/

	//	WMR�M�~�b�N�̐�
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	��s�ǂݍ���
	DividedNum = strtok_s(Buffer, ",", &ConText);			//	����
	pGimmickData->StageWMRData.GimmickWMRNum = atoi(DividedNum);	//	�ǂݍ��݃Z�b�g


	//	WMR�f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StageWMRData.GimmickWMRNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	��s�ǂݍ���
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	����
		pGimmickData->StageWMRData.GimmickWMR[GimmickNum][0] = atoi(DividedNum);//	�M�~�b�N�̍ŏ����Z�b�g

		//	�c�����
		for (int XNum = 1; XNum < 5; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	����
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	����������I���
			if (strlen(DividedNum) <= 0)break;				//	�v�f������������I���
			pGimmickData->StageWMRData.GimmickWMR[GimmickNum][XNum] = atoi(DividedNum);//	����ȊO����
		}

	}

	//	���s((�M�~�b�N�̍ő吔 + ���₷���p�̈�s)-����)
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	���̍s��



	/*--------------�������犴���M�~�b�N�̓ǂݍ���-----------*/

	//	�����M�~�b�N�̐�
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	��s�ǂݍ���
	DividedNum = strtok_s(Buffer, ",", &ConText);			//	����
	pGimmickData->StagePresData.GimmickPresNum = atoi(DividedNum);	//	�ǂݍ��݃Z�b�g


	//	�����f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StagePresData.GimmickPresNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	��s�ǂݍ���
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	����
		pGimmickData->StagePresData.GimmickPres[GimmickNum][0] = atoi(DividedNum);//	�M�~�b�N�̍ŏ����Z�b�g

		//	�c�����
		for (int XNum = 1; XNum < 5; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	����
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	����������I���
			if (strlen(DividedNum) <= 0)break;						//	�v�f������������I���
			pGimmickData->StagePresData.GimmickPres[GimmickNum][XNum] = atoi(DividedNum);//	����ȊO����
		}

	}

	//	���s((�M�~�b�N�̍ő吔 + ���₷���p�̈�s)-����)
	for (int GimmickSetNum = GimmickNum; GimmickSetNum < 5; GimmickSetNum++)
	{
		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	���̍s��
	}

	/*--------------��������ʓd�M�~�b�N�̓ǂݍ���-----------*/

	//	�ʓd�M�~�b�N�̐�
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	��s�ǂݍ���
	DividedNum = strtok_s(Buffer, ",", &ConText);					//	����
	pGimmickData->StageEnerData.GimmickEnerNum = atoi(DividedNum);	//	�ǂݍ��݃Z�b�g


	//	�ʓd�f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StageEnerData.GimmickEnerNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	��s�ǂݍ���
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	����
		pGimmickData->StageEnerData.GimmickEner[GimmickNum][0] = atoi(DividedNum);//	�M�~�b�N�̍ŏ����Z�b�g

		//	�c�����
		for (int XNum = 1; XNum < 6; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);				//	����
			if (DividedNum == NULL || DividedNum[0] == '\0')break;			//	����������I���
			if (strlen(DividedNum) <= 0)break;						//	�v�f������������I���
			pGimmickData->StageEnerData.GimmickEner[GimmickNum][XNum] = atoi(DividedNum);//	����ȊO����
		}

	}

	fclose(CSVDataFile);									//	�t�@�C�������
}

/*
�X�e�[�W�̏������݃N���X
	CSV�t�@�C���ɃX�e�[�W�f�[�^(�u���b�N�̔z�u���ށE�M�~�b�N�̔z�u����)����������
*/

//	�X�e�[�W�̃f�[�^��CSV�t�@�C���ɍ��킹�ď�������
void CSVWrite::StageDataWrite(int StageNo, MAP_INFO::Stage StageData, MAP_INFO::GimmickData GimmickData)
{
	FILE* CSVDataFile;										//	�t�@�C���p
	//	�}�b�v�`�b�v�t�@�C���̎w��

	char FilePathBuffer[255] = { "" };						//	�t�@�C���̑��΃p�X�p�̃o�b�t�@
	sprintf_s(FilePathBuffer, CSVFilePath, StageNo);		//	�t�@�C���̑��΃p�X�̃o�b�t�@���X�e�[�W�ԍ��������
	fopen_s(&CSVDataFile, FilePathBuffer, "w");				//	�������ރt�@�C�����w��

	char Buffer[1024];										//	�ǂݍ��݃o�b�t�@

	/*--------------��������t�@�C���̏�������-----------*/

	sprintf_s(												//	�ǂ̎��
		Buffer, 1024, "%d,%d,,,,,,,,,,,,,,,,,,", StageData.MapPanelNo, StageData.MapWallNo);
	fprintf(CSVDataFile, "%s", Buffer);


	//	�}�b�v�`�b�v�̏�������
	for (int ynum = 0; ynum < MAP_HEIGHT_NUM; ynum++)
	{
		sprintf_s(Buffer, 1024, "%d", StageData.BlockData[ynum][0]);	//	1�ڂ̃}�b�v�`�b�v

		//	�}�b�v�`�b�vX���W�̏�������
		for (int XNum = 1; XNum < MAP_WIDTH_NUM; XNum++)
		{
			sprintf_s(										//	�ǂ̎��
				Buffer, 1024, "%s,%d", Buffer, StageData.BlockData[ynum][XNum]);
		}
		fprintf(CSVDataFile, "%s", Buffer);
	}
	fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");				//	���s
	int GimmickNum = 0;										//	�J��Ԃ��g�p
	int CountNum = 0;											//	�J���}�̎g�p��

	/*--------------��������WMR�M�~�b�N�̓ǂݍ���-----------*/

	//	WMR�M�~�b�N�̐�
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StageWMRData.GimmickWMRNum);


	//	WMR�f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < GimmickData.StageWMRData.GimmickWMRNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StageWMRData.GimmickWMR[GimmickNum][0]);	//	1�ڂ̃}�b�v�`�b�v

		//	�c��f�[�^����
		for (int snum = 1; snum < 5; snum++)
		{
			sprintf_s(										//	�ǂ̎��
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StageWMRData.GimmickWMR[GimmickNum][snum]);
			CountNum++;										//	�J�E���g�A�b�v
		}
		//	�c��̃J���}�����
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	�c��̃J���}
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	����
	}

	//	���s((�M�~�b�N�̍ő吔 + ���₷���p�̈�s)-����)
	fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");				//	���s

	/*--------------�������犴���M�~�b�N�̓ǂݍ���-----------*/

	CountNum = 0;												//	������

	//	�����M�~�b�N�̐�
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StagePresData.GimmickPresNum);


	//	�����f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < GimmickData.StagePresData.GimmickPresNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StagePresData.GimmickPres[GimmickNum][0]);	//	1�ڂ̃}�b�v�`�b�v

		//	�c��f�[�^����
		for (int snum = 1; snum < 5; snum++)
		{
			sprintf_s(										//	�ǂ̎��
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StagePresData.GimmickPres[GimmickNum][snum]);
			CountNum++;										//	�J�E���g�A�b�v
		}
		//	�c��̃J���}�����
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	�c��̃J���}
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	����
	}

	//	���s((�M�~�b�N�̍ő吔 + ���₷���p�̈�s)-����)
	for (int GimmickSetNum = GimmickNum; GimmickSetNum < 5; GimmickSetNum++)
	{
		fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");			//	���s
	}

	/*--------------��������ʓd�M�~�b�N�̓ǂݍ���-----------*/

	CountNum = 0;												//	������

	//	�ʓd�M�~�b�N�̐�
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StageEnerData.GimmickEnerNum);


	//	�ʓd�f�[�^�̓ǂݍ���(����)
	for (GimmickNum = 0; GimmickNum < GimmickData.StageEnerData.GimmickEnerNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StageEnerData.GimmickEner[GimmickNum][0]);	//	1�ڂ̃}�b�v�`�b�v

		//	�c��f�[�^����
		for (int snum = 1; snum < 6; snum++)
		{
			sprintf_s(										//	�ǂ̎��
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StageEnerData.GimmickEner[GimmickNum][snum]);
			CountNum++;										//	�J�E���g�A�b�v
		}
		//	�c��̃J���}�����
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	�c��̃J���}
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	����
	}
	fclose(CSVDataFile);									//	�t�@�C�������
}

/*
�X�e�[�W�̓ǂݍ��݃N���X
	CSV�t�@�C������X�e�[�W�f�[�^(�u���b�N�̔z�u���ށE�M�~�b�N�̔z�u����)��ǂݍ���
*/

//	dat�t�@�C������Z�[�u�f�[�^��ǂݍ���
void GameData::Load()
{
	FILE* GameDataFile;												//	�t�@�C���p
	
	char Buffer[10] = { "" };										//	�ǂݍ��݃o�b�t�@

		//	�}�b�v�`�b�v�t�@�C���̎w��
	fopen_s(&GameDataFile, GameFile, "r");

	//	�t�@�C�����Ȃ��ꍇ����
	if (GameDataFile == NULL)return;

	/*--------------��������t�@�C���̓ǂݍ���-----------*/
	fscanf_s(GameDataFile, "%d", &GameSaveData.ReleaseStage);	//	����ς݂̃X�e�[�W�ԍ��Z�b�g
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveSEVolume);	//	���ʉ��ʂ̃Z�b�g
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveBGMVolume);	//	�w�i���ʃZ�b�g
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveUIVolume);	//	�w�i���ʃZ�b�g

	//	�t�@�C�������
	fclose(GameDataFile);
}

//	dat�t�@�C���ɃQ�[���̃Z�[�u�f�[�^����������
void GameData::SaveStageNo(int SetNo)
{
	GameSaveData.ReleaseStage = SetNo;

	FILE* GameDataFile;										//	�t�@�C���p
	//	�t�@�C���̎w��
	fopen_s(&GameDataFile, GameFile, "w");
	/*--------------��������t�@�C���̓ǂݍ���-----------*/

	fprintf(GameDataFile, "%d\n", GameSaveData.ReleaseStage);	//	������Ă���X�e�[�W��ǂݍ���
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveSEVolume);	//	SE�̉��ʂ�ǂݍ���
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveBGMVolume);	//	BGM�̉��ʂ�ǂݍ���
	fprintf(GameDataFile, "%d", GameSaveData.SaveUIVolume);	//	BGM�̉��ʂ�ǂݍ���
	fclose(GameDataFile);									//	�t�@�C�������
}

//	dat�t�@�C���ɉ��̃Z�[�u�f�[�^����������
void GameData::SaveSoundVolume(int SEVolume, int BGMVolume, int UIVolume)
{
	GameSaveData.SaveSEVolume = SEVolume;					//	SE�̉��ʂ��Z�b�g
	GameSaveData.SaveBGMVolume = BGMVolume;					//	BGM�̉��ʂ��Z�b�g
	GameSaveData.SaveUIVolume = UIVolume;					//	UI�̉��ʂ��Z�b�g

	FILE* GameDataFile;										//	�t�@�C���p
	//	�t�@�C���̎w��
	fopen_s(&GameDataFile, GameFile, "w");
	/*--------------��������t�@�C���̓ǂݍ���-----------*/

	fprintf(GameDataFile, "%d\n", GameSaveData.ReleaseStage);	//	������Ă���X�e�[�W����������
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveSEVolume);	//	SE�̉��ʂ���������
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveBGMVolume);	//	BGM�̉��ʂ���������
	fprintf(GameDataFile, "%d", GameSaveData.SaveUIVolume);	//	UI�̉��ʂ���������
	fclose(GameDataFile);									//	�t�@�C�������
}

//	���ʃZ�[�u�f�[�^���
void GameData::LoadSoundVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume)
{
	*pSEVolume = GameSaveData.SaveSEVolume;					//	���ʉ��ʑ��
	*pBGMVolume = GameSaveData.SaveBGMVolume;				//	���ʉ��ʑ��
	*pUIVolume = GameSaveData.SaveUIVolume;					//	���ʉ��ʑ��
}