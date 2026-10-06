// cl: /EHs /MD
//
// ?rva0047ED64@Rva0047ED64@@QAEX PAX W4CommandSourceType@@@Z at retail 0x0047ED64 (101B).
// Stack AICommandParms (0xC0 block via rowed ctor 0x00351BD0 with 0x2E and
// src) with m_obj overwritten from param1, virtual slot 0 call with parms,
// then inlined vector-free of m_coords start via rowed free 0x00030830.
// Callers 0x0047EDC9 0x004B2C00 0x004BAF2D. Layout copied from
// AICommandParmsCtor.cpp (m_cmd +0 m_cmdSource +4 m_pos +8 m_obj +14
// m_coords +20) with manual freeing coords to get EH plus free like retail.
// Honest-address virtual class; 0x2E is retail immediate.

#include <stddef.h>

extern "C" void __cdecl free(void *p);

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_DUMMY_46 = 46
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
	char m_tail[0xC0 - 0x2C];
};

class Rva0047ED64
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void rva0047ED64(void *obj, CommandSourceType src);

private:
	int m_pad;
};

void Rva0047ED64::rva0047ED64(void *obj, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x2E, src);
	parms.m_obj = obj;
	rvaVirtual(&parms);
}
