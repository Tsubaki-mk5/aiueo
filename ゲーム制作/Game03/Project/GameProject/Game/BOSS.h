#pragma once
#include "../Base/Base.h"

class Boss : public Base {
private:
	CImage m_img;
	bool m_flip;
public:
	Boss(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};