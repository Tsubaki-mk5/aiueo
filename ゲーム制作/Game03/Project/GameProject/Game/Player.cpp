#include"Player.h"
#include"AnimData.h"
#include"Sword.h"
#include"Arrow.h"
#include"Bow.h"
#include "Field.h"

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(32, 32);
	m_flip = flip;
	m_state = eState_Idle;
	m_is_ground;
	m_attack_no = rand();
	m_damage_no = -1;
	m_rect = CRect(-32, -32, 32, 0);
	m_hp = 1;
}

void Player::StateIdle() {

	const float move_speed = 6;
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
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Sword(m_pos + CVector2D(-50, -50), m_flip, eType_Sword, m_attack_no));
		}
		else {
			Base::Add(new Sword(m_pos + CVector2D(50, -50), m_flip, eType_Sword, m_attack_no));
		}
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateAttackArrow()
{
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Bow(m_pos + CVector2D(-30, -30), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(-50, -50), m_flip, m_attack_no));
		}
		else {
			Base::Add(new Bow(m_pos + CVector2D(30, -30), m_flip));
			Base::Add(new Arrow(m_pos + CVector2D(50, -50), m_flip, m_attack_no));
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
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�X�N���[���ݒ�
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
		//�S�[������
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
		//�U���I�u�W�F�N�g�Ƃ̔���
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//�����U���̘A���_���[�W�h�~
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
		//Field�^�փL���X�g�A�^�ϊ��ł�����
		if (Field* f = dynamic_cast<Field*>(b)) {
			//�n�ʂ�艺�ɂ�������
			if (m_pos.y > f->GetGroundY()) {
				//�n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				//�������x���Z�b�g
				m_vec.y = 0;
				//�ڒn�t���OON
				m_is_ground = true;
			}
		}
		break;
	}
}