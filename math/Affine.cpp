#include "Affine.h"
#include "AxisIndicator.h"


Affine::Affine() {

	this->Afiine_ = {};
	this->Scale_ = { 1.0f,1.0f,1.0f };
	this->Rot_ = { 0.0f,0.0f,0.0f };
	this->Trans_ = { 0.0f,  0.0f, 0.0f };

}

Affine::~Affine() {

}

//���[���h�ϊ��s��

//�g��k��
Matrix4 Affine::Scale(Vector3 Scale) {

	//�X�P�[�����O�s���錾
	Matrix4 matScale;

	//�X�P�[�����O�{�����s���ݒ肷��
	matScale = { Scale.x, 0.0f, 0.0f,    0.0f, 0.0f, Scale.y, 0.0f, 0.0f,
				0.0f,    0.0f, Scale.z, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f };

	return matScale;
};

//��]X
Matrix4 Affine::RotX(float roteX) {

	Matrix4 matRotX;

	// X����]�s��̊e�v�f��ݒ肷��
	matRotX = { 1.0f, 0.0f,        0.0f,       0.0f, 0.0f, cos(roteX), sin(roteX), 0.0f,
			   0.0f, -sin(roteX), cos(roteX), 0.0f, 0.0f, 0.0f,       0.0f,       1.0f };

	return matRotX;
};

//��]Y
Matrix4 Affine::RotY(float roteY) {

	Matrix4 matRotY;

	// Y����]�s��̊e�v�f��ݒ肷��

	matRotY = { cos(roteY), 0.0f, -sin(roteY), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			   sin(roteY), 0.0f, cos(roteY),  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	return matRotY;
};

//��]Z
Matrix4 Affine::RotZ(float roteZ) {

	Matrix4 matRotZ;

	// Z����]�s��̊e�v�f��ݒ肷��

	matRotZ = { cos(roteZ), sin(roteZ), 0.0f, 0.0f, -sin(roteZ), cos(roteZ), 0.0f, 0.0f,
			   0.0f,       0.0f,       1.0f, 0.0f, 0.0f,        0.0f,       0.0f, 1.0f };

	return matRotZ;
};

//��]����
Matrix4 Affine::Rot(Matrix4 RotX, Matrix4 RotY, Matrix4 RotZ) {

	// �����p��]�s���錾
	Matrix4 matRot;

	//�e���̉�]�s�������
	matRot = (RotZ *= RotX *= RotY);

	return matRot;
};

//���s�ړ�
Matrix4 Affine::Trans(Vector3 Trans) {

	//�X�P�[�����O�s���錾
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	//�X�P�[�����O�{�����s���ݒ肷��
	matTrans = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    1.0f,    0.0f,    0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, Trans.x, Trans.y, Trans.z, 1.0f };

	return matTrans;
};

//���[���h�ϊ��s��
Matrix4 Affine::World(Matrix4 Scale, Matrix4 Rot, Matrix4 Trans) {

	Matrix4 worldTransform_;

	//�s��̍���

	//�P�ʍs���������
	worldTransform_ = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.f,  0.0f, 1.0f };

	//�|���Z���đ������
	worldTransform_ *= Scale *= Rot *= Trans;

	////�s��̓]��
	// worldTransform.TransferMatrix();

	return worldTransform_;
};