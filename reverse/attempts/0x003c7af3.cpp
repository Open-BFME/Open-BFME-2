// ?Rva003C7AF3Do@@YGXPAVParameter@@H@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C7AF3Do@@YGXPAVParameter@@H@Z @0x003C7AF3 200B script move named unit via TerrainLogic slot 0x88 with rva003C75DD else Rva00295A0FCommand.
// Evidence: rowed getUnitNamed 0x003588E7 plus TerrainLogic virtual 0x88 plus rowed AIUpdate 0x0026295E plus rowed leaveGroup plus pinned Object rva0028ECDB plus rowed rva003C75DD plus rowed Rva00295A0FCommand 0x00295A0F; caller 0x003CA67B; honest Rva name.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter;
class Object;
class Waypoint;
class AICommandInterface;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

class Waypoint
{
public:
	char m_pad00[0x0C];
	float m_x; // +0x0C
	float m_y; // +0x10
	float m_z; // +0x14
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33();
	virtual Waypoint *s34(int id);
};

extern ScriptEngine *g_Va009FE16C;
extern TerrainLogic *TheTerrainLogic;

class AICommandInterface
{
public:
	void rva003C75DD(const Coord3D *pos, CommandSourceType src);
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(const void *pos, int a, int b);
};

class AIUpdateInterface
{
public:
	void rva0026295E();
	char m_pad[0x20];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	void leaveGroup();
	bool rva0028ECDB(const Coord3D *pos) const;
	char m_pad00[0x258];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x31C - 0x25C];
	int m_31C; // +0x31C float bits
	int m_320; // +0x320 float bits
};

// ?Rva003C7AF3Do@@YGXPAVParameter@@H@Z present-unmatched
void __stdcall Rva003C7AF3Do(Parameter *p, int id)
{
	Object *obj = g_Va009FE16C->getUnitNamed(p);
	if (obj == 0)
		return;
	Waypoint *wp = TheTerrainLogic->s34(id);
	if (wp == 0)
		return;
	Coord3D pos;
	pos.x = wp->m_x;
	AIUpdateInterface *ai = obj->m_ai;
	pos.y = wp->m_y;
	pos.z = wp->m_z;
	if (ai == 0)
		return;
	ai->rva0026295E();
	obj->leaveGroup();
	if (obj->rva0028ECDB(&pos)) {
		float xy[2];
		xy[0] = pos.x;
		obj->m_31C = *(int *)&xy[0];
		xy[1] = pos.y;
		obj->m_320 = *(int *)&xy[1];
		ai->m_commands.rva003C75DD(&pos, (CommandSourceType)1);
	} else {
		((Rva00295A0FCommands *)&ai->m_commands)->Rva00295A0FCommand(&pos, 0x7FFFFFFF, 1);
	}
}
