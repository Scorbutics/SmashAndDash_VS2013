#pragma once
#include "ButtonState.h"
#include "WidgetEvent.h"
#include "../../Point.h"

namespace ska {
	enum MouseEventType {
		MOUSE_ENTER,
		MOUSE_OUT,
		MOUSE_OVER,
		MOUSE_CLICK,
		MOUSE_RELEASE
	};
	class Widget;
	class HoverEvent : public WidgetEvent {
	public:
		HoverEvent(const MouseEventType& state, const Point<int>& pos);
		const MouseEventType& getState() const;
		const ska::Point<int>& getPosition() const;
		const ska::Point<int> getPosition(const ska::Widget& w) const;
		bool isOn(const Widget& w) const;
		virtual ~HoverEvent() = default;

	private:
		MouseEventType m_state;
		Point<int> m_pos;

	};
}