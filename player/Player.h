#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"
#include "Shadow.h"

class Player {

public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update(Vector3 lightTrans_, Vector3 floorTrans_, Vector3 floorScale_);

	//描画
	void Draw(ViewProjection& viewProjection_);

	//旋回
	void Rotate();

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//アフィン行列
	Affine* affine_;

private:
	//影
	Shadow* shadow_ = nullptr;
};