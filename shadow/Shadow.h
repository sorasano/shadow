#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Affine.h"

class Shadow
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update(Vector3 playerTrans_, Vector3 lightTrans_, Vector3 floorTrans_, Vector3 floorScale_);

	void Draw(const ViewProjection& viewProjection);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_ = nullptr;

	Vector3 setTranslation_ = {};

};

