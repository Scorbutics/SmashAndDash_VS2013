#include "CheckBox.h"

ska::CheckBox::CheckBox(Widget& parent, ska::Point<int> relativePos, const std::string& placeHolderStyleName, const ska::Rectangle* clip) :
	Button(parent, relativePos, placeHolderStyleName, clip, [&](Widget* tthis, ClickEvent& e) {
		if (e.getState() == ska::MouseEventType::MOUSE_RELEASE) {
			m_value = !m_value;
		}
	}),
	m_value(false),
	m_check(MENU_DEFAULT_THEME_PATH + "/check.png") {
}

void ska::CheckBox::display() const {
	ska::Button::display();
	if(m_value) {
		const auto& absPos = getAbsolutePosition();
		m_check.render(absPos.x + (getBox().w - m_check.getWidth()) / 2, absPos.y + (getBox().h - m_check.getHeight()) / 2);
	}
}

bool ska::CheckBox::getValue() const {
	return m_value;
}

