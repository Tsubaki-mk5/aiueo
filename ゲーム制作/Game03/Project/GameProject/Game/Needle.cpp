#include "Needle.h"
#include"Field.h"

Needle::Needle(const CVector2D& pos) : Base(eType_Needle) {

	m_img = COPY_RESOURCE("Needle", CImage);
	m_pos = pos;
	m_img.SetSize(100,60);
	m_img.SetCenter(50, 60);
	m_rect = CRect(-30, -30, 30, 0);
}
void Needle::Update() {
}
void Needle::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}