#include "Thunder.h"
static TexAnim _effect_Thunder[] = {
	{ 0,7 },
	{ 1,7 },
	{ 2,7 },
	{ 3,7 },
	{ 4,7 },
	{ 5,7 },
	{ 6,7 },
	{ 7,7 },

};
TexAnimData effect_Thunder_anim_data[] = {
	ANIMDATA(_effect_Thunder),
};
Thunder::Thunder(const char* name, const CVector2D& pos, bool flip) : Base(eType_Thunder)
{
	m_img = COPY_RESOURCE(name, CImage);
	m_pos = pos;
	m_img.SetSize(100, 100);
	m_img.SetCenter(64, 64);
	m_img.ChangeAnimation(0, false);
	m_flip = flip;
}

void Thunder::Update()
{
	m_img.UpdateAnimation();
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Thunder::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
