// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /EHsc /MD
#include "ascii_string.h"
#include "ArmyPlacerWaypoints.h"

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
	Coord3D m_position;
};

Waypoint *findNamedWaypoint(const AsciiString &name);

// Retail 0x0037F7B6..0x0037F87A; WB ArmyPlacer::GetWalkOnWaypointLocations.
// Native callers 0x0037F87A and 0x0037F985 establish the ECX receiver.
// Record +0x14 is independently established by both format operations.
// The packet literals and caller argument layout establish the record name and output positions.
bool ArmyPlacer::GetWalkOnWaypointLocations(Rva0037F7B6Record *record, Coord3D *spawn, Coord3D *gather)
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
