#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"

class ScoreResultScene {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// スコアの描画処理
	/// </summary>
	void GamePlayDraw2DNear();

	/// <summary>
	/// スコアの計算と描画処理
	/// </summary>
	void DrawScore();

	bool IsSceneEnd() { return isSceneEnd; }

	Scene NextScene() { return Scene::TITLE; }

	void SetGameScore(int Score) { gameScore = Score; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビューポートプロジェクション
	ViewProjection viewProjection_;

	// シーンを終わらせるフラグ
	bool isSceneEnd = false;

	// ナンバー
	uint32_t textureHandleNumber = 0;
	Sprite* spriteNumber_[4] = {};

	// スコア
	uint32_t textureHandleSCORE = 0;
	Sprite* spriteScore = {};
	int gameScore = 0;
};
