#include "Needle.h"
#include"Field.h"

Needle::Needle(const CVector2D& pos) : Base(eType_Needle) {

	m_img = COPY_RESOURCE("Needle", CImage);
	m_pos = pos;
	m_img.SetSize(120,80);
	m_img.SetCenter(0, 80);
	m_rect = CRect(0, -80, 120, 0);
	m_cnt = 15;
}
void Needle::Update() {
}
void Needle::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}
void Needle::Collision(Base*b) {

}