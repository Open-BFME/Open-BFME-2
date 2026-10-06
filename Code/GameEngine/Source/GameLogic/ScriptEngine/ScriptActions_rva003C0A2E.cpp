// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003C0A2E@ScriptActions@@IAEXABVAsciiString@@@Z 61B @0x003C0A2E: single team lookup plus two armor map removes.
// Evidence: ScriptActions neighbour 0x003C09DA plus getTeamNamed row 0x003584E9 plus StringBase copy row 0x000365F0 plus Rva003A2897 row 0x003A2897 plus Rva003A28ED row 0x003A28ED. Caller at 0x003CC988.
#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Team
{
public:
	char m_pad[1];
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

class Rva003A28ED
{
public:
	bool rva003A28ED(NameKeyType key);
};

class ScriptActions
{
protected:
	void rva003C0A2E(const AsciiString &);
};

void ScriptActions::rva003C0A2E(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	((Rva003A2897 *)team)->rva003A2897(NAMEKEY_INVALID);
	((Rva003A28ED *)team)->rva003A28ED((NameKeyType)0);
}
