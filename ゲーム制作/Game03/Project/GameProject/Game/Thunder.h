#pragma once
#include "../Base/Base.h"
extern TexAnimData effect_Thunder_anim_data[];
class Thunder : public Base {
private:
	CImage m_img;
	bool m_flip;

public:

	Thunder(const char* name, const CVector2D& pos, bool flip);
	void Update();
	void Draw();

};