#pragma once
#include "../Base/Base.h"
#include "HP.h"
//ボスのアニメーションデータ
extern TexAnimData Boss_anim_data[];
class Boss : public Base {
private:
	enum {
		AnimIdle,
		AnimAttack,
		AnimDamage,
		AnimWait,
	};
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait,
	};
	int m_hp;
	HP m_gauge;
	int m_state;
	int m_cnt;
	CImage m_img;
	bool m_flip;
	bool m_is_ground;
	int m_damage_no;
	int m_attack_no;

	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
	void StateWait();


public:
	Boss(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};