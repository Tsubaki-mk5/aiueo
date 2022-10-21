#include "Enemy.h"
#include "Player.h"
#include "Field.h"
#include "Slash.h"
#include "Sword.h"
#include "Arrow.h"
#include "AnimData.h"
#include "Effect.h"

static TexAnim enemyIdle[] = {
	{ 0,7 },
	{ 1,7 },
	{ 2,7 },
	{ 3,7 },
};
static TexAnim enemyRun[] = {
	{ 6,8 },
	{ 7,8 },
	{ 8,8 },
	{ 9,8 },
	{ 10,8 },
};
static TexAnim enemyJumpUp[] = {
	{ 35,6 },
	{ 34,6 },
};
static TexAnim enemyJumpDown[] = {
	{ 29,6 },
	{ 28,6 },
};

static TexAnim enemyAttack01[] = {
	{ 12,5 },
	{ 13,5 },
	{ 14,5 },
	{ 15,5 },
	{ 16,5 },
};
static TexAnim enemyAttack01End[] = {
	{ 5,8 },
	{ 4,8 },
	{ 3,8 },
	{ 2,8 },
};
static TexAnim enemyAttack02[] = {
	{ 0,0 },
};
static TexAnim enemyAttack02End[] = {
	{ 0,0 },
};
static TexAnim enemyAttack03[] = {
	{ 0,0 },
};
static TexAnim enemyAttack03End[] = {
	{ 0,0 },
};
static TexAnim enemyDamage[] = {
	{ 18,6 },
	{ 19,6 },
};
static TexAnim enemyDamageEnd[] = {
	{ 18,6 },
	{ 19,6 },
};
static TexAnim enemyDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim enemyDown[] = {
	{ 30,6 },
	{ 29,6 },
};


TexAnimData enemy_anim_data[] = {
	ANIMDATA(enemyIdle),
	ANIMDATA(enemyRun),
	ANIMDATA(enemyJumpUp),
	ANIMDATA(enemyJumpDown),
	ANIMDATA(enemyAttack01),
	ANIMDATA(enemyAttack01End),
	ANIMDATA(enemyAttack02),
	ANIMDATA(enemyAttack02End),
	ANIMDATA(enemyAttack03),
	ANIMDATA(enemyAttack03End),
	ANIMDATA(enemyDamage),
	ANIMDATA(enemyDamageEnd),
	ANIMDATA(enemyDeath),
	ANIMDATA(enemyDown),
	
};

Enemy::Enemy(const CVector2D& p, bool flip) : Base(eType_Enemy) {
	m_img.Load("Image/Enemy1.png", enemy_anim_data, 96, 100);
	m_rad = 16;
	m_img.SetSize(160, 160);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(100, 150);
	m_rect = CRect(-41, -100, 41, 0);
	m_flip = flip;

	m_state = eState_Idle;


	m_is_ground = true;
	m_attack_no = rand();
	m_damage_no = (0);
	m_hp = 200;

}

void Enemy::StateIdle() {

	const float move_speed = 3;
	bool move_flag = false;
	const float jump_pow = 12;
	Base* player = Base::FindObject(eType_Player);

	if (player) {

		//左移動
		if (player->m_pos.x > m_pos.x - 64) {
			m_pos.x += move_speed;
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (player->m_pos.x < m_pos.x + 64) {
			m_pos.x += -move_speed;
			m_flip = false;
			move_flag = true;
		}
		else {
			//攻撃状態へ移行
			m_state = eState_Attack;
			m_attack_no++;
		}
	}

		if (move_flag) {
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			m_img.ChangeAnimation(eAnimIdle);
		}
		if (--m_cnt <= 0) {
			m_cnt = rand() % 120 + 180;
			m_state = eState_Wait;
		}
	}


void Enemy::StateWait() {
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
	//カウント0で通常状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		m_state = eState_Idle;
	}
}

void Enemy::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack01, false);
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(10, -30), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(10, -30), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;

	}
}

void Enemy::StateDamage() {
	if (m_damage_no)
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}

}

void Enemy::StateDown() {
	/*
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		//Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}*/
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_hp <= 0) {
		m_kill = true;
	}
}
void Enemy::Update() {
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
	case eState_Wait:
		StateWait();
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
	m_scroll.x;
	//m_img.ChangeAnimation(eAnimIdle);

}

void Enemy::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	DrawRect();
	/*
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.m_img.SetCenter(50, 160);
	m_gauge.Draw();*/
}

void Enemy::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Sword:
		if (Sword* s = dynamic_cast<Sword*>(b)) {
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
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Arrow:
		if (Arrow* s = dynamic_cast<Arrow*>(b)) {
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

			break;
		}
	}
}

