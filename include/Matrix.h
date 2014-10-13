#pragma once

#include "Vector.h"
#include "Vector.h"
#include <string>

using namespace std;

class Matrix4x4
{
public:
	Matrix4x4();

	static float* GetOrtho();

	Vector4 operator*(Vector4 vec);
	Matrix4x4 operator*(Matrix4x4 mat4);

	string ToString();

	static float* GetOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

	float matrix[4][4];
};

struct Matrix3x3
{
	Matrix3x3();
	Matrix3x3(float a_, float b_, float c_, float d_, float e_, float f_, float g_, float h_, float i_);
	
	static Matrix3x3 CreateRotationMatrix(float rotation_);
	static Matrix3x3 CreateTranslationMatrix(Vector3 pos_);
	static Matrix3x3 CreateScaleMatrix(float scalar_);

	void SetupRotation		(float rotation_);
	
	void SetupTranslation	(Vector3  vec_);
	void SetupIdentity		();
	void SetupScale			(float scalar_);
	void SetPosition		(Vector3 pos_);
	Vector3	GetPosition		();
	void Move				(Vector3 movement_);
	Vector3	Direction		();
	Vector3 operator*		(Vector3 vec_);
	Matrix3x3 operator*		(Matrix3x3 mat3x3_);
	Matrix3x3				Transpose();
	void					Scale(float scalar_);

	std::string ToString();

	float matrix[3][3];
};