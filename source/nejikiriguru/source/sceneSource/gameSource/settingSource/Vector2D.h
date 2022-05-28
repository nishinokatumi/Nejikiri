#pragma once
#include <math.h>
#define PI 3.1415926535897932384626433832795f			//	�~����

/*
	2D�x�N�g���N���X
	�x�N�g����2������C++�Ŏg�p�ł���悤�ɂ�������
	���l�̎w���傫���̏o��
*/
class Vector2D
{
public:
	//�ϐ�
	float X = 0.0f;											//X�̐��l
	float Y = 0.0f;											//Y�̐��l

	//�����ݒ�
	Vector2D(float NumX, float NumY);						//	�x�N�g���̐���(float X�FX�̐��l, float Y�FY�̐��l)

	//�x�N�g���̓��͂Əo��
	Vector2D Zero();										//	��x�N�g�����o��
	Vector2D Set(float NumX, float NumY);					//	�x�N�g���̒l��ύX���o��
	Vector2D Add(Vector2D Vec);								//	�x�N�g���Ƀx�N�g�������Z���o��
	Vector2D Add(float NumX, float NumY);					//	�x�N�g���Ɏw�萔�����Z���o��
	Vector2D Subtract(Vector2D Vec);						//	�x�N�g���Ƀx�N�g�������Z���o��
	Vector2D Subtract(float NumX, float NumY);				//	�x�N�g���Ɏw�萔�����Z���o��
	Vector2D Multiply(float Scalar);						//	�x�N�g���ɐ��l����Z���o��
	Vector2D Multiply(Vector2D Vec);						//	�x�N�g���Ƀx�N�g������Z���o��
	Vector2D Divide(float Scalar);							//	�x�N�g���ɐ��l�����Z���o��
	Vector2D Divide(Vector2D Vec);							//	�x�N�g���Ƀx�N�g�������Z���o��
	float Length();											//	�x�N�g���̑傫�����o��
	float LengthSquared();									//	�x�N�g���̑傫�����悵�����l���o��

	//���Z�q�̃I�[�o�[���[�h
	Vector2D operator =(Vector2D Vec);						//	�x�N�g���Ɏw��x�N�g������
	Vector2D operator +=(Vector2D Vec);						//	�x�N�g���Ɏw��x�N�g�������Z���
	Vector2D operator -=(Vector2D Vec);						//	�x�N�g���Ɏw��x�N�g�������Z���
	Vector2D operator *=(float Scalar);						//	�x�N�g���ɒl����Z
	Vector2D operator /=(float Scalar);						//	�x�N�g���ɒl�����Z
	Vector2D operator +();									//	�x�N�g����+����Z
	Vector2D operator +(Vector2D Vec);						//	�x�N�g���Ɏw��x�N�g�������Z
	Vector2D operator -();									//	�x�N�g����-����Z
	Vector2D operator -(Vector2D Vec);						//	�x�N�g���Ɏw��x�N�g�������Z
	Vector2D operator *(float Scalar);						//	�x�N�g���ɒl����Z
	Vector2D operator /(float Scalar);						//	�x�N�g���ɒl�����Z

	//�x�N�g���̌v�Z��
	Vector2D Normalize();									//	�x�N�g���̐��K��������
	Vector2D LengthSet(float Scalar);						//	�x�N�g���̑傫����l�ɂ���
	static float Dot(Vector2D Vec1, Vector2D Vec2);			//	�x�N�g���̓���
	static float Cross(Vector2D Vec1, Vector2D Vec2);		//	�x�N�g���̊O��
	float Dot(Vector2D Vec);								//	���x�N�g���ƃx�N�g���̓���
	float Cross(Vector2D Vec);								//	���x�N�g���ƃx�N�g���̊O��
};

