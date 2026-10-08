// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /EHsc /MD /arch:SSE
// ArmyPlacer.cpp -- helpers recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. TheTerrainLogic (0x00DFEC50) answers waypoint-by-name
// through vtable slot 34 (+0x88; see GameLogic/Map/TerrainLogic.cpp).
#include "ascii_string.h"
#include "Coord3D.h"

class Waypoint
{
public:
	char m_pad[12];
	Coord3D m_position;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33();
	virtual Waypoint *getWaypointByName(const AsciiString &name);	// +0x88
};

extern TerrainLogic *TheTerrainLogic;

// findNamedWaypoint, retail 0x0037F4D0.
Waypoint *findNamedWaypoint(const AsciiString &name)
{
	if (TheTerrainLogic)
		return TheTerrainLogic->getWaypointByName(name);
	return 0;
}

// Retail 0x0037F62D, 189B; WB ArmyPlacer::GetStartPosWaypointLocations
// identifies the waypoint strings and argument roles. Native fallback copies
// start to rally before adding ten to start.x, as the WB body also does.
bool __stdcall Rva0037F62DGet(int player, Coord3D *start, Coord3D *rally)
{
	AsciiString startName;
	startName.format("Player_%d_Start", player + 1);
	Waypoint *startWaypoint = findNamedWaypoint(startName);
	if (!startWaypoint)
		return false;
	*start = startWaypoint->m_position;
	AsciiString rallyName;
	rallyName.format("Player_%d_Start_Rally", player + 1);
	Coord3D *rallyOutput = rally;
	Waypoint *rallyWaypoint = findNamedWaypoint(rallyName);
	if (rallyWaypoint)
		*rallyOutput = rallyWaypoint->m_position;
	else
	{
		*rallyOutput = *start;
		start->x += 10.0f;
	}
	return true;
}
