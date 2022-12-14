#include "Thunder.h"
static TexAnim _effect_Thunder[] = {
	{ 0,10 },
	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },
	{ 5,10 },
	{ 6,10 },
	{ 7,10 },

};
TexAnimData effect_Thunder_anim_data[] = {
	ANIMDATA(_effect_Thunder),
};
Thunder::Thunder(const char* name, const CVector2D& pos, bool flip, int attack_no) : Base(eType_Thunder)
{
	m_img = COPY_RESOURCE(name, CImage);
	m_pos = pos;
	m_img.SetSize(500, 500);
	m_img.SetCenter(200, 200);
	m_img.ChangeAnimation(0, false);
	m_rect = CRect(-200, -100, 300, 200);
	m_rad = 200;
	m_flip = flip;
	m_attack_no = attack_no;
}

void Thunder::Update()
{
	const float speed = 15;
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
	DrawRect();
}
