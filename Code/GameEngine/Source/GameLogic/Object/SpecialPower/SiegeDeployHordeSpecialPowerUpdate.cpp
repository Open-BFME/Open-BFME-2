// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?update@SiegeDeployHordeSpecialPower@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x004C64EE (154 bytes): slot 9 of the +0x10 update table 0x0085DD64 just
// before SiegeDeployHordeSpecialPower's primary vtable 0x0085DD94, so `this`
// is the module +0x10 (Object at -8). The horde marches its siege engine to
// the deploy target (ObjectID +0x38, rowed xfer): nothing more once the AI
// is gone or its last command came from the player (AI slot +0x23C); a dead
// or missing target idles the AI. A target without status 0x3B is handed to
// the AI command 0x00352ECA each frame; with it, once a logic second has
// passed (+0x48 counter, BfmeLogicFramesPerSecond frames) the AI idles and moves to the
// stored deploy position (+0x3C, set by slot 14 0x004C63DE). Storage view: no
// constructor or destructor, no vtable emitted.
#include "../../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_3B = 0x3B
};

struct Coord3D;
extern int BfmeLogicFramesPerSecond;	// logic frames per second
extern GameLogic *TheGameLogic;

class Object;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"


class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	AIUpdateInterface *getAI() { return m_ai; }
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;		// +0x438
};

class SiegeDeployHordePrimary
{
public:
	virtual ~SiegeDeployHordePrimary();
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class SiegeDeployHordeIface0C
{
public:
	virtual void f0C();
};
class SiegeDeployHordeUpdateIface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual void u8();
	virtual UpdateSleepTime update() = 0;	// slot 9
};

class SiegeDeployHordeSpecialPower : public SiegeDeployHordePrimary, public SiegeDeployHordeIface0C, public SiegeDeployHordeUpdateIface
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned char m_pad14[0x38 - 0x14];
	ObjectID m_targetID;		// +0x38
	unsigned char m_pos[12];	// +0x3C, the deploy position
	int m_counter;			// +0x48
};

UpdateSleepTime SiegeDeployHordeSpecialPower::update()
{
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	AIUpdateInterface *ai = m_object->getAI();
	if (ai && ai->vslot143() != CMD_FROM_PLAYER)
	{
		if (target && !(target->m_privateStatus & 1))
		{
			if (target->testStatus(OBJECT_STATUS_3B))
			{
				if (++m_counter < BfmeLogicFramesPerSecond)
					return UPDATE_SLEEP_NONE;
				m_counter = 0;
				ai->aiIdle(CMD_FROM_AI);
				ai->aiMoveToPosition((const Coord3D *)m_pos, CMD_FROM_AI);
			}
			else
			{
				ai->aiMoveToObject((Object *)target, CMD_FROM_AI);
				return UPDATE_SLEEP_NONE;
			}
		}
		else
		{
			ai->aiIdle(CMD_FROM_AI);
		}
	}
	return UPDATE_SLEEP_FOREVER;
}
