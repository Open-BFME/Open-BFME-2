// ?GetCollapseIndex@PathfindZoneManager@@SAHABUPathfindZoneParams@@@Z
// partial score=0.95 date=2026-10-07
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

class PathfindZoneManager
{
public:
	static int GetCollapseIndex(const PathfindZoneParams &par);
};

// PathfindZoneManager::GetCollapseIndex, retail 0x0053123A (132 bytes;
// WorldBuilder pathfinder_zonemanager.cpp lines 683..710,
// wb-name-unverified): the zone collapse slot for a surface combination;
// -666 for combinations WorldBuilder reports as unsupported.
int PathfindZoneManager::GetCollapseIndex(const PathfindZoneParams &par)
{
	int surfaces = par.m_acceptableSurfaces;
	if ((surfaces & 0x01) && (surfaces & 0x10) && (surfaces & 0x02) && (surfaces & 0x80) && (surfaces & 0x20) && (surfaces & 0x40))
		return 5;

	switch (surfaces & 0x87)
	{
	case 0x00:
		return -666;
	case 0x01:
		if (par.m_0C)
			return 6;
		return (surfaces & 0x10) ? 3 : 0;
	case 0x02:
		return 0;
	case 0x04:
		return 0;
	case 0x05:
		return 1;
	case 0x06:
		return -666;
	case 0x80:
		return 0;
	case 0x82:
		return 4;
	case 0x83:
		return 2;
	case 0x87:
		return -1;
	default:
		return -666;
	}
}
