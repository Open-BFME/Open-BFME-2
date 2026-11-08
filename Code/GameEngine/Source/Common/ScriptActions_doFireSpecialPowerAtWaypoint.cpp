// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doFireSpecialPowerAtWaypoint@ScriptActions@@QAEXABVAsciiString@@00@Z
// @0x003C41BA 80B. WorldBuilder's ScriptActions::doFireSpecialPowerAtWaypoint
// (ScriptActions.cpp, asserts "Invalid waypoint/power in
// FireSpecialPowerAtWaypoint") looks the waypoint up through TheTerrainLogic
// (+0x88), the power through findSpecialPowerTemplate 0x0029B6EB, and fires
// at the waypoint's location (+0xC) with FireSpecialPowerAtPosition
// 0x003C069B; retail is that body with the asserts compiled out. StringBase
// copy 0x000365F0 for the by-value AsciiString; caller 0x003CC74F.
#include "ascii_string.h"

#include "../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

struct Coord3D;

class ScriptActions
{
public:
	void doFireSpecialPowerAtWaypoint(const AsciiString &playerName,
		const AsciiString &powerName, const AsciiString &waypointName);
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();
};

void ScriptActions::doFireSpecialPowerAtWaypoint(const AsciiString &playerName,
	const AsciiString &powerName, const AsciiString &waypointName)
{
	void *waypoint = TheTerrainLogic->getWaypointByName(waypointName);
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(powerName);
	if (waypoint != 0 && power != 0)
		FireSpecialPowerAtPosition(playerName, power, (const Coord3D *)((char *)waypoint + 0xc));
}
