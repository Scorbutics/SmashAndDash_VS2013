#pragma once
#include "../Script/ScriptSleepComponent.h"
#include "../ECS/Component.h"
#include "../Graphic/Point.h"
#include "../Utils/TimeUtils.h"
namespace ska {
	class IADefinedMovementComponent : public Component {
	public:
		IADefinedMovementComponent() {
			delay = 0;
			directionIndex = 0;
			loop = false;
			ghost = false;
			callbackActive = false;
			lastTimeStarted = ska::TimeUtils::getTicks();
		}

		bool loop;
		bool ghost;
		unsigned int directionIndex;
		std::vector<ska::Point<int>> directions;
		unsigned int delay;
		ska::Point<int> origin;
		unsigned int lastTimeStarted;

		bool callbackActive;
		ScriptSleepComponent callback;
	};
}