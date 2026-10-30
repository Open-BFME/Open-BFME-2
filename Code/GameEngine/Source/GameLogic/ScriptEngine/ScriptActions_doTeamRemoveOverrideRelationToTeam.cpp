// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doTeamRemoveOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0@Z 84B @0x003C09DA: two team lookups plus armor map remove.
// Evidence: ScriptActions neighbour 0x003C0983 plus getTeamNamed row 0x003584E9 twice plus StringBase copy row 0x000365F0 twice plus Rva003A2897 row plus Team plus0x34 key. Caller at 0x003CC970.
#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class Rva003A2897
{
public:
	bool rva003A2897(NameKeyType key);
};

class ScriptActions
{
protected:
	void doTeamRemoveOverrideRelationToTeam(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamRemoveOverrideRelationToTeam(const AsciiString &asciiString, const AsciiString &teamName2)
{
	Team *team1 = TheScriptEngine->getTeamNamed(asciiString, false);
	Team *team2 = TheScriptEngine->getTeamNamed(teamName2, false);
	if (team1 == 0)
		return;
	if (team2 == 0)
		return;
	((Rva003A2897 *)team1)->rva003A2897((NameKeyType)team2->getID());
}
