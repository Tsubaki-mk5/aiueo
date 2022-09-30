#include "Boss.h"
#include "AnimData.h"
static TexAnim BossIdle[] = {
	{ 0,5 },
	{ 1,5 },
	{ 2,5 },
	{ 3,5 },
	{ 4,5 },
	{ 5,5 },
	{ 6,5 },
	{ 7,5 },
	{ 8,5 },
};

static TexAnim BossAttack[] = {
	{ 0,10 },
	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },
};
TexAnimData Boss_anim_data[] = {
	ANIMDATA(BossIdle),
	ANIMDATA(BossAttack),
};
Boss::Boss(const CVector2D& p, bool flip) : Base(e_Type_Boss) {
	m_img = COPY_RESOURCE("Boss", CImage);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(128, 244);
	m_flip = flip;
	m_state = eState_Idle;
}
void Boss::StateIdle()
{
	const float move_speed = 6;
	bool move_flag = false;
}
void Boss::StateAttack()
{
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Boss::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Boss::StateDown()
{
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
