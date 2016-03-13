#include "CommandTeleport.h"
#include <string>
#include <map>
#include "../../Gameplay\WGameCore.h"
#include "../../Utils\IDs.h"
#include "../../ska/Utils\StringUtils.h"

using namespace std;

CommandTeleport::CommandTeleport()
{
}


CommandTeleport::~CommandTeleport()
{
}

int CommandTeleport::argumentsNumber() {
	return 3;
}

std::string CommandTeleport::execute(ska::IScript* script, std::vector<std::string>& args)
{
	WGameCore& wScreen = WGameCore::getInstance();
	int id, number;
	string param;

	id = ska::StringUtils::strToInt(args[0]);
	number = ska::StringUtils::strToInt(args[1]);
	param = args[2];

	if (id != 0)
	{
		int x, y;
		x = atoi(param.substr(0, param.find_first_of(':')).c_str());
		y = atoi(param.substr(param.find_first_of(':') + 1, param.size()).c_str());

		//wScreen.getEntityFactory().getNPC(id, number)->teleport(x*TAILLEBLOC, y*TAILLEBLOC);
	}
	else {
		teleportHeroToMap(param);
	}
	return "";
}

void CommandTeleport::teleportHeroToMap(string param)
{
	WGameCore& wScreen = WGameCore::getInstance();
	ska::World& w = wScreen.getWorld();
	//Character* hero = wScreen.getHero();

	string fichier, fichier2, fichierD;
	int x = 1, y;


	fichier = ska::StringUtils::extractTo(0, param, '/', NULL);
	fichierD = ska::StringUtils::extractTo((int)strlen(fichier.c_str()) + 1, param, '/', NULL);
	fichier2 = ska::StringUtils::extractTo((int)strlen(fichier.c_str()) + (int)strlen(fichierD.c_str()) + 2, param, '/', NULL);
	ska::StringUtils::extractTo((int)strlen(fichier.c_str()) + (int)strlen(fichierD.c_str()) + (int)strlen(fichier2.c_str()) + 3, param, ':', &x);

	// cr�er un flux de sortie
	ostringstream oss;
	oss << x; //on ecrit la valeur de l'entier x dedans
	string buf; //on le transforme en string
	buf = oss.str();
	oss.clear();
	y = atoi(param.substr(param.find_last_of(':') + 1, param.find_last_of('\0')).c_str());

	//wScreen.transition(0);

	buf = ".\\Levels"FILE_SEPARATOR""
		+ fichier.substr(0, fichier.find_last_of("."))
		+ ""FILE_SEPARATOR""
		+ fichier.substr(0, fichier.find_last_of("."))
		+ ".ini";

	ska::IniReader mapReader(buf);

	string chipsetName = mapReader.getString("Chipset file");

	if (chipsetName == "STRINGNOTFOUND" || chipsetName == "EMPTYDATA")
		cerr << "Erreur : impossible de trouver le nom du chipset de la map de depart" << endl;

	w.changeLevel(fichier, chipsetName);

	//hero->teleport(x*TAILLEBLOC - wScreen.getHero()->getWidth() / 2, y*TAILLEBLOC - wScreen.getHero()->getHeight() / 2);

}