#include "CommandHideCharacter.h"
#include "Utils/StringUtils.h"
#include "Script/ScriptComponent.h"
#include "Graphic/GraphicComponent.h"
#include "ECS/EntityManager.h"
#include "Utils/SpritePath.h"
#include "Script/System/ScriptAutoSystem.h"

CommandHideCharacter::CommandHideCharacter(ska::EntityManager& entityManager) : AbstractFunctionCommand(entityManager)
{
}


CommandHideCharacter::~CommandHideCharacter()
{
}

int CommandHideCharacter::argumentsNumber() {
	return 2;
}

std::string CommandHideCharacter::execute(ska::ScriptComponent& script, std::vector<std::string>& args)
{
	const std::string& id = args[0];
	//ska::EntityId internalEntity = script.parent->getEntityFromName(id);
	const int hiding = ska::StringUtils::strToInt(args[2]);
	if (hiding) {
		m_entityManager.removeComponent<ska::GraphicComponent>(script.getEntity());
	} else {
		ska::GraphicComponent gc;
		gc.sprite.resize(1);
		gc.sprite[0].load(ska::SpritePath::getInstance().getPath(SPRITEBANK_CHARSET, ska::StringUtils::strToInt(id)), 6, 8, 3);
		gc.sprite[0].setDelay(100);
		m_entityManager.addComponent<ska::GraphicComponent>(script.getEntity(), gc);
	}
	return "";
}