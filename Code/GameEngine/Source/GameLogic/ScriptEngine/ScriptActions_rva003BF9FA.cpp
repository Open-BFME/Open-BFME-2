// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BF9FADo@ScriptActions@@QAEXABVAsciiString@@M0@Z @0x003BF9FA 125B.
// Script team action chaining landed rva003570D1: prototype via first name
// then handler at proto+8; empty third name resolves team via getTeamNamed
// and centroid else null.
// Evidence: rowed rva003570D1 getTeamNamed isEmpty copy-ctor centroid
// recruitSpecificTeam, extern g_Va009FE16C, caller 0x003CA9CD, ret 0xc.
#include "ascii_string.h"

class TeamPrototype;
class Team;
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva002A9DFE
{
public:
	void recruitSpecificTeam(void *a1, float a2, void *a3);
};

#include "../../../Include/GameLogic/ScriptEngine.h"

class Team
{
public:
	Coord3D *rva0039DA2A(Coord3D *out) const;
};

class TeamPrototype
{
public:
	char m_pad00[8];
	Rva002A9DFE *m_handler08;
};

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BF9FADo(const AsciiString &asciiString, float f, const AsciiString &a3)
{
	TeamPrototype *proto = TheScriptEngine->rva003570D1(asciiString);
	if (proto == 0)
		return;
	Rva002A9DFE *handler = proto->m_handler08;
	if (handler == 0)
		return;
	if (!a3.isEmpty()) {
		Team *team = TheScriptEngine->getTeamNamed(a3, false);
		if (team == 0)
			return;
		Coord3D pos;
		team->rva0039DA2A(&pos);
		handler->recruitSpecificTeam(proto, f, &pos);
	} else {
		handler->recruitSpecificTeam(proto, f, 0);
	}
}
