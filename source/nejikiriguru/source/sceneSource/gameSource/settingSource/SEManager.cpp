#include "SEManager.h"

/*
音の管理クラス
	音を読み込みそれぞれ設定し再生する
*/

//	音を再生する
void SEManager::SoundPlay(int PlaySoundNo)
{
	//	音が再生されているかの確認
	if (CheckSoundMem(SoundHandle[PlaySoundNo]) == false) {
		//	再生されていなければ...

		int PlayTypeSet = DX_PLAYTYPE_BACK;					//	バックグラウンド再生

		//	選択した音がループする音の時にループする再生に変更
		if (SoundStatData[PlaySoundNo].SoundLoop) PlayTypeSet = DX_PLAYTYPE_LOOP;

		//	指定の音を再生する
		PlaySoundMem(SoundHandle[PlaySoundNo], PlayTypeSet, true);
	}
}

//	音を停止する
void SEManager::SoundFinal(int PlaySoundNo)
{
	StopSoundMem(SoundHandle[PlaySoundNo]);					//	指定の音を停止する
}

//	音を読み込む
void SEManager::SoundLoad(float BGMVolume, float SEVolume, float UIVolume)
{
	//	音の種類の数だけ繰り返す
	for (int SoundNo = 0; SoundNo < SOUND_NAME::SoundLength; SoundNo++)
	{

		//	読み込む音の長さを設定
		SetCreateSoundTimeStretchRate(SoundStatData[SoundNo].SoundStart);
		SoundHandle[SoundNo] = LoadSoundMem(SEfname[SoundNo]);	//	音を読み込み保存する
	}
	SettingVolume(BGMVolume, SEVolume, UIVolume);		//	音量の設定をする
}

//	音量を設定する
void SEManager::SettingVolume(float BGMVolume, float SEVolume, float UIVolume)
{
	BGMBaseVolume = BGMVolume;							//	背景音基本を更新
	SEBaseVolume = SEVolume;								//	効果音基本を更新
	UIBaseVolume = UIVolume;								//	システム音基本を更新

	//	音の種類の数だけ繰り返す
	for (int SoundNo = 0; SoundNo < SOUND_NAME::SoundLength; SoundNo++)
	{
		//	音の再生位置を設定する
		SetCurrentPositionSoundMem((int)(SoundStatData[SoundNo].SoundStart * 44100), SoundHandle[SoundNo]);

		//	音のカテゴリ確認
		if (SoundStatData[SoundNo].SoundCatego == 0)
		{
			//	カテゴリがBGMの際...
			//	音量を音のステータスとBGM全体の音量から設定する
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (BGMVolume)), SoundHandle[SoundNo]);
		}
		else if (SoundStatData[SoundNo].SoundCatego == 1)
		{
			//	カテゴリがSEの際...
			//	音量を音のステータスとSE全体の音量から設定する
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (SEVolume)), SoundHandle[SoundNo]);
		}
		else if (SoundStatData[SoundNo].SoundCatego == 2)
		{
			//	カテゴリがUIの際...
			//	音量を音のステータスとUI全体の音量から設定する
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (UIVolume)), SoundHandle[SoundNo]);
		}
	}
}