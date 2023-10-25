#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class Bom {

public:
	void Initialize(Model* model, Vector3 position);

	void Update();

	void Draw(ViewProjection viewProjection);

	Vector3 GetWorldPosition();

	void OnCollision();

	bool IsDead() const { return isDead_; }

	float GetRadius() { return radius_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;

	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	// デスフラグ
	bool isDead_ = false;

	// 敵の半径
	float radius_ = 0.5f;
};
