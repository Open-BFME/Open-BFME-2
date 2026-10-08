// cl: /DNDEBUG /MD
//
// ?rva0036FBC5@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z, retail 0x0036FBC5, 61 bytes.
// AIGroup forward of aiBfmeCommand33 to each member via the rowed
// AICommandInterface method at 0x0036EDB1 plus an Object+0x410 clear.
// Evidence: same list-at-+0x00 plus Object+0x258 plus +0x20 subobject loop
// as the rowed groupAttackTeam at 0x0036FF33 and the landed rva0036FA56 at
// 0x0036FA56; caller at 0x003BF70B.
//
// AIGroup::groupIdle, retail 0x0036FC23 (321 bytes), and its contain-iterator
// callback rva0036FC02 (33 bytes) just before it. WorldBuilder names the body
// (AIGroup.cpp); the BFME1 donor AIGroup_groupIdle.cpp gives its shape. BFME2
// deltas: the contain and AI pointers sit at Object+0x250 / +0x258, the player
// idle flag at AI+0x3CC, and the stealth gate tests status bits through the
// rowed Object::testStatus.

#include <list>

#include "../../Common/GameLogicObjectLookupView.h"

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_STEALTHED = 0x0F,
	OBJECT_STATUS_DETECTED = 0x11,
	OBJECT_STATUS_CAN_STEALTH = 0x12
};

class AICommandInterface
{
public:
	void aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateModuleData
{
public:
	char m_pad[0x1C];
	unsigned int m_autoAcquireEnemiesWhenIdle; // +0x1C
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int arg);
	void rva0026304D(int frame); // ZH setNextMoodCheckTime
	bool canAutoAcquire() const { return m_moduleData->m_autoAcquireEnemiesWhenIdle != 0; }
	bool canAutoAcquireWhileStealthed() const { return (m_moduleData->m_autoAcquireEnemiesWhenIdle & 2) != 0; }
	char m_pad00[4];
	AIUpdateModuleData *m_moduleData; // +0x04
	char m_pad08[0x20 - 0x08];
	AICommandInterface m_commands; // +0x20
	char m_pad21[0x3CC - 0x21];
	bool m_playerIdle; // +0x3CC
};

// The stealth update module (0x00373EC6 family); its module data keeps the
// stealth delay at +0x08.
class Rva00373EC6ModuleData
{
public:
	char m_pad[8];
	unsigned int m_stealthDelay;
};

class Rva00373EC6
{
public:
	char m_pad[4];
	Rva00373EC6ModuleData *m_moduleData;
};

class Object;
typedef void (*ContainIterateFunc)(Object *obj, void *userData);

