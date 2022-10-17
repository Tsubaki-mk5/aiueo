#include "Enemy.h"
#include "Player.h"
#include "Field.h"
#include "Slash.h"
#include "Sword.h"
#include "Arrow.h"
#include "AnimData.h"

Enemy::Enemy(const CVector2D& p, bool flip) : Base(eType_Enemy) {
	m_img.Load("Image/Enemy1.png", enemy_anim_data, 96, 96);
	m_rad = 16;
	m_img.SetSize(151, 151);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(75, 150);
	m_rect = CRect(-41, -111, 41, 0);
	m_flip = flip;

	m_state = eState_Idle;


	m_is_ground = true;
	m_attack_no = rand();
	m_damage_no = (0);
	m_hp = 100;

}

void Enemy::StateIdle() {

	const float move_speed = 3;
	bool move_flag = false;
	const float jump_pow = 12;
	Base* player = Base::FindObject(eType_Player);

	if (player) {

		//左移動
		if (player->m_pos.x < m_pos.x - 64) {
			m_pos.x += -move_speed;
			m_flip = true;
			move_flag = false;
		}
		//右移動
		if (player->m_pos.x > m_pos.x + 64) {
			m_pos.x += move_speed;
			m_flip = false;
			move_flag = false;
		}
		/*
		else {
			//攻撃状態へ移行
			if (player->m_pos.x < m_pos.x + 1)
			m_state = eState_Attack;
			m_attack_no++;
		}*/
	}

	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun, false);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle, false);
	}
	
	//カウント0で待機状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}
	

}

void Enemy::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack03, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Enemy::StateDamage() {
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}

}

void Enemy::StateDown() {
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
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
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形の表示
	DrawRect();
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.Draw();
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

