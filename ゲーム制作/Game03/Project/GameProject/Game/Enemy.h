#pragma once
#include "../Base/Base.h"
#include "HP.h"
class Enemy : public Base {
private:

	//状態
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	enum {
		eAnimIdle = 0,
		eAnimRun,
		eAnimAttackSword,
		eAnimAttackArrow,
		eAnimAttack01,
		eAnimAttack01End,
		eAnimDamage,
		eAnimDown,
	};
	//状態変数
	int m_state;
	int m_cnt;

	CImage m_img;
	bool m_flip;

	//着地フラグ
	bool m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	//ヒットポイント
	int m_hp;
	//HP m_gauge;
	//各状態での挙動
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
	void StateWait();

public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};