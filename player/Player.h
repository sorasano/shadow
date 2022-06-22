#pragma once

#include "WorldTransform.h"
#include "WinApp.h"
#include "Model.h"
#include "DebugText.h"
#include "Input.h"
#include "Affine.h"
#include "Shadow.h"

class Player {

public:
	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update(Vector3 lightTrans_, Vector3 floorTrans_, Vector3 floorScale_);

	//�`��
	void Draw(ViewProjection& viewProjection_);

	//����
	void Rotate();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//�A�t�B���s��
	Affine* affine_;

private:
	//�e
	Shadow* shadow_ = nullptr;
};