#pragma once
#include <GLLibrary.h>

//!�A�j���[�V�����̎��
enum  {
	eAnimIdle = 0,
	eAnimRun,
	eAnimJumpUp,
	eAnimJumpDown,
	eAnimAttack01,
	eAnimAttack01End,
	eAnimAttack02,
	eAnimAttack02End,
	eAnimDamage,
	eAnimDamageEnd,
	eAnimDown,
	eAnimDownGround,
};
//�v���C���[�̃A�j���[�V�����f�[�^
extern TexAnimData player_anim_data[];
//�G�̃A�j���[�V�����f�[�^
extern TexAnimData enemy_anim_data[];
//�G�t�F�N�g�̃A�j���[�V�����f�[�^
extern TexAnimData effect_blood_anim_data[];
extern TexAnimData effect_smoke_anim_data[];
extern TexAnimData effect_slash_anim_data[];
extern TexAnimData effect_bomb_anim_data[];