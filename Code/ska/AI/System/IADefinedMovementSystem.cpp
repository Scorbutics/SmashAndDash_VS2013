#include "IADefinedMovementSystem.h"
#include "../../Utils/TimeUtils.h"
#include "../../Utils/PhysicUtils.h"
#include "../../Utils/NumberUtils.h"
#include "../../Utils/RectangleUtils.h"
#include "../../Physic/WorldCollisionComponent.h"

ska::IADefinedMovementSystem::IADefinedMovementSystem(ska::EntityManager& entityManager, ska::ScriptAutoSystem* scriptSystem) : System(entityManager), m_scriptSystem(scriptSystem) {
}

void ska::IADefinedMovementSystem::refresh() {
	std::vector<ska::EntityId> entityWithComponentsToDelete;

	for (EntityId entityId : m_processed) {
		MovementComponent& mc = m_entityManager.getComponent<MovementComponent>(entityId);
		PositionComponent& pc = m_entityManager.getComponent<PositionComponent>(entityId);
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

		const ska::Point<int> targetPoint = targetVector + iamc.origin;
		const ska::Point<float> finalMovement = ska::NumberUtils::cartesian(polarVectorMovement.radius, polarVectorMovement.angle);
		
		/* Either the time is up, or the goal is reached (if we are going farer and farer from the target pos, goal is reached) */
		const unsigned int distanceSquaredToTarget = ska::RectangleUtils::distanceSquared(centerPos, targetPoint);
		const unsigned int nextDistanceSquaredToTarget = ska::RectangleUtils::distanceSquared(centerPos + finalMovement, targetPoint);
		const bool directionChanged = distanceSquaredToTarget < nextDistanceSquaredToTarget;
		
		bool collisioned;
		if (iamc.ghost) {
			m_entityManager.removeComponent<WorldCollisionComponent>(entityId);
			collisioned = false;
		} else {
			collisioned = m_entityManager.hasComponent<WorldCollisionComponent>(entityId);
		}
		bool finished = false;
		if (TimeUtils::getTicks() - iamc.lastTimeStarted >= iamc.delay || directionChanged || collisioned) {

			iamc.origin = iamc.directions[iamc.directionIndex];
			if (iamc.directionIndex+1 < iamc.directions.size()) {
				iamc.directionIndex++;
			} else if (iamc.loop) {
				iamc.directionIndex = 0;
			} else {
				finished = true;
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

		if (!finished) {
			mc.vx = finalMovement.x;
			mc.vy = finalMovement.y;
		} else if (directionChanged) {
			mc.vx = 0;
			mc.vy = 0;
			mc.ay = 0;
			mc.ax = 0;
		}
	}

	for (ska::EntityId id : entityWithComponentsToDelete) {
		m_entityManager.removeComponent<IADefinedMovementComponent>(id);
	}
}

ska::IADefinedMovementSystem::~IADefinedMovementSystem() {
}
