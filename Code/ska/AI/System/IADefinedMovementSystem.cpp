#include "IADefinedMovementSystem.h"
#include "../../Utils/TimeUtils.h"
#include "../../Utils/PhysicUtils.h"
#include "../../Utils/NumberUtils.h"
#include "../../Utils/RectangleUtils.h"

ska::IADefinedMovementSystem::IADefinedMovementSystem(ska::EntityManager& entityManager, ska::ScriptAutoSystem* scriptSystem) : System(entityManager), m_scriptSystem(scriptSystem) {
}

void ska::IADefinedMovementSystem::refresh() {
	std::vector<ska::EntityId> entityWithComponentsToDelete;

	for (EntityId entityId : m_processed) {
		MovementComponent& mc = m_entityManager.getComponent<MovementComponent>(entityId);
		const PositionComponent& pc = m_entityManager.getComponent<PositionComponent>(entityId);
		IADefinedMovementComponent& iamc = m_entityManager.getComponent<IADefinedMovementComponent>(entityId);
		const HitboxComponent& hc = m_entityManager.getComponent<HitboxComponent>(entityId);
		const auto& centerPos = ska::PositionComponent::getCenterPosition(pc, hc);

		if (iamc.directionIndex >= iamc.directions.size()) {
			continue;
		}

		const ska::Point<int>& targetVector = iamc.directions[iamc.directionIndex];
		ska::PolarPoint<float> polarVectorMovement = ska::NumberUtils::polar(targetVector.x, targetVector.y);
		
		/* speed */
		polarVectorMovement.radius = 5;

		const ska::Point<float> finalMovement = ska::NumberUtils::cartesian(polarVectorMovement.radius, polarVectorMovement.angle);
		const ska::Point<int> diff = centerPos - (iamc.origin + targetVector);
		
		/* Either the time is up, or the goal is reached (if there is a direction change, goal is reached) */
		const bool directionChanged = iamc.lastDirectionDiff.x == 0 && iamc.lastDirectionDiff.y == 0 ? false : (diff.x * iamc.lastDirectionDiff.x) <= 0 && (diff.y * iamc.lastDirectionDiff.y) <= 0;
		if (TimeUtils::getTicks() - iamc.lastTimeStarted >= iamc.delay || directionChanged) {

			iamc.origin = iamc.directions[iamc.directionIndex];
			if (iamc.directionIndex+1 < iamc.directions.size()) {
				iamc.directionIndex++;
			} else if (iamc.loop) {
				iamc.directionIndex = 0;
			} else {
				if (m_scriptSystem != nullptr && iamc.callbackActive) {
					/* triggers callback */
					ska::EntityId scriptEntity = m_entityManager.createEntity();
					m_entityManager.addComponent<ScriptSleepComponent>(scriptEntity, iamc.callback);
					m_scriptSystem->registerScript(nullptr, scriptEntity, entityId);
				}
				/* removes component */
				entityWithComponentsToDelete.push_back(entityId);
			}

			iamc.lastTimeStarted = TimeUtils::getTicks();
		}
		iamc.lastDirectionDiff = diff;

		mc.vx = finalMovement.x;
		mc.vy = finalMovement.y;
	}

	for (ska::EntityId id : entityWithComponentsToDelete) {
		m_entityManager.removeComponent<IADefinedMovementComponent>(id);
	}
}

ska::IADefinedMovementSystem::~IADefinedMovementSystem() {
}
