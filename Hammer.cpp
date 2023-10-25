#include "Hammer.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>

Hammer::~Hammer() { delete model_; }

Hammer::Hammer() {}

void Hammer::Initialize(Model* model,  Vector3 position) {
	assert(model);
	input_ = Input::GetInstance();
	// ワールドトランスホームフォームの初期化
	worldTransform_.Initialize();
	// モデル
	model_ = model;
	
	// X,Y,Z方向の平行移動を設定
	worldTransform_.translation_ = position;
	// ハンマースケールの設定
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
}

void Hammer::Update() {

	Vector3 move = {0.0f, 0.0f, 0.0f};
	// 上がるときのスピード
	const float kUpSpeed = 1.0f;
	// 下がるときのスピード
	const float kDownSpeed = 10.0f;

	if (input_->TriggerKey(DIK_SPACE) && worldTransform_.translation_.y >= 23) {
		flag_ = true;
	}

	if (flag_ == true) {
		if (worldTransform_.translation_.y >= -10) {
			move.y = -kDownSpeed;
		} else {
			flag_ = false;
		}
	}

	if (flag_ == false) {

		if (worldTransform_.translation_.y <= 23) {
			move.y = +kUpSpeed;
		}
	}

	worldTransform_.translation_.y += move.y;

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Debug1");
	float playerPos[] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("HammerPos", playerPos, 0, 1280);

	// 処理のままだとSilderFloat3でplayerPosの値を変えているので実際の座標(translation)が
	// 変わっていないのでここで変更する
	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];

	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void Hammer::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Hammer::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Hammer::OnCollision() { isDead_ = true; }
