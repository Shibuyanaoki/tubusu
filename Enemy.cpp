#include "Enemy.h"
#include "TextureManager.h"
#include "iostream"
#include <cassert>

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, Vector3 position) {
	assert(model);

	worldTransform_.Initialize();
	model_ = model;
	worldTransform_.translation_ = position;

	worldTransform_.scale_ = {4.0f, 4.0f, 4.0f};
}

void Enemy::Update() {

	Vector3 move = {0, 0, 0};

	const float kSpeed = 0.2f;

	// 移動限界座標
	const float kMoveLimitX = 60;
	const float kMoveLimitY = 19;

	worldTransform_.rotation_.y += 0.01f;

	move.x = -kSpeed;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 座標飯銅(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 敵が左左端に行ったらdelete
	if (worldTransform_.translation_.x <= -kMoveLimitX) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection viewProjection) { model_->Draw(worldTransform_, viewProjection); }

Vector3 Enemy::GetWorldPosition() {

	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() { isDead_ = true; }