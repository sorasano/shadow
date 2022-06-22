#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"

class Light {

public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection_);

	//Vector3 GetTrans();
	//ワールド変換データ
	WorldTransform worldtransform_;

private:

	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_;

};