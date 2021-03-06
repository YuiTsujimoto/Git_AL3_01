#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	
	delete model_; 

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");

	model_ = Model::Create();

	worldTransform_.translation_ = {10.0f,10.0f,10.0f,};
	worldTransform_.rotation_ = {XMConvertToRadians(45.0f), XMConvertToRadians(45.0f), 0.0f};
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};

	worldTransform_.Initialize();
	viewProjection_.Initialize();

}

void GameScene::Update() {

	debugText_->SetPos(50, 50);
	debugText_->Printf("translation:(%f,%f,%f)", 10.0f, 10.0f, 10.0f);

	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "scale:(%f,%f,%f)", XMConvertToRadians(45.0f), XMConvertToRadians(45.0f), 0.0f);

	debugText_->SetPos(50, 90);
	debugText_->Printf("rotation:(%f,%f,%f)", 5.0f, 5.0f, 5.0f);


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

	// 3Dオブジェクト描画後処理

	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	Model::PostDraw();
	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
