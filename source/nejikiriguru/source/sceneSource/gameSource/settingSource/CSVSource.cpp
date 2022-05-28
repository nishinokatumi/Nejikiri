#include "CSVHeader.h"


/*
ステージの読み込みクラス
	CSVファイルからステージデータ(ブロックの配置や種類・ギミックの配置や情報)を読み込む
*/

//	ステージのデータをCSVファイルから読み込みポインタで値を渡す
void CSVLoad::StageDataLoad(int StageNo, MAP_INFO::Stage* pStageData, MAP_INFO::GimmickData* pGimmickData)
{
	FILE* CSVDataFile;

	//	マップチップファイルの指定
	char FilePathBuffer[255] = { "" };						//	ファイルの相対パス用のバッファ
	sprintf_s(FilePathBuffer, CSVFilePath, StageNo);		//	ファイルの相対パスのバッファをステージ番号から入力
	fopen_s(&CSVDataFile, FilePathBuffer, "r");				//	読み込むファイルを指定

	char* ConText;											//	位置情報の格納
	char Buffer[1024] = { "" };								//	読み込みバッファ

	/*--------------ここからファイルの読み込み-----------*/

	//	マップのブロックの種類の読み込み
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	一行読み込み
	char* DividedNum = strtok_s(Buffer, ",", &ConText);		//	分割

	pStageData->MapPanelNo = atoi(DividedNum);				//	パネルセット
	DividedNum = strtok_s(NULL, ",", &ConText);				//	次の要素
	pStageData->MapWallNo = atoi(DividedNum);				//	壁セット

	//	マップチップの読み込み
	for (int YNum = 0; YNum < MAP_HEIGHT_NUM; YNum++)
	{
		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	一行読み込み
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	分割
		pStageData->BlockData[YNum][0] = atoi(DividedNum);	//	マップチップの最初をセット

		//	残りを代入
		for (int XNum = 1; XNum < MAP_WIDTH_NUM; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	分割
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	無かったら終わり
			if (strlen(DividedNum) <= 0)break;						//	要素が無かったら終わり
			pStageData->BlockData[YNum][XNum] = atoi(DividedNum);	//	それ以外入力
		}

	}

	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	読み込みの改行

	int GimmickNum = 0;										//	繰り返し使用


	/*--------------ここからWMRギミックの読み込み-----------*/

	//	WMRギミックの数
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	一行読み込み
	DividedNum = strtok_s(Buffer, ",", &ConText);			//	分割
	pGimmickData->StageWMRData.GimmickWMRNum = atoi(DividedNum);	//	読み込みセット


	//	WMRデータの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StageWMRData.GimmickWMRNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	一行読み込み
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	分割
		pGimmickData->StageWMRData.GimmickWMR[GimmickNum][0] = atoi(DividedNum);//	ギミックの最初をセット

		//	残りを代入
		for (int XNum = 1; XNum < 5; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	分割
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	無かったら終わり
			if (strlen(DividedNum) <= 0)break;				//	要素が無かったら終わり
			pGimmickData->StageWMRData.GimmickWMR[GimmickNum][XNum] = atoi(DividedNum);//	それ以外入力
		}

	}

	//	改行((ギミックの最大数 + 見やすい用の一行)-数分)
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	次の行へ



	/*--------------ここから感圧ギミックの読み込み-----------*/

	//	感圧ギミックの数
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	一行読み込み
	DividedNum = strtok_s(Buffer, ",", &ConText);			//	分割
	pGimmickData->StagePresData.GimmickPresNum = atoi(DividedNum);	//	読み込みセット


	//	感圧データの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StagePresData.GimmickPresNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	一行読み込み
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	分割
		pGimmickData->StagePresData.GimmickPres[GimmickNum][0] = atoi(DividedNum);//	ギミックの最初をセット

		//	残りを代入
		for (int XNum = 1; XNum < 5; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);		//	分割
			if (DividedNum == NULL || DividedNum[0] == '\0')break;	//	無かったら終わり
			if (strlen(DividedNum) <= 0)break;						//	要素が無かったら終わり
			pGimmickData->StagePresData.GimmickPres[GimmickNum][XNum] = atoi(DividedNum);//	それ以外入力
		}

	}

	//	改行((ギミックの最大数 + 見やすい用の一行)-数分)
	for (int GimmickSetNum = GimmickNum; GimmickSetNum < 5; GimmickSetNum++)
	{
		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	次の行へ
	}

	/*--------------ここから通電ギミックの読み込み-----------*/

	//	通電ギミックの数
	fgets(Buffer, sizeof(Buffer), CSVDataFile);				//	一行読み込み
	DividedNum = strtok_s(Buffer, ",", &ConText);					//	分割
	pGimmickData->StageEnerData.GimmickEnerNum = atoi(DividedNum);	//	読み込みセット


	//	通電データの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < pGimmickData->StageEnerData.GimmickEnerNum; GimmickNum++)
	{


		fgets(Buffer, sizeof(Buffer), CSVDataFile);			//	一行読み込み
		DividedNum = strtok_s(Buffer, ",", &ConText);		//	分割
		pGimmickData->StageEnerData.GimmickEner[GimmickNum][0] = atoi(DividedNum);//	ギミックの最初をセット

		//	残りを代入
		for (int XNum = 1; XNum < 6; XNum++)
		{
			DividedNum = strtok_s(NULL, ",", &ConText);				//	分割
			if (DividedNum == NULL || DividedNum[0] == '\0')break;			//	無かったら終わり
			if (strlen(DividedNum) <= 0)break;						//	要素が無かったら終わり
			pGimmickData->StageEnerData.GimmickEner[GimmickNum][XNum] = atoi(DividedNum);//	それ以外入力
		}

	}

	fclose(CSVDataFile);									//	ファイルを閉じる
}

