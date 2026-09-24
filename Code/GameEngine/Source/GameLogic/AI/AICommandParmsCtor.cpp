// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z,
// retail 0x00351BD0, 120 bytes. Dedicated shard TU for the parameter-block
// constructor used by every AICommandInterface command builder.
//
// The block is 0xC0 bytes: command plus source, a zeroed position, three
// null object slots, a coordinate vector at +0x20, waypoint plus polygon
// plus integer slots, a zeroed float at +0x38, a +0x3C member built through
// the rowed Rva00263895Member init pin, two trailing integer zeros, and the
// position zeroed plus the vector cleared in the body (clear lowers to the
// rowed vector erase, SpawnBehavior precedent).
//
// The vector and tail members are TU-local stand-ins with trivial
// destructors so the constructor stays EH-free like retail (a real
// _STL::vector member would arm an EH prolog retail never has). Their
// constructor and erase spellings resolve through alias pins to the rowed
// Vector_base, erase, and init bodies.

typedef int Int;
typedef float Real;

class Object;

enum AICommandType
{
	AICMD_IDLE = 5
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct AICommandCoordAlloc
{
	AICommandCoordAlloc() {}
};

struct AICommandCoordVector
{
	AICommandCoordVector(const AICommandCoordAlloc &alloc = AICommandCoordAlloc());
	Coord3D *erase(Coord3D *first, Coord3D *last);

	Coord3D *_M_start;
	Coord3D *_M_finish;
	Coord3D *_M_end_of_storage;
};

struct AICommandParmsTail
{
	AICommandParmsTail();

	char m_data[0x7C];
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
	Object *m_otherObj; // +0x18
	const void *m_team; // +0x1C
	AICommandCoordVector m_coords; // +0x20
	const void *m_waypoint; // +0x2C
	const void *m_polygon; // +0x30
	Int m_intValue; // +0x34
	Real m_f38; // +0x38
	AICommandParmsTail m_tail; // +0x3C
	Int m_B8; // +0xB8
	Int m_BC; // +0xBC
};

// ??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z @0x351BD0
AICommandParms::AICommandParms(AICommandType cmd, CommandSourceType cmdSource)
	: m_cmd(cmd),
	  m_cmdSource(cmdSource),
	  m_obj(0),
	  m_otherObj(0),
	  m_team(0),
	  m_waypoint(0),
	  m_polygon(0),
	  m_intValue(0),
	  m_f38(0.0f),
	  m_B8(0),
	  m_BC(0)
{
	m_pos.zero();
	AICommandCoordVector &coords = m_coords;
	coords.erase(coords._M_start, coords._M_finish);
}
