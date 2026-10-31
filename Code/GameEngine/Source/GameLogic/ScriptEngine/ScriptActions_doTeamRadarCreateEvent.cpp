// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?doTeamRadarCreateEvent@ScriptActions@@QAEXPBVAsciiString@@PAX@Z @0x003C00CE 110B (dump range 18).
// Team-centre dispatch: team-name copy, getTeamNamed, rowed Team kind check
// 0x0039DEC4, team centre into a Coord3D through the pinned 0x0039E5B9
// member, a float-4.0 call through the pinned 0x002D88A4 member on the
// 0x00DFF070 global, and a final Coord3D call through the pinned 0x001DDAE1
// member on the 0x00DFDC30 global. Globals/extra-arg identities unproven.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

// Rowed 0x002D88A4: Radar::createEvent (Radar_createEvent.cpp).
enum RadarEventType { RADAR_EVENT_INVALID };
class Radar
{
public:
	void createEvent(const Coord3D *world, RadarEventType type, float secondsToLive);
};
extern class Radar *TheRadar;

class Rva001DDAE1
{
public:
	void rva001DDAE1(Coord3D *pos);
};
extern class Eva *TheEva;

void ScriptActions::doTeamRadarCreateEvent(const AsciiString *teamName, void *extra)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (!team)
		return;
	if (!team->hasAnyUnits())
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	TheRadar->createEvent(&pos, (RadarEventType)(int)extra, 4.0f);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1(&pos);
}
