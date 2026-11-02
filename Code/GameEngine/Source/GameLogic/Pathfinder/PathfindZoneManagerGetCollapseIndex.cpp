// ?GetCollapseIndex@PathfindZoneManager@@SAHABUPathfindZoneParams@@@Z
// cl: /O1 /DNDEBUG /MD
//
// pathfinder_zonemanager.cpp -- PathfindZoneManager members at their
// WorldBuilder home (reverse/wb_name_leads.csv); retail supplies the bytes.

// The pathfind request's surface set: WorldBuilder's assert names
// par.m_acceptableSurfaces (+0x00); the byte at +0x0C selects the
// ground-only variant.
struct PathfindZoneParams
{
	int m_acceptableSurfaces;		// +0x00, LOCOMOTORSURFACE_* bits
	unsigned char m_pad04[0x0C - 0x04];
	bool m_0C;				// +0x0C
};

#include "../../../Include/GameLogic/PathfindZoneManager.h"

// PathfindZoneManager::GetCollapseIndex, retail 0x0053123A (132 bytes;
// WorldBuilder pathfinder_zonemanager.cpp lines 683..710,
// wb-name-unverified): the zone collapse slot for a surface combination;
// -666 for combinations WorldBuilder reports as unsupported.
int PathfindZoneManager::GetCollapseIndex(const PathfindZoneParams &par)
{
	int surfaces = par.m_acceptableSurfaces;
	// One result variable and a case order that places retail's shared
	// "pop eax; ret" tail (cross-jumped push-immediate returns).
	int r;
	if ((surfaces & 0x01) && (surfaces & 0x10) && (surfaces & 0x02) && (surfaces & 0x80) && (surfaces & 0x20) && (surfaces & 0x40))
		return 5;
	switch (surfaces & 0x87)
	{
	case 0x00: r = -666; break;
	case 0x04: r = 0; break;
	case 0x82: r = 4; break;
	case 0x02: r = 0; break;
	default: r = -666; break;
	case 0x87: r = -1; break;
	case 0x05: r = 1; break;
	case 0x80: r = 0; break;
	case 0x83: r = 2; break;
	case 0x06: r = -666; break;
	case 0x01:
		if (par.m_0C) { r = 6; break; }
		r = (surfaces & 0x10) ? 3 : 0; break;
	}
	return r;
}
