#include "CommandStop.h"

#include "../../Utils/IDs.h"
#include "Script/ScriptComponent.h"

CommandStop::CommandStop(ska::EntityManager& entityManager) : AbstractFunctionCommand(entityManager)
{
}


CommandStop::~CommandStop()
{
}

int CommandStop::argumentsNumber() {
	return 0;
}

std::string CommandStop::execute(ska::ScriptComponent&, ska::MemoryScript&, std::vector<std::string>&) {
	/*WGameCore& wScreen = WGameCore::getInstance();
	ofstream scriptList;
	scriptList.open(("." FILE_SEPARATOR "Data" FILE_SEPARATOR "Saves" FILE_SEPARATOR + wScreen.getSavegameManager().getSaveName() + FILE_SEPARATOR "scripts.data").c_str(), ios::app);
	scriptList << script.extendedName << endl;
	scriptList.close();*/
	return "";
}
