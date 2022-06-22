#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"

class Floor {

public:

	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�`��
	void Draw(ViewProjection& viewProjection_);

	//Vector3 GetTrans();

	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;

private:

	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_;

};