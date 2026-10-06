// cl: /EHs /MD
// ?rva00462224@Rva00462224@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x00462224 108B
// Stack AICommandParms 0xC0 via rowed ctor 0x00351BD0 with 0x38 and src,
// m_pos 12B copy from param1, virtual slot 0 call, then inlined vector-free
// via rowed free 0x00030830. Recipe precedent Rva00394191.cpp 108B
// (same ctor plus slot 0 plus inlined RvaCoords free, flags /O1 /EHs /MD).
// Evidence: immediates 0x38 0x00351BD0 0x00030830; caller 0x004622FC.

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

class Rva00462224
{
public:
	virtual void v0(AICommandParms *parms) = 0;
	void rva00462224(const Coord3D *pos, CommandSourceType src);
};

void Rva00462224::rva00462224(const Coord3D *pos, CommandSourceType src)
{
	AICommandParms parms((AICommandType)0x38, src);
	parms.m_pos = *pos;
	v0(&parms);
}
