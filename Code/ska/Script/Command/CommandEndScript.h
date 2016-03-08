#pragma once
#include <vector>
#include "CommandEnd.h"

namespace ska {
	class CommandEndScript :
		public CommandEnd
	{
	public:
		CommandEndScript();
		virtual ~CommandEndScript();

		virtual std::string execute(ska::IScript* script, std::vector<std::string>& args) override;
		virtual int argumentsNumber();
	};

}