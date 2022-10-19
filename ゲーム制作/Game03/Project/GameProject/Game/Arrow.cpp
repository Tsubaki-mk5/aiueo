#include "Arrow.h"

Arrow::Arrow(const CVector2D& pos, bool flip,int attack_no) :
	Base(eType_Arrow){
	m_img = COPY_RESOURCE("Arrow",CImage);
	m_pos = pos;
	m_rad = 12;
	m_flip = flip;
	m_img.SetSize(30, 10);
	m_img.SetCenter(15, 5);
	m_attack_no = attack_no;
	m_cnt = 30;
}

void Arrow::Update()
{
	const int move_speed = 15;
	if (m_flip) {
		m_pos.x -= move_speed;
	}
	else {
		m_pos.x += move_speed;
	}
	if (--m_cnt <= 0) {
		m_kill = true;
	}
}

void Arrow::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();

}