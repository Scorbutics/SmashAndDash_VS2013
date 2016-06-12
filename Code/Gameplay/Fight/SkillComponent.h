#pragma once
#include "../../ska/ECS/Component.h"
#include "../../ska/Utils/TimeUtils.h"


class SkillComponent : public ska::Component {
public:
	SkillComponent() {
		damage = 0;
		knockback = 0;
		speed = 0.01;
		noise = 0;

		lastTime = ska::TimeUtils::getTicks();
		currentTime = lastTime;
		firstTime = lastTime;
	}

	int damage;
	int knockback;

	unsigned int range;

	int noise;	
	
	ska::EntityId battler;
	ska::Point<int> origin;
	ska::Point<int> target;
	unsigned int currentTime;
	unsigned int lastTime;
	unsigned int firstTime;

	float speed;
	float amplitude;
};
