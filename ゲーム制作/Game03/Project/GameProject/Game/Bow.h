#pragma once
#include "../Base/Base.h"

class Bow : public Base {
private:
	CImage m_img;
	bool	m_flip;
	int m_cnt;

public:
	Bow(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
};