// cl: /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/moduledata
// stlport
//
// ?update@OneRingPenaltyUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00499E98,
// 173 bytes: slot 0 of OneRingPenaltyUpdate's UpdateModuleInterface vftable
// 0x00C50254 (installed at +0x10 by the matched ctor 0x00499A70), so `this`
// is that subobject. The Object counts as wearing when Object::rva0028F518
// holds or it has status 0xF, and the object Object::rva0028F4BC hands out
// has its +0x31 flag. With the +0x30 frame set and the module data's +0x14
// frames past it: 0x00499C35. Otherwise the +0x28 start frame is stamped when
// wearing begins; when wearing stops it clears and, with +0x24 set, runs
// 0x00499C46; while wearing, +0x24 runs 0x00499D23, else 0x00499AFD fires
// once the data's +0x0C frames have passed. Sleeps the logic frame rate
// (BfmeLogicFramesPerSecond). The four helpers are members on the primary this, named by
// address (0x00499C46 is also rowed as BfmeC987::bfmeGo987C from a BFME 1
// donor placement). 0x00499C35 (17 bytes) is carried here: it clears the
// +0x30 frame and sets the Object's status 0x12.
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

extern int BfmeLogicFramesPerSecond;

class BfmeC987
{
public:
	void bfmeGo987C();
	char m_bfmePad[0x24]; // +0x00
	int m_bfmeId; // +0x24
};

class Rva00373EC6
{
public:
	void rva00374815();
	char m_pad00[0x31];
	bool m_31; // +0x31 +0x31
};

#include "../../../Common/Thing/thing.h"
enum ObjectID;
enum ObjectStatusTypes;
class Team;
class AIUpdateInterface;
class Rva00373EC6;
enum DamageType { DAMAGE_SNIPER = 8 };
enum DeathType { DEATH_NORMAL = 0 };
class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType);
	bool rva0028F518();
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	Rva00373EC6 *rva0028F4BC();
	void rva0028EC68(int kind, void *payload, int flag);
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad60[0x74 - 0x60];
public:
	ObjectID m_id74; // +0x74
private:
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
public:
	Team *m_team304; // +0x304
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "OneRingPenaltyModuleDataView.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class OneRingPenaltyUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	void rva00499AFD();
	void rva00499C35();
	void rva00499C46();
	void rva00499D23();
	unsigned char m_pad20[0x24 - 0x20];
	int m_24; // +0x24
	UnsignedInt m_28; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	UnsignedInt m_30; // +0x30
};

UpdateSleepTime OneRingPenaltyUpdate::update()
{
	const OneRingPenaltyUpdateModuleData *oneRingPenaltyUpdateModuleData = reinterpret_cast<const OneRingPenaltyUpdateModuleData *>(getModuleData());
	Object *obj = m_object;
	Bool wearing = false;
	if (obj->rva0028F518() || obj->testStatus((ObjectStatusTypes)0xF))
	{
		Rva00373EC6 *ring = obj->rva0028F4BC();
		if (ring && ring->m_31)
			wearing = true;
	}
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_30 != 0 && now > oneRingPenaltyUpdateModuleData->m_timeRingPowerSuppressed + m_30)
		rva00499C35();
	else if (m_28 == 0)
	{
		if (wearing)
			m_28 = now;
	}
	else if (!wearing)
	{
		m_28 = 0;
		if (m_24)
			((BfmeC987 *)this)->bfmeGo987C();
	}
	else if (m_24)
		rva00499D23();
	else if (now > oneRingPenaltyUpdateModuleData->m_ringTimeBeforeSpawning + m_28)
		rva00499AFD();
	return (UpdateSleepTime)BfmeLogicFramesPerSecond;
}

void OneRingPenaltyUpdate::rva00499C35()
{
	m_30 = 0;
	m_object->setStatus((ObjectStatusTypes)0x12, true);
}
