#include "Matrix.h"
#include <math.h>

///////////////////////////////////////////
//Matrix4x4 class
///////////////////////////////////////////

float* 
Matrix4x4::GetOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	float* toReturn = new float[16];
	toReturn[0] = 2.0/(right - left);
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0/(top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0/(a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1*((right + left)/(right - left));
	toReturn[13] = -1*((top + bottom)/(top - bottom));
	toReturn[14] = -1*((a_fFar + a_fNear)/(a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}

Matrix4x4::Matrix4x4()
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			matrix[row][col] = 0.f;
		}
	}
}

Vector4 Matrix4x4::operator*(Vector4 vec)
{
	Vector4 ret;
	
	ret.x = matrix[0][0] * vec.x;
	ret.x += matrix[1][0] * vec.x;
	ret.x += matrix[2][0] * vec.x;
	ret.x += matrix[3][0] * vec.x;

	ret.y = matrix[0][1] * vec.y;
	ret.y += matrix[1][1] * vec.y;
	ret.y += matrix[2][1] * vec.y;
	ret.y += matrix[3][1] * vec.y;

	ret.z = matrix[0][2] * vec.z;
	ret.z += matrix[1][2] * vec.z;
	ret.z += matrix[2][2] * vec.z;
	ret.z += matrix[3][2] * vec.z;

	ret.w = matrix[0][3] * vec.w;
	ret.w += matrix[1][3] * vec.w;
	ret.w += matrix[2][3] * vec.w;
	ret.w += matrix[3][3] * vec.w;
	
	return ret;
}

//thank you for the brain liquification
Matrix4x4 Matrix4x4::operator*(Matrix4x4 mat4)
{
	Matrix4x4 ret;

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			for (int component = 0; component < 4; ++component)
			{
				ret.matrix[row][col] += this->matrix[row][component] * mat4.matrix[component][col];
			}			
		}
	}

	return ret;
}

string Matrix4x4::ToString()
{
	string matrixString = "";
	
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			matrixString += to_string(matrix[row][col]);
			matrixString += ';';
		}
		matrixString += '\n';
	}

	return matrixString;
}


///////////////////////////////////////////
//Matrix3x3 class
///////////////////////////////////////////
//void Matrix3x3::SetPosition		(Vector3 pos_)
//{
//	matrix[2][0] = pos_.x;
//	matrix[2][1] = pos_.y;
//}

//void Matrix3x3::Scale(float scalar_)
//{
//	matrix[0][0] *= scalar_;
//	matrix[1][1] *= scalar_;
//	matrix[2][2] *= scalar_;
//}

Vector3 Matrix3x3::Direction()
{
	return Vector3 (matrix[0][0],matrix[0][1], 0);
}

Vector3 Matrix3x3::GetPosition()
{
	return Vector3 (matrix[2][0], matrix[2][1], 1.0);
}

void Matrix3x3::Move		(Vector3 movement_)
{
	matrix[2][0] += movement_.x;
	matrix[2][1] += movement_.y;
}

Matrix3x3::Matrix3x3()
{
	matrix[0][0] = 0.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 0.0;
	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 0.0;
}

void Matrix3x3::SetupIdentity()
{
	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;

	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
	matrix[1][2] = 0.0f;

	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 1.0f;
}

Matrix3x3::Matrix3x3(float a_, float b_, float c_, float d_, float e_, float f_, float g_, float h_, float i_)
{
	matrix[0][0] = a_;
	matrix[0][1] = b_;
	matrix[0][2] = c_;
	matrix[1][0] = d_;
	matrix[1][1] = e_;
	matrix[1][2] = f_;
	matrix[2][0] = g_;
	matrix[2][1] = h_;
	matrix[2][2] = i_;
}

void Matrix3x3::SetupRotation		(float rot_)
{
	matrix[0][0] = cos(rot_);
	matrix[0][1] = -sin(rot_);
	matrix[0][2] = 0.0;
	matrix[1][0] = sin(rot_);
	matrix[1][1] = cos(rot_);
	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
}

Matrix3x3 Matrix3x3::CreateRotationMatrix(float rot_)
{
	Matrix3x3 ret;
	ret.matrix[0][0] = cos(rot_);
	ret.matrix[0][1] = -sin(rot_);
	ret.matrix[0][2] = 0.0;
	ret.matrix[1][0] = sin(rot_);
	ret.matrix[1][1] = cos(rot_);
	ret.matrix[1][2] = 0.0;
	ret.matrix[2][0] = 0.0;
	ret.matrix[2][1] = 0.0;
	ret.matrix[2][2] = 1.0;
	return ret;
}


