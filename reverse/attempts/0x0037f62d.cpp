// ?Rva0037F62DGet@@YG_NHPAURva0037F59BCoord@@0@Z
// partial score=0.92 date=2026-10-07
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

// ?Rva0037F62DGet@@YA_NHPAURva0037F59BCoord@@0@Z @0x0037F62D 189B
// Caller shapes and waypoint string literals establish the index and position arguments.
bool __stdcall Rva0037F62DGet(int player, Rva0037F59BCoord *start, Rva0037F59BCoord *rally)
{
	AsciiString startName;
	startName.format("Player_%d_Start", player + 1);
	Waypoint *startWaypoint = findNamedWaypoint(startName);
	if (!startWaypoint)
		return false;
	*start = startWaypoint->m_position;
	AsciiString rallyName;
	rallyName.format("Player_%d_Start_Rally", player + 1);
	Rva0037F59BCoord *rallyOutput = rally;
	Waypoint *rallyWaypoint = findNamedWaypoint(rallyName);
	if (rallyWaypoint)
		*rallyOutput = rallyWaypoint->m_position;
	else
	{
		*rallyOutput = *start;
		rallyOutput->x += 10.0f;
	}
	return true;
}
