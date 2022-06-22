#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"

class Floor {

public:

	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

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

	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_;

};