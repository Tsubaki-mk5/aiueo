#include "Enemy.h"
#include "Player.h"
#include "Field.h"
#include "Arrow.h"
#include"Sword.h"
#include"Bow.h"
#include "AnimData.h"
#include "Slash.h"

Enemy::Enemy(const CVector2D& p, bool flip) : Base(eType_Enemy) {
	m_img.Load("Image/Enemy1.png", enemy_anim_data, 96, 96);
	m_rad = 16;
	m_img.SetSize(150, 150);
	m_img.ChangeAnimation(0);
	m_pos = p;
	m_img.SetCenter(75, 142);
	m_rect = CRect(-30, -89, 30, 0);
	m_flip = flip;
	m_scroll.x;
	m_state = eState_Idle;
	
	m_is_ground = true;
	m_attack_no = rand();
	m_damage_no = (0);
	m_hp = 100;

}

void Enemy::StateIdle() {

	//�ړ���
	const float move_speed = 4;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 12;
	//�v���C���[��T��
	Base* player = Base::FindObject(eType_Player);

	if (player) {

		//���ړ�
		if (player->m_pos.x < m_pos.x - 64) {
			m_pos.x += -move_speed;
			m_flip = true;
			move_flag = false;
		}
		//�E�ړ�
		if (player->m_pos.x > m_pos.x + 64) {
			m_pos.x += move_speed;
			m_flip = false;
			move_flag = false;
		}

		if (move_flag) {
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			m_img.ChangeAnimation(eAnimIdle);
		}

	
		//�J�E���g0�őҋ@��Ԃ�
		if (--m_cnt <= 0) {
			//�ҋ@����3�b�`5�b
			m_cnt = rand() % 120 + 180;
			m_state = eState_Wait;
		}

	}
}

void Enemy::StateAttack() {
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_flip) {
		Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
	}
	else {
		Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
	}

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
	//�ҋ@�A�j���[�V����
	m_img.ChangeAnimation(eAnimIdle);
	//�J�E���g0�Œʏ��Ԃ�
	if (--m_cnt <= 0) {
		//�ҋ@����3�b�`5�b
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
	m_scroll.x;
}

void Enemy::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�̕\��
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
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}/*
	case eType_Arrow:
		if (Arrow* s = dynamic_cast<Arrow*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}*/
				else {
					m_state = eState_Damage;
				}
			}
		}
		break;

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

			break;
		}

			}
		}
	