Matrix3x3 Matrix3x3::CreateTranslationMatrix (Vector3  vec_)
{
	Matrix3x3 ret;	
	ret.matrix[0][0] = 1.0;
	ret.matrix[0][1] = 0.0;
	ret.matrix[0][2] = 0.0;
	ret.matrix[1][0] = 0.0;
	ret.matrix[1][1] = 1.0;
	ret.matrix[1][2] = 0.0;
	ret.matrix[2][0] = vec_.x;
	ret.matrix[2][1] = vec_.y;
	ret.matrix[2][2] = 1.0;
	return ret;
}


void Matrix3x3::SetupTranslation	(Vector3  vec_)
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[2][0] = vec_.x;
	matrix[2][1] = vec_.y;
	matrix[2][2] = 1.0;
}

void Matrix3x3::SetupScale			(float scalar_)
{
	matrix[0][0] = scalar_;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;

	matrix[1][0] = 0.0f;
	matrix[1][1] = scalar_;
	matrix[1][2] = 0.0f;

	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 1.0f;
}

Matrix3x3 Matrix3x3::CreateScaleMatrix(float scalar_)
{
	Matrix3x3 ret;

	ret.matrix[0][0] = scalar_;
	ret.matrix[0][1] = 0.0f;
	ret.matrix[0][2] = 0.0f;
	ret.matrix[1][0] = 0.0f;
	ret.matrix[1][1] = scalar_;
	ret.matrix[1][2] = 0.0f;
	ret.matrix[2][0] = 0.0f;
	ret.matrix[2][1] = 0.0f;
	ret.matrix[2][2] = 1.0f;

	return ret;
}

Vector3 Matrix3x3::operator*		(Vector3 vec_)
{
	Vector3 ret;	
	
	ret.x = matrix[0][0] * vec_.x;
	ret.x += matrix[1][0] * vec_.y;
	ret.x += matrix[2][0] * vec_.z;

	ret.y = matrix[0][1] * vec_.x;
	ret.y += matrix[1][1] * vec_.y;
	ret.y += matrix[2][1] * vec_.z;

	ret.z = matrix[0][2] * vec_.x;
	ret.z += matrix[1][2] * vec_.y;
	ret.z += matrix[2][2] * vec_.z;

	return ret;
}

Matrix3x3 Matrix3x3::operator*		(Matrix3x3 mat3_)
{
	Matrix3x3 ret;

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			for (int component = 0; component < 3; ++component)
			{
				ret.matrix[row][col] += this->matrix[row][component] * mat3_.matrix[component][col];
			}			
		}
	}
	return ret;
}

Matrix3x3 Matrix3x3::Transpose()
{
	Matrix3x3 ret;

	ret.matrix[0][0] = this->matrix[0][0];
	ret.matrix[1][0] = this->matrix[0][1];
	ret.matrix[2][0] = this->matrix[0][2];

	ret.matrix[0][1] = this->matrix[1][0];
	ret.matrix[1][1] = this->matrix[1][1];
	ret.matrix[2][1] = this->matrix[1][2];

	ret.matrix[0][2] = this->matrix[2][0];
	ret.matrix[1][2] = this->matrix[2][1];
	ret.matrix[2][2] = this->matrix[2][2];
	
	return ret;
}



string Matrix3x3::ToString()
{
	string ret = "";

	ret += "0,0: " + to_string(matrix[0][0]) + "\t";
	ret += "0,1: " + to_string(matrix[0][1]) + "\t";
	ret += "0,2: " + to_string(matrix[0][2]) + "\t\n";

	ret += "1,0: " + to_string(matrix[1][0]) + "\t";
	ret += "1,1: " + to_string(matrix[1][1]) + "\t";
	ret += "1,2: " + to_string(matrix[1][2]) + "\t\n";

	ret += "2,0: " + to_string(matrix[2][0]) + "\t";
	ret += "2,1: " + to_string(matrix[2][1]) + "\t";
	ret += "2,2: " + to_string(matrix[2][2]) + "\t\n";
	
	return ret;
}
