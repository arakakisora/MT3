#include <Novice.h>
#include "MyMath.h"
#include"RenderingPipeline.h"
#include "imgui.h"
#include "Vector2.h"


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


		Matrix4x4 localShoulderMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 localElbowMatrix = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 localHandMatrix = MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		Matrix4x4 worldShoulderMatrix = localShoulderMatrix;
		Matrix4x4 worldElbowMatrix = Multiply(localElbowMatrix, localShoulderMatrix);
		Matrix4x4 worldHandMatrix = Multiply(Multiply(localHandMatrix, localElbowMatrix), localShoulderMatrix);

		Sphere shoulder{

			Vector3{
				worldShoulderMatrix.m[3][0],
				worldShoulderMatrix.m[3][1],
				worldShoulderMatrix.m[3][2]
			},
			0.1f,

		};

		Sphere elbow{

			Vector3{
				worldElbowMatrix.m[3][0],
				worldElbowMatrix.m[3][1],
				worldElbowMatrix.m[3][2]
			},
			0.1f,

		};

		Sphere hand{

			Vector3{
				worldHandMatrix.m[3][0],
				worldHandMatrix.m[3][1],
				worldHandMatrix.m[3][2]
			},
			0.1f,

		};




		ImGui::Begin("Window");
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("CameraTranslate", &cameraTransform.translate.x, 0.01f);
			ImGui::DragFloat3("CameraRotate", &cameraTransform.rotate.x, 0.01f);
		}


		if (ImGui::CollapsingHeader("controlPoint", ImGuiTreeNodeFlags_DefaultOpen))
		{

			ImGui::DragFloat3("scalea[0]", &scales[0].x, 0.01f);
			ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
			ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);

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



		DrawGrid(worldviewprojectionMatrix, viewportMatrix);
		DrawSphere(shoulder, viewprojectionMatrix, viewportMatrix, RED);
		DrawSphere(elbow, viewprojectionMatrix, viewportMatrix, GREEN);
		DrawSphere(hand, viewprojectionMatrix, viewportMatrix, BLUE);

		



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
