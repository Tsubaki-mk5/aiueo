#pragma once
#include"../Base/Base.h"

class Field : public Base {
private:
	CImage m_foreground;
	CImage m_DOUKUTSU;
	float m_ground_y;
public:
	Field();

	void Draw();
	float GetGroundY() {
		return m_ground_y;
	}
};

