// cl: /EHs /MD
// ?rva00336B23@Rva00336B23@@QAEXPAXW4CommandSourceType@@@Z @0x00336B23 101B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x2F and src,
// m_obj from param1, virtual slot 0 call, then inlined coords-free via
// rowed free 0x00030830. Recipe from landed precedent Rva00352ECAAICommand.cpp
// (101B, same obj/src shape) and sibling Rva00336B88AICommand.cpp (92B).
// Evidence: caller at 0x00337119; immediates 0x2F 0x00351BD0 0x00030830.

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
	AICMD_2F = 0x2F
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

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
	char m_tail[0xC0 - 0x2C];
};

class Rva00336B23
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void rva00336B23(void *obj, CommandSourceType src);
};

void Rva00336B23::rva00336B23(void *obj, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x2F, src);
	parms.m_obj = obj;
	rvaVirtual(&parms);
}
