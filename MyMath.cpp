#include "MyMath.h"

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 ans;

	ans.m[0][0] = 1;
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;

	ans.m[1][0] = 0;
	ans.m[1][1] = 1;
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;

	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = 1;
	ans.m[2][3] = 0;

	ans.m[3][0] = translate.x;
	ans.m[3][1] = translate.y;
	ans.m[3][2] = translate.z;
	ans.m[3][3] = 1;

	return ans;

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 ans;

	ans.m[0][0] = scale.x;
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;

	ans.m[1][0] = 0;
	ans.m[1][1] = scale.y;
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;

	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = scale.z;
	ans.m[2][3] = 0;

	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = 0;
	ans.m[3][3] = 1;
	return ans;

}

Vector3 TransformVector3(const Vector3& vector, const Matrix4x4& matrix)
{

	Vector3 ans;

	ans.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	ans.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	ans.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	ans.x /= w;
	ans.y /= w;
	ans.z /= w;
	return ans;

}

Matrix4x4 MakeRotateXMatrix(float radian)
{

	Matrix4x4 ans;
	ans.m[0][0] = 1;
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;

	ans.m[1][0] = 0;
	ans.m[1][1] = std::cos(radian);;
	ans.m[1][2] = std::sin(radian);;
	ans.m[1][3] = 0;

	ans.m[2][0] = 0;
	ans.m[2][1] = -std::sin(radian);;
	ans.m[2][2] = std::cos(radian);;
	ans.m[2][3] = 0;

	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = 0;
	ans.m[3][3] = 1;

	return ans;

}

Matrix4x4 MakeRotateYMatrix(float radian)
{

	Matrix4x4 ans;
	ans.m[0][0] = std::cos(radian);
	ans.m[0][1] = 0;
	ans.m[0][2] = -std::sin(radian);
	ans.m[0][3] = 0;

	ans.m[1][0] = 0;
	ans.m[1][1] = 1;
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;

	ans.m[2][0] = std::sin(radian);;
	ans.m[2][1] = 0;
	ans.m[2][2] = std::cos(radian);;
	ans.m[2][3] = 0;

	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = 0;
	ans.m[3][3] = 1;

	return ans;

}

Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 ans;
	ans.m[0][0] = std::cos(radian);
	ans.m[0][1] = std::sin(radian);
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;

	ans.m[1][0] = -std::sin(radian);
	ans.m[1][1] = std::cos(radian);
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;

	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = 1;
	ans.m[2][3] = 0;

	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = 0;
	ans.m[3][3] = 1;


	return ans;

}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{

	Matrix4x4 rotateXYZ = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));
	return Multiply(Multiply(MakeScaleMatrix(scale), rotateXYZ), MakeTranslateMatrix(translate));

}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{

	static const int kColumanWidth = 60;

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumanWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumanWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumanWidth * 3, y, "%s", label);


}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{

	static const int krowHeight = 20;
	static const int kcolumnWidth = 60;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kcolumnWidth, y + row * krowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 Add(const Matrix4x4& mt1, const Matrix4x4& mt2)
{

	Matrix4x4 ans;

	ans.m[0][0] = mt1.m[0][0] + mt2.m[0][0];
	ans.m[0][1] = mt1.m[0][1] + mt2.m[0][1];
	ans.m[0][2] = mt1.m[0][2] + mt2.m[0][2];
	ans.m[0][3] = mt1.m[0][3] + mt2.m[0][3];

	ans.m[1][0] = mt1.m[1][0] + mt2.m[1][0];
	ans.m[1][1] = mt1.m[1][1] + mt2.m[1][1];
	ans.m[1][2] = mt1.m[1][2] + mt2.m[1][2];
	ans.m[1][3] = mt1.m[1][3] + mt2.m[1][3];

	ans.m[2][0] = mt1.m[2][0] + mt2.m[2][0];
	ans.m[2][1] = mt1.m[2][1] + mt2.m[2][1];
	ans.m[2][2] = mt1.m[2][2] + mt2.m[2][2];
	ans.m[2][3] = mt1.m[2][3] + mt2.m[2][3];

	ans.m[3][0] = mt1.m[3][0] + mt2.m[3][0];
	ans.m[3][1] = mt1.m[3][1] + mt2.m[3][1];
	ans.m[3][2] = mt1.m[3][2] + mt2.m[3][2];
	ans.m[3][3] = mt1.m[3][3] + mt2.m[3][3];



	return ans;


}

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return
	{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
}





Matrix4x4 Subtract(const Matrix4x4& mt1, const Matrix4x4& mt2)
{

	Matrix4x4 ans;

	ans.m[0][0] = mt1.m[0][0] - mt2.m[0][0];
	ans.m[0][1] = mt1.m[0][1] - mt2.m[0][1];
	ans.m[0][2] = mt1.m[0][2] - mt2.m[0][2];
	ans.m[0][3] = mt1.m[0][3] - mt2.m[0][3];

	ans.m[1][0] = mt1.m[1][0] - mt2.m[1][0];
	ans.m[1][1] = mt1.m[1][1] - mt2.m[1][1];
	ans.m[1][2] = mt1.m[1][2] - mt2.m[1][2];
	ans.m[1][3] = mt1.m[1][3] - mt2.m[1][3];

	ans.m[2][0] = mt1.m[2][0] - mt2.m[2][0];
	ans.m[2][1] = mt1.m[2][1] - mt2.m[2][1];
	ans.m[2][2] = mt1.m[2][2] - mt2.m[2][2];
	ans.m[2][3] = mt1.m[2][3] - mt2.m[2][3];

	ans.m[3][0] = mt1.m[3][0] - mt2.m[3][0];
	ans.m[3][1] = mt1.m[3][1] - mt2.m[3][1];
	ans.m[3][2] = mt1.m[3][2] - mt2.m[3][2];
	ans.m[3][3] = mt1.m[3][3] - mt2.m[3][3];



	return ans;


}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{

	Vector3 ans;

	ans.x = v1.x - v2.x;
	ans.y = v1.y - v2.y;
	ans.z = v1.z - v2.z;

	return ans;


}

Matrix4x4 Multiply(const Matrix4x4& mt1, const Matrix4x4& mt2)
{

	Matrix4x4 ans = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {

				ans.m[i][j] += mt1.m[i][k] * mt2.m[k][j];

			}

		}

	}
	return ans;

}

