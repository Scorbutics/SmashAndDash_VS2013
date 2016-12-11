#include <iostream>
#include <fstream>
#include <string>

#include "HoverEvent.h"
#include "KeyEvent.h"
#include "FocusEvent.h"

#include <SDL2/SDL.h>
#include "Input.h"
#include "../../../Utils/StringUtils.h"

ska::Input::Input(Widget& parent, const std::string& text, int fontSize, ska::Point<int> relativePos) :
	WidgetPanel<ClickEventListener, KeyEventListener, FocusEventListener>(parent, relativePos),
	m_keyFocus(false) {

	auto& button = std::make_unique<Button>(parent, relativePos, Button::MENU_DEFAULT_THEME_PATH + "textfield", nullptr, [&](ska::Widget* tthis, ska::ClickEvent& e) {
		if (!m_keyFocus && e.getState() == ska::MouseEventType::MOUSE_CLICK) {
			m_keyFocus = true;
			SDL_StartTextInput();
		}
		e.setTarget(this);
		auto b = reinterpret_cast<Button*>(tthis);
		b->forceState(ButtonState::PRESSED);
	});

	auto& label = std::make_unique<Label>(*this, text, fontSize, ska::Point<int>(5, button->getBox().h / 2 - fontSize/2));
	setWidth(button->getBox().w);
	setHeight(button->getBox().h);

	m_clip.y = 0;
	m_clip.w = getBox().w - 10;
	adaptDisplayWithText(*label);

	addWidget(std::move(button));
	addWidget(std::move(label));

	addHandler<FocusEventListener>([&](ska::Widget* tthis, ska::FocusEvent& e) {
		auto f = e.getState() == ska::MouseEventType::MOUSE_FOCUS;
		focus(f);
		e.setTarget(this);	
		auto b = reinterpret_cast<Button*>(getWidget(0));
		b->forceState(f ? ButtonState::PRESSED : ButtonState::NONE);
	});

	addHandler<KeyEventListener>([&](ska::Widget* tthis, ska::KeyEvent& e) {
		if (!isFocused()) {
			return;
		}
		auto l = reinterpret_cast<Label*>(getWidget(1));
		if(e.getState() == ska::KeyEventType::KEY_DOWN) {
			if (m_rawText.size() > 1 && e.getScanCode() == SDL_SCANCODE_BACKSPACE) {
				m_rawText.pop_back();
			} else {
				m_rawText = L" ";
			}
		} else {
			if (m_rawText.size() == 1 && m_rawText[0] == ' ') {
				m_rawText.pop_back();
			}
			m_rawText += e.getText();
		}

		l->modifyText(ska::StringUtils::toANSI(m_rawText));
		adaptDisplayWithText(*l);
	});


}

void ska::Input::adaptDisplayWithText(Label& l) {
	auto xLimit = getBox().w - 10;
	if (l.getBox().w > xLimit) {
		m_clip.x = l.getBox().w - xLimit;
		m_clip.h = l.getBox().h;
		l.setClip(&m_clip);
	} else {
		m_clip.x = 0;
		m_clip.h = l.getBox().h;
		l.setClip(nullptr);
	}
	
}
