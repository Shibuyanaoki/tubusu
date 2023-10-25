#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <stdlib.h>
#include <time.h>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete bomModel_;
	delete haikei_;

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}

	for (Bom* bom : boms_) {
		delete bom;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	haikeiTextureHandle_ = TextureManager::Load("haikei.png");
	// スコア文字テクスチャ
	textureHandleSCORE = TextureManager::Load("score.png");
	// スコアの数字テクスチャ
	textureHandleNumber = TextureManager::Load("number.png");
	// スコアのスプライト描画
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i] = Sprite::Create(textureHandleNumber, {130.0f + i * 26, 10});
	}
	// 背景スプライト
	haikeiTextureHandle_ = TextureManager::Load("haikei.png");

	// サウンドデータの読み込み
	// soundDataHandle_ = audio_->LoadWave("");

	// スプライト描画
	haikei_ = Sprite::Create(haikeiTextureHandle_, {0, 0});

	// 3Dモデルの生成
	model_ = Model::Create();
	// ハンマーの生成
	hammerModel_ = Model::CreateFromOBJ("Hammer", true);
	// 敵の生成
	enemyModel_ = Model::CreateFromOBJ("Enemy", true);
	// ボウリングの生成
	bomModel_ = Model::CreateFromOBJ("Bom", true);
	// スコアのスプライト描画
	spriteScore = Sprite::Create(textureHandleSCORE, {0.0f, 10});
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビューポートプロジェクションの初期化
	viewProjection_.Initialize();
	// プレイヤーの生成
	hammer_ = new Hammer;
	// デバッグカメラの生成
	// debugCamera_ = new DebugCamera(1280, 720);
	// ハンマーの初期ポジション
	Vector3 hammerPosition = {-5.5f, .0f, 50.0f};
	// ハンマーの初期化
	hammer_->Initialize(hammerModel_, hammerPosition);
	// ランダム関数
	srand((unsigned int)time(NULL));

	enemyTimer_ = 0;

	bomTimer_ = 0;

	gameTimer_ = 60 * 30;

	gameScore = 0;

	isSceneEnd = false;

	viewProjection_.translation_ = {0.0f, 50.0f, -25.5f};
	viewProjection_.rotation_ = {0.5f, 0.0f, 0.0f};

}

void GameScene::Update() {
	gameTimer_--;
	enemyTimer_--;
	bomTimer_--;

	if (enemyTimer_ <= 0) {

		// 敵の初期ポジション
		Vector3 enemyPosition = {(float)80, -15, 40};

		// 敵の生成処理
		EnemyGenerate(enemyPosition);

		// 敵の生成時間(ランダム)
		enemyTimer_ = 10 + rand() % 60 * 1;
	}

	if (bomTimer_ <= 0) {
		// 敵の初期ポジション
		Vector3 bomPosition = {80, -15, 50};

		// 敵の生成処理
		BouringGenerate(bomPosition);

		bomTimer_ = 180 + rand() % 60 * 6;
	}

	viewProjection_.UpdateMatrix();

	// ハンマーの更新
	hammer_->Update();

	// 敵の更新
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	for (Bom* bouring : boms_) {
		bouring->Update();
	}

	// 当たり判定の処理
	CheckAllCollisions();

	// デスフラグの立った敵を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// デスフラグの立った敵を削除
	boms_.remove_if([](Bom* bouring) {
		if (bouring->IsDead()) {
			delete bouring;
			return true;
		}
		return false;
	});

	if (gameTimer_ <= 0) {
		isSceneEnd = true;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	haikei_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	hammer_->Draw(viewProjection_);

	// 敵の描画
	for (Enemy* enemy : enemys_) {

		enemy->Draw(viewProjection_);
	}

	for (Bom* bom : boms_) {
		bom->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
