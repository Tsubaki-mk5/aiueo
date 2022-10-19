#pragma once
#include <GLLibrary.h>

//!アニメーションの種類
enum {
	eAnimIdle = 0,
	eAnimRun,
	eAnimJumpUp,
	eAnimJumpDown,
	eAnimAttackSword,
	eAnimAttackArrow,
	eAnimDamage,
	eAnimDown,
	eAnimAttack03,
};
//プレイヤーのアニメーションデータ
extern TexAnimData player_anim_data[];
//敵のアニメーションデータ
extern TexAnimData enemy_anim_data[];
//エフェクトのアニメーションデータ
extern TexAnimData effect_blood_anim_data[];
extern TexAnimData effect_smoke_anim_data[];
extern TexAnimData effect_slash_anim_data[];
extern TexAnimData effect_bomb_anim_data[];