#pragma once
#include "../Base/Base.h"
extern TexAnimData effect_Thunder_anim_data[];
class Thunder : public Base {
private:
	CImage m_img;
	bool m_flip;
	int m_attack_no;

public:

	Thunder(const char* name, const CVector2D& pos, bool flip, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};