#pragma once
#include "../../ska/Script/Command/AbstractFunctionCommand.h"

namespace ska {
	class World;
}

class CommandExpulse :
	public ska::AbstractFunctionCommand
{
public:
	CommandExpulse(ska::World& w, ska::EntityManager& entityManager);
	
	virtual ~CommandExpulse();

	virtual std::string execute(ska::ScriptComponent& script, std::vector<std::string>& args) override;
	virtual int argumentsNumber();

private:
	ska::World& m_world;
};

