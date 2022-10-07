#pragma once
#include "../Base/Base.h"

class Effect : public Base {
private:
	CImage m_img;

	bool m_flip;

public:

	Effect(const char* name, const CVector2D& pos, bool flip);
	void Update();
	void Draw();

};