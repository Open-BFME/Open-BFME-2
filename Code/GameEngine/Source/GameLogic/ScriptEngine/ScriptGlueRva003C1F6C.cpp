// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C1F6CDo@ScriptActions@@QAEXPBVAsciiString@@H@Z @0x003C1F6C 65B (dump range 18).
// Team player forward: team-name copy, getTeamNamed, rowed Team
// getControllingPlayer, then the rowed 0x002A9CDE member on the player
// with (team-as-int, int). Callee identity fuzzy (two rowed names, same
// 18B body); called through the Rva002A9CDE view with a zero-byte cast.
#include "ascii_string.h"

class Player;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Rva002A9CDE
{
public:
	void guardSupplyCenter(int a, int b);
};

void ScriptActions::Rva003C1F6CDo(const AsciiString *teamName, int x)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	Player *player = team->getControllingPlayer();
	if (player == 0)
		return;
	((Rva002A9CDE *)player)->guardSupplyCenter((int)team, x);
}
