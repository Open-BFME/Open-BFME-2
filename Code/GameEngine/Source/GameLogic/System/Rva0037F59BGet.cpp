// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /arch:SSE /G7 /EHsc /MD
#include "ascii_string.h"

#include "ArmyPlacerWaypoints.h"

class Waypoint
{
public:
	char m_pad[12];
	Coord3D m_position;
};

Waypoint *findNamedWaypoint(const AsciiString &name);

// Native37F59B..37F62D and WB ArmyPlacer::GetDefenderReinforcementWaypointLocations.
// WB and native40CCC6 calls establish the ECX receiver and two coordinate outputs.
// Both literal names and waypoint position +12 are established by retail.
bool ArmyPlacer::GetDefenderReinforcementWaypointLocations(Coord3D *spawn, Coord3D *gather)
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
