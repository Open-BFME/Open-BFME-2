// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// ArmyPlacer.cpp -- helpers recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. TheTerrainLogic (0x00DFEC50) answers waypoint-by-name
// through vtable slot 34 (+0x88; see GameLogic/Map/TerrainLogic.cpp).
#include "ascii_string.h"

class Waypoint;

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
