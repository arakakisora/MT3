#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#pragma once
#include <assert.h>
#include <Novice.h>
#include <cmath>
#include <stdio.h>
#include <numbers>

struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
struct Sphere {
	Vector3 centor;
	float radius;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};
//回転
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
//拡大
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
//同時座標変換
Vector3 TransformVector3(const Vector3& vector, const Matrix4x4& matrix);

//回転X
Matrix4x4 MakeRotateXMatrix(float radian);
//回転Y
Matrix4x4 MakeRotateYMatrix(float radian);
//回転Z
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

void  VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

//スクリーンプリントf
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);

//足し算
Matrix4x4 Add(const Matrix4x4& mt1, const Matrix4x4& mt2);
//引き算
Matrix4x4 Subtract(const Matrix4x4& mt1, const Matrix4x4& mt2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//掛け算
Matrix4x4 Multiply(const Matrix4x4& mt1, const Matrix4x4& mt2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& mt1);


Matrix4x4 Transpose(const Matrix4x4& mt1);
//0行列
Matrix4x4 MekeIdentity4x4();

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& v1, const Vector3& v2);


float Lenght(const Vector3& v);

Vector3 Normaraize(const Vector3& v);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
