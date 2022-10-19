#include "Field.h"

Field::Field() :Base(eType_Field) {

	m_DOUKUTSU = COPY_RESOURCE("DOUKUTSU", CImage);
	m_foreground = COPY_RESOURCE("Foreground", CImage);

	m_ground_y = 800;
}
void Field::Draw() {
	float sc;
	m_DOUKUTSU.Draw();
	sc = m_scroll.x / 4;
	m_DOUKUTSU.SetRect(sc, 0, sc + 1920, 1080);
	sc = m_scroll.x;
	m_foreground.SetRect(sc, 0, sc + 1920, 1080);
	m_foreground.Draw();
}