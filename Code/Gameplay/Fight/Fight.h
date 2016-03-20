#ifndef DEF_COMBAT
#define DEF_COMBAT

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "EndFightReasonEnum.h"
#include "../Player.h"
#include "../../ska/Graphic/Animation.h"
#include "../../ska/Graphic/Texture.h"
#include "../../ska/Graphic/Draw/DrawableFixedPriority.h"

class World;
class DialogMenu;

class Fight : public ska::DrawableFixedPriority
{
    public:
    Fight();
	void updateAreaStates();
	bool isInFightArea(Player* hero);
    bool isFighting();
	void start(Character* opponent);
	void showDialog(unsigned int duration);
    
	void refreshFight();
    void refresh();
    void end(EndFightReason::Enum endReason);
    ~Fight();
    void setAreasFromLayerEvent();
    void setFightCount(int x);
    void setFight(bool x);
	bool isVisible() const override;

    int getFightCount();
    Character* getOpponent();
    Player* getPokemon();
    Player* getTrainer();
    DialogMenu* getDialog();
	const ska::Rectangle& getArea(int i);

    void addArea(int x, int y, int w, int h);
	void addArea(ska::Rectangle area);
    void deleteAllAreas();
	void display() override;
	
    private:
    void displayDialog();
	bool m_isFighting, m_dialogActive;
    unsigned int m_t0, m_duration, m_mobAggroRange;
    int m_fightCount;
    Character *m_opponent; 
	Player* m_pkmn, *m_trainer;
	std::vector<ska::Rectangle> m_areaList;
	ska::Rectangle m_opponentID;
    ska::Animation m_animGrass;
    ska::Texture m_grassSprite;
    std::unique_ptr<DialogMenu> m_dial;

};

#endif
