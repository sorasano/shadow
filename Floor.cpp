#include "Floor.h"
#include "Affine.h"
#include "GameScene.h"

//������
void Floor::Initialize(Model* model, uint32_t textureHandle) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ă����Ƃ����f�[�^���L�^
	model_ = model;
	textureHandle_ = textureHandle;

	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ�������
	worldtransform_.Initialize();

	//�A�t�B���s��
	affine_ = new Affine();

	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = { -10,-10,0 };
	worldtransform_.scale_ = {100,1,100};

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(worldtransform_.scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

};


//�`��
void Floor::Draw(ViewProjection& viewProjection_) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

};

//Vector3 GetTrans() {
//
//
//};

