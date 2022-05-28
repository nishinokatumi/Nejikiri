#include "Vector2D.h"

/*
	2D�x�N�g���N���X
	�x�N�g����2������C++�Ŏg�p�ł���悤�ɂ�������
	���l�̎w���傫���̏o��
*/
//	�x�N�g���̐���(float X�FX�̐��l, float Y�FY�̐��l)
Vector2D::Vector2D(float NumX, float NumY)
{
	this->X = NumX;											//	X���w��̒l�ɐݒ�
	this->Y = NumY;											//	Y���w��̒l�ɐݒ�
}

//	��x�N�g�����o��
Vector2D Vector2D::Zero()
{
	this->X = 0.0f;											//	X��0�ɕύX
	this->Y = 0.0f;											//	Y��0�ɕύX
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���̒l��ύX���o��
Vector2D Vector2D::Set(float NumX, float NumY)
{
	this->X = NumX;											//	X���w�萔�ɕύX
	this->Y = NumY;											//	Y���w�萔�ɕύX
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ƀx�N�g�������Z���o��
Vector2D Vector2D::Add(Vector2D Vec)
{
	this->X += Vec.X;										//	X�Ɏw��x�N�g����X�����Z
	this->Y += Vec.Y;										//	Y�Ɏw��x�N�g����Y�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ɏw�萔�����Z���o��
Vector2D Vector2D::Add(float NumX, float NumY)
{
	this->X += NumX;										//	X�Ɏw�萔�����Z
	this->Y += NumY;										//	Y�Ɏw�萔�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ƀx�N�g�������Z���o��
Vector2D Vector2D::Subtract(Vector2D Vec)
{
	this->X -= Vec.X;										//	X�Ɏw��x�N�g����X�����Z
	this->Y -= Vec.Y;										//	Y�Ɏw��x�N�g����Y�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ɏw�萔�����Z���o��
Vector2D Vector2D::Subtract(float NumX, float NumY)
{
	this->X -= NumX;										//	X�Ɏw�萔�����Z
	this->Y -= NumY;										//	Y�Ɏw�萔�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���ɐ��l����Z���o��
Vector2D Vector2D::Multiply(float Scalar)
{
	this->X *= Scalar;										//	X�Ɏw�萔����Z
	this->Y *= Scalar;										//	Y�Ɏw�萔����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ƀx�N�g������Z���o��
Vector2D Vector2D::Multiply(Vector2D Vec)
{
	this->X *= Vec.X;										//	X�Ɏw��x�N�g����X����Z
	this->Y *= Vec.Y;										//	Y�Ɏw��x�N�g����Y����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���ɐ��l�����Z���o��
Vector2D Vector2D::Divide(float Scalar)
{
	if (Scalar == 0) return this->Zero();					//	�w�萔��0�̍ۃx�N�g����0�ɂ��I���
	this->X /= Scalar;										//	X�Ɏw�萔�����Z
	this->Y /= Scalar;										//	Y�Ɏw�萔�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���Ƀx�N�g�������Z���o��
Vector2D Vector2D::Divide(Vector2D Vec)
{
	if (Vec.X == 0 || Vec.Y == 0) return this->Zero();		//	�w��x�N�g����XY�ǂ��炩��0�̍ۃx�N�g����0�ɂ��I���
	this->X /= Vec.X;										//	X�Ɏw��x�N�g��X�����Z
	this->Y /= Vec.Y;										//	Y�Ɏw��x�N�g��Y�����Z
	return *this;											//	�ύX�����x�N�g�����o��
}

//	�x�N�g���̑傫�����o��
float Vector2D::Length()
{
	return (float)sqrt(this->LengthSquared());				//	�x�N�g���̑傫�����悵�����l�̕��������o��
}

//	�x�N�g���̑傫�����悵�����l���o��
float Vector2D::LengthSquared()
{
	return (this->X * this->X + this->Y * this->Y);			//	�x�N�g���̑傫�����v�Z���o�͂���
}

//	�x�N�g���Ɏw��x�N�g������
Vector2D Vector2D::operator =(Vector2D vector)
{
	return this->Set(vector.X, vector.Y);					//	���x�N�g���Ɏw��x�N�g���������o��
}

//	�x�N�g���Ɏw��x�N�g�������Z���
Vector2D Vector2D::operator +=(Vector2D vector)
{
	return this->Add(vector);								//	���x�N�g���Ɏw��x�N�g�������Z���o��
}

//	�x�N�g���Ɏw��x�N�g�������Z���
Vector2D Vector2D::operator -=(Vector2D vector)
{
	return this->Subtract(vector);							//	���x�N�g���Ɏw��x�N�g�������Z���o��
}

//	�x�N�g���ɒl����Z
Vector2D Vector2D::operator *=(float scalar)
{
	return this->Multiply(scalar);							//	���x�N�g���Ɏw��x�N�g������Z���o��
}

//	�x�N�g���ɒl�����Z
Vector2D Vector2D::operator /=(float scalar)
{
	return this->Divide(scalar);							//	���x�N�g���Ɏw��x�N�g�������Z���o��
}

//	�x�N�g����+����Z
Vector2D Vector2D::operator +()
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result *= 1;										//	�Ԃ��x�N�g����+�P��Z���o��
}

//	�x�N�g���Ɏw��x�N�g�������Z
Vector2D Vector2D::operator +(Vector2D vector)
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result.Add(vector);								//	�Ԃ��x�N�g���Ɏw��x�N�g�������Z���o��
}

//	�x�N�g����-����Z
Vector2D Vector2D::operator -()
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result *= -1;									//	�Ԃ��x�N�g����-�P��Z���o��
}

//	�x�N�g���Ɏw��x�N�g�������Z
Vector2D Vector2D::operator -(Vector2D vector)
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result.Subtract(vector);							//	�Ԃ��x�N�g���Ɏw��x�N�g�������Z���o��
}

//	�x�N�g���ɒl����Z
Vector2D Vector2D::operator *(float scalar)
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result.Multiply(scalar);							//	�Ԃ��x�N�g���Ɏw�萔��Z���o��
}

//	�x�N�g���ɒl�����Z
Vector2D Vector2D::operator /(float scalar)
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result.Divide(scalar);							//	�Ԃ��x�N�g���Ɏw�萔���Z���o��
}

//	�x�N�g���̐��K��������
Vector2D Vector2D::Normalize()
{
	float Len = this->Length();								//	���x�N�g���̒�����ݒ�
	if (Len < 0.0001f) return this->Zero();					//	���x�N�g���̒�����0����Ȃ��߂��ꍇ���x�N�g����0�ɂ��ďo��
	return *this /= Len;									//	���x�N�g�������x�N�g���̏��Z���Đ��K�����o��
}

//	�x�N�g���̑傫����l�ɂ���
Vector2D Vector2D::LengthSet(float Scalar)
{
	Vector2D Result = *this;								//	���x�N�g����Ԃ��x�N�g������(���x�N�g�����ω����Ȃ����߂�)
	return Result.Normalize() * Scalar;						//	���K�������Ԃ��x�N�g���Ɏw�萔����Z��������ς��ďo��
}

//	�x�N�g���̓���
float Vector2D::Dot(Vector2D Vec1, Vector2D vec_2)
{
	return Vec1.X * vec_2.X + Vec1.Y * vec_2.Y;				//	�w��x�N�g��1���w��x�N�g��2�̓��ς��o��
}

//	�x�N�g���̊O��
float Vector2D::Cross(Vector2D Vec1, Vector2D vec_2)
{
	return Vec1.X * vec_2.Y - Vec1.Y * vec_2.X;				//	�w��x�N�g��1���w��x�N�g��2�̊O�ς��o��
}

//	���x�N�g���ƃx�N�g���̓���
float Vector2D::Dot(Vector2D Vec)
{
	return (float)(this->X * Vec.X + this->Y * Vec.Y);		//	���x�N�g�����w��x�N�g���̓��ς��o��
}

//	���x�N�g���ƃx�N�g���̊O��
float Vector2D::Cross(Vector2D Vec)
{
	return (float)(this->X * Vec.Y - this->Y * Vec.X);		//	���x�N�g�����w��x�N�g���̊O�ς��o��
}