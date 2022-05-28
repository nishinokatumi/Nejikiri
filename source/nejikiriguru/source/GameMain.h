#pragma once
#include "SceneSource/GameSource/SettingSource/Gameinformation.h"

class SceneManager;

/*
�Q�[���̊��N���X
	DXLib�ŃQ�[���𓮂������߂̐ݒ���s��
*/
class GameMain
{
private:
	SceneManager* GameMainSceneManager;						//	�V�[���Ǘ��N���X
public:
	static const int WinWidth = GAME_WIN_WIDTH;				//	�E�B���h�E�̕� Default 640
	static const int WinHeight = GAME_WIN_HEIGHT;			//	�E�B���h�E�̍��� Default 480

	GameMain();												//	�����ݒ�
	~GameMain();											//	�Q�[�������ۂ̏���
	void Run();												//	�Q�[���𑖂点��
};