#include "Enemy.h"
//#include "Player.h"
#include "Field.h"
//#include "Slash.h"
//#include "Effect.h"
#include "AnimData.h"

Enemy::Enemy(const CVector2D& p, bool flip) : Base(eType_Enemy) {
	//�摜����
	m_img.Load("Image/Enemy1.png", enemy_anim_data, 96, 96);
	m_rad = 16;
	m_img.SetSize(150, 150);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(75, 75);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-32, -128, 32, 0);
	//���]�t���O
	m_flip = flip;

	//�ʏ��Ԃ�
	m_state = eState_Idle;

	//���n�t���O
	m_is_ground = true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;
	//�q�b�g�|�C���g
	m_hp = 100;

}

void Enemy::StateIdle() {

	//�ړ���
	const float move_speed = 6;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 12;
	//�v���C���[��T��
	Base* player = Base::FindObject(eType_Player);

	if (player) {

		//���ړ�
		if (player->m_pos.x < m_pos.x - 64) {

			//�ړ��ʂ�ݒ�
			m_pos.x += -move_speed;
			//���]�t���O
			m_flip = true;
			move_flag = true;
		}
		//�E�ړ�
		if (player->m_pos.x > m_pos.x + 64) {

			//�ړ��ʂ�ݒ�
			m_pos.x += move_speed;
			//���]�t���O
			m_flip = false;
			move_flag = true;
		}
		else {
			//�U����Ԃֈڍs
			m_state = eState_Attack;
			m_attack_no++;
		}
	}

	if (move_flag) {
		//����A�j���[�V����
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//�ҋ@�A�j���[�V����
		m_img.ChangeAnimation(eAnimIdle);
	}
	//�J�E���g0�őҋ@��Ԃ�
	if (--m_cnt <= 0) {
		//�ҋ@����3�b�`5�b
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
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
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;

	}
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//�d�͂ɂ�闎��
//	m_vec.y += GRAVITY;
	m_pos += m_vec;


	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�X�N���[���ݒ�
//	m_scroll.x;
	m_img.ChangeAnimation(eAnimIdle);

}

void Enemy::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos((m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�̕\��
	//DrawRect();
	m_gauge.HpMax = 1000;
	m_gauge.NowHp = m_hp;
	m_gauge.Width = 200;
	m_gauge.m_pos = m_pos;
	m_gauge.Draw();
}

void Enemy::Collision(Base* b)
{
	

}
