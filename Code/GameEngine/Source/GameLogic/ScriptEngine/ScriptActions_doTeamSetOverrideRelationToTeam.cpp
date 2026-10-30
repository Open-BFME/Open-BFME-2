// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doTeamSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0PAVObject@@@Z 87B @0x003C0983: two team lookups plus filtered map register.
// Evidence: ScriptActions neighbours 0x003C062D 0x003C0F09 plus getTeamNamed row 0x003584E9 twice plus StringBase copy row 0x000365F0 twice plus Team rva003A2CEB row plus Team plus0x34 key. Caller at 0x003CC94B.
#include "ascii_string.h"

typedef bool Bool;

class Object;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamSetOverrideRelationToTeam(const AsciiString &, const AsciiString &, Object *);
};

void ScriptActions::doTeamSetOverrideRelationToTeam(const AsciiString &asciiString, const AsciiString &teamName2, Object *val)
{
	Team *team1 = TheScriptEngine->getTeamNamed(asciiString, false);
	Team *team2 = TheScriptEngine->getTeamNamed(teamName2, false);
	if (team1 == 0)
		return;
	if (team2 == 0)
		return;
	team1->rva003A2CEB(team2->getID(), val);
}
