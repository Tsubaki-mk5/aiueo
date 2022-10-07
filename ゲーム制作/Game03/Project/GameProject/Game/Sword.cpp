#include "Sword.h"

Sword::Sword(const CVector2D& pos, bool flip, int type, int attack_no) : Base(type) {

	m_img = COPY_RESOURCE("Sword", CImage);
	m_flip = flip;
	m_pos = pos;
	m_img.SetSize(50, 50);
	m_img.SetCenter(25, 25);
	m_rect = CRect(-25, -25, 25, 25);
	m_img.ChangeAnimation(0, false);
	m_attack_no = attack_no;
}
void Sword::Update() {
	m_img.UpdateAnimation();
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}
void Sword::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}