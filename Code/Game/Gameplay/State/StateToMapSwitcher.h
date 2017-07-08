#pragma once
#include "Core/State/StateBase.h"
#include "../World/WorldState.h"
#include "../World/WorldStateChanger.h"

class StateMap;

class StateToMapSwitcher {
public:
	StateToMapSwitcher(const std::string& map, const std::string& chipsetName, WorldState& ws) :
		m_ws(ws),
		m_mapName(map),
		m_chipsetName(chipsetName) {}
	StateToMapSwitcher& operator=(const StateToMapSwitcher&) = delete;
	~StateToMapSwitcher() = default;

	template<class EM, class ED>
	void switchTo(ska::StateBase<EM, ED>& lastScene) const {
		WorldStateChanger wsc(m_ws, m_mapName, m_chipsetName, m_ws.getFileName() == m_mapName);
		lastScene.template makeNextStateAndTransmitLinkedSubstates<ska::StateBase<EM, ED>, StateMap>(lastScene, wsc);
	}

protected:
	WorldState& m_ws;
	const std::string m_mapName;
	const std::string m_chipsetName;
};
