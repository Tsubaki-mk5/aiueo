#include "Enemy.h"
//#include "Player.h"
#include "Field.h"
//#include "Slash.h"
//#include "Effect.h"
#include "AnimData.h"

Enemy::Enemy(const CVector2D& p, bool flip) : Base(eType_Enemy) {
	m_img.Load("Image/Enemy1.png", enemy_anim_data, 96, 96);
	m_rad = 16;
	m_img.SetSize(150, 150);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(75, 75);
	m_rect = CRect(-32, -128, 32, 0);
	m_flip = flip;

	m_state = eState_Idle;


	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//ヒットポイント
	m_hp = 100;

}

void Enemy::StateIdle() {

	//移動量
	const float move_speed = 4;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	//プレイヤーを探索
	Base* player = Base::FindObject(eType_Player);

	if (player) {

		//左移動
		if (player->m_pos.x < m_pos.x - 64) {

			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (player->m_pos.x > m_pos.x + 64) {

			//移動量を設定
			m_pos.x += move_speed;
			//反転フラグ
			m_flip = false;
			move_flag = true;
		}/*
		else {
			//攻撃状態へ移行
			m_state = eState_Attack;
			m_attack_no++;
		}*/
	}

	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
	/*
	//カウント0で待機状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}
	*/

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
		//通常状態
	case eState_Idle:
		StateIdle();
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
	m_img.ChangeAnimation(eAnimIdle);

}

void Enemy::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形の表示
	//DrawRect();
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.Draw();
}

void Enemy::Collision(Base* b) {
	switch (b->m_type) {
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

