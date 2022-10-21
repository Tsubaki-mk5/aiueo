#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include"Boss.h"
#include"Needle.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Boss(CVector2D(1000, 700), true));
	Base::Add(new Player(CVector2D(200, 800), true));
	Base::Add(new Field());
	Base::Add(new Needle(CVector2D(800, 800)));
	Base::Add(new Enemy(CVector2D(1000, 50), true));
	Base::Add(new Enemy(CVector2D(1800, 500), true));
	Base::Add(new Enemy(CVector2D(2100, 500), true));
	Base::Add(new Enemy(CVector2D(2800, 500), true));

}
Game::~Game()
{
	Base::KillAll();
	Base::Add(new Title());
}

void Game::Update()
{
	if (!Base::FindObject(eType_Boss)) {
		SetKill();
	}

	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}