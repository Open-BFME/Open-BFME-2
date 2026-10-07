// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD
#include "ascii_string.h"

struct Rva0037F7B6Coord
{
	float x;
	float y;
	float z;
};

class Rva0037F7B6Record
{
public:
	char m_pad[0x14];
	AsciiString m_name;
};

class Waypoint
{
public:
	char m_pad[12];
	Rva0037F7B6Coord m_position;
};

Waypoint *findNamedWaypoint(const AsciiString &name);

// ?Rva0037F7B6Get@@YA_NPAURva0037F7B6Record@@PAURva0037F7B6Coord@@1@Z @0x0037F7B6 196B
// The packet literals and caller argument layout establish the record name and output positions.
bool __stdcall Rva0037F7B6Get(Rva0037F7B6Record *record, Rva0037F7B6Coord *spawn, Rva0037F7B6Coord *gather)
{
	AsciiString spawnName;
	spawnName.format("WOTRSpawnPoint_%s_1", record->m_name.str());
	AsciiString gatherName;
	gatherName.format("WOTRGatherPoint_%s_1", record->m_name.str());
	Waypoint *spawnWaypoint = findNamedWaypoint(spawnName);
	Waypoint *gatherWaypoint = findNamedWaypoint(gatherName);
	if (!spawnWaypoint || !gatherWaypoint)
		return false;
	*spawn = spawnWaypoint->m_position;
	*gather = gatherWaypoint->m_position;
	return true;
}
