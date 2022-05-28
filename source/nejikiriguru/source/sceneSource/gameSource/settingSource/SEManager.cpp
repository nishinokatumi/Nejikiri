#include "SEManager.h"

/*
���̊Ǘ��N���X
	����ǂݍ��݂��ꂼ��ݒ肵�Đ�����
*/

//	�����Đ�����
void SEManager::SoundPlay(int PlaySoundNo)
{
	//	�����Đ�����Ă��邩�̊m�F
	if (CheckSoundMem(SoundHandle[PlaySoundNo]) == false) {
		//	�Đ�����Ă��Ȃ����...

		int PlayTypeSet = DX_PLAYTYPE_BACK;					//	�o�b�N�O���E���h�Đ�

		//	�I�������������[�v���鉹�̎��Ƀ��[�v����Đ��ɕύX
		if (SoundStatData[PlaySoundNo].SoundLoop) PlayTypeSet = DX_PLAYTYPE_LOOP;

		//	�w��̉����Đ�����
		PlaySoundMem(SoundHandle[PlaySoundNo], PlayTypeSet, true);
	}
}

//	�����~����
void SEManager::SoundFinal(int PlaySoundNo)
{
	StopSoundMem(SoundHandle[PlaySoundNo]);					//	�w��̉����~����
}

//	����ǂݍ���
void SEManager::SoundLoad(float BGMVolume, float SEVolume, float UIVolume)
{
	//	���̎�ނ̐������J��Ԃ�
	for (int SoundNo = 0; SoundNo < SOUND_NAME::SoundLength; SoundNo++)
	{

		//	�ǂݍ��މ��̒�����ݒ�
		SetCreateSoundTimeStretchRate(SoundStatData[SoundNo].SoundStart);
		SoundHandle[SoundNo] = LoadSoundMem(SEfname[SoundNo]);	//	����ǂݍ��ݕۑ�����
	}
	SettingVolume(BGMVolume, SEVolume, UIVolume);		//	���ʂ̐ݒ������
}

//	���ʂ�ݒ肷��
void SEManager::SettingVolume(float BGMVolume, float SEVolume, float UIVolume)
{
	BGMBaseVolume = BGMVolume;							//	�w�i����{���X�V
	SEBaseVolume = SEVolume;								//	���ʉ���{���X�V
	UIBaseVolume = UIVolume;								//	�V�X�e������{���X�V

	//	���̎�ނ̐������J��Ԃ�
	for (int SoundNo = 0; SoundNo < SOUND_NAME::SoundLength; SoundNo++)
	{
		//	���̍Đ��ʒu��ݒ肷��
		SetCurrentPositionSoundMem((int)(SoundStatData[SoundNo].SoundStart * 44100), SoundHandle[SoundNo]);

		//	���̃J�e�S���m�F
		if (SoundStatData[SoundNo].SoundCatego == 0)
		{
			//	�J�e�S����BGM�̍�...
			//	���ʂ����̃X�e�[�^�X��BGM�S�̂̉��ʂ���ݒ肷��
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (BGMVolume)), SoundHandle[SoundNo]);
		}
		else if (SoundStatData[SoundNo].SoundCatego == 1)
		{
			//	�J�e�S����SE�̍�...
			//	���ʂ����̃X�e�[�^�X��SE�S�̂̉��ʂ���ݒ肷��
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (SEVolume)), SoundHandle[SoundNo]);
		}
		else if (SoundStatData[SoundNo].SoundCatego == 2)
		{
			//	�J�e�S����UI�̍�...
			//	���ʂ����̃X�e�[�^�X��UI�S�̂̉��ʂ���ݒ肷��
			ChangeVolumeSoundMem((int)((SoundStatData[SoundNo].SoundVolu) * (UIVolume)), SoundHandle[SoundNo]);
		}
	}
}