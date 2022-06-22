#include "Light.h"
#include "Affine.h"
#include "GameScene.h"

//������
void Light::Initialize(Model* model, uint32_t textureHandle) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ă����Ƃ����f�[�^���L�^
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ�������
	worldtransform_.Initialize();

	//�A�t�B���s��
	affine_ = new Affine();

	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = { 10,10,0 };

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

};

//�X�V
void Light::Update() {

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0.0f,0.0f,0.0f };

	//�L�����N�^�[�̈ړ�����
	const float speed = 0.2f;

	//�ړ��x�N�g���̕ύX
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

	//�ړ����E���W
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	//�x�N�g���̉��Z
	worldtransform_.translation_.x += move.x;
	worldtransform_.translation_.y += move.y;
	worldtransform_.translation_.z += move.z;

	worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, kMoveLimitY);

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 40);
	debugText_->Printf("LightPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

};

//�`��
void Light::Draw(ViewProjection& viewProjection_) {

	//3D���f����`��
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
