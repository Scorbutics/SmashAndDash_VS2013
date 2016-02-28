#ifndef DEF_IMAGE_AREA
#define DEF_IMAGE_AREA

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window_Area.h"
#include "../Texture.h"


class Image_Area : public Window_Area
{
    public:
		Image_Area(DialogMenu* parent, ska::Rectangle relativePos, ska::Rectangle* rectSrcBuf, std::string name, bool alpha);
		Image_Area(DialogMenu* parent, ska::Rectangle relativePos, ska::Rectangle* rectSrcBuf, Texture* tex, bool alpha);
	virtual void display();
	std::string getImageName() const;
    virtual std::string getKey(){return "";};
    virtual void forceValue(unsigned int index){index = index;};
    virtual ~Image_Area();
    void setImage(std::string name, bool alpha);

    private:
	Texture m_image;
    std::string m_name;
	bool m_alpha;
	ska::Rectangle m_rectSrc;

};


#endif
