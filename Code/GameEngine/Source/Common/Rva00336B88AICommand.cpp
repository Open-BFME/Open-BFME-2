// cl: /EHs /MD
// ?rva00336B88@Rva00336B88@@QAEXW4CommandSourceType@@@Z @0x00336B88 92B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x3A and src,
// virtual slot 0 call, then inlined coords-free via rowed free 0x00030830.
// Recipe from landed precedent Rva004BFD27Command.cpp (92B, same shape):
// RvaCoords member at +0x20 carries the conditional free in its inline dtor,
// which arms the EH prolog like retail. Evidence: caller at 0x003371A8;
// immediates 0x3A 0x00351BD0 0x00030830.
#include <stddef.h>

extern "C" void __cdecl free(void *p);

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_3A = 0x3A
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

class Rva00336B88
{
public:
	virtual void rvaVirtual(AICommandParms *parms) = 0;
	void rva00336B88(CommandSourceType src);
};

void Rva00336B88::rva00336B88(CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x3A, src);
	rvaVirtual(&parms);
}
