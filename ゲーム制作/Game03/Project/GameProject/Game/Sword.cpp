#include "Sword.h"

Sword::Sword(const CVector2D& pos, bool flip, int attack_no) : Base(eType_Sword) {

	m_img = COPY_RESOURCE("Sword", CImage);
	m_flip = flip;
	m_pos = pos;
	m_img.SetSize(60, 60);
	m_img.SetCenter(0,60);
	m_rect = CRect(-30, -30, 30, 30);
	m_img.ChangeAnimation(0, false);
	m_cnt = 15;
	m_attack_no = attack_no;
}
void Sword::Update() {
	m_img.UpdateAnimation();
	//m_ang -= 0.1;
	if (m_flip) {
		m_img.SetCenter(60, 60);
		m_ang += 0.1;
	}
	else {
		m_ang -= 0.1;
	}
	if (--m_cnt <= 0) {
		SetKill();
	}
}
void Sword::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.SetAng(m_ang);
	m_img.Draw();
}