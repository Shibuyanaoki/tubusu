#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Hammer {
public:
	~Hammer();

	Hammer();

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

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// 3Dモデル
	Model* model_ = nullptr;
	// デスフラグ
	bool isDead_ = false;
	// スペースを押したかのフラグ
	bool flag_ = false;
	// ハンマーの半径
	float radius_ = 1.5f;
};
