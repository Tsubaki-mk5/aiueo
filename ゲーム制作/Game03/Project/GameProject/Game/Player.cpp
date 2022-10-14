#include"Player.h"
#include"AnimData.h"
#include"Sword.h"
#include"Arrow.h"
#include"Bow.h"
#include "Field.h"

static TexAnim playerIdle[] = {
	{ 8,8 },
};
static TexAnim playerRun[] = {
	{ 12,7 },
	{ 13,7 },
	{ 14,7 },
	{ 15,7 },
};
static TexAnim playerJumpUp[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
};
static TexAnim playerJumpDown[] = {
	{ 3,4 },
	{ 3,4 },
};
static TexAnim playerAttackSword[] = {
	{ 32,5 },
	{ 33,5 },
	{ 34,5 },
	{ 35,5 },
};
static TexAnim playerAttackArrow[] = {
	{ 21,6 },
	{ 22,6 },
	{ 23,6 },
};
static TexAnim playerDamage[] = {
	{ 88,2 },
	{ 89,2 },
	{ 90,2 },
	{ 91,2 },
};
static TexAnim playerDown[] = {
	{ 27,4 },
	{ 36,4 },
	{ 45,4 },
	{ 46,4 },
	{ 47,4 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),
	ANIMDATA(playerRun),
	ANIMDATA(playerJumpUp),
	ANIMDATA(playerJumpDown),
	ANIMDATA(playerAttackSword),
	ANIMDATA(playerAttackArrow),
	ANIMDATA(playerDamage),
	ANIMDATA(playerDown),
};

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(40, 40);
	m_img.SetSize(80, 80);
	m_flip = flip;
	m_state = eState_Idle;
	m_is_ground;
	m_attack_no = rand();
	m_damage_no = -1;
	m_rect = CRect(-40, -40, 40, 0);
	m_hp = 1;
}

void Player::StateIdle() {

	const float move_speed = 4;
	const float jump_pow = 12;
	bool move_flag = false;

	if (HOLD(CInput::eLeft)) {
		m_pos.x += -move_speed;
		m_flip = true;
		move_flag = true;
	}
	if (HOLD(CInput::eRight)) {
		m_pos.x += move_speed;
		m_flip = false;
		move_flag = true;
	}
	
	if (PUSH(CInput::eButton1)) {
		m_state = eState_Attack_Sword;
		m_attack_no++;
	}
	if (PUSH(CInput::eButton2)) {
		m_state = eState_Attack_Arrow;
		m_attack_no++;
	}

	
	if (m_is_ground && PUSH(CInput::eButton3)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	if (!m_is_ground) {
		if (m_vec.y < 0)
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			m_img.ChangeAnimation(eAnimJumpDown, false);
	}
	else
	{
		if (move_flag) {
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			m_img.ChangeAnimation(eAnimIdle);
		}
	}
}

void Player::StateAttackSword()
{
	m_img.ChangeAnimation(eAnimAttackSword, false);
	if (m_img.GetIndex() == 0) {
		if (m_flip) {
			Base::Add(new Sword(m_pos + CVector2D(-20, 10), m_flip, m_attack_no));
		}
		else {
			Base::Add(new Sword(m_pos + CVector2D(20, 10), m_flip, m_attack_no));
		}
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateAttackArrow()
{
	m_img.ChangeAnimation(eAnimAttackArrow, false);
	if (m_img.GetIndex() == 1) {
		if (m_flip) {
			Base::Add(new Bow(m_pos + CVector2D(-30, 0), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(-50, 0), m_flip, m_attack_no));
		}
		else {
			Base::Add(new Bow(m_pos + CVector2D(30, 0), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(50, 0), m_flip, m_attack_no));
		}
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateDown() {
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}

void Player::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack_Sword:
		StateAttackSword();
		break;
	case eState_Attack_Arrow:
		StateAttackArrow();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	//アニメーション更新
	m_img.UpdateAnimation();
	//スクロール設定
	m_scroll.x = m_pos.x - 1280 / 4;
}
void Player::Draw() {

	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
		/*
		//ゴール判定
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
		//攻撃オブジェクトとの判定
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
		*/
	case eType_Field:
		//Field型へキャスト、型変換できたら
		if (Field* f = dynamic_cast<Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;
			}
		}
		break;
	}
}