// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003C00CEDo@@YGXPBVAsciiString@@PAX@Z @0x003C00CE 110B (dump range 18).
// Team-centre dispatch: team-name copy, getTeamNamed, rowed Team kind check
// 0x0039DEC4, team centre into a Coord3D through the pinned 0x0039E5B9
// member, a float-4.0 call through the pinned 0x002D88A4 member on the
// 0x00DFF070 global, and a final Coord3D call through the pinned 0x001DDAE1
// member on the 0x00DFDC30 global. Globals/extra-arg identities unproven.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team
{
public:
	bool rva0039DEC4();
	void rva0039E5B9(Coord3D *pos);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class Rva002D88A4
{
public:
	void rva002D88A4(Coord3D *pos, void *extra, float scale);
};
extern Rva002D88A4 *g_00DFF070;

class Rva001DDAE1
{
public:
	void rva001DDAE1(Coord3D *pos);
};
extern Rva001DDAE1 *g_00DFDC30;

void __stdcall Rva003C00CEDo(const AsciiString *teamName, void *extra)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (!team)
		return;
	if (!team->rva0039DEC4())
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	g_00DFF070->rva002D88A4(&pos, extra, 4.0f);
	g_00DFDC30->rva001DDAE1(&pos);
}
