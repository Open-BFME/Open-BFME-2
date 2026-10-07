// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD
#include "ascii_string.h"

struct Rva0037F59BCoord
{
	float x;
	float y;
	float z;
};

class Waypoint
{
public:
	char m_pad[12];
	Rva0037F59BCoord m_position;
};

Waypoint *findNamedWaypoint(const AsciiString &name);

// ?Rva0037F59BGet@@YA_NPAURva0037F59BCoord@@0@Z @0x0037F59B 146B
// Looks up two named waypoints and copies their positions; literal names and caller/output shape from retail.
bool __stdcall Rva0037F59BGet(Rva0037F59BCoord *spawn, Rva0037F59BCoord *gather)
{
	AsciiString spawnName("WOTRSpawnPoint_DefenderReinforcements_1");
	AsciiString gatherName("WOTRGatherPoint_DefenderReinforcements_1");
	Waypoint *spawnWaypoint = findNamedWaypoint(spawnName);
	Waypoint *gatherWaypoint = findNamedWaypoint(gatherName);
	if (!spawnWaypoint || !gatherWaypoint)
		return false;
	*spawn = spawnWaypoint->m_position;
	*gather = gatherWaypoint->m_position;
	return true;
}
