#include "Arrow.h"

Arrow::Arrow(const CVector2D& pos, bool flip,int attack_no) :
	Base(eType_Arrow){
	m_img.Load("Image/Arrow.png");
	m_pos = pos;
	m_rad = 12;
	m_flip = flip;
	m_img.SetSize(32, 32);
	m_img.SetCenter(16, 16);
	m_attack_no = attack_no;
}

void Arrow::Update()
{
	const int move_speed = 9;
	m_pos.x += move_speed;
}

void Arrow::Draw()
{
	m_img.SetPos(m_pos);
	m_img.Draw();

}
void Arrow::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Enemy:
		if (Base::CollisionCircle(this, b)) {
			b->SetKill();
		}
		break;
	case eType_Boss:
		if (Base::CollisionCircle(this, b)) {
			b->SetKill();
		}
		break;
	}
	
}