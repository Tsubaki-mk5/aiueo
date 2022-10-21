#pragma once
#include "../Base/Base.h"

class Slash : public Base {

private:
	CImage m_img;
	bool m_flip;
	int m_attack_no;
public:
	Slash(const CVector2D& pos, bool flip, int type, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};
