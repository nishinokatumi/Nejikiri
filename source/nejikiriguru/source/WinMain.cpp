#include "DxLib.h"
#include "GameMain.h"
#include "sceneSource/SceneGame.h"
#include "sceneSource/SceneSelect.h"
#include "sceneSource/SceneTitle.h"

/*
WinMain�֐�
�������X�^�[�g
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �Q�[�����C���N���X�̍쐬
	GameMain gameMain;

	// �Q�[���J�n�@���ŃQ�[�����[�v���s��
	gameMain.Run();

	// Run�֐��𔲂��Ă�����Q�[���I��
	return 0;
};