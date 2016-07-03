
#include "SlotPokemonArea.h"
#include "../../Gameplay\WGameCore.h"
#include "../../ska/Graphic/SpritePath.h"
#include "../../ska/Utils\StringUtils.h"
#include "Button.h"
#include "../../Gameplay/Character.h"
#include "../../Gameplay/Data/Statistics.h"
#include "../../Utils/IDs.h"

using namespace std;

SlotPokemon_Area::SlotPokemon_Area(DialogMenu* parent, ska::Rectangle relativePos, string styleName, string styleNamePressed, string action, int* boolUseObjectSelectPkmn, int key) :DynamicWindowArea(parent), m_image(styleName, DEFAULT_T_RED, DEFAULT_T_GREEN, DEFAULT_T_BLUE), m_imagePressed(styleNamePressed, DEFAULT_T_RED, DEFAULT_T_GREEN, DEFAULT_T_BLUE)
{
    m_key = key;
    m_boolUseObjectSelectPkmn = boolUseObjectSelectPkmn;
    m_action = action;
    m_style = styleName;
    m_stylePressed = styleNamePressed;
    m_relativePos = relativePos;
    m_pkmn = NULL;
}

void SlotPokemon_Area::setPokemon(unsigned int index)
{
	WGameCore& wScreen = WGameCore::getInstance();
    m_index = index;
    //m_pkmn = wScreen.getPokemonManager().getPokemon(index);
	ska::Rectangle rectSrcBuf, buf;
    buf.x = m_relativePos.x;
    buf.y = m_relativePos.y;
    rectSrcBuf.x = 0;
    /*rectSrcBuf.y = m_pkmn->getHeight();
    rectSrcBuf.w = m_pkmn->getWidth();
    rectSrcBuf.h = m_pkmn->getHeight();
	m_spriteArea = unique_ptr<Image_Area>(new Image_Area(m_parent, buf, &rectSrcBuf, ska::SpritePath::getInstance().getPath(SPRITEBANK_CHARSET, m_pkmn->getID()), false));
    buf.x += rectSrcBuf.w + 4;
	buf.y += 6;
    m_nameArea = unique_ptr<Text_Area>(new Text_Area(m_parent, "Nom : " + m_pkmn->getDescriptor()->getName(), 20, buf));
    buf.x += 4*TAILLEBLOCFENETRE;
	m_levelArea = unique_ptr<Text_Area>(new Text_Area(m_parent, "Niveau : " + ska::StringUtils::intToStr(m_pkmn->getStatistics()->getLevel()), 20, buf));
    buf.x -= 4*TAILLEBLOCFENETRE;
    buf.y += 21;
    m_type1Area = unique_ptr<Text_Area>(new Text_Area(m_parent, "Type 1 : " + m_pkmn->getDescriptor()->getType(1), 20, buf));
    buf.x += 4*TAILLEBLOCFENETRE;
    m_type2Area = unique_ptr<Text_Area>(new Text_Area(m_parent, "Type 2 : " + m_pkmn->getDescriptor()->getType(2), 20, buf));
    buf.x -= 4*TAILLEBLOCFENETRE;
    buf.y += 21;
	m_pvArea = unique_ptr<Text_Area>(new Text_Area(m_parent, "PVs : " + ska::StringUtils::uintToStr(m_pkmn->getHp()) + "/" + ska::StringUtils::uintToStr(m_pkmn->getStatistics()->getHpMax()), 20, buf));
    if(m_action == "use_object")
    {
        vector<string> vUse;
        vector<int> vBool;
        vBool.push_back(0);
        vBool.push_back(1); 
        vUse.push_back("Utiliser");
        vUse.push_back("Ok !");
        buf.x += 5*TAILLEBLOCFENETRE;
		m_buttonArea = unique_ptr<Button>(new Button(m_parent, buf, "."FILE_SEPARATOR"Menu"FILE_SEPARATOR"button.png", "."FILE_SEPARATOR"Menu"FILE_SEPARATOR"buttonpressed.png", m_boolUseObjectSelectPkmn, vBool, vUse, 20, "team_use_object_" + ska::StringUtils::intToStr(m_key), false));
        buf.x -= 5*TAILLEBLOCFENETRE;
    }
    else
        m_buttonArea = NULL;

    buf.x -= rectSrcBuf.w + 4;
    buf.y -= 42;
    buf.w = TAILLEBLOC;
    buf.h = TAILLEBLOC;*/

}

void SlotPokemon_Area::display()
{
	ska::Rectangle buf = m_relativePos;
    buf.x += m_parent->getRect().x;
	buf.y += m_parent->getRect().y;

	WGameCore& wScreen = WGameCore::getInstance();

	const ska::InputActionContainer& in = wScreen.getActions();

	if (in[ska::InputAction::LClic]) {
		m_imagePressed.render(buf.x, buf.y);
	} else {
		m_image.render(buf.x, buf.y);
	}
        
    m_spriteArea->display();
    m_pvArea->display();
    m_levelArea->display();
    m_type1Area->display();
    m_type2Area->display();
    m_nameArea->display();

	if (m_buttonArea != NULL) {
		m_buttonArea->display();
	}

}

void SlotPokemon_Area::refresh()
{
	if(m_buttonArea != NULL)
		m_buttonArea->refresh();
}

ska::Rectangle SlotPokemon_Area::getRectSize()
{
	ska::Rectangle rect = m_parent->getRect();
    rect.x += m_relativePos.x;
    rect.y += m_relativePos.y;
    rect.w = m_pkmn->getWidth();
    rect.h = m_pkmn->getHeight();

    return rect;
}

Character* SlotPokemon_Area::getPokemon()
{
    if(m_pkmn != NULL)
        return m_pkmn;
    else
    {
        cerr << "Erreur (classe SlotPokemon_Area) : Slot de Pok�mon \""<< m_key <<"\" vide" << endl;
        return NULL;
    }
}

SlotPokemon_Area::~SlotPokemon_Area()
{
}




