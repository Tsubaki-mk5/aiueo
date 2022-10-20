#pragma once
#pragma once
#include "../Base/Base.h"
#include "HP.h"
class Enemy : public Base {
private:

	//���
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
		eAnimJumpUp,
		eAnimJumpDown,
		eAnimAttackSword,
		eAnimAttackArrow,
		eAnimAttack03,
		eAnimAttack01,
		eAnimAttack01End,
		eAnimAttack03End,
		eAnimDamage,
		eAnimDeath,
		eAnimDown,
		eAnimWakeUp,
		eAnimGuard,
		eAnimGuardEnd,
		eAnimCrash,
		eAnimCrashEnd,
		eAnimExtAttack01,
		eAnimExtAttack01End,
		eAnimExtAttack02,
		eAnimExtAttack02End,
		eAnimStep,
	};
	//��ԕϐ�
	int m_state;
	int m_cnt;

	CImage m_img;
	bool m_flip;

	//���n�t���O
	bool m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	//�q�b�g�|�C���g
	int m_hp;
	//HP m_gauge;

	//�e��Ԃł̋���
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