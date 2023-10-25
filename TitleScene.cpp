#include "TitleScene.h"

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd = true;
	}

}

void TitleScene::Draw() {}
