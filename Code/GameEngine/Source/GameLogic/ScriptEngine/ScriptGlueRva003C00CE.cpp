// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
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
extern class Radar *TheRadar;

class Rva001DDAE1
{
public:
	void rva001DDAE1(Coord3D *pos);
};
extern class Eva *TheEva;

void __stdcall Rva003C00CEDo(const AsciiString *teamName, void *extra)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (!team)
		return;
	if (!team->rva0039DEC4())
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	(*(Rva002D88A4 **)&TheRadar)->rva002D88A4(&pos, extra, 4.0f);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1(&pos);
}
