#include "Boss.h"
#include "AnimData.h"
#include "Field.h"
#include "Thunder.h"

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
	{ 8,15 },
	{ 9,15 },
	{ 10,15 },
	{ 11,15 },
};
static TexAnim BossDamage[] = {
	{ 12,5 },
	{ 13,5 },
	{ 14,5 },
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
	m_img.SetCenter(400,400 );
	m_img.SetSize(500, 500);
	m_rad = 300;
	m_rect = CRect(-32, -128, 32, 0);
	m_flip = flip;
	m_is_ground = false;
	m_state = eState_Idle;
	m_hp = 500;
}
void Boss::StateIdle()
{
	m_img.ChangeAnimation(AnimIdle);
	const float move_speed = 0;
	bool move_flag = false;
	Base* player = Base::FindObject(eType_Player);
	
	if (player->m_pos.x < m_pos.x - 64) {
		m_pos.x += -move_speed;
		m_flip = false;
		move_flag = true;
	}
	if (player->m_pos.x > m_pos.x + 64) {
		m_pos.x += move_speed;
		m_flip = true;
		move_flag = true;
	}

	float d = player->m_pos.x - m_pos.x;
	if (abs(d) <= 1000)
		m_state = eState_Attack;
	Base::Add(new Thunder("Effect_Thunder", m_pos + CVector2D(0, -128), m_flip));
	
}

void Boss::StateAttack()
{
	m_img.ChangeAnimation(AnimAttack, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Boss::StateDamage()
{
	m_img.ChangeAnimation(AnimDamage, false);
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

	m_vec.y += GRAVITY;
	m_pos += m_vec;
}

void Boss::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	DrawRect();

	m_gauge.m_img.SetCenter(200, 400);
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.Draw();
}

void Boss::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_pos.y > f->GetGroundY()) {
				m_pos.y = f->GetGroundY();
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}
