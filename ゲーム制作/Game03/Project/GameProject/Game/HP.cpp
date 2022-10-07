#include "HP.h"

HP::HP() : Base(eType_HP) {
	m_img.Load("Image/hp.png");
	m_img.SetSize(150, 150);
}

void HP::Draw() {
	
	float s = Width * NowHp / HpMax;

	m_img.SetPos(m_pos);
	m_img.SetSize(110, 40);
	m_img.Draw();
}