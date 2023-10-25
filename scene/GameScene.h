#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Scene.h"
#include "Enemy.h"
#include "Hammer.h"
#include "Bom.h"

#include <list>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	/// 当たり判定
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵を複数生成する処理
	/// </summary>
	/// <param name="Position"></param>
	void EnemyGenerate(Vector3 Position);

	/// <summary>
	/// ボウリングを複数生成する処理
	/// </summary>
	/// <param name="Position"></param>
	void BouringGenerate(Vector3 Position);

	/// <summary>
	/// スコアの描画処理
	/// </summary>
	void GamePlayDraw2DNear();

	/// <summary>
	/// スコアの計算と描画処理
	/// </summary>
	void DrawScore();

	/// <summary>
	/// デバッグカメラ有効
	/// </summary>
	bool isDebugCameraActive_ = false;

	int GetGameScore() { return gameScore; };

	/// <summary>
	/// シーンを終わらせるフラグ
	/// </summary>
	/// <returns></returns>
	bool IsSceneEnd() { return isSceneEnd; }

	/// <summary>
	/// 次のゲームシーンに飛ばす処理
	/// </summary>
	/// <returns></returns>
	Scene NextScene() { return Scene::RESULT; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 背景
	uint32_t haikeiTextureHandle_ = 0;

	// 背景スプライト
	Sprite* haikei_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビューポートプロジェクション
	ViewProjection viewProjection_;
	// ハンマー
	Hammer* hammer_ = nullptr;
	// 敵
	Enemy* enemy_ = nullptr;
	// Bouring* bouring_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;
	// ハンマーの3Dモデル
	Model* hammerModel_ = nullptr;
	// 敵の3Dモデル
	Model* enemyModel_ = nullptr;
	// ボウリングの3Dモデル
	Model* bomModel_ = nullptr;
	//// デバッグカメラ
	// DebugCamera* debugCamera_ = nullptr;
	//  敵のリスト
	std::list<Enemy*> enemys_;
	// ボウリング玉のリスト
	std::list<Bom*> boms_;
	// 敵の生成するための時間
	int enemyTimer_ = 0;
	// ボウリングの生成時間
	int bomTimer_ = 0;
	// ゲーム時間
	int gameTimer_ = 0;

	// ナンバー
	uint32_t textureHandleNumber = 0;
	Sprite* spriteNumber_[4] = {};

	// スコア
	uint32_t textureHandleSCORE = 0;
	Sprite* spriteScore = {};
	int gameScore = 0;

	// シーンを終わらせるフラグ
	bool isSceneEnd = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
