#include "Core/Window.h"
#include "../World/WorldState.h"
#include "StateFight.h"
#include "StateGUIBattle.h"
#include "Task/Task.h"
#include "Task/CompoundTask.h"
#include "../CustomEntityManager.h"
#include "../Fight/FightComponent.h"
#include "../Data/PokemonDescriptor.h"
#include "Transition/Map/PokeballTransition.h"
#include "Transition/Map/DialogTransition.h"

#include "AI/IARandomMovementComponent.h"
#include "../Fight/System/SkillRefreshSystem.h"
#include "AI/System/IARandomMovementSystem.h"
#include "../Fight/System/BattleSystem.h"

StateFight::StateFight(StateData& data, ska::State& oldScene, WorldState& ws, ska::Point<int> fightPos, FightComponent fc) :
AbstractStateMap_(data, oldScene, ws, true),
m_iaICM(ska::InputContextManager::instantiateEmpty(data.m_inputCManager)),
m_opponentScriptId(fc.opponentScriptId),
m_opponent("." FILE_SEPARATOR "Data" FILE_SEPARATOR "Monsters" FILE_SEPARATOR + ska::StringUtils::intToStr(fc.opponentScriptId) + ".ini"),
m_pokemon("." FILE_SEPARATOR "Data" FILE_SEPARATOR "Monsters" FILE_SEPARATOR + ska::StringUtils::intToStr(fc.pokemonScriptId) + ".ini"),
m_pokemonId(fc.fighterPokemon),
m_trainerId(fc.trainer),
m_opponentId(fc.fighterOpponent),
m_sceneLoaded(false),
m_loadState(0),
m_worldEntityCollisionResponse(ws.getWorld(), data.m_eventDispatcher, m_entityManager),
m_skillEntityCollisionResponse(*m_collisionSystem, data.m_eventDispatcher, m_entityManager),
m_ic(nullptr),
m_skillFactory(ws, fc.level),
m_loader(m_entityManager, m_eventDispatcher, m_worldState, m_pokemonId, m_opponentId, m_trainerId, m_pokeball, &m_ic, reinterpret_cast<ska::CameraSystem**>(&m_cameraSystem)) {

	m_cameraSystem = addLogic<ska::CameraFixedSystem>(m_window.getWidth(), m_window.getHeight(), fightPos);
	addLogic<PokeballSystem>();
	addLogic<BattleSystem>(data.m_inputCManager, m_iaICM, fc.fighterPokemon, fc.fighterOpponent, m_pokemon, m_opponent);
	addLogic<SkillRefreshSystem>();
	addLogic<StatisticsSystem>(data.m_window, data.m_inputCManager, ws, data.m_eventDispatcher);
	addLogic<ska::IARandomMovementSystem>();

	addSubState<StateGUIBattle>();

	//TODO add IA input context ???
	//m_iaICM.addContext(ska::InputContextPtr());
}

ska::CameraSystem& StateFight::getCamera() {
	return *m_cameraSystem;
}


void StateFight::beforeLoad(ska::StatePtr* lastScene) {
	AbstractStateMap::beforeLoad(lastScene);
	if (m_sceneLoaded) {
		return;
	}

	SkillsHolderComponent shc;
	m_skillFactory.loadSkills(m_pokemon, m_pokemonId, shc);
	m_entityManager.addComponent<SkillsHolderComponent>(m_pokemonId, shc);

	SkillsHolderComponent shcOpponent;
	m_skillFactory.loadSkills(m_opponent, m_opponentId, shcOpponent);

	m_entityManager.addComponent<SkillsHolderComponent>(m_opponentId, shcOpponent);
	m_descriptor.load(m_opponent, "Description");

	m_ic = &m_entityManager.getComponent<ska::InputComponent>(m_trainerId);
	m_entityManager.removeComponent<ska::InputComponent>(m_trainerId);


	auto delay = 3000;
	auto dialogTask = std::make_unique<DialogTransition>(delay, m_entityManager, m_eventDispatcher, m_trainerId, "Un " + m_descriptor.getName() + " sauvage appara�t !");
	auto pokeballTask = std::make_unique<PokeballTransition>(delay, m_entityManager, m_pokemonId, m_trainerId, m_pokeball);

	auto finalTask = m_loader.load();


	queueTask(dialogTask);
	queueTask(pokeballTask);
	queueTask(finalTask);
}

bool StateFight::beforeUnload() {
	AbstractStateMap::beforeUnload();

	/* Triggers end fight cinematic to the next scene */
	const auto delay = 3000U;

	auto preTask = m_loader.unload();

    std::unique_ptr<ska::CompoundTask> firstTask;
    {
        auto pokeballTask = std::make_unique<PokeballTransition>(delay, m_entityManager, m_pokemonId, m_trainerId, m_pokeball);
        auto dialogTask = std::make_unique<DialogTransition>(delay, m_entityManager, m_eventDispatcher, m_trainerId, "Le " + m_descriptor.getName() + " a �t� battu.");
        firstTask = std::make_unique<ska::CompoundTask>(std::move(pokeballTask), std::move(dialogTask));
    }

	auto finalTask = std::make_unique<ska::Task>([&](ska::Task&) {

		m_loadState = 0;
		m_entityManager.removeComponent<ska::IARandomMovementComponent>(m_trainerId);
		m_entityManager.addComponent<ska::InputComponent>(m_trainerId, *m_ic);
		m_ic = nullptr;
		m_entityManager.removeEntity(m_pokemonId);
		return false;
	});


	queueTask(preTask);
	queueTask(firstTask);
	queueTask(finalTask);
	
	return false;
}

StateFight::~StateFight() {
}