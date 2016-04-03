#include "../World/WorldScene.h"
#include "SceneFight.h"
#include "../CustomEntityManager.h"
#include "../Fight/FightComponent.h"
#include "../Data/PokemonDescriptor.h"

SceneFight::SceneFight(ska::SceneHolder& sh, WorldScene& ws, ska::InputContextManager& ril, ska::Point<int> fightPos, FightComponent fc) :
AbstractSceneMap(sh, ril),
m_worldScene(ws),
m_cameraSystem(ws.getEntityManager(), ws.getScreenW(), ws.getScreenH(), fightPos),
m_id(fc.id),
m_level(fc.level),
m_opponent("."FILE_SEPARATOR"Data"FILE_SEPARATOR"Monsters"FILE_SEPARATOR + ska::StringUtils::intToStr(m_id) + ".ini"){
	m_logics.push_back(&m_cameraSystem);
}

void SceneFight::graphicUpdate(ska::DrawableContainer& drawables) {
	 //WGameCore& core = WGameCore::getInstance();
	/*World& world = core.getWorld();*/
	/*Pokeball& pokeball = core.getPokeball();
	Fight& fight = core.getFight();*/
	/*SpriteAnimationManager& spriteAnimManager = core.getSpriteAnimationManager();
	ParticleManager& particleManager = core.getParticleManager();
	MouseCursor& mouseCursor = core.getMouseCursor();
	GUI& gui = core.getGUI();
	Settings& settings = core.getSettings();*/

	m_worldScene.graphicUpdate(drawables);
	AbstractSceneMap::graphicUpdate(drawables);
	
	//Affiche l'UI des combats et les attaques (dispos� apr�s le dessin de la Pok�ball)
	/*fight.setPriority(pokeball.getPriority() + 1);*/
	/*drawables.add(fight);*/
}

void SceneFight::load() {
	m_worldScene.linkCamera(&m_cameraSystem);
	m_worldScene.load();

	//TODO stats
	/*m_stats = unique_ptr<Statistics>(new Statistics(&data, "BaseStats"));
	m_stats->nextLevel();
	m_stats->nextLevel();

	refreshStats(true);*/
	std::vector<std::string> skills;
	for (unsigned int i = 0; m_opponent.get("Skills " + ska::StringUtils::intToStr(i)); i++) {
		if (m_opponent.getInt("Skills " + ska::StringUtils::intToStr(i) + "_level") <= m_level) {
			skills.push_back(m_opponent.getString("Skills " + ska::StringUtils::intToStr(i)));
		}
	}

	m_descriptor.load(m_opponent, "Description");
	m_descriptor.getName()

}

void SceneFight::unload() {
	m_worldScene.unload();
}

void SceneFight::eventUpdate(bool movingDisallowed) {
	/*WGameCore& core = WGameCore::getInstance();
	Fight& fight = core.getFight();*/
	AbstractSceneMap::eventUpdate(movingDisallowed);
	m_worldScene.eventUpdate(movingDisallowed);

	//Ev�nements combat
	/*fight.refreshFight();*/
}

SceneFight::~SceneFight()
{
}
