#pragma once
#include "../Base/Base.h"

class Needle : public Base {
private:
	CImage m_img;
	int m_cnt;

public:
	Needle(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base*b);
};