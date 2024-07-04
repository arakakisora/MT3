﻿#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#pragma once
#include <assert.h>
#include <Novice.h>
#include <cmath>
#include <stdio.h>
#include <numbers>
#include <algorithm>


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

struct Plane {

	Vector3 normal;
	float distance;

};

struct Triangle {

	Vector3 vertices[3];
};

struct AABB {

	Vector3 min;
	Vector3 max;
};

//Vector3 operator+(const Vector3&v1,const Vector3 v2)

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float s, const Vector3& v);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator/(const Vector3& v, float s);
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator* (const Matrix4x4& m1, const Matrix4x4& m2);

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
Vector3 Add(const Vector3& v1, const Vector3& v2);
//引き算
Matrix4x4 Subtract(const Matrix4x4& mt1, const Matrix4x4& mt2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//掛け算
Matrix4x4 Multiply(const Matrix4x4& mt1, const Matrix4x4& mt2);
Vector3 Multiply(const Vector3& mt1, const float& mt2);
Vector3 Multiply(const Vector3& mt1, const Vector3& mt2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& mt1);


Matrix4x4 Transpose(const Matrix4x4& mt1);
//0行列
Matrix4x4 MekeIdentity4x4();

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);
//ドット積
float Dot(const Vector3& v1, const Vector3& v2);
float Dot(const Vector3& v1, const float& num);
//長さ
float Length(const Vector3& v);
//正規化
Vector3 Normaraize(const Vector3& v);
//グリット
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
//球
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//最近接点
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
//当たり判定
bool IsCollision(const Sphere& s1, const Sphere& s2);
bool IsCollision(const Sphere& s1, const Plane& plane);
bool IsCollision(const Segment& segment, const Plane& plane);
bool IsCollision(const Segment& segment, const Triangle& triangle);

//四頂点を求める
Vector3 Perpendicular(const Vector3& vector);
//平面
void DroawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);