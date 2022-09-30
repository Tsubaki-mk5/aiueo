#include "Field.h"

Field::Field() :Base(eType_Field) {
	m_space = COPY_RESOURCE("space", CImage);

}
void Field::Draw() {
	float sc;
	m_space.Draw();
	sc = m_scroll.x / 4;
	m_space.SetRect(sc, 0, sc + 1280, 720);
}