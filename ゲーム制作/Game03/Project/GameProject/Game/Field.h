#pragma once
#include"../Base/Base.h"
class Field :public Base {
private:
	//�n�ʂ̍���
	float m_ground_y;
public:
	///�R���X�g���N�^
	Field();
	///�`��
	void Draw();
	///�n�ʂ̍������擾
	float GetGroundY() {
		return m_ground_y;
	}
};