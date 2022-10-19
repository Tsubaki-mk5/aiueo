#pragma once
#include "../Base/Base.h"

class Needle : public Base {
private:
	CImage m_img;

public:
	Needle(const CVector2D& pos);
	void Update();
	void Draw();
};