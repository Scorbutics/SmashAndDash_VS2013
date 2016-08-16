#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Text_Area.h"
#include "../../Utils/IDs.h"

Text_Area::Text_Area(DialogMenu& parent, const std::string& text, int fontSize, ska::Point<int> relativePos) : Window_Area(parent)
{
    m_type = BUTTON_TEXT_AREA;
    m_text = text;
    m_relativePos.x = relativePos.x;
    m_relativePos.y = relativePos.y;
    m_fontSize = fontSize;

    m_color.r = 0;
    m_color.g = 0;
    m_color.b = 0;
	m_color.a = 255;

    m_stext.loadFromText(m_fontSize, m_text, m_color);
}

void Text_Area::display() const {

	if (!m_parent.isVisible()) {
		return;
	}
    

	ska::Point<int> buf = m_relativePos;
	buf.x += (m_parent.getRect()).x;
	buf.y += (m_parent.getRect()).y;
	
	m_stext.render(buf.x, buf.y);

}

Text_Area::~Text_Area()
{
}
