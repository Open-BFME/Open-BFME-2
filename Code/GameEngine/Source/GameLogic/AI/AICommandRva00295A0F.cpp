// cl: /DNDEBUG /MD /GX
// ?Rva00295A0FCommand@Rva00295A0FCommands@@QAEXPAXHH@Z @0x00295A0F 117B leaf
// Position command via rowed AICommandParms ctor 0x351BD0 (cmd 0x0F + source),
// pos copy to m_pos, maxShots to m_intValue, aiDoCommand at vtable slot 0,
// teardown via inline free 0x30830. Prev aiAttackPosition gives block layout
// and slot-0 pattern; LINK AssaultTransport helper names this mangling.
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;

enum AICommandType
{
	AICMD_DUMMY_00 = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

extern "C" void free(void *block);

class Rva003427DD
{
public:
	Rva003427DD &operator=(const Rva003427DD &src);
private:
	char m_data[0x7C];
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const void *m_team;
	void *m_coordsStart;
	void *m_coordsFinish;
	void *m_coordsEnd;
	const Waypoint *m_waypoint;
	const void *m_polygon;
	Int m_intValue;
	float m_float38;
	Rva003427DD m_3C;
	char m_tailPad[0xC0 - 0x3C - 0x7C];
};

class Rva00295A0FCommands
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void Rva00295A0FCommand(void *pos, int maxShots, int source);
};

void Rva00295A0FCommands::Rva00295A0FCommand(void *pos, int maxShots, int source)
{
	AICommandParms parms((AICommandType)0x0F, (CommandSourceType)source);
	parms.m_pos = *(const Coord3D *)pos;
	parms.m_intValue = maxShots;
	aiDoCommand(&parms);
}
