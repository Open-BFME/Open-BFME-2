// cl: /EHs /MD
// ?rva00352F9D@Rva00352F9D@@QAEXPBXHW4CommandSourceType@@@Z @0x00352F9D 110B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x11 and src,
// m_waypoint from param1 plus m_intValue from param2, virtual slot 0 call,
// then inlined vector-free of m_coords start via rowed free 0x00030830.
// Evidence: immediates 0x11 0x00351BD0 0x00030830; unblocks 0x0036FAF8 0x00353F13 0x0036FB57;
// precedent Rva0047ED64AICommand.cpp same recipe with 0x2E and m_obj.
#include <stddef.h>

extern "C" void __cdecl free(void *p);

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_DUMMY_17 = 17
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
};

struct RvaCoords
{
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;

	~RvaCoords()
	{
		if (m_start)
			free(m_start);
	}
};

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

class Rva0035149F
{
public:
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};

class Rva00352F9D
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void rva00352F9D(const void *waypoint, Int intVal, CommandSourceType src);
	void rva0035300B(const void *obj, const Coord3D &pos, CommandSourceType src);
	void rva00353080(const void *obj, const class Rva0035149F &coords, CommandSourceType src);
	void rva003530F3(const void *obj, const Coord3D &pos, CommandSourceType src);
	void rva00353168(const void *obj, const class Rva0035149F &coords, CommandSourceType src);
	void rva003531DB(const void *obj, const Coord3D &pos, CommandSourceType src);
	void rva0035325A(const void *obj, CommandSourceType src);
};

void Rva00352F9D::rva00352F9D(const void *waypoint, Int intVal, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x11, src);
	parms.m_waypoint = waypoint;
	parms.m_intValue = intVal;
	rvaVirtual(&parms);
}

// ?rva0035300B@Rva00352F9D@@QAEXPBXABUCoord3D@@W4CommandSourceType@@@Z @0x0035300B 117B
// Evidence: unlock same TU as 0x00352F9D; AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x4B and src; m_pos from pos param (12B via 3x movsd) plus m_obj from obj; virtual slot 0 call then RvaCoords free via rowed free 0x00030830; callers 0x003533A8 0x00547929.
void Rva00352F9D::rva0035300B(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4B, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

void Rva00352F9D::rva00353080(const void *obj, const class Rva0035149F &coords, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4D, src);
	((class Rva0035149F &)parms.m_coords).rva0035149F(coords);
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

// ?rva003530F3@Rva00352F9D@@QAEXPBXABUCoord3D@@W4CommandSourceType@@@Z @0x003530F3 117B
// Evidence: unlock same TU as 0x0035300B; AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x4A and src; m_pos from pos (12B) plus m_obj from obj; virtual slot 0 then free; caller 0x00353392.
void Rva00352F9D::rva003530F3(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4A, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

void Rva00352F9D::rva003531DB(const void *obj, const Coord3D &pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x54, src);
	parms.m_pos = pos;
	parms.m_obj = (void *)obj;
	parms.m_intValue = 0x7fffffff;
	rvaVirtual(&parms);
}

// ?rva00353168@Rva00352F9D@@QAEXPBXABVRva0035149F@@W4CommandSourceType@@@Z @0x00353168 115B
// Evidence: gap same TU/class as 0x003530F3/0x003531DB with same // cl: /O1 /EHs /MD; AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x4C and src; m_coords via rowed rva0035149F 0x0035149F then m_obj from obj; virtual slot 0 then free via rowed free 0x00030830; caller 0x00354C09 pushes obj coords src.
void Rva00352F9D::rva00353168(const void *obj, const class Rva0035149F &coords, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x4C, src);
	((class Rva0035149F &)parms.m_coords).rva0035149F(coords);
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}

void Rva00352F9D::rva0035325A(const void *obj, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x3C, src);
	parms.m_obj = (void *)obj;
	rvaVirtual(&parms);
}
