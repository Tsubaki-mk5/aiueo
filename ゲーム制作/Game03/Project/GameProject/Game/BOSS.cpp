#include "Boss.h"
#include "AnimData.h"
Boss::Boss(const CVector2D& p, bool flip) : Base(e_Type_Boss) {
	m_img = COPY_RESOURCE("Boss", CImage);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(128, 244);
	m_flip = flip;

}

void Boss::Update()
{
	m_img.ChangeAnimation(eAnimIdle);
	m_img.UpdateAnimation();
}

void Boss::Draw()
{
	m_img.SetPos(m_pos);
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Boss::Collision(Base* b)
{
}
