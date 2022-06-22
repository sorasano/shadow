#pragma once

#include "DebugText.h"


class Affine
{

public:

	Matrix4 Afiine_;
	Vector3 Scale_;
	Vector3 Rot_;
	Vector3 Trans_;

public:

	//�R���X�g���N�^
	Affine();

	//�f�X�g���N�^
	~Affine();

	//���[���h�ϊ��s��

	//�g��k��
	Matrix4 Scale(Vector3 Scale);

	//��]X
	Matrix4 RotX(float roteX);

	//��]Y
	Matrix4 RotY(float roteY);

	//��]Z
	Matrix4 RotZ(float roteZ);

	//��]����
	Matrix4 Rot(Matrix4 RotX, Matrix4 RotY, Matrix4 RotZ);

	//���s�ړ�
	Matrix4 Trans(Vector3 Trans);

	//���[���h�ϊ��s��
	Matrix4 World(Matrix4 Scale, Matrix4 Rot, Matrix4 Trans);

};

