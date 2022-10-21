#pragma once
#include "../Base/Base.h"

class Game : public Base {
public:
	Game();
	~Game();
	void Update();
	CImage m_img1;
	CImage m_img2;
	void Draw();
};