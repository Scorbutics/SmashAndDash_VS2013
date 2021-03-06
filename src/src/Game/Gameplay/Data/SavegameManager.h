#pragma once
#include "Core/ECS/EntityManager.h"
#include "../PokemonGameEventDispatcher.h"
#include "Core/Data/MemoryScript.h"

class SavegameManager : 
	public ska::MemoryScript {
public:
	explicit SavegameManager(ska::EntityManager& em, PokemonGameEventDispatcher& ged, const std::string& filename = "");

	SavegameManager& operator=(const SavegameManager&) = delete;

	void newGame();
	void loadGame(const std::string& filename);
	void saveGame(const std::string& filename);

	std::string getSaveName() const override;
	int getGameVariable(const std::string& x) const override;
	std::string getComponentVariable(const std::string& variable) const override;
	
	void setComponentVariable(const std::string& variable, const std::string& value) override;
	void setGameVariable(const std::string& x, int value) override;

	const std::string& getStartChipsetName();
	const std::string& getPathName();
	const std::string& getStartMapName();
	~SavegameManager() = default;

private:
	void extractEntityComponent(const std::string& str, std::string& component, std::string& field, ska::EntityId& entityId) const;
	void loadItem(int id, unsigned int amount);
	void loadTrainer();
	void saveTrainer();
	void saveItems();
	void savePokemonTeam();
	void loadPokemonTeam();

	ska::EntityManager& m_entityManager;
	PokemonGameEventDispatcher& m_ged;

	std::string m_pathname, m_startMapChipsetName, m_startMapName;
	std::unordered_map<std::string, int> m_game_variables;

};

