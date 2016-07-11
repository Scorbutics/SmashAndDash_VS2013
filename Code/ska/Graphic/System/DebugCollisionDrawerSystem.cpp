#include "DebugCollisionDrawerSystem.h"
#include "../SpritePath.h"
#include "../../Utils/SkaConstants.h"
#include "../../Physic/PositionComponent.h"
#include "../GraphicComponent.h"
#include "../DeleterComponent.h"

ska::DebugCollisionDrawerSystem::DebugCollisionDrawerSystem(EntityManager& em) : System(em) {
}

void ska::DebugCollisionDrawerSystem::refresh() {
	for (ska::EntityId entityId : m_processed) {
		WorldCollisionComponent& wcol = m_entityManager.getComponent<WorldCollisionComponent>(entityId);
		DebugCollisionGraphicComponent& dcgc = m_entityManager.getComponent<DebugCollisionGraphicComponent>(entityId);	

		const bool onlyOneAxis = wcol.xaxis ^ wcol.yaxis;
		if (dcgc.collidedBlocks.size() >= 2) {
			if (onlyOneAxis) {
				dcgc.collidedBlocks.pop();
			} else {
				return;
			}
		}

		if (wcol.xaxis) {
			dcgc.collidedBlocks.push(createDebugCollisionEntity(wcol.blockColPosX));
		}
		
		if (wcol.yaxis) {
			dcgc.collidedBlocks.push(createDebugCollisionEntity(wcol.blockColPosY));
		}
		
	}
}

ska::EntityId ska::DebugCollisionDrawerSystem::createDebugCollisionEntity(const ska::Point<int>& p) {
	ska::EntityId e = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	gc.sprite.resize(1);
	gc.sprite[0].load(ska::SpritePath::getInstance().getPath(SPRITEBANK_ANIMATION, 18), 2, 1, 2, false, DEFAULT_T_RED, DEFAULT_T_GREEN, DEFAULT_T_BLUE, 40);
	gc.sprite[0].setDelay(500);
	m_entityManager.addComponent<GraphicComponent>(e, gc);
	DeleterComponent dc;
	dc.delay = 3000;
	m_entityManager.addComponent<DeleterComponent>(e, dc);
	PositionComponent pc = p;
	m_entityManager.addComponent<PositionComponent>(e, pc);
	return e;
}