#include <Novice.h>
#include "MyMath.h"
#include"RenderingPipeline.h"
#include "imgui.h"
#include "Vector2.h"
#include "Vector3.h"


const char kWindowTitle[] = "学籍番号";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//クライアント領域のサイズ
	const int32_t kClientWindth = 1280;
	const int32_t kClientHeight = 720;
	Transform transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f} ,{0.0f,0.0f,0.0f} };
	Transform cameraTransform = { {1.0f,1.0f,1.0f},{0.26f,0.0f,0.0f} ,{ 0.0f,1.9f,-6.49f} };
	Sphere sphere1{ 0.0f,0.0f,1.0f, 1 };
	Sphere sphere2{ 1.0f,0.0f,1.0f, 0.5 };

	Segment segment{ {-0.7f,0.3f,0.0f},{2.0f,-0.5f,0.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Plane plane{ {0.0f,1.0f,0.0f},1.0f };
	Triangle triangle{ { {1.0f,0.0f,0.0f},{-1.0f,0.0f,0.0f},{1.0f,+0.5f,0.0f} } };

	AABB aabb1{

		{-0.5f, -0.5f, -0.5f},
		{0.5f, 0.5f, 0.5f },

	};

	AABB aabb2{

		 {0.2f, 0.2f, 0.2f},
		 {1.0f, 1.0f, 1.0f},
	};



	Vector3 controlPoints[3] = {
		{-0.8f, 0.58f, 1.0f },
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f },
	};


	//肩、肘、手
	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};
	Vector3 rotates[3]{
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, 1.4f},
		{0.0f, 0.0f, 0.0f },
	};
	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};


	Vector3 a{ 0.2f, 1.0f, 0.0f };
	Vector3 b{ 2.4f, 3.1f, 1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;


	Spring spring{};
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficent = 2.0f;

	Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float deltaTime = 1.0f / 60.0f;
	float length = 0;// Length(diff);

	int  MousePosX;
	int  MousePosY;
	Vector2 preMouse = { 0 };
	Transform precamera = { 0 };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&MousePosX, &MousePosY);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWindth) / float(kClientHeight), 0.1f, 100.0f);
		Matrix4x4 worldviewprojectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewprojectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kClientWindth), float(kClientHeight), 0.0f, 1.0f);



		Vector3 diff = ball.position - spring.anchor;
	

		if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
			
		}

		if (length != 0.0f)
		{
			Vector3 direction = Normaraize(diff);
			Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
			Vector3 displacement = length * (ball.position - restPosition);
			Vector3 restoringFore = -spring.stiffness * displacement;
			Vector3 dampingForce = -spring.dampingCoefficent * ball.velocity;
			Vector3 force = restoringFore+dampingForce;
			ball.acceleration = force / ball.mass;
			
		}

		// 次の処理を追加
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;






		ImGui::Begin("Window");
		if (ImGui::Button("start")) {
			length = Length(diff);
		}

		ImGui::End();

	

		if (keys[DIK_SPACE]) {
			if (Novice::IsTriggerMouse(2) || Novice::IsTriggerMouse(0)) {

				preMouse.x = (float)MousePosX;
				preMouse.y = (float)MousePosY;
				precamera = cameraTransform;

			}
			Vector2 dist;
			dist.x = preMouse.x - (float)MousePosX;
			dist.y = preMouse.y - (float)MousePosY;
			dist.y *= -1;
			if (Novice::IsPressMouse(2)) {

				cameraTransform.translate.x = precamera.translate.x + (float)dist.x * 0.001f;
				cameraTransform.translate.y = ((precamera.translate.y + (float)dist.y * 0.001f));

			}
			cameraTransform.translate.z += Novice::GetWheel() * 0.001f;
			if (Novice::IsPressMouse(0)) {

				cameraTransform.rotate.y = precamera.rotate.y + (float)dist.x * 0.001f;
				cameraTransform.rotate.x = precamera.rotate.x + (float)dist.y * 0.001f;

			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		Vector3 start = TransformVector3(TransformVector3(Vector3{0,0,0}, viewprojectionMatrix), viewportMatrix);

		Vector3 end = TransformVector3(TransformVector3(ball.position,viewprojectionMatrix), viewportMatrix);


		



		DrawGrid(worldviewprojectionMatrix, viewportMatrix);
		DrawSphere(Sphere{ ball.position ,0.1f }, viewprojectionMatrix, viewportMatrix, BLUE);
		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, WHITE);


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
