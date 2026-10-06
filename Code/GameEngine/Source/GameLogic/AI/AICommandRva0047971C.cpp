// cl: /DNDEBUG /MD /EHsc
// ?rva0047971C@AICommandInterface@@QAEXABVRva0035149F@@PAVObject@@W4CommandSourceType@@@Z @ 0x0047971C (115B).
// AICommandInterface wrapper cmd 0x0A: builds AICommandParms block via
// 0x00351BD0 plus vector assign 0x0035149F into +0x20 plus m_obj store
// plus slot-0 aiDoCommand plus inline coord free 0x00030830. Evidence:
// ctor 0x00351BD0 plus assign 0x0035149F plus virtual slot 0 plus free;
// callers 0x00479A9E 0x0048823F 0x004A0B48 0x004A68F3 0x004F4A5F; shape
// follows AICommandInterfaceAttackCommands precedent.
typedef int Int;
typedef float Real;
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};
class Object;
enum AICommandType
{
	AICMD_0A = 0x0A
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
void __cdecl free(void *block);
class Rva0035149F
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};
struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coords.m_start) free(m_coords.m_start); }
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const void *m_team;
	Rva0035149F m_coords;
	const void *m_waypoint;
	const void *m_polygon;
	Int m_intValue;
	float m_float38;
	char m_tail[0x7C];
	Int m_B8;
	Int m_BC;
};
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void rva0047971C(const Rva0035149F &info, Object *target, CommandSourceType cmdSource);
};
void AICommandInterface::rva0047971C(const Rva0035149F &info, Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_0A, cmdSource);
	parms.m_coords.rva0035149F(info);
	parms.m_obj = target;
	aiDoCommand(&parms);
}
