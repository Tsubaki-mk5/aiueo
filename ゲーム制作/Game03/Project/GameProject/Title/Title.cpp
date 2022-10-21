#include "Title.h"
#include "../Game/Game.h"

Title::Title() :Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("DOUKUTSU", CImage);
}

Title::~Title()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//ゲームシーンへ
	Base::Add(new Game());
}
void Title::Update()
{
	//ボタン１でタイトル破棄
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void Title::Draw()
{
	m_img.Draw();
	//文字表示
	m_title_text.Draw(650, 500, 255, 255, 0, "「竜を倒すゲーム」");
	m_title_text.Draw(700, 700, 255, 255, 1, "< GameStart >");
	m_title_text.Draw(800, 800, 255, 255, 1, "PUSH [Z]");
}