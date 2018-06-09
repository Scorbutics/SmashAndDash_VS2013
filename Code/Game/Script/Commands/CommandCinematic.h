#pragma once
#include "Script/Command/AbstractFunctionCommand.h"
class CommandCinematic :
	public ska::AbstractFunctionCommand
{
public:
	CommandCinematic(ska::EntityManager& entityManager);
	virtual ~CommandCinematic();

	virtual std::string execute(ska::ScriptComponent& script, ska::MemoryScript& memory, const std::vector<std::string>& args) override;
	virtual int argumentsNumber();
};

