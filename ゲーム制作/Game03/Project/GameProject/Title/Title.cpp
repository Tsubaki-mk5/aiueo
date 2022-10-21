#include "Title.h"
#include "../Game/Game.h"

Title::Title() :Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("DOUKUTSU", CImage);
}

Title::~Title()
{
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�Q�[���V�[����
	Base::Add(new Game());
}
void Title::Update()
{
	//�{�^���P�Ń^�C�g���j��
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void Title::Draw()
{
	m_img.Draw();
	//�����\��
	m_title_text.Draw(650, 500, 255, 255, 0, "�u����|���Q�[���v");
	m_title_text.Draw(700, 700, 255, 255, 1, "< GameStart >");
	m_title_text.Draw(800, 800, 255, 255, 1, "PUSH [Z]");
}