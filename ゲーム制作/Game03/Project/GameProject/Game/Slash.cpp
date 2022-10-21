#include "Slash.h"
#include "AnimData.h"

Slash::Slash(const CVector2D& pos, bool flip, int type, int attack_no) : Base(type)
{
	m_img.Load("Image/Effect_Slash.png", effect_slash_anim_data, 128, 128);
	m_flip = flip;
	m_pos = pos;
	m_img.SetSize(128, 128);
	m_img.SetCenter(64, 64);
	m_rect = CRect(-64, -64, 64, 64);
	m_img.ChangeAnimation(0, false);
	m_attack_no = attack_no;

}

void Slash::Update()
{
	m_img.UpdateAnimation();
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Slash::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
