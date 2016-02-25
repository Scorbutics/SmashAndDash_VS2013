#ifndef DEF_SPRITEANIMATIONMANAGER
#define DEF_SPRITEANIMATIONMANAGER

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "./Draw/DrawableFixedPriority.h"

class SpriteAnimation;

class SpriteAnimationManager : public DrawableFixedPriority
{
	public:
		SpriteAnimationManager();
		void reset();
		SpriteAnimation* play(int type, int id, SDL_Rect pos, unsigned int cycles, int alpha = -1, unsigned int framesNumber = 4, unsigned int delay = 300);
		~SpriteAnimationManager();
		void display() override;

	private:
		std::vector<unsigned int> m_cycles;
		std::vector<std::unique_ptr<SpriteAnimation>> m_sprites;
};

#endif