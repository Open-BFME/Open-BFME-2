// cl: /O1 /DNDEBUG /MD /GX
//
// ?aiForceAttackObject@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z,
// retail 0x0036F05A, 110 bytes, plus
// ?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z,
// retail 0x0029599A, 117 bytes. Dedicated TU for the two SpawnBehavior
// slave-loop callees.
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/
// AICommandInterfaceAttackCommands.cpp, AICommandInterface::aiForceAttackObject
// plus aiAttackPosition): build the parameter block on the stack, drop the
// victim or position plus the shot count into their slots, then aiDoCommand
// at vtable slot 0. BFME2 deltas: the command ids are 0x0C and 0x0E, the
// block constructor is the opaque 0x351BD0 pin (cmd plus source, builds the
// +0x20 coordinate vector among the zeroed slots), and block teardown is an
// inline coordinate-buffer free through the C++-linkage free pinned at
// 0x00030830 (pin note: that decoration is what carries the unwind state).

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
	AICMD_IDLE = 5,
	AICMD_FORCE_ATTACK_OBJECT = 0x0C,
	AICMD_ATTACK_POSITION = 0x0E
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

void free(void *block);

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
	Object *m_otherObj; // +0x18
	const void *m_team; // +0x1C
	void *m_coordsStart; // +0x20, coordinate vector buffer
	char m_midPad[0x34 - 0x24]; // +0x24..+0x33
	Int m_intValue; // +0x34
	char m_tailPad[0xC0 - 0x38]; // +0x38..+0xBF, retail block size
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;

	void aiIdle(CommandSourceType cmdSource);
	void aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
};

// ?aiIdle@AICommandInterface@@QAEXW4CommandSourceType@@@Z @0x1E8A38
void AICommandInterface::aiIdle(CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_IDLE, cmdSource);
	aiDoCommand(&parms);
}

// ?aiForceAttackObject@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z @0x36F05A
void AICommandInterface::aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FORCE_ATTACK_OBJECT, cmdSource);
	parms.m_obj = victim;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// ?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z @0x29599A
void AICommandInterface::aiAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_ATTACK_POSITION, cmdSource);
	parms.m_pos = *pos;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}
