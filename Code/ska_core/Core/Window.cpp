#include <iostream>
#include <string>
#include "../Exceptions/IllegalArgumentException.h"
#include "Window.h"
#include "../Draw/SDLRenderer.h"

ska::Window::Window(const std::string& title, unsigned int w, unsigned int h) :
	BaseWindow(w, h),
	m_wName(title),
	m_containsDefaultRenderer(false) {

	m_screen = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w, h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

	if (m_screen == nullptr) {
		std::cerr << "Erreur lors de la cr�ation de la fen�tre SDL :" << SDL_GetError() << std::endl;
		throw IllegalArgumentException("Bad instanciation : screen cannot be null");
	}

	m_renderer.load(m_screen, -1, SDL_RENDERER_ACCELERATED);

	if(SDLRenderer::getDefaultRenderer() == nullptr) {
        m_containsDefaultRenderer = true;
        SDLRenderer::setDefaultRenderer(&m_renderer);
	}
}

void ska::Window::display() const{
	m_renderer.renderPresent();
	m_renderer.renderClear();
}

void ska::Window::showMessageBox(Uint32 flags, const std::string& title, const std::string& message) const {
    SDL_ShowSimpleMessageBox(flags,
            title.c_str(),
            message.c_str(),
            m_screen);
}

ska::Window::~Window() {
    if(m_containsDefaultRenderer) {
        SDLRenderer::setDefaultRenderer(nullptr);
    }
	SDL_DestroyWindow(m_screen);
}
