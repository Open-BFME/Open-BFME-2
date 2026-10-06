// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BF9FADo@@YGXABVAsciiString@@M0@Z @0x003BF9FA 125B.
// Script team action chaining landed rva003570D1: prototype via first name
// then handler at proto+8; empty third name resolves team via getTeamNamed
// and centroid else null.
// Evidence: rowed rva003570D1 getTeamNamed isEmpty copy-ctor centroid
// rva002A9DFE, extern g_Va009FE16C, caller 0x003CA9CD, ret 0xc.
#include "ascii_string.h"

class TeamPrototype;
class Team;
struct Coord3D { float x; float y; float z; };

class Rva002A9DFE
{
public:
	void rva002A9DFE(void *a1, float a2, void *a3);
};

class ScriptEngine
{
public:
	TeamPrototype *rva003570D1(AsciiString name);
	Team *getTeamNamed(AsciiString name, bool create);
};

class Team
{
public:
	void rva0039DA2A(Coord3D *out) const;
};

class TeamPrototype
{
public:
	char m_pad00[8];
	Rva002A9DFE *m_handler08;
};

extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BF9FADo(const AsciiString &a1, float f, const AsciiString &a3)
{
	TeamPrototype *proto = TheScriptEngine->rva003570D1(a1);
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
		handler->rva002A9DFE(proto, f, &pos);
	} else {
		handler->rva002A9DFE(proto, f, 0);
	}
}
