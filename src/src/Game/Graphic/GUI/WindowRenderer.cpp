#include "WindowRenderer.h"

int WindowRenderer::render(ska::SDLRenderer*, ska::Texture*, int , int , ska::Rectangle*) const{
	/*ska::Rectangle destBuf = { x, y, static_cast<int>(tex->getWidth()), static_cast<int>(tex->getHeight()) };

	if (clip != nullptr) {
		destBuf.w = clip->w;
		destBuf.h = clip->h;
	}*/


	//return SDL_RenderCopy(win->getRenderer(), tex->getInstance()->getInstancer(), clip, &destBuf);
	return 0;
}
