#pragma once
#include"../Base/Base.h"
class Player :public Base {
public:
	enum {
		eState_Idle,
		eState_Attack_Sword,
		eState_Attack_Arrow,
		eState_Damage,
		eState_Down,
	};
private:
	enum {
		eAnimIdle = 0,
		eAnimRun,
		eAnimJumpUp,
		eAnimJumpDown,
		eAnimAttackSword,
		eAnimAttackArrow,
		eAnimDamage,
		eAnimDown,
	};
	int m_state;
	bool m_flip;
	bool m_is_ground;
	int m_attack_no;
	int m_damage_no;
	int m_cnt;
	int m_hp = 100;

	CImage m_img;

	void StateIdle();
	void StateAttackSword();
	void StateAttackArrow();
	void StateDamage();
	void StateDown();
public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetState() {
		return m_state;
	}
};