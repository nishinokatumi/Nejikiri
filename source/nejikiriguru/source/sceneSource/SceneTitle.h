#pragma once
#include "SceneBase.h"

/*
�^�C�g����ʃN���X
	�I����ʂւ̗U���������s��
*/
class SceneTitle :public SceneBase
{
private:
	SceneBase* pNextSceneSave = this;						//	���̃V�[���ۑ��p
	int BackGraph;											//	�w�i�摜�n���h��
	int TittleGraph;										//	�^�C�g���摜�n���h��

public:
	SceneTitle();											//	�����ݒ�

	//	�^�C�g����ʂ̏���
	void Initia();											//	��������
	void Final();											//	�ŏI����
	SceneBase* Update();									//	�X�V����
	void BaseUpdate();										//	�X�V�����̓��e
	void Draw();											//	�\������
};