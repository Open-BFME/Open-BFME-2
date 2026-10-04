// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// FellBeastSwoopPower slot 17 (vftable 0x00C5DF80), retail 0x004C6E06, 67
// bytes, on the primary this, and the two AICommandInterface commands it
// issues, which retail emits as copies in this unit beside it.
//
//   0x004C6E06  when the Object has an AI (+0x258): the Object TheGameLogic
//               finds for the ID at +0x40 gets command 0x3F from CMD_FROM_AI;
//               without one, the position at +0x44 gets command 0x40.
//   0x004C6D35  (101 bytes) AICommandParms 0x3F with the Object, then
//               aiDoCommand (slot 0).
//   0x004C6D9A  (108 bytes) AICommandParms 0x40 with the position, then
//               aiDoCommand.
// The commands build the stack AICommandParms through the rowed ctor
// 0x00351BD0 and free its coordinate buffer inline on the way out, the recipe
// of the rowed AICommandInterface commands (AICommandInterfaceAttackCommands.cpp,
// Rva00336B23AICommand.cpp). Names by address.
extern "C" void __cdecl free(void *p);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

enum AICommandType
{
	AICMD_BFME_3F = 0x3F,
	AICMD_BFME_40 = 0x40
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);	// 0x00351BD0
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd;		// +0x00
	CommandSourceType m_cmdSource;	// +0x04
	Coord3D m_pos;			// +0x08
	Object *m_obj;			// +0x14
	Object *m_otherObj;		// +0x18
	const void *m_team;		// +0x1C
	void *m_coordsStart;		// +0x20
	void *m_coordsFinish;		// +0x24
	void *m_coordsEnd;		// +0x28
	char m_tail[0xC0 - 0x2C];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void rva004C6D35(Object *obj, CommandSourceType cmdSource);
	void rva004C6D9A(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commandInterface;	// +0x20
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;	// +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class ModuleData;
class FellBeastSwoopPower
{
public:
	virtual ~FellBeastSwoopPower();
	virtual void rva004C6E06();
private:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x40 - 0x0C];
	ObjectID m_targetID;		// +0x40
	Coord3D m_targetPos;		// +0x44
};

void AICommandInterface::rva004C6D35(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3F, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

void AICommandInterface::rva004C6D9A(const Coord3D *pos, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_40, cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

void FellBeastSwoopPower::rva004C6E06()
{
	AIUpdateInterface *ai = m_object->getAI();
	if (ai == 0)
		return;
	const Coord3D *pos = &m_targetPos;
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	if (target)
		ai->getCommandInterface()->rva004C6D35(target, CMD_FROM_AI);
	else if (pos)
		ai->getCommandInterface()->rva004C6D9A(pos, CMD_FROM_AI);
}
