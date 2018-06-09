#pragma once
#include "Script/Command/AbstractFunctionCommand.h"
class CommandAddPokemon :
	public ska::AbstractFunctionCommand
{
public:
	CommandAddPokemon(ska::EntityManager& entityManager);
	virtual ~CommandAddPokemon();

	virtual std::string execute(ska::ScriptComponent& script, ska::MemoryScript& memory, const std::vector<std::string>& args) override;
	virtual int argumentsNumber();
};

