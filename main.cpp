#include <Novice.h>
#include "MyMath.h"
#include"RenderingPipeline.h"
#include "imgui.h"

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

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

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



		







		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTransform.translate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraTransform.rotate.x, 0.01f);
		if (ImGui::CollapsingHeader("segment", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
			ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);
			//ImGui::DragFloat("Segment.Diff", &sphere1.radius, 0.01f);
		}

		// 項目2
		if (ImGui::CollapsingHeader("Object2", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("plane.Normal", &plane.normal.x, 0.01f);
			ImGui::DragFloat("plane.Distance", &plane.distance, 0.01f);
		
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
		if (IsCollision(segment,plane)) {

			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), RED);
		}
		else{ Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE); }
		DroawPlane(plane, viewprojectionMatrix, viewportMatrix, WHITE);
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
