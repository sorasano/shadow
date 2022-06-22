#include "Player.h"
#include "Affine.h"
#include "GameScene.h"

//������
void Player::Initialize(Model* model, uint32_t textureHandle) {

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

	//�e�𐶐���������
	shadow_ = new Shadow();
	shadow_->Initialize(model_, worldtransform_.translation_);

	////�e��o�^����
	//bullet_ = newBullet;
};

//�X�V
void Player::Update(Vector3 lightTrans_, Vector3 floorTrans_,Vector3 floorScale_) {

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0.0f,0.0f,0.0f };

	//�L�����N�^�[�̈ړ�����
	const float speed = 0.2f;

	//�ړ��x�N�g���̕ύX
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

	//�ړ����E���W
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	//�x�N�g���̉��Z
	worldtransform_.translation_.x += move.x;
	worldtransform_.translation_.y += move.y;
	worldtransform_.translation_.z += move.z;

	worldtransform_.translation_.x = max(worldtransform_.translation_.x,-kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, kMoveLimitY);

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 0);
	debugText_->Printf("PlayerPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

	Rotate();
	//�L�����N�^�[�U������

	shadow_->Update(worldtransform_.translation_, lightTrans_,floorTrans_,floorScale_);
};

//�`��
void Player::Draw(ViewProjection& viewProjection_) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

	//�e�`��
	shadow_->Draw(viewProjection_);
};

void Player::Rotate() {


	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 rot = { 0.0f,0.0f,0.0f };

	//�L�����N�^�[�̈ړ�����
	const float rotY = 0.01f;

	//�ړ��x�N�g���̕ύX
	if (input_->PushKey(DIK_R)) {
		rot = { 0.0f,rotY,0.0f };
	}
	else if (input_->PushKey(DIK_T)) {
		rot = {0.0f,-rotY,0.0f };
	}

	//�x�N�g���̉��Z

	worldtransform_.rotation_.x += rot.x;
	worldtransform_.rotation_.y += rot.y;
	worldtransform_.rotation_.z += rot.z;

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(affine_->Scale_), affine_->Rot(affine_->RotX(worldtransform_.rotation_.x), affine_->RotY(worldtransform_.rotation_.y), affine_->RotZ(worldtransform_.rotation_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

	debugText_->SetPos(0, 20);
	debugText_->Printf("PlayerRot(%f,%f,%f)", worldtransform_.rotation_.x, worldtransform_.rotation_.y, worldtransform_.rotation_.z);


};

