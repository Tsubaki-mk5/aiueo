#pragma once
#include "../Base/Base.h"
//ボスのアニメーションデータ
extern TexAnimData Boss_anim_data[];

class Boss : public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	int m_state;
	CImage m_img;
	bool m_flip;

	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();


public:
	Boss(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};