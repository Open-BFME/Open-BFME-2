// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C7AF3Do@@YGXPAVParameter@@H@Z @0x003C7AF3 200B
// Script command: move a named unit to the waypoint indexed by the second argument.
// Target evidence: getUnitNamed 0x003588E7; TerrainLogic vslot +0x88;
// AIUpdate 0x0026295E; leaveGroup 0x0028C01F; position test 0x0028ECDB;
// move command 0x003C75DD or 0x00295A0F. Target stores position x/y float bits
// at Object+0x31C/+0x320 before the move command. The 0x00295A0F declaration
// matches the existing row's void* ABI.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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
	float m_x;
	float m_y;
	float m_z;
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

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

class AICommandInterface
{
public:
	void aiAttackMoveToPositionAmphibious(const Coord3D *pos, CommandSourceType src);
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int a, int b);
};

class AIUpdateInterface
{
public:
	void rva0026295E();
	char m_pad[0x20];
	AICommandInterface m_commands;
};

// The ledger row at 0x0028ECDB is Rva0028ECDBHost::rva0028ECDB(void *).
class Rva0028ECDBHost
{
public:
	bool rva0028ECDB(void *pos);
};

class Object
{
public:
	void leaveGroup();
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x31C - 0x25C];
	int m_31C;
	int m_320;
};

void __stdcall Rva003C7AF3Do(Parameter *p, int id)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
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
	if (((Rva0028ECDBHost *)obj)->rva0028ECDB(&pos)) {
		float xy[2];
		xy[0] = pos.x;
		int xbits = *(volatile int *)&xy[0];
		float y = *(volatile float *)&pos.y;
		obj->m_31C = xbits;
		xy[1] = y;
		obj->m_320 = *(int *)&xy[1];
		ai->m_commands.aiAttackMoveToPositionAmphibious(&pos, (CommandSourceType)1);
	} else {
		((Rva00295A0FCommands *)&ai->m_commands)->Rva00295A0FCommand(&pos, 0x7FFFFFFF, 1);
	}
}
