#include "Bow.h"

Bow::Bow(const CVector2D& pos,bool flip) :Base(eType_Bow)
{
	m_img.Load("Image/Bow.png");
	m_pos = pos;
	m_rad = 12;
	m_img.SetSize(32, 32);
	m_img.SetCenter(16, 16);
}

void Bow::Update()
{
}

void Bow::Draw()
{
	m_img.SetPos(m_pos);
	m_img.Draw();

}