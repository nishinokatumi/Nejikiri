#pragma once
#pragma once
#include "DxLib.h"


#define VOLUMAX			255;								//	�T�E���h�̍ő剹��

//	���̎��
enum SOUND_NAME
{
	Electricity = 0,	//	�d�C
	Enter,				//	����
	FootStep,			//	������
	GameOver,			//	�Q�[���I�[�o�[
	Gole,				//	�S�[��
	Jump,				//	�W�����v
	Land,				//	���n
	Select,				//	�I��(�J�[�\��)
	Switch,				//	����
	Timelimit,			//	��������
	WMRdown,			//	WMR���[�v(�o)
	Wind,				//	���̉�BGM
	SoundLength,				//	�񋓐�
};

//	���̃t�@�C���p�X
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

//	���p�̃X�e�[�^�X
struct SoundStat
{
	int SoundCatego = 0;									//	���̃J�e�S��...BGM:0,SE:1,UI,2
	float SoundStart = 0.0f;								//	�Đ�����ʒu...0 �` 255
	int SoundVolu = 0;										//	����...0 �` 255
	bool SoundLoop = false;									//	���[�v�邷�邩�ǂ���
};

/*
���̊Ǘ��N���X
	����ǂݍ��݂��ꂼ��ݒ肵�Đ�����
*/
class SEManager
{
private:
	int SoundHandle[SoundLength] = { 0 };						//	���̃f�[�^�n���h��
	float SEBaseVolume = 1.0f;								//	SE�̉��� �ω���0.0�`1.0
	float BGMBaseVolume = 1.0f;								//	BGM�̉��� �ω���0.0�`1.0
	float UIBaseVolume = 1.0f;								//	UI�̉��� �ω���0.0�`1.0

	//	SE���ꂼ��̃X�e�[�^�X
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
	void SoundPlay(int PlaySoundNo);						//	�����Đ�����
	void SoundFinal(int PlaySoundNo);						//	�����~����
	void SoundLoad(float SEVolume, float BGMVolume, float UIVolume);	//	����ǂݍ���
	void SettingVolume(float SEVolume, float BGMVolume, float UIVolume);//	���ʂ�ݒ肷��
	void LoadVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume) {	//	���ʂ�ǂݍ���
		*pSEVolume = (int)(100.0 * SEBaseVolume);						//	���ʉ��ǂݍ���
		*pBGMVolume = (int)(100.0 * BGMBaseVolume);						//	�w�i���ǂݍ���
		*pUIVolume = (int)(100.0 * UIBaseVolume);						//	�V�X�e�����ǂݍ���
	}
	//	�w�艹���Đ�����Ă��邩�m�F����
	bool CheckSE(int PlaySoundNo)
	{
		return CheckSoundMem(SoundHandle[PlaySoundNo]);		//	�����Đ�����Ă��邩�m�F
	}
};