class ContainModuleInterface
{
#define CONTAIN_SLOT(name) virtual void slot##name();
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(04) CONTAIN_SLOT(08) CONTAIN_SLOT(0C)
	CONTAIN_SLOT(10) CONTAIN_SLOT(14) CONTAIN_SLOT(18) CONTAIN_SLOT(1C)
	CONTAIN_SLOT(20) CONTAIN_SLOT(24) CONTAIN_SLOT(28) CONTAIN_SLOT(2C)
	CONTAIN_SLOT(30) CONTAIN_SLOT(34) CONTAIN_SLOT(38) CONTAIN_SLOT(3C)
	CONTAIN_SLOT(40) CONTAIN_SLOT(44) CONTAIN_SLOT(48) CONTAIN_SLOT(4C)
	CONTAIN_SLOT(50) CONTAIN_SLOT(54) CONTAIN_SLOT(58) CONTAIN_SLOT(5C)
	CONTAIN_SLOT(60) CONTAIN_SLOT(64) CONTAIN_SLOT(68) CONTAIN_SLOT(6C)
	CONTAIN_SLOT(70) CONTAIN_SLOT(74) CONTAIN_SLOT(78) CONTAIN_SLOT(7C)
	CONTAIN_SLOT(80) CONTAIN_SLOT(84) CONTAIN_SLOT(88) CONTAIN_SLOT(8C)
	CONTAIN_SLOT(90) CONTAIN_SLOT(94) CONTAIN_SLOT(98) CONTAIN_SLOT(9C)
	CONTAIN_SLOT(A0) CONTAIN_SLOT(A4) CONTAIN_SLOT(A8) CONTAIN_SLOT(AC)
	CONTAIN_SLOT(B0) CONTAIN_SLOT(B4) CONTAIN_SLOT(B8) CONTAIN_SLOT(BC)
	CONTAIN_SLOT(C0) CONTAIN_SLOT(C4) CONTAIN_SLOT(C8) CONTAIN_SLOT(CC)
	CONTAIN_SLOT(D0) CONTAIN_SLOT(D4) CONTAIN_SLOT(D8) CONTAIN_SLOT(DC)
	CONTAIN_SLOT(E0) CONTAIN_SLOT(E4) CONTAIN_SLOT(E8) CONTAIN_SLOT(EC)
	CONTAIN_SLOT(F0) CONTAIN_SLOT(F4) CONTAIN_SLOT(F8) CONTAIN_SLOT(FC)
	CONTAIN_SLOT(100) CONTAIN_SLOT(104) CONTAIN_SLOT(108) CONTAIN_SLOT(10C)
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse); // +0x110
#undef CONTAIN_SLOT
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void orderSlavesToGoIdle(CommandSourceType cmdSource); // +0x20
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	bool rva0028F518();
	Rva00373EC6 *rva0028F4BC();
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

	char m_pad00[0x250];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x410 - 0x25C];
	int m_410;
};

extern GameLogic *TheGameLogic;
extern const int g_009BA4E4; // logic frames per second

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class AIGroup
{
public:
	void rva0036FBC5(const Waypoint *waypoint, CommandSourceType cmdSource);
	void groupIdle(CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FBC5(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		obj->m_410 = 0;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai != 0)
			ai->m_commands.aiBfmeCommand33(waypoint, cmdSource);
	}
}

// Retail 0x0036FC02, 33 bytes: the contain iterator callback groupIdle hands
// a member without an AI, idling each contained object that has one.
void rva0036FC02(Object *obj, void *userData)
{
	if (obj)
	{
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai)
			ai->m_commands.aiIdle(*(CommandSourceType *)userData);
	}
}

// Retail 0x0036FC23, 321 bytes.
void AIGroup::groupIdle(CommandSourceType cmdSource)
{
	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (obj == 0)
			continue;

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai)
		{
			ai->m_commands.aiIdle(cmdSource);

			if (cmdSource == CMD_FROM_PLAYER)
				ai->m_playerIdle = true;

			if (cmdSource == CMD_FROM_PLAYER &&
				obj->testStatus(OBJECT_STATUS_CAN_STEALTH) &&
				ai->canAutoAcquire())
			{
				if (!obj->rva0028F518() &&
					!obj->testStatus(OBJECT_STATUS_STEALTHED) &&
					!obj->testStatus(OBJECT_STATUS_DETECTED) &&
					!ai->canAutoAcquireWhileStealthed())
				{
					Rva00373EC6 *stealth = obj->rva0028F4BC();
					if (stealth)
					{
						unsigned int stealthFrames = stealth->m_moduleData->m_stealthDelay;
						unsigned int randomFrames = GetGameLogicRandomValue(0, g_009BA4E4,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIGroup.cpp",
							0x9EE);
						ai->rva0026304D(TheGameLogic->getFrame() + stealthFrames + randomFrames);
					}
				}
			}
		}
		else
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				contain->iterateContained(rva0036FC02, &cmdSource, true);
		}

		SpawnBehaviorInterface *spawnInterface = obj->getSpawnBehaviorInterface();
		if (spawnInterface)
			spawnInterface->orderSlavesToGoIdle(cmdSource);
	}
}
