#ifndef DEF_SPRITEANIMATION
#define DEF_SPRITEANIMATION

#include "Animation.h"
#include "Texture.h"
#include "Rectangle.h"
class WGameCore;

class SpriteAnimation
{
	public:
	SpriteAnimation(int type, int id, unsigned int framesNumber = 4, unsigned int delay = 300, int alpha = -1);
	SpriteAnimation(int type, int id, ska::Rectangle pos, unsigned int framesNumber = 4, unsigned int delay = 300, int alpha = -1);
	//SpriteAnimation(int type, int id, Rectangle pos, unsigned int framesNumber, unsigned int delay, int alpha);
	void refresh();

	void setPos(ska::Rectangle pos);
    void setID(int id);
    void setType(int type);

	Animation* getAnimation();
    unsigned int getHeight();
    unsigned int getWidth();

	private:
	void display();

	Animation m_anim;
	Texture m_sprite;
	int m_type, m_id;
	ska::Rectangle m_pos, m_offset;
};

#endif
