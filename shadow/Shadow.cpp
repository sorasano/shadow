#include "Shadow.h"
#include "GameScene.h"
#include "DebugText.h"

void Shadow::Initialize(Model* model, const Vector3& position) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.jpg");

	//ワールド変換初期化
	worldtransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldtransform_.translation_ = { position.x,position.y,position.z };

	//アフィン行列
	affine_ = new Affine();

	debugText_ = DebugText::GetInstance();

}

void Shadow::Update(Vector3 playerTrans_, Vector3 lightTrans_, Vector3 floorTrans_, Vector3 floorScale_) {

	//----プレイヤーと光源の間のベクトル(影ベクトル)を求める----\\

	//影ベクトルの定義
	Vector3 shadowVec = { 0,0,0 };

	//影ベクトルの大きさの定義
	float shadowVecSize = 0;

	///プレイヤーと光源の位置から影ベクトルを求める
	shadowVec = { playerTrans_.x - lightTrans_.x ,playerTrans_.y - lightTrans_.y ,playerTrans_.z - lightTrans_.z };

	//プレイヤーと光源の位置から影ベクトルの大きさを求める
	shadowVecSize = sqrt(((playerTrans_.x - lightTrans_.x) * (playerTrans_.x - lightTrans_.x)) + ((playerTrans_.y - lightTrans_.y) * (playerTrans_.y - lightTrans_.y)) + ((playerTrans_.z - lightTrans_.z) * (playerTrans_.z- lightTrans_.z)));

	//影ベクトルを正規化する

	shadowVec = { shadowVec.x / shadowVecSize ,shadowVec.y / shadowVecSize ,shadowVec.z / shadowVecSize };



	////---プレイヤーと地面の間のベクトル(影の移動ベクトル)を求める---\\

	////影の移動ベクトルの定義
	//Vector3 shadowMoveVec = { 0,0,0 };

	////影の移動ベクトルの大きさの定義
	//float shadowMoveVecSize = 0;

	/////プレイヤーと地面の位置から影の移動ベクトルを求める
	//shadowMoveVec = {floorTrans_.x - playerTrans_.x ,floorTrans_.y - playerTrans_.y,floorTrans_.z - playerTrans_.z };

	////プレイヤーと地面の位置から影の移動ベクトルの大きさを求める
	//shadowMoveVecSize = sqrt(((floorTrans_.x - playerTrans_.x) * ( floorTrans_.x - playerTrans_.x )) + ((floorTrans_.y - playerTrans_.y ) * (floorTrans_.y - playerTrans_.y)) + ((floorTrans_.z - playerTrans_.z) * (floorTrans_.z- playerTrans_.z)));

	////---影の計算を座標に入れる---\\

	////影ベクトルと影の移動ベクトルから影の移動量を計算する

	////影の移動ベクトルを正規化した影ベクトルで割って影を正規化した影ベクトル何個分の位置に置くか決める
	//float shadowSpeed = (shadowMoveVecSize / shadowVec.y);

	//setTranslation_ = { shadowVec.x * shadowSpeed ,shadowVec.y * shadowSpeed ,shadowVec.z * shadowSpeed };

	////上の計算を反映
	//worldtransform_.translation_ = -setTranslation_;

	////座標をplayerTransに戻し再計算
	//setTranslation_ = playerTrans_;


	//影がオブジェクト(floor)まで行ったかどうか
	int shadowHitfloor = false;

	//影の座標がfloorを超えていたらtrueにする

	if (setTranslation_.y <= floorTrans_.y + (floorScale_.y * 2)) {
		shadowHitfloor = true;
	}

	//影の影の座標がfloorを超えていなかったら影の座標を移動
	if (shadowHitfloor == false) {
		setTranslation_ += (shadowVec *= 1);
	}
	else {

		//floorを超えるギリギリの時の座標のみを反映
		worldtransform_.translation_ = setTranslation_;
		//座標をplayerTransに戻し再計算
		setTranslation_ = playerTrans_;
	}

	worldtransform_.scale_ = { 1.0f,0.1f,1.0f };

	debugText_->SetPos(0, 60);
	debugText_->Printf("ShadowPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

	debugText_->SetPos(0, 80);
	debugText_->Printf("ShadowVec(%f,%f,%f)", shadowVec.x, shadowVec.y, shadowVec.z);

	//行列更新
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(worldtransform_.scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void Shadow::Draw(const ViewProjection& viewProjection) {

	//3Dモデルを描画
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}