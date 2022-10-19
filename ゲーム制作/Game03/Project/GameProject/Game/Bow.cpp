#include "Bow.h"

Bow::Bow(const CVector2D& pos,bool flip) :Base(eType_Bow)
{
	//m_img.Load("Image/Bow.png");
	m_img = COPY_RESOURCE("Bow", CImage);
	m_pos = pos;
	m_flip = flip;
	m_cnt = 12;
	m_img.SetSize(26, 54);
	m_img.SetCenter(13, 27);
}

void Bow::Update()
{
	m_img.UpdateAnimation();
	if (--m_cnt<=0) {
		SetKill();
	}
}

void Bow::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}