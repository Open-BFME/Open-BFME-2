// cl: /EHs /MD
// ?invoke@Rva00352F2FOpaque@@QAEXPBVWaypoint@@HW4CommandSourceType@@@Z @0x00352F2F 110B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x10 and src,
// m_waypoint from Waypoint param plus m_intValue from int param, virtual slot 0 call,
// then inlined vector-free via rowed free 0x00030830.
// Evidence: pin 0x00352F2F Waypoint plus int plus source; callers 0x0036FA34 0x003C87E5 matched rows;
// precedent Rva00352F9DAICommand.cpp 110B same recipe with 0x11, gap between 0x00352ECA and 0x00352F9D.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport, and <stddef.h> with it so
// their _errno declarations agree.
#define _CRTIMP
#include <stddef.h>
#include <stdlib.h>
#undef _CRTIMP

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_DUMMY_16 = 16
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Waypoint;

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/RvaCoords.h"

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	void *m_obj;
	void *m_otherObj;
	const void *m_team;
	RvaCoords m_coords;
	const void *m_waypoint;
	const void *m_polygon;
	Int m_intValue;
	char m_rest[0xC0 - 0x38];
};

class Rva00352F2FOpaque
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void invoke(const Waypoint *waypoint, Int intVal, CommandSourceType src);
};

void Rva00352F2FOpaque::invoke(const Waypoint *waypoint, Int intVal, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x10, src);
	parms.m_waypoint = waypoint;
	parms.m_intValue = intVal;
	rvaVirtual(&parms);
}
