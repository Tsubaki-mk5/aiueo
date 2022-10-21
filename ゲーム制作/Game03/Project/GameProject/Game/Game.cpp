#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include"Boss.h"
#include"Needle.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Boss(CVector2D(5000, 700), true));
	Base::Add(new Player(CVector2D(200, 800), true));
	Base::Add(new Field());
	Base::Add(new Needle(CVector2D(800, 800)));
	Base::Add(new Needle(CVector2D(1200, 800)));
	Base::Add(new Needle(CVector2D(1600, 800)));
	Base::Add(new Needle(CVector2D(2000, 800)));
	Base::Add(new Needle(CVector2D(2400, 800)));
	Base::Add(new Needle(CVector2D(2560, 800)));

	Base::Add(new Enemy(CVector2D(1000, 50), true));
	Base::Add(new Enemy(CVector2D(1800, 500), true));
	Base::Add(new Enemy(CVector2D(2100, 500), true));
	Base::Add(new Enemy(CVector2D(2800, 500), true));
	m_img1 = COPY_RESOURCE("GameOver", CImage);
	m_img1.SetSize(636, 144);
	m_img1.SetPos(660, 480);

	m_img2 = COPY_RESOURCE("GameClear", CImage);
	m_img2.SetSize(712, 144);
	m_img2.SetPos(640, 480);
}
Game::~Game()
{
	Base::KillAll();
	Base::Add(new Title());
}

void Game::Update()
{
	if (!Base::FindObject(eType_Boss) && PUSH(CInput::eButton1)) {
		SetKill();
	}
	

	if (!Base::FindObject(eType_Player)) {
		SetKill();
	}
}

void Game::Draw()
{
	if (Player* player = dynamic_cast<Player*>(Base::FindObject(eType_Player)))
	{
		if (player->GetState() == Player::eState_Down) {
			m_img1.Draw();
		}
	}
	if (!Base::FindObject(eType_Boss)) {
		m_img2.Draw();
	}
}
