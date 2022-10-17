#pragma once
#include"../Base/Base.h"
class Arrow :public Base {
public:
	CImage m_img;
	bool	m_flip;
	int m_attack_no;
	int m_cnt;

public:
	Arrow(const CVector2D& pos,bool flip,int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};