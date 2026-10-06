// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003C09DA@ScriptActions@@IAEXABVAsciiString@@0@Z 84B @0x003C09DA: two team lookups plus armor map remove.
// Evidence: ScriptActions neighbour 0x003C0983 plus getTeamNamed row 0x003584E9 twice plus StringBase copy row 0x000365F0 twice plus Rva003A2897 row plus Team plus0x34 key. Caller at 0x003CC970.
#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Team
{
public:
	char m_pad[0x34];
	int m_key34;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
};
extern class ScriptEngine *TheScriptEngine;

class Rva003A2897
{
public:
	bool rva003A2897(NameKeyType key);
};

class ScriptActions
{
protected:
	void rva003C09DA(const AsciiString &, const AsciiString &);
};

void ScriptActions::rva003C09DA(const AsciiString &teamName1, const AsciiString &teamName2)
{
	Team *team1 = TheScriptEngine->getTeamNamed(teamName1, false);
	Team *team2 = TheScriptEngine->getTeamNamed(teamName2, false);
	if (team1 == 0)
		return;
	if (team2 == 0)
		return;
	((Rva003A2897 *)team1)->rva003A2897((NameKeyType)team2->m_key34);
}
