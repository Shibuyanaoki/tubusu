#include "ScoreResultScene.h"

void ScoreResultScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// スコア文字テクスチャ
	textureHandleSCORE = TextureManager::Load("score.png");
	// スコアの数字テクスチャ
	textureHandleNumber = TextureManager::Load("number.png");
	// スコアのスプライト描画
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i] = Sprite::Create(textureHandleNumber, {130.0f + i * 26, 10});
	}
	// スコアのスプライト描画
	spriteScore = Sprite::Create(textureHandleSCORE, {0.0f, 10});
	// ワールドトランスフォームの初期化
	// worldTransform_.Initialize();
	// ビューポートプロジェクションの初期化
	viewProjection_.Initialize();
}

void ScoreResultScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd = true;
	}

	GamePlayDraw2DNear();
}

void ScoreResultScene::Draw() {}

void ScoreResultScene::GamePlayDraw2DNear() {
	// 描画

	spriteScore->Draw();
	DrawScore();
}

void ScoreResultScene::DrawScore() {
	int eachNumber[4] = {};
	int number = gameScore;

	int keta = 1000;
	for (int i = 0; i < 4; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i]->SetSize({32, 64});
		spriteNumber_[i]->SetTextureRect({32.0f * eachNumber[i], 0}, {32, 64});
		spriteNumber_[i]->Draw();
	}
}
