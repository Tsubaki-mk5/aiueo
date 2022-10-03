#include "Boss.h"
#include "AnimData.h"
static TexAnim BossIdle[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
};

static TexAnim BossAttack[] = {
	{ 0,10 },
	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },
};
static TexAnim BossDamage[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
};
TexAnimData Boss_anim_data[] = {
	ANIMDATA(BossIdle),
	ANIMDATA(BossAttack),
	ANIMDATA(BossDamage),
};
Boss::Boss(const CVector2D& p, bool flip) : Base(eType_Boss) {
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
	Base* player = Base::FindObject(eType_Player);
	
	/*if (player->m_pos.x < m_pos.x - 64) {
		m_pos.x += -move_speed;
		m_flip = true;
		move_flag = true;
	}
	if (player->m_pos.x > m_pos.x + 64) {
		m_flip = false;
		move_flag = true;
	}
	*/
}
void Boss::StateAttack()
{
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
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
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
