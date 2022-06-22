#include "Floor.h"
#include "Affine.h"
#include "GameScene.h"

//初期化
void Floor::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);

	//因数としてうけとったデータを記録
	model_ = model;
	textureHandle_ = textureHandle;

	debugText_ = DebugText::GetInstance();

	//ワールド変換初期化
	worldtransform_.Initialize();

	//アフィン行列
	affine_ = new Affine();

	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { -10,-10,0 };
	worldtransform_.scale_ = {100,1,100};

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(worldtransform_.scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

};


//描画
void Floor::Draw(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};

//Vector3 GetTrans() {
//
//
//};

