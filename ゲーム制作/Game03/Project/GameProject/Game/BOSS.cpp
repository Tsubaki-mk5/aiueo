#include "Boss.h"
#include "AnimData.h"
#include "Field.h"
#include "Thunder.h"
#include "Arrow.h"
#include "Sword.h"

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
	{ 8,20 },
	{ 9,20 },
	{ 10,20 },
	{ 11,20 },
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
};
static TexAnim BossDamage[] = {
	{ 17,7 },
	{ 18,7 },
	{ 19,7 },
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
	m_img.SetCenter(480,480 );
	m_img.SetSize(500, 500);
	m_rect = CRect(-400, -250, 400, 0);
	m_rad = 270;
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
	if (abs(d) <= 1000) {
		Base::Add(new Thunder("Effect_Thunder", m_pos + CVector2D(-750, -300), m_flip));
		m_state = eState_Attack;
	}
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
	m_kill = true;
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

	/*m_gauge.m_img.SetCenter(200, 400);
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.Draw();*/
}

void Boss::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Arrow:
		//Slash型へキャスト、型変換できたら
		if (Arrow* s = dynamic_cast<Arrow*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 10;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;
	case eType_Sword:
		//Slash型へキャスト、型変換できたら
		if (Sword* s = dynamic_cast<Sword*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 40;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;
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
