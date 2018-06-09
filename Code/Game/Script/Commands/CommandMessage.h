#pragma once
#include "Script/Command/AbstractFunctionCommand.h"
#include "../../Gameplay/PokemonGameEventDispatcher.h"

class CommandMessage :
	public ska::AbstractFunctionCommand
{
public:
	CommandMessage(PokemonGameEventDispatcher& pged, ska::EntityManager& entityManager);

	virtual ~CommandMessage() = default;

	virtual std::string execute(ska::ScriptComponent& script, ska::MemoryScript& memory, const std::vector<std::string>& args) override;
	virtual int argumentsNumber();
private:
    PokemonGameEventDispatcher& m_ged;
};

