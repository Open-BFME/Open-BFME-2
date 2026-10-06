// cl: /EHs /MD
// ?aiMoveToPositionEvenIfSleeping@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x00394191 108B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x36 and src,
// m_pos 12B copy from param1, virtual slot 0 call, then inlined vector-free
// via rowed free 0x00030830. Recipe precedent Rva00352ECAAICommand.cpp 101B
// (same ctor plus slot 0 plus inlined RvaCoords free, flags /O1 /EHs /MD).
// Evidence: immediates 0x36 0x00351BD0 0x00030830; callers 0x00395286 0x0039A44B 0x004560DF.

extern "C" void __cdecl free(void *p);

typedef int Int;
typedef float Real;

enum AICommandType
{
	AICMD_DUMMY_1 = 1
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

class AICommandInterface
{
public:
	virtual void v0(AICommandParms *parms) = 0;
	void aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType src);
};

void AICommandInterface::aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x36, src);
	parms.m_pos = *pos;
	v0(&parms);
}
