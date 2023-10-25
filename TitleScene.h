#pragma once

#include "Scene.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"

class TitleScene {
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
	/// シーンを終わらせるフラグ
	/// </summary>
	/// <returns></returns>
	bool IsSceneEnd() { return isSceneEnd; }

	/// <summary>
	/// 次のゲームシーンに飛ばす処理
	/// </summary>
	/// <returns></returns>
	Scene NextScene() { return Scene::GAME; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//シーンを終わらせるフラグ
	bool isSceneEnd = false;
};
