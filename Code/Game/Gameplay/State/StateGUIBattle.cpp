#include "StateGUIBattle.h"
#include "Draw/DrawableContainer.h"

StateGUIBattle::StateGUIBattle(StateData& data, ska::StateHolder& sh) :
    StateBase(data.m_entityManager, data.m_eventDispatcher, sh),
    m_gui(data.m_eventDispatcher) {

}
void StateGUIBattle::onGraphicUpdate(unsigned int ellapsedTime, ska::DrawableContainer& drawables) {
	//Affiche l'UI des combats et les attaques (dispos� apr�s le dessin de la Pok�ball)
	m_gui.graphicUpdate(ellapsedTime, drawables);
}

bool StateGUIBattle::beforeUnload() {
    /* Resets GUI */
    m_gui.clear();
	return false;
}

void StateGUIBattle::onEventUpdate(unsigned int) {
	//m_gui.eventUpdate(ellapsedTime);
}
