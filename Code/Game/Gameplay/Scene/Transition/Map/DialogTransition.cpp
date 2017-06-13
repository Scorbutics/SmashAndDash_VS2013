#include "DialogTransition.h"
#include "../../../Fight/BattleComponent.h"
#include "../../../CustomEntityManager.h"
#include "ECS/Basics/Graphic/DirectionalAnimationComponent.h"
#include "ECS/Basics/Graphic/DialogComponent.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/HitboxComponent.h"
#include "../../../PokeballComponent.h"

DialogTransition::DialogTransition(unsigned int delay, CustomEntityManager& em, PokemonGameEventDispatcher& ged, ska::CameraSystem* cs, const ska::EntityId& pokemonId, const ska::EntityId& opponentId, const ska::EntityId& trainerId, const std::string& pokemonName) :
    ska::RepeatableTask<ska::TaskReceiver<>, ska::TaskSender<ska::InputComponent>>([&, delay](ska::Task<bool, ska::TaskReceiver<>, ska::TaskSender<ska::InputComponent>>& t) {
		if (m_loadState == 0) {
			m_loadState++;

			if (!m_entityManager.hasComponent<ska::InputComponent>(m_pokemonId)) {
				return false;
			}

			auto& ic = m_entityManager.getComponent<ska::InputComponent>(m_pokemonId);
			m_entityManager.removeComponent<ska::InputComponent>(m_pokemonId);

			BattleEvent be(BATTLE_END, *m_cameraSystem, m_pokemonId, m_opponentId, m_entityManager);
			m_eventDispatcher.ska::Observable<BattleEvent>::notifyObservers(be);

			m_entityManager.removeComponent<BattleComponent>(m_pokemonId);
			m_entityManager.removeComponent<BattleComponent>(m_opponentId);

			if (m_entityManager.hasComponent<ska::DirectionalAnimationComponent>(m_trainerId)) {
				auto& dac = m_entityManager.getComponent<ska::DirectionalAnimationComponent>(m_trainerId);
				dac.type = ska::DirectionalAnimationType::MOVEMENT;
				dac.looked = 0;
			}

			ska::GUIEvent ge(ska::GUIEventType::ADD_BALLOON);
			ge.text = "Le " + m_pokemonName + " a �t� battu.";
			ge.delay = delay;
			ge.windowName = "trainerBalloon";
			m_eventDispatcher.ska::Observable<ska::GUIEvent>::notifyObservers(ge);

			ska::DialogComponent dc;
			dc.handle = ge.balloonHandle;
			dc.name = ge.windowName;
			m_entityManager.addComponent<ska::DialogComponent>(m_trainerId, dc);

			t.forward(ic);
			return true;
		}
		// Continue until dialog and pokeball is still visible
		return m_entityManager.hasComponent<ska::DialogComponent>(m_trainerId) ||
			m_entityManager.hasComponent<PokeballComponent>(m_pokeball);
	}),
	m_pokeball(0),
	m_loadState(0),
	m_pokemonId(pokemonId),
	m_opponentId(opponentId),
	m_trainerId(trainerId),
    m_pokemonName(pokemonName),
    m_entityManager(em),
    m_eventDispatcher(ged),
    m_cameraSystem(cs) {

}
