﻿#pragma once
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

//掛け算
Matrix4x4 Multiply(const Matrix4x4& mt1, const Matrix4x4& mt2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& mt1);


Matrix4x4 Transpose(const Matrix4x4& mt1);
//0行列
Matrix4x4 MekeIdentity4x4();

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