/*
ステージの書き込みクラス
	CSVファイルにステージデータ(ブロックの配置や種類・ギミックの配置や情報)を書き込む
*/

//	ステージのデータをCSVファイルに合わせて書き込む
void CSVWrite::StageDataWrite(int StageNo, MAP_INFO::Stage StageData, MAP_INFO::GimmickData GimmickData)
{
	FILE* CSVDataFile;										//	ファイル用
	//	マップチップファイルの指定

	char FilePathBuffer[255] = { "" };						//	ファイルの相対パス用のバッファ
	sprintf_s(FilePathBuffer, CSVFilePath, StageNo);		//	ファイルの相対パスのバッファをステージ番号から入力
	fopen_s(&CSVDataFile, FilePathBuffer, "w");				//	書き込むファイルを指定

	char Buffer[1024];										//	読み込みバッファ

	/*--------------ここからファイルの書き込み-----------*/

	sprintf_s(												//	壁の種類
		Buffer, 1024, "%d,%d,,,,,,,,,,,,,,,,,,", StageData.MapPanelNo, StageData.MapWallNo);
	fprintf(CSVDataFile, "%s", Buffer);


	//	マップチップの書き込み
	for (int ynum = 0; ynum < MAP_HEIGHT_NUM; ynum++)
	{
		sprintf_s(Buffer, 1024, "%d", StageData.BlockData[ynum][0]);	//	1個目のマップチップ

		//	マップチップX座標の書き込み
		for (int XNum = 1; XNum < MAP_WIDTH_NUM; XNum++)
		{
			sprintf_s(										//	壁の種類
				Buffer, 1024, "%s,%d", Buffer, StageData.BlockData[ynum][XNum]);
		}
		fprintf(CSVDataFile, "%s", Buffer);
	}
	fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");				//	改行
	int GimmickNum = 0;										//	繰り返し使用
	int CountNum = 0;											//	カンマの使用回数

	/*--------------ここからWMRギミックの読み込み-----------*/

	//	WMRギミックの数
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StageWMRData.GimmickWMRNum);


	//	WMRデータの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < GimmickData.StageWMRData.GimmickWMRNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StageWMRData.GimmickWMR[GimmickNum][0]);	//	1個目のマップチップ

		//	残りデータを代入
		for (int snum = 1; snum < 5; snum++)
		{
			sprintf_s(										//	壁の種類
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StageWMRData.GimmickWMR[GimmickNum][snum]);
			CountNum++;										//	カウントアップ
		}
		//	残りのカンマを入力
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	残りのカンマ
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	入力
	}

	//	改行((ギミックの最大数 + 見やすい用の一行)-数分)
	fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");				//	改行

	/*--------------ここから感圧ギミックの読み込み-----------*/

	CountNum = 0;												//	初期化

	//	感圧ギミックの数
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StagePresData.GimmickPresNum);


	//	感圧データの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < GimmickData.StagePresData.GimmickPresNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StagePresData.GimmickPres[GimmickNum][0]);	//	1個目のマップチップ

		//	残りデータを代入
		for (int snum = 1; snum < 5; snum++)
		{
			sprintf_s(										//	壁の種類
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StagePresData.GimmickPres[GimmickNum][snum]);
			CountNum++;										//	カウントアップ
		}
		//	残りのカンマを入力
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	残りのカンマ
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	入力
	}

	//	改行((ギミックの最大数 + 見やすい用の一行)-数分)
	for (int GimmickSetNum = GimmickNum; GimmickSetNum < 5; GimmickSetNum++)
	{
		fprintf(CSVDataFile, ",,,,,,,,,,,,,,,,,,");			//	改行
	}

	/*--------------ここから通電ギミックの読み込み-----------*/

	CountNum = 0;												//	初期化

	//	通電ギミックの数
	fprintf(CSVDataFile, "%d,,,,,,,,,,,,,,,,,,", GimmickData.StageEnerData.GimmickEnerNum);


	//	通電データの読み込み(数分)
	for (GimmickNum = 0; GimmickNum < GimmickData.StageEnerData.GimmickEnerNum; GimmickNum++)
	{
		sprintf_s(Buffer, 1024, "%d", GimmickData.StageEnerData.GimmickEner[GimmickNum][0]);	//	1個目のマップチップ

		//	残りデータを代入
		for (int snum = 1; snum < 6; snum++)
		{
			sprintf_s(										//	壁の種類
				Buffer, 1024, "%s,%d", Buffer, GimmickData.StageEnerData.GimmickEner[GimmickNum][snum]);
			CountNum++;										//	カウントアップ
		}
		//	残りのカンマを入力
		for (int cnyu = 0; cnyu < CSV_MAX_COMMA - CountNum; cnyu++)
		{
			sprintf_s(Buffer, 1024, "%s,", Buffer);			//	残りのカンマ
		}
		fprintf(CSVDataFile, "%s", Buffer);					//	入力
	}
	fclose(CSVDataFile);									//	ファイルを閉じる
}

/*
ステージの読み込みクラス
	CSVファイルからステージデータ(ブロックの配置や種類・ギミックの配置や情報)を読み込む
*/

//	datファイルからセーブデータを読み込む
void GameData::Load()
{
	FILE* GameDataFile;												//	ファイル用
	
	char Buffer[10] = { "" };										//	読み込みバッファ

		//	マップチップファイルの指定
	fopen_s(&GameDataFile, GameFile, "r");

	//	ファイルがない場合無視
	if (GameDataFile == NULL)return;

	/*--------------ここからファイルの読み込み-----------*/
	fscanf_s(GameDataFile, "%d", &GameSaveData.ReleaseStage);	//	解放済みのステージ番号セット
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveSEVolume);	//	効果音量のセット
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveBGMVolume);	//	背景音量セット
	fscanf_s(GameDataFile, "%d", &GameSaveData.SaveUIVolume);	//	背景音量セット

	//	ファイルを閉じる
	fclose(GameDataFile);
}

//	datファイルにゲームのセーブデータを書き込む
void GameData::SaveStageNo(int SetNo)
{
	GameSaveData.ReleaseStage = SetNo;

	FILE* GameDataFile;										//	ファイル用
	//	ファイルの指定
	fopen_s(&GameDataFile, GameFile, "w");
	/*--------------ここからファイルの読み込み-----------*/

	fprintf(GameDataFile, "%d\n", GameSaveData.ReleaseStage);	//	解放しているステージを読み込む
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveSEVolume);	//	SEの音量を読み込む
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveBGMVolume);	//	BGMの音量を読み込む
	fprintf(GameDataFile, "%d", GameSaveData.SaveUIVolume);	//	BGMの音量を読み込む
	fclose(GameDataFile);									//	ファイルを閉じる
}

//	datファイルに音のセーブデータを書き込む
void GameData::SaveSoundVolume(int SEVolume, int BGMVolume, int UIVolume)
{
	GameSaveData.SaveSEVolume = SEVolume;					//	SEの音量をセット
	GameSaveData.SaveBGMVolume = BGMVolume;					//	BGMの音量をセット
	GameSaveData.SaveUIVolume = UIVolume;					//	UIの音量をセット

	FILE* GameDataFile;										//	ファイル用
	//	ファイルの指定
	fopen_s(&GameDataFile, GameFile, "w");
	/*--------------ここからファイルの読み込み-----------*/

	fprintf(GameDataFile, "%d\n", GameSaveData.ReleaseStage);	//	解放しているステージを書き込み
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveSEVolume);	//	SEの音量を書き込み
	fprintf(GameDataFile, "%d\n", GameSaveData.SaveBGMVolume);	//	BGMの音量を書き込み
	fprintf(GameDataFile, "%d", GameSaveData.SaveUIVolume);	//	UIの音量を書き込み
	fclose(GameDataFile);									//	ファイルを閉じる
}

//	音量セーブデータ代入
void GameData::LoadSoundVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume)
{
	*pSEVolume = GameSaveData.SaveSEVolume;					//	効果音量代入
	*pBGMVolume = GameSaveData.SaveBGMVolume;				//	効果音量代入
	*pUIVolume = GameSaveData.SaveUIVolume;					//	効果音量代入
}