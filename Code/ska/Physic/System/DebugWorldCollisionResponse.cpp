#include <iostream>
#include "../CollisionEvent.h"
#include "DebugWorldCollisionResponse.h"
#include "../../Graphic/DebugGraphicComponent.h"
#include "../WorldCollisionComponent.h"
#include "../CollidableComponent.h"
#include "../../ECS/EntityManager.h"
#include "CollisionSystem.h"

ska::DebugWorldCollisionResponse::DebugWorldCollisionResponse(GameEventDispatcher& ged, EntityManager& em) :
WorldCollisionObserver(bind(&DebugWorldCollisionResponse::onWorldCollision, this, std::placeholders::_1)),
	m_entityManager(em),
	m_ged(ged) {
	m_ged.ska::Observable<CollisionEvent>::addObserver(*this);
}

bool ska::DebugWorldCollisionResponse::onWorldCollision(CollisionEvent& e) const{
	DebugGraphicComponent dgc;
	dgc.typeMask = COLLISION;
	m_entityManager.addComponent<DebugGraphicComponent>(e.entity, dgc);
	return true;
}

ska::DebugWorldCollisionResponse::~DebugWorldCollisionResponse() {
	m_ged.ska::Observable<CollisionEvent>::removeObserver(*this);
}