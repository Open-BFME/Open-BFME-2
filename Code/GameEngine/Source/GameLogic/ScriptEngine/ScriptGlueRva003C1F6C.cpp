// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD
//
// ?Rva003C1F6CDo@@YGXPBVAsciiString@@H@Z @0x003C1F6C 65B (dump range 18).
// Team player forward: team-name copy, getTeamNamed, rowed Team
// getControllingPlayer, then the rowed 0x002A9CDE member on the player
// with (team-as-int, int). Callee identity fuzzy (two rowed names, same
// 18B body); called through the Rva002A9CDE view with a zero-byte cast.
#include "ascii_string.h"

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class Rva002A9CDE
{
public:
	void rva002A9CDE(int a, int b);
};

void __stdcall Rva003C1F6CDo(const AsciiString *teamName, int x)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	Player *player = team->getControllingPlayer();
	if (player == 0)
		return;
	((Rva002A9CDE *)player)->rva002A9CDE((int)team, x);
}
