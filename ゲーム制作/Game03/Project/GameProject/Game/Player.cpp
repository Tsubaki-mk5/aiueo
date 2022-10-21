#include"Player.h"
#include"AnimData.h"
#include"Sword.h"
#include"Arrow.h"
#include"Bow.h"
#include "Field.h"
#include"Needle.h"
#include"Slash.h"
#include"Thunder.h"

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
	{ 32,4 },
	{ 32,1 },
	{ 33,5 },
	{ 34,5 },
	{ 35,5 },
};
static TexAnim playerAttackArrow[] = {
	{ 21,5 },
	{ 21,1 },
	{ 22,6 },
	{ 23,6 },
};
static TexAnim playerDamage[] = {
	{ 42,5 },
	{ 43,5 },
	{ 44,5 },
};
static TexAnim playerDown[] = {
	{ 42,5 },
	{ 43,5 },
	{ 44,5 },
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
	m_img.SetCenter(40, 80);
	m_img.SetSize(80, 80);
	m_rect = CRect(-40, -80, 40, 0);
	m_flip = flip;
	m_state = eState_Idle;
	m_is_ground;
	m_attack_no = rand();
	m_damage_no = -1;
	m_hp = 100;
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
	if (m_img.GetIndex() == 1) {
		if (m_flip) {
			Base::Add(new Sword(m_pos + CVector2D(-20, -30), m_flip, m_attack_no));
		}
		else {
			Base::Add(new Sword(m_pos + CVector2D(20, -30), m_flip, m_attack_no));
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
			Base::Add(new Bow(m_pos + CVector2D(-30, -30), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(-50, -30), m_flip, m_attack_no));
		}
		else {
			Base::Add(new Bow(m_pos + CVector2D(30, -30), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(50, -30), m_flip, m_attack_no));
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
	//if (m_img.CheckAnimationEnd()) {
	//}
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
		*/
	case eType_Thunder:
		if (Thunder* t = dynamic_cast<Thunder*>(b)) {
			if (m_damage_no != t->GetAttackNo() && Base::CollisionCircle(this, t)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = t->GetAttackNo();
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
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 20;
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
	case eType_Needle:
		if (Needle* n = dynamic_cast<Needle*>(b)) {
			if (Base::CollisionRect(this, n)) {
				m_hp -= 30;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;
	}
}