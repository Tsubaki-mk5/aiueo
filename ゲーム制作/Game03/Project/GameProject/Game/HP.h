#pragma once
#include "../Base/Base.h"

class HP : public Base {
public:
	CImage m_img;
public:
	HP();
	int HpMax;
	int NowHp;
	int Width;
	
	
	void Draw();
};
