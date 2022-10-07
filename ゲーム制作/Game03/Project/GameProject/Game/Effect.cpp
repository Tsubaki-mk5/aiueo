#include "Effect.h"

Effect::Effect(const char* name, const CVector2D& pos, bool flip) : Base(eType_Effect)
{
	m_img = COPY_RESOURCE(name, CImage);
	m_pos = pos;
	m_img.SetSize(128, 128);
	m_img.SetCenter(64, 64);
	m_img.ChangeAnimation(0, false);
	m_flip = flip;
}

void Effect::Update()
{
	m_img.UpdateAnimation();
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Effect::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
