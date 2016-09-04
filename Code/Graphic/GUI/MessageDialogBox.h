#pragma once
#include <string>
#include "DialogMenu.h"


namespace ska {
	class InputContextManager;
	class MouseObservable;
}

class MessageDialogBox : public IDialogMenu
{
public:
	MessageDialogBox(ska::MouseObservable& gui, ska::InputContextManager& icm, const std::string& text, const std::string& messImg, const unsigned int screenH, const unsigned int screenW, const int timeout = -1);
	//const ska::Rectangle getRect() const override;
	void refresh() override;
	void display() const override;
	void hide(bool x) override;
	bool isVisible() const override;
	int getPriority() const override;

	static bool instanceExists();

	~MessageDialogBox();
private:
	static int m_instanceExists;
	DialogMenu m_talker;
	DialogMenu m_dialog;

	const ska::InputContextManager& m_playerICM;
};

