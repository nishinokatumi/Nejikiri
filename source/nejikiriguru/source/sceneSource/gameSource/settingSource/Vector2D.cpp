#include "Vector2D.h"

/*
	2Dベクトルクラス
	ベクトルを2次元をC++で使用できるようにしたもの
	数値の指定や大きさの出力
*/
//	ベクトルの生成(float X：Xの数値, float Y：Yの数値)
Vector2D::Vector2D(float NumX, float NumY)
{
	this->X = NumX;											//	Xを指定の値に設定
	this->Y = NumY;											//	Yを指定の値に設定
}

//	零ベクトルを出力
Vector2D Vector2D::Zero()
{
	this->X = 0.0f;											//	Xを0に変更
	this->Y = 0.0f;											//	Yを0に変更
	return *this;											//	変更したベクトルを出力
}

//	ベクトルの値を変更し出力
Vector2D Vector2D::Set(float NumX, float NumY)
{
	this->X = NumX;											//	Xを指定数に変更
	this->Y = NumY;											//	Yを指定数に変更
	return *this;											//	変更したベクトルを出力
}

//	ベクトルにベクトルを加算し出力
Vector2D Vector2D::Add(Vector2D Vec)
{
	this->X += Vec.X;										//	Xに指定ベクトルのXを加算
	this->Y += Vec.Y;										//	Yに指定ベクトルのYを加算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルに指定数を加算し出力
Vector2D Vector2D::Add(float NumX, float NumY)
{
	this->X += NumX;										//	Xに指定数を加算
	this->Y += NumY;										//	Yに指定数を加算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルにベクトルを減算し出力
Vector2D Vector2D::Subtract(Vector2D Vec)
{
	this->X -= Vec.X;										//	Xに指定ベクトルのXを減算
	this->Y -= Vec.Y;										//	Yに指定ベクトルのYを減算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルに指定数を減算し出力
Vector2D Vector2D::Subtract(float NumX, float NumY)
{
	this->X -= NumX;										//	Xに指定数を減算
	this->Y -= NumY;										//	Yに指定数を減算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルに数値を乗算し出力
Vector2D Vector2D::Multiply(float Scalar)
{
	this->X *= Scalar;										//	Xに指定数を乗算
	this->Y *= Scalar;										//	Yに指定数を乗算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルにベクトルを乗算し出力
Vector2D Vector2D::Multiply(Vector2D Vec)
{
	this->X *= Vec.X;										//	Xに指定ベクトルのXを乗算
	this->Y *= Vec.Y;										//	Yに指定ベクトルのYを乗算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルに数値を除算し出力
Vector2D Vector2D::Divide(float Scalar)
{
	if (Scalar == 0) return this->Zero();					//	指定数が0の際ベクトルを0にし終わる
	this->X /= Scalar;										//	Xに指定数を除算
	this->Y /= Scalar;										//	Yに指定数を除算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルにベクトルを除算し出力
Vector2D Vector2D::Divide(Vector2D Vec)
{
	if (Vec.X == 0 || Vec.Y == 0) return this->Zero();		//	指定ベクトルのXYどちらかが0の際ベクトルを0にし終わる
	this->X /= Vec.X;										//	Xに指定ベクトルXを除算
	this->Y /= Vec.Y;										//	Yに指定ベクトルYを除算
	return *this;											//	変更したベクトルを出力
}

//	ベクトルの大きさを出力
float Vector2D::Length()
{
	return (float)sqrt(this->LengthSquared());				//	ベクトルの大きさを二乗した数値の平方根を出力
}

//	ベクトルの大きさを二乗した数値を出力
float Vector2D::LengthSquared()
{
	return (this->X * this->X + this->Y * this->Y);			//	ベクトルの大きさを計算し出力する
}

//	ベクトルに指定ベクトルを代入
Vector2D Vector2D::operator =(Vector2D vector)
{
	return this->Set(vector.X, vector.Y);					//	自ベクトルに指定ベクトルを代入し出力
}

//	ベクトルに指定ベクトルを加算代入
Vector2D Vector2D::operator +=(Vector2D vector)
{
	return this->Add(vector);								//	自ベクトルに指定ベクトルを加算し出力
}

//	ベクトルに指定ベクトルを減算代入
Vector2D Vector2D::operator -=(Vector2D vector)
{
	return this->Subtract(vector);							//	自ベクトルに指定ベクトルを減算し出力
}

//	ベクトルに値を乗算
Vector2D Vector2D::operator *=(float scalar)
{
	return this->Multiply(scalar);							//	自ベクトルに指定ベクトルを乗算し出力
}

//	ベクトルに値を除算
Vector2D Vector2D::operator /=(float scalar)
{
	return this->Divide(scalar);							//	自ベクトルに指定ベクトルを除算し出力
}

//	ベクトルに+を乗算
Vector2D Vector2D::operator +()
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result *= 1;										//	返しベクトルに+１乗算し出力
}

//	ベクトルに指定ベクトルを加算
Vector2D Vector2D::operator +(Vector2D vector)
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result.Add(vector);								//	返しベクトルに指定ベクトルを加算し出力
}

//	ベクトルに-を乗算
Vector2D Vector2D::operator -()
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result *= -1;									//	返しベクトルに-１乗算し出力
}

//	ベクトルに指定ベクトルを減算
Vector2D Vector2D::operator -(Vector2D vector)
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result.Subtract(vector);							//	返しベクトルに指定ベクトルを減算し出力
}

//	ベクトルに値を乗算
Vector2D Vector2D::operator *(float scalar)
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result.Multiply(scalar);							//	返しベクトルに指定数乗算し出力
}

//	ベクトルに値を除算
Vector2D Vector2D::operator /(float scalar)
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result.Divide(scalar);							//	返しベクトルに指定数除算し出力
}

//	ベクトルの正規化をする
Vector2D Vector2D::Normalize()
{
	float Len = this->Length();								//	自ベクトルの長さを設定
	if (Len < 0.0001f) return this->Zero();					//	自ベクトルの長さが0限りなく近い場合自ベクトルを0にして出力
	return *this /= Len;									//	自ベクトルを自ベクトルの除算して正規化し出力
}

//	ベクトルの大きさを値にする
Vector2D Vector2D::LengthSet(float Scalar)
{
	Vector2D Result = *this;								//	自ベクトルを返しベクトルを代入(自ベクトルが変化しないために)
	return Result.Normalize() * Scalar;						//	正規化した返しベクトルに指定数を乗算し長さを変えて出力
}

//	ベクトルの内積
float Vector2D::Dot(Vector2D Vec1, Vector2D vec_2)
{
	return Vec1.X * vec_2.X + Vec1.Y * vec_2.Y;				//	指定ベクトル1を指定ベクトル2の内積を出力
}

//	ベクトルの外積
float Vector2D::Cross(Vector2D Vec1, Vector2D vec_2)
{
	return Vec1.X * vec_2.Y - Vec1.Y * vec_2.X;				//	指定ベクトル1を指定ベクトル2の外積を出力
}

//	自ベクトルとベクトルの内積
float Vector2D::Dot(Vector2D Vec)
{
	return (float)(this->X * Vec.X + this->Y * Vec.Y);		//	自ベクトルを指定ベクトルの内積を出力
}

//	自ベクトルとベクトルの外積
float Vector2D::Cross(Vector2D Vec)
{
	return (float)(this->X * Vec.Y - this->Y * Vec.X);		//	自ベクトルを指定ベクトルの外積を出力
}