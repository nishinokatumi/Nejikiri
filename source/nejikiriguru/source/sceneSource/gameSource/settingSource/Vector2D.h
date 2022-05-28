#pragma once
#include <math.h>
#define PI 3.1415926535897932384626433832795f			//	円周率

/*
	2Dベクトルクラス
	ベクトルを2次元をC++で使用できるようにしたもの
	数値の指定や大きさの出力
*/
class Vector2D
{
public:
	//変数
	float X = 0.0f;											//Xの数値
	float Y = 0.0f;											//Yの数値

	//初期設定
	Vector2D(float NumX, float NumY);						//	ベクトルの生成(float X：Xの数値, float Y：Yの数値)

	//ベクトルの入力と出力
	Vector2D Zero();										//	零ベクトルを出力
	Vector2D Set(float NumX, float NumY);					//	ベクトルの値を変更し出力
	Vector2D Add(Vector2D Vec);								//	ベクトルにベクトルを加算し出力
	Vector2D Add(float NumX, float NumY);					//	ベクトルに指定数を加算し出力
	Vector2D Subtract(Vector2D Vec);						//	ベクトルにベクトルを減算し出力
	Vector2D Subtract(float NumX, float NumY);				//	ベクトルに指定数を減算し出力
	Vector2D Multiply(float Scalar);						//	ベクトルに数値を乗算し出力
	Vector2D Multiply(Vector2D Vec);						//	ベクトルにベクトルを乗算し出力
	Vector2D Divide(float Scalar);							//	ベクトルに数値を除算し出力
	Vector2D Divide(Vector2D Vec);							//	ベクトルにベクトルを除算し出力
	float Length();											//	ベクトルの大きさを出力
	float LengthSquared();									//	ベクトルの大きさを二乗した数値を出力

	//演算子のオーバーロード
	Vector2D operator =(Vector2D Vec);						//	ベクトルに指定ベクトルを代入
	Vector2D operator +=(Vector2D Vec);						//	ベクトルに指定ベクトルを加算代入
	Vector2D operator -=(Vector2D Vec);						//	ベクトルに指定ベクトルを減算代入
	Vector2D operator *=(float Scalar);						//	ベクトルに値を乗算
	Vector2D operator /=(float Scalar);						//	ベクトルに値を除算
	Vector2D operator +();									//	ベクトルに+を乗算
	Vector2D operator +(Vector2D Vec);						//	ベクトルに指定ベクトルを加算
	Vector2D operator -();									//	ベクトルに-を乗算
	Vector2D operator -(Vector2D Vec);						//	ベクトルに指定ベクトルを減算
	Vector2D operator *(float Scalar);						//	ベクトルに値を乗算
	Vector2D operator /(float Scalar);						//	ベクトルに値を除算

	//ベクトルの計算式
	Vector2D Normalize();									//	ベクトルの正規化をする
	Vector2D LengthSet(float Scalar);						//	ベクトルの大きさを値にする
	static float Dot(Vector2D Vec1, Vector2D Vec2);			//	ベクトルの内積
	static float Cross(Vector2D Vec1, Vector2D Vec2);		//	ベクトルの外積
	float Dot(Vector2D Vec);								//	自ベクトルとベクトルの内積
	float Cross(Vector2D Vec);								//	自ベクトルとベクトルの外積
};

