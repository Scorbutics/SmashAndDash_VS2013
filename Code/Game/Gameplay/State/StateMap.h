#pragma once
#include <memory>
#include "StateFight.h"
#include "AbstractStateMap.h"

struct WorldStateChanger;
class WorldState;

namespace ska {
	class Window;
	class ScriptAutoSystem;
	class ScriptRefreshSystem;
	class CameraSystem;
}

class StateMap :
	public AbstractStateMap,
	public ska::SubObserver<ska::GameEvent> {
public:
	StateMap(CustomEntityManager& em, PokemonGameEventDispatcher& pged, WorldState& ws, const std::string& worldFileName, const std::string& worldChipsetName, ska::Point<int> screenSize = ska::Point<int>());
	
	virtual ~StateMap();

private:
	void resetScriptEntities();
	virtual void beforeLoad(ska::State* lastState) override final;
	virtual void afterLoad(ska::State* lastState) override final;
	bool onGameEvent(ska::GameEvent& ge);
	void init();

	WorldState& m_worldState;
	const std::string m_fileName;
	const std::string m_chipsetName;
	ska::ScriptAutoSystem* m_scriptAutoSystem;
	ska::ScriptRefreshSystem* m_scriptSystem;

	/*ska::WorldCollisionResponse m_worldCollisionResponse;
	ska::EntityCollisionResponse m_entityCollisionResponse;*/
	ska::Point<int> m_screenSize;

};