Vector3 Multiply(const Vector3& mt1, const float& mt2)
{
	Vector3 ans;
	ans.x = mt1.x * mt2;
	ans.y = mt1.y * mt2;
	ans.z = mt1.z * mt2;
	return ans;
}

Matrix4x4 Inverse(const Matrix4x4& mt1)
{
	Matrix4x4 ans;
	float A = 0;
	A = mt1.m[0][0] * mt1.m[1][1] * mt1.m[2][2] * mt1.m[3][3] + mt1.m[0][0] * mt1.m[1][2] * mt1.m[2][3] * mt1.m[3][1] + mt1.m[0][0] * mt1.m[1][3] * mt1.m[2][1] * mt1.m[3][2]
		- mt1.m[0][0] * mt1.m[1][3] * mt1.m[2][2] * mt1.m[3][1] - mt1.m[0][0] * mt1.m[1][2] * mt1.m[2][1] * mt1.m[3][3] - mt1.m[0][0] * mt1.m[1][1] * mt1.m[2][3] * mt1.m[3][2]
		- mt1.m[0][1] * mt1.m[1][0] * mt1.m[2][2] * mt1.m[3][3] - mt1.m[0][2] * mt1.m[1][0] * mt1.m[2][3] * mt1.m[3][1] - mt1.m[0][3] * mt1.m[1][0] * mt1.m[2][1] * mt1.m[3][2]
		+ mt1.m[0][3] * mt1.m[1][0] * mt1.m[2][2] * mt1.m[3][1] + mt1.m[0][2] * mt1.m[1][0] * mt1.m[2][1] * mt1.m[3][3] + mt1.m[0][1] * mt1.m[1][0] * mt1.m[2][3] * mt1.m[3][2]
		+ mt1.m[0][1] * mt1.m[1][2] * mt1.m[2][0] * mt1.m[2][2] + mt1.m[0][2] * mt1.m[1][3] * mt1.m[2][0] * mt1.m[3][1] + mt1.m[0][3] * mt1.m[1][1] * mt1.m[2][0] * mt1.m[3][2]
		- mt1.m[0][3] * mt1.m[1][2] * mt1.m[2][0] * mt1.m[3][1] - mt1.m[0][2] * mt1.m[1][1] * mt1.m[2][0] * mt1.m[3][3] - mt1.m[0][1] * mt1.m[1][3] * mt1.m[2][0] * mt1.m[3][2]
		- mt1.m[0][1] * mt1.m[1][2] * mt1.m[2][3] * mt1.m[3][0] - mt1.m[0][2] * mt1.m[1][3] * mt1.m[2][1] * mt1.m[3][0] - mt1.m[0][3] * mt1.m[1][1] * mt1.m[2][2] * mt1.m[3][0]
		+ mt1.m[0][3] * mt1.m[1][2] * mt1.m[2][0] * mt1.m[3][0] + mt1.m[0][2] * mt1.m[1][1] * mt1.m[2][3] * mt1.m[3][0] + mt1.m[0][1] * mt1.m[1][3] * mt1.m[2][2] * mt1.m[3][0];



	ans.m[0][0] = (mt1.m[1][1] * mt1.m[2][2] * mt1.m[3][3] + mt1.m[1][2] * mt1.m[2][3] * mt1.m[3][1] + mt1.m[1][3] * mt1.m[2][1] * mt1.m[3][2]
		- mt1.m[1][3] * mt1.m[2][2] * mt1.m[3][1] - mt1.m[1][2] * mt1.m[2][1] * mt1.m[3][3] - mt1.m[1][1] * mt1.m[2][3] * mt1.m[3][2]) / A;

	ans.m[0][1] = (-mt1.m[0][1] * mt1.m[2][2] * mt1.m[3][3] - mt1.m[0][2] * mt1.m[2][3] * mt1.m[3][1] - mt1.m[0][3] * mt1.m[2][1] * mt1.m[3][2]
		+ mt1.m[0][3] * mt1.m[2][2] * mt1.m[3][1] + mt1.m[0][2] * mt1.m[2][1] * mt1.m[3][3] + mt1.m[0][1] * mt1.m[2][3] * mt1.m[3][2]) / A;

	ans.m[0][2] = (mt1.m[0][1] * mt1.m[1][2] * mt1.m[3][3] + mt1.m[0][2] * mt1.m[1][3] * mt1.m[3][1] + mt1.m[0][3] * mt1.m[1][1] * mt1.m[3][2]
		- mt1.m[0][3] * mt1.m[1][2] * mt1.m[3][1] - mt1.m[0][2] * mt1.m[1][1] * mt1.m[3][3] - mt1.m[0][1] * mt1.m[1][3] * mt1.m[3][2]) / A;

	ans.m[0][3] = (-mt1.m[0][1] * mt1.m[1][2] * mt1.m[2][3] - mt1.m[0][2] * mt1.m[1][3] * mt1.m[2][1] - mt1.m[0][3] * mt1.m[1][1] * mt1.m[2][2]
		+ mt1.m[0][3] * mt1.m[1][2] * mt1.m[2][1] + mt1.m[0][2] * mt1.m[1][1] * mt1.m[2][3] + mt1.m[0][1] * mt1.m[1][3] * mt1.m[2][2]) / A;


	ans.m[1][0] = (-mt1.m[1][0] * mt1.m[2][2] * mt1.m[3][3] - mt1.m[1][2] * mt1.m[2][3] * mt1.m[3][0] - mt1.m[1][3] * mt1.m[2][0] * mt1.m[3][2]
		+ mt1.m[1][3] * mt1.m[2][2] * mt1.m[3][0] + mt1.m[1][2] * mt1.m[2][0] * mt1.m[3][3] + mt1.m[1][0] * mt1.m[2][3] * mt1.m[3][2]) / A;

	ans.m[1][1] = (mt1.m[0][0] * mt1.m[2][2] * mt1.m[3][3] + mt1.m[0][2] * mt1.m[2][3] * mt1.m[3][0] + mt1.m[0][3] * mt1.m[2][0] * mt1.m[3][2]
		- mt1.m[0][3] * mt1.m[2][2] * mt1.m[3][0] - mt1.m[0][2] * mt1.m[2][0] * mt1.m[3][3] - mt1.m[0][0] * mt1.m[2][3] * mt1.m[3][2]) / A;

	ans.m[1][2] = (-mt1.m[0][0] * mt1.m[1][2] * mt1.m[3][3] - mt1.m[0][2] * mt1.m[1][3] * mt1.m[3][0] - mt1.m[0][3] * mt1.m[1][0] * mt1.m[3][2]
		+ mt1.m[0][3] * mt1.m[1][2] * mt1.m[3][0] + mt1.m[0][2] * mt1.m[1][0] * mt1.m[3][3] + mt1.m[0][0] * mt1.m[1][3] * mt1.m[3][2]) / A;

	ans.m[1][3] = (mt1.m[0][0] * mt1.m[1][2] * mt1.m[2][3] + mt1.m[0][2] * mt1.m[1][3] * mt1.m[2][0] + mt1.m[0][3] * mt1.m[1][0] * mt1.m[2][2]
		- mt1.m[0][3] * mt1.m[1][2] * mt1.m[2][0] - mt1.m[0][2] * mt1.m[1][0] * mt1.m[2][3] - mt1.m[0][0] * mt1.m[1][3] * mt1.m[2][2]) / A;



	ans.m[2][0] = (mt1.m[1][0] * mt1.m[2][1] * mt1.m[3][3] + mt1.m[1][1] * mt1.m[2][3] * mt1.m[3][0] + mt1.m[1][3] * mt1.m[2][0] * mt1.m[3][1]
		- mt1.m[1][3] * mt1.m[2][1] * mt1.m[3][0] - mt1.m[1][1] * mt1.m[2][0] * mt1.m[3][3] - mt1.m[1][0] * mt1.m[2][3] * mt1.m[3][1]) / A;

	ans.m[2][1] = (-mt1.m[0][0] * mt1.m[2][1] * mt1.m[3][3] - mt1.m[0][1] * mt1.m[2][3] * mt1.m[3][0] - mt1.m[0][3] * mt1.m[2][0] * mt1.m[3][1]
		+ mt1.m[0][3] * mt1.m[2][1] * mt1.m[3][0] + mt1.m[0][1] * mt1.m[2][0] * mt1.m[3][3] + mt1.m[0][0] * mt1.m[2][3] * mt1.m[3][1]) / A;

	ans.m[2][2] = (mt1.m[0][0] * mt1.m[1][1] * mt1.m[3][3] + mt1.m[0][1] * mt1.m[1][3] * mt1.m[3][0] + mt1.m[0][3] * mt1.m[1][0] * mt1.m[3][1]
		- mt1.m[0][3] * mt1.m[1][1] * mt1.m[3][0] - mt1.m[0][1] * mt1.m[1][0] * mt1.m[3][3] - mt1.m[0][0] * mt1.m[1][3] * mt1.m[3][1]) / A;

	ans.m[2][3] = (-mt1.m[0][0] * mt1.m[1][1] * mt1.m[2][3] - mt1.m[0][1] * mt1.m[1][3] * mt1.m[2][0] - mt1.m[0][3] * mt1.m[1][0] * mt1.m[2][1]
		+ mt1.m[0][3] * mt1.m[1][1] * mt1.m[2][0] + mt1.m[0][1] * mt1.m[1][0] * mt1.m[2][3] + mt1.m[0][0] * mt1.m[1][3] * mt1.m[2][1]) / A;


	ans.m[3][0] = (-mt1.m[1][0] * mt1.m[2][1] * mt1.m[3][2] - mt1.m[1][1] * mt1.m[2][2] * mt1.m[3][0] - mt1.m[1][2] * mt1.m[2][0] * mt1.m[3][1]
		+ mt1.m[1][2] * mt1.m[2][1] * mt1.m[3][0] + mt1.m[1][1] * mt1.m[2][0] * mt1.m[3][2] + mt1.m[1][0] * mt1.m[2][2] * mt1.m[3][1]) / A;

	ans.m[3][1] = (mt1.m[0][0] * mt1.m[2][1] * mt1.m[3][2] + mt1.m[0][1] * mt1.m[2][2] * mt1.m[3][0] + mt1.m[0][2] * mt1.m[2][0] * mt1.m[3][1]
		- mt1.m[0][2] * mt1.m[2][1] * mt1.m[3][0] - mt1.m[0][1] * mt1.m[2][0] * mt1.m[3][2] - mt1.m[0][0] * mt1.m[2][2] * mt1.m[3][1]) / A;

	ans.m[3][2] = (-mt1.m[0][0] * mt1.m[1][1] * mt1.m[3][2] - mt1.m[0][1] * mt1.m[1][2] * mt1.m[3][0] - mt1.m[0][2] * mt1.m[1][0] * mt1.m[3][1]
		+ mt1.m[0][2] * mt1.m[1][1] * mt1.m[3][0] + mt1.m[0][1] * mt1.m[1][0] * mt1.m[3][2] + mt1.m[0][0] * mt1.m[1][2] * mt1.m[3][1]) / A;

	ans.m[3][3] = (mt1.m[0][0] * mt1.m[1][1] * mt1.m[2][2] + mt1.m[0][1] * mt1.m[1][2] * mt1.m[2][0] + mt1.m[0][2] * mt1.m[1][0] * mt1.m[2][1]
		- mt1.m[0][2] * mt1.m[1][1] * mt1.m[2][0] - mt1.m[0][1] * mt1.m[1][0] * mt1.m[2][2] - mt1.m[0][0] * mt1.m[1][2] * mt1.m[2][1]) / A;

	return ans;

}

Matrix4x4 Transpose(const Matrix4x4& mt1)
{

	Matrix4x4 ans;


	ans.m[0][0] = mt1.m[0][0];
	ans.m[0][1] = mt1.m[1][0];
	ans.m[0][2] = mt1.m[2][0];
	ans.m[0][3] = mt1.m[3][0];

	ans.m[1][0] = mt1.m[0][1];
	ans.m[1][1] = mt1.m[1][1];
	ans.m[1][2] = mt1.m[2][1];
	ans.m[1][3] = mt1.m[3][1];

	ans.m[2][0] = mt1.m[0][2];
	ans.m[2][1] = mt1.m[1][2];
	ans.m[2][2] = mt1.m[2][2];
	ans.m[2][3] = mt1.m[3][2];

	ans.m[3][0] = mt1.m[0][3];
	ans.m[3][1] = mt1.m[1][3];
	ans.m[3][2] = mt1.m[2][3];
	ans.m[3][3] = mt1.m[3][3];


	return ans;

}

Matrix4x4 MekeIdentity4x4()
{

	Matrix4x4 ans;


	ans.m[0][0] = 1;
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;

	ans.m[1][0] = 0;
	ans.m[1][1] = 1;
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;

	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = 1;
	ans.m[2][3] = 0;

	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = 0;
	ans.m[3][3] = 1;

	return ans;

}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 ans;

	ans.x = v1.y * v2.z - v1.z * v2.y;
	ans.y = v1.z * v2.x - v1.x * v2.z;
	ans.z = v1.x * v2.y - v1.y * v2.x;

	return ans;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	float ans;

	ans = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return ans;
}

float Dot(const Vector3& v1, const float& num)
{
	float ans;

	ans = v1.x * num + v1.y * num + v1.z * num;
	return ans;
}

float Length(const Vector3& v)
{
	float ans;

	ans = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return ans;
}

Vector3 Normaraize(const Vector3& v)
{
	Vector3 ans;
	float lenght;
	lenght = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	ans.x = v.x / lenght;
	ans.y = v.y / lenght;
	ans.z = v.z / lenght;
	return ans;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);
	//奥から手前への線を順番に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfWidth + (xIndex * kGridEvery);
		unsigned int color = 0xAAAAAAFF;
		Vector3 start{ x,0.0f,-kGridHalfWidth };
		Vector3 end{ x,0.0f,kGridHalfWidth };

		Vector3 startScreen = TransformVector3(TransformVector3(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = TransformVector3(TransformVector3(end, viewProjectionMatrix), viewportMatrix);

		if (x == 0.0f) {
			color = BLACK;
		}
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);

	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + (zIndex * kGridEvery);
		unsigned int color = 0xAAAAAAFF;
		Vector3 start{ -kGridHalfWidth,0.0f,z };
		Vector3 end{ kGridHalfWidth,0.0f,z };

		Vector3 startScreen = TransformVector3(TransformVector3(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = TransformVector3(TransformVector3(end, viewProjectionMatrix), viewportMatrix);

		if (z == 0.0f) {
			color = BLACK;
		}
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);

	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSbdivision = 16;
	const float kLonEvery = 2 * std::numbers::pi_v<float> / kSbdivision;
	const float KLatEvery = std::numbers::pi_v<float> / kSbdivision;

	for (uint32_t latIndex = 0; latIndex < kSbdivision; ++latIndex) {
		float lat = -std::numbers::pi_v<float> / 2.0f + KLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSbdivision; ++lonIndex) {

			float lon = lonIndex * kLonEvery;
			Vector3 a = {
				sphere.radius * std::cosf(lat) * std::cosf(lon) + sphere.centor.x,
				sphere.radius * std::sinf(lat) + sphere.centor.y,
				sphere.radius * std::cosf(lat) * std::sinf(lon) + sphere.centor.z
			};

			Vector3 b = {
				sphere.radius * std::cosf(lat + KLatEvery) * std::cosf(lon) + sphere.centor.x,
				sphere.radius * std::sinf(lat + KLatEvery) + sphere.centor.y,
				sphere.radius * std::cosf(lat + KLatEvery) * std::sinf(lon) + sphere.centor.z
			};

			Vector3 c = {
				sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery) + sphere.centor.x,
				sphere.radius * std::sinf(lat) + sphere.centor.y,
				sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) + sphere.centor.z
			};



			Vector3 aScreen = TransformVector3(TransformVector3(a, viewProjectionMatrix), viewportMatrix);
			Vector3 bScreen = TransformVector3(TransformVector3(b, viewProjectionMatrix), viewportMatrix);
			Vector3 cScreen = TransformVector3(TransformVector3(c, viewProjectionMatrix), viewportMatrix);

			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(bScreen.x), int(bScreen.y), color);
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(cScreen.x), int(cScreen.y), color);


		}


	}
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	float t = Dot(v1, v2) / Dot(v2, v2);
	Vector3 tb = { v2.x * t,v2.y * t,v2.z * t };
	return tb;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 v = Subtract(point, segment.origin);
	float t = Dot(v, segment.diff) / Dot(segment.diff, segment.diff);
	t = std::clamp(t, 0.0f, 1.0f);

	Vector3 tb = { t * segment.diff.x, t * segment.diff.y,t * segment.diff.z };
	return Add(segment.origin, tb);
}

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(Subtract(s2.centor, s1.centor));

	if (distance <= s1.radius + s2.radius) { return true; };

	return false;
}

bool IsCollision(const Sphere& s1, const Plane& plane)
{
	float d = Dot(plane.normal, plane.distance);
	float k = fabs(Dot(plane.normal, s1.centor) - d);
	if (k <= s1.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (0<=t&&t<=1) { return true; }
	return false;

}


//四頂点を求める
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return{ 0.0f,-vector.z,vector.y };
}

void DroawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 center = Multiply(plane.normal, plane.distance);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normaraize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(perpendiculars[index], 2.0f);
		Vector3 point = Add(center, extend);
		points[index] = TransformVector3(TransformVector3(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
}


