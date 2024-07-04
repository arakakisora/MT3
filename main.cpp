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

	Segment segment{ {-2.0f,-1.0f,0.0f},{1.0f,0.0f,0.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Plane plane{ {0.0f,1.0f,0.0f},1.0f };
	Triangle triangle{ { {1.0f,0.0f,0.0f},{-1.0f,0.0f,0.0f},{1.0f,+0.5f,0.0f} } };

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


		if (Novice::IsTriggerMouse(2) || Novice::IsTriggerMouse(0)) {

			preMouse.x = (float)MousePosX;
			preMouse.y = (float)MousePosY;
			precamera = cameraTransform;

		}

		if (keys[DIK_SPACE]) {
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

				cameraTransform.rotate.y = precamera.rotate.y+ (float)dist.x * 0.001f;
				cameraTransform.rotate.x = precamera.rotate.x + (float)dist.y * 0.001f;

			}
		}





		ImGui::Begin("Window");
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("CameraTranslate", &cameraTransform.translate.x, 0.01f);
			ImGui::DragFloat3("CameraRotate", &cameraTransform.rotate.x, 0.01f);
		}

		if (ImGui::CollapsingHeader("segment", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
			ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);
			//ImGui::DragFloat("Segment.Diff", &sphere1.radius, 0.01f);
		}

		// 項目2
		if (ImGui::CollapsingHeader("Object2", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("triangle0", &triangle.vertices[0].x, 0.01f);
			ImGui::DragFloat3("triangle1", &triangle.vertices[1].x, 0.01f);
			ImGui::DragFloat3("triangle2", &triangle.vertices[2].x, 0.01f);


			plane.normal = Normaraize(plane.normal);

		}

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vector3 start = TransformVector3(TransformVector3(segment.origin, viewprojectionMatrix), viewportMatrix);
		Vector3 end = TransformVector3(TransformVector3(Add(segment.origin, segment.diff), viewprojectionMatrix), viewportMatrix);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		DrawGrid(worldviewprojectionMatrix, viewportMatrix);
		if (IsCollision(segment, triangle)) {

			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), RED);
		}
		else { Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE); }
		DrawTriangle(triangle, viewprojectionMatrix, viewportMatrix, WHITE);
		//DroawPlane(plane, viewprojectionMatrix, viewportMatrix, WHITE);
		//DrawSphere(sphere2, viewprojectionMatrix, viewportMatrix, WHITE);

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
