#pragma once
#include <unordered_set>
#include "../../../ska/ECS/System.h"
#include "../../../ska/Physic/PositionComponent.h"
#include "../../../ska/Scene/SceneHolder.h"
#include "../BattleComponent.h"
#include "../SkillsHolderComponent.h"
#include "../../World/WorldScene.h"

class StatisticsSystem : public ska::System<std::unordered_set<ska::EntityId>, ska::PositionComponent, BattleComponent> {
public:
	StatisticsSystem(ska::EntityManager& em, ska::SceneHolder& sceneHolder, ska::InputContextManager& icm, WorldScene& ws);
	virtual ~StatisticsSystem();

protected:
	virtual void refresh() override;

private:
	ska::SceneHolder& m_sceneHolder;
	ska::InputContextManager& m_playerICM;
	WorldScene& m_worldScene;
};