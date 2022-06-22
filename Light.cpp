#include "Light.h"
#include "Affine.h"
#include "GameScene.h"

//初期化
void Light::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);

	//因数としてうけとったデータを記録
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換初期化
	worldtransform_.Initialize();

	//アフィン行列
	affine_ = new Affine();

	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { 10,10,0 };

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

};

//更新
void Light::Update() {

	//キャラクターの移動ベクトル
	Vector3 move = { 0.0f,0.0f,0.0f };

	//キャラクターの移動速さ
	const float speed = 0.2f;

	//移動ベクトルの変更
	if (input_->PushKey(DIK_A)) {
		move = { -speed,0,0 };
	}
	else if (input_->PushKey(DIK_D)) {
		move = { speed,0,0 };
	}

	if (input_->PushKey(DIK_W)) {
		move = { 0,speed,0 };
	}
	else if (input_->PushKey(DIK_S)) {
		move = { 0,-speed,0 };
	}

	if (input_->PushKey(DIK_Q)) {
		move = { 0,0,speed };
	}
	else if (input_->PushKey(DIK_E)) {
		move = { 0,0,-speed };
	}

	//移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	//ベクトルの加算
	worldtransform_.translation_.x += move.x;
	worldtransform_.translation_.y += move.y;
	worldtransform_.translation_.z += move.z;

	worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, kMoveLimitY);

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 40);
	debugText_->Printf("LightPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

};

//描画
void Light::Draw(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};


//Vector3 GetTrans() {
//
//	Vector3 translation;
//
//	worldtransform_.translation_;
//
//	translation = worldtransform_.translation_;
//
//	return translation;
//};
