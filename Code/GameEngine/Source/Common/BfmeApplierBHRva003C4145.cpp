// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x003C4145 (RVA 0x003C4145) size 117: ScriptActions apply power at team pos.
// Evidence: ScriptEngine 0xDFE16C getTeamNamed then Team hasAnyObjects then rva0039E5B9 Coord3D then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then ScriptActions::FireSpecialPowerAtPosition 0x3C069B (WB callgraph caller of it).
#include "ascii_string.h"

class Team;
#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class Team
{
public:
	bool hasAnyObjects(bool b);
	void rva0039E5B9(Coord3D *p);
};

class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class ScriptActions
{
public:
	void rva003C4145(const AsciiString &playerName, const AsciiString &powerName, const AsciiString &teamName);
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();
};

void ScriptActions::rva003C4145(const AsciiString &playerName, const AsciiString &powerName, const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	if (!team->hasAnyObjects(false))
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(powerName);
	if (found == 0)
		return;
	FireSpecialPowerAtPosition(playerName, found, &pos);
}
