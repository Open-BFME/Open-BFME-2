// cl: /EHs /MD
// AICommandInterface::aiMoveToAndDie (WorldBuilder name, AI.h line 715: command 0x41 with the position).
// was ?rva00462290@Rva00462290@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x00462290 108B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x41 and src,
// m_pos 12B copy from param1, virtual slot 0 call, then inlined vector-free
// via rowed free 0x00030830. Recipe precedent Rva00462224.cpp 108B
// (same shape with 0x38, flags /O1 /EHs /MD).
// Evidence: immediates 0x41 0x00351BD0 0x00030830; caller 0x004622FC; prev row 0x00462224.

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
	void aiMoveToAndDie(const Coord3D *pos, CommandSourceType src);
};

void AICommandInterface::aiMoveToAndDie(const Coord3D *pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x41, src);
	parms.m_pos = *pos;
	v0(&parms);
}
