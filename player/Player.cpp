#include "Player.h"
#include "Affine.h"
#include "GameScene.h"

//初期化
void Player::Initialize(Model* model, uint32_t textureHandle) {

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

	//影を生成し初期化
	shadow_ = new Shadow();
	shadow_->Initialize(model_, worldtransform_.translation_);

	////影を登録する
	//bullet_ = newBullet;
};

//更新
void Player::Update(Vector3 lightTrans_, Vector3 floorTrans_,Vector3 floorScale_) {

	//キャラクターの移動ベクトル
	Vector3 move = { 0.0f,0.0f,0.0f };

	//キャラクターの移動速さ
	const float speed = 0.2f;

	//移動ベクトルの変更
	if (input_->PushKey(DIK_LEFT)) {
		move = { -speed,0,0 };
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move = { speed,0,0 };
	}

	if (input_->PushKey(DIK_UP)) {
		move = { 0,speed,0 };
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move = { 0,-speed,0 };
	}

	//移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	//ベクトルの加算
	worldtransform_.translation_.x += move.x;
	worldtransform_.translation_.y += move.y;
	worldtransform_.translation_.z += move.z;

	worldtransform_.translation_.x = max(worldtransform_.translation_.x,-kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, kMoveLimitY);

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 0);
	debugText_->Printf("PlayerPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

	Rotate();
	//キャラクター攻撃処理

	shadow_->Update(worldtransform_.translation_, lightTrans_,floorTrans_,floorScale_);
};

//描画
void Player::Draw(ViewProjection& viewProjection_) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

	//影描画
	shadow_->Draw(viewProjection_);
};

void Player::Rotate() {


	//キャラクターの移動ベクトル
	Vector3 rot = { 0.0f,0.0f,0.0f };

	//キャラクターの移動速さ
	const float rotY = 0.01f;

	//移動ベクトルの変更
	if (input_->PushKey(DIK_R)) {
		rot = { 0.0f,rotY,0.0f };
	}
	else if (input_->PushKey(DIK_T)) {
		rot = {0.0f,-rotY,0.0f };
	}

	//ベクトルの加算

	worldtransform_.rotation_.x += rot.x;
	worldtransform_.rotation_.y += rot.y;
	worldtransform_.rotation_.z += rot.z;

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 20);
	debugText_->Printf("PlayerRot(%f,%f,%f)", worldtransform_.rotation_.x, worldtransform_.rotation_.y, worldtransform_.rotation_.z);


};

