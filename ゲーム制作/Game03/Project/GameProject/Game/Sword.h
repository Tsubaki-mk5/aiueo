#pragma once
#include "../Base/Base.h"

class Sword : public Base {
private:
	CImage m_img;
	bool	m_flip;
	int m_cnt;
	int m_attack_no;

public:
	Sword(const CVector2D& pos, bool flip, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};