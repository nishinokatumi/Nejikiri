#pragma once
#pragma once
#include "DxLib.h"


#define VOLUMAX			255;								//	サウンドの最大音量

//	音の種類
enum SOUND_NAME
{
	Electricity = 0,	//	電気
	Enter,				//	決定
	FootStep,			//	歩く音
	GameOver,			//	ゲームオーバー
	Gole,				//	ゴール
	Jump,				//	ジャンプ
	Land,				//	着地
	Select,				//	選択中(カーソル)
	Switch,				//	感圧
	Timelimit,			//	制限時間
	WMRdown,			//	WMRワープ(出)
	Wind,				//	風の音BGM
	SoundLength,				//	列挙数
};

//	音のファイルパス
static const char* SEfname[SoundLength] =
{
	"resource/sound/electricity.mp3",
	"resource/sound/enter.mp3",
	"resource/sound/footsteps.mp3",
	"resource/sound/gameover.mp3",
	"resource/sound/gole.mp3",
	"resource/sound/jump.mp3",
	"resource/sound/land.mp3",
	"resource/sound/select.mp3",
	"resource/sound/switch.mp3",
	"resource/sound/timelimit.mp3",
	"resource/sound/warpmobiusring.mp3",
	"resource/sound/windbgm.mp3"
};

//	音用のステータス
struct SoundStat
{
	int SoundCatego = 0;									//	音のカテゴリ...BGM:0,SE:1,UI,2
	float SoundStart = 0.0f;								//	再生する位置...0 ～ 255
	int SoundVolu = 0;										//	音量...0 ～ 255
	bool SoundLoop = false;									//	ループるするかどうか
};

/*
音の管理クラス
	音を読み込みそれぞれ設定し再生する
*/
class SEManager
{
private:
	int SoundHandle[SoundLength] = { 0 };						//	音のデータハンドル
	float SEBaseVolume = 1.0f;								//	SEの音量 変化量0.0～1.0
	float BGMBaseVolume = 1.0f;								//	BGMの音量 変化量0.0～1.0
	float UIBaseVolume = 1.0f;								//	UIの音量 変化量0.0～1.0

	//	SEぞれぞれのステータス
	SoundStat SoundStatData[SoundLength] =
	{
		{1,1.0f,200,false},									//	0	Electricity
		{2,1.0f,190,false},									//	1	Enter
		{1,0.35f,255,true},									//	2	FootStep
		{2,1.0f,200,false},									//	3	GameOver
		{2,1.0f,200,false},									//	4	Gole
		{1,0.35f,215,false},								//	5	Jump
		{1,1.0f,225,false},									//	6	Land
		{2,1.0f,190,false},									//	7	Select
		{1,1.0f,255,false},									//	8	Switch
		{2,1.0f,225,true},									//	9	Timelimit
		{1,0.1f,240,false},									//	11	WMRdown
		{0,1.0f,165,true}									//	12	wind
	};

public:
	void SoundPlay(int PlaySoundNo);						//	音を再生する
	void SoundFinal(int PlaySoundNo);						//	音を停止する
	void SoundLoad(float SEVolume, float BGMVolume, float UIVolume);	//	音を読み込む
	void SettingVolume(float SEVolume, float BGMVolume, float UIVolume);//	音量を設定する
	void LoadVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume) {	//	音量を読み込む
		*pSEVolume = (int)(100.0 * SEBaseVolume);						//	効果音読み込み
		*pBGMVolume = (int)(100.0 * BGMBaseVolume);						//	背景音読み込み
		*pUIVolume = (int)(100.0 * UIBaseVolume);						//	システム音読み込み
	}
	//	指定音が再生されているか確認する
	bool CheckSE(int PlaySoundNo)
	{
		return CheckSoundMem(SoundHandle[PlaySoundNo]);		//	音が再生されているか確認
	}
};