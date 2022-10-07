#include "Field.h"

Field::Field() :Base(eType_Field) {

	m_DOUKUTSU = COPY_RESOURCE("DOUKUTSU", CImage);
	m_ground_y = 1000;
}
void Field::Draw() {
	float sc;
	m_DOUKUTSU.Draw();
	sc = m_scroll.x / 4;
	m_DOUKUTSU.SetRect(sc, 0, sc + 1280, 720);
}