#include "Shadow.h"
#include "GameScene.h"
#include "DebugText.h"

void Shadow::Initialize(Model* model, const Vector3& position) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.jpg");

	//���[���h�ϊ�������
	worldtransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldtransform_.translation_ = { position.x,position.y,position.z };

	//�A�t�B���s��
	affine_ = new Affine();

	debugText_ = DebugText::GetInstance();

}

void Shadow::Update(Vector3 playerTrans_, Vector3 lightTrans_, Vector3 floorTrans_, Vector3 floorScale_) {

	//----�v���C���[�ƌ����̊Ԃ̃x�N�g��(�e�x�N�g��)�����߂�----\\

	//�e�x�N�g���̒�`
	Vector3 shadowVec = { 0,0,0 };

	//�e�x�N�g���̑傫���̒�`
	float shadowVecSize = 0;

	///�v���C���[�ƌ����̈ʒu����e�x�N�g�������߂�
	shadowVec = { playerTrans_.x - lightTrans_.x ,playerTrans_.y - lightTrans_.y ,playerTrans_.z - lightTrans_.z };

	//�v���C���[�ƌ����̈ʒu����e�x�N�g���̑傫�������߂�
	shadowVecSize = sqrt(((playerTrans_.x - lightTrans_.x) * (playerTrans_.x - lightTrans_.x)) + ((playerTrans_.y - lightTrans_.y) * (playerTrans_.y - lightTrans_.y)) + ((playerTrans_.z - lightTrans_.z) * (playerTrans_.z- lightTrans_.z)));

	//�e�x�N�g���𐳋K������

	shadowVec = { shadowVec.x / shadowVecSize ,shadowVec.y / shadowVecSize ,shadowVec.z / shadowVecSize };



	////---�v���C���[�ƒn�ʂ̊Ԃ̃x�N�g��(�e�̈ړ��x�N�g��)�����߂�---\\

	////�e�̈ړ��x�N�g���̒�`
	//Vector3 shadowMoveVec = { 0,0,0 };

	////�e�̈ړ��x�N�g���̑傫���̒�`
	//float shadowMoveVecSize = 0;

	/////�v���C���[�ƒn�ʂ̈ʒu����e�̈ړ��x�N�g�������߂�
	//shadowMoveVec = {floorTrans_.x - playerTrans_.x ,floorTrans_.y - playerTrans_.y,floorTrans_.z - playerTrans_.z };

	////�v���C���[�ƒn�ʂ̈ʒu����e�̈ړ��x�N�g���̑傫�������߂�
	//shadowMoveVecSize = sqrt(((floorTrans_.x - playerTrans_.x) * ( floorTrans_.x - playerTrans_.x )) + ((floorTrans_.y - playerTrans_.y ) * (floorTrans_.y - playerTrans_.y)) + ((floorTrans_.z - playerTrans_.z) * (floorTrans_.z- playerTrans_.z)));

	////---�e�̌v�Z�����W�ɓ����---\\

	////�e�x�N�g���Ɖe�̈ړ��x�N�g������e�̈ړ��ʂ��v�Z����

	////�e�̈ړ��x�N�g���𐳋K�������e�x�N�g���Ŋ����ĉe�𐳋K�������e�x�N�g�������̈ʒu�ɒu�������߂�
	//float shadowSpeed = (shadowMoveVecSize / shadowVec.y);

	//setTranslation_ = { shadowVec.x * shadowSpeed ,shadowVec.y * shadowSpeed ,shadowVec.z * shadowSpeed };

	////��̌v�Z�𔽉f
	//worldtransform_.translation_ = -setTranslation_;

	////���W��playerTrans�ɖ߂��Čv�Z
	//setTranslation_ = playerTrans_;


	//�e���I�u�W�F�N�g(floor)�܂ōs�������ǂ���
	int shadowHitfloor = false;

	//�e�̍��W��floor�𒴂��Ă�����true�ɂ���

	if (setTranslation_.y <= floorTrans_.y + (floorScale_.y * 2)) {
		shadowHitfloor = true;
	}

	//�e�̉e�̍��W��floor�𒴂��Ă��Ȃ�������e�̍��W���ړ�
	if (shadowHitfloor == false) {
		setTranslation_ += (shadowVec *= 1);
	}
	else {

		//floor�𒴂���M���M���̎��̍��W�݂̂𔽉f
		worldtransform_.translation_ = setTranslation_;
		//���W��playerTrans�ɖ߂��Čv�Z
		setTranslation_ = playerTrans_;
	}

	worldtransform_.scale_ = { 1.0f,0.1f,1.0f };

	debugText_->SetPos(0, 60);
	debugText_->Printf("ShadowPos(%f,%f,%f)", worldtransform_.translation_.x, worldtransform_.translation_.y, worldtransform_.translation_.z);

	debugText_->SetPos(0, 80);
	debugText_->Printf("ShadowVec(%f,%f,%f)", shadowVec.x, shadowVec.y, shadowVec.z);

	//�s��X�V
	worldtransform_.matWorld_ = affine_->World(affine_->Scale(worldtransform_.scale_), affine_->Rot(affine_->RotX(affine_->Rot_.x), affine_->RotY(affine_->Rot_.y), affine_->RotZ(affine_->Rot_.z)), affine_->Trans(worldtransform_.translation_));
	worldtransform_.TransferMatrix();

}

void Shadow::Draw(const ViewProjection& viewProjection) {

	//3D���f����`��
	model_->Draw(worldtransform_, viewProjection, textureHandle_);

}