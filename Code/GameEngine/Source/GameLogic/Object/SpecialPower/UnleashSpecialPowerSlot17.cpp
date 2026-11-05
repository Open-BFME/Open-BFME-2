// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ?triggerAbilityEffect@UnleashSpecialPower@@UAEXXZ, retail 0x004CE18A, 187 bytes:
// slot 17 of UnleashSpecialPower's primary vtable 0x00C5FDC0 (ctor
// 0x004CE006), over the SpecialAbilityUpdate slot-17 base 0x0045108D (pinned;
// named by its address, like WoundArrowUpdateSlot17.cpp). After the base,
// through the owner's "SlaveWatcherBehavior" module (key cached in a function
// static, rowed nameToKey and Object::findModule) it finds the watched slaver
// (the module's +0x20 ObjectID, getter 0x0030D377 pinned) and, for each of
// the slaver's behavior modules (the null-terminated +0x244 list) whose +0x0C
// interface hands out an interface from slot 26, runs that interface's slot 6
// and sends the slaver's AI (+0x258) hunting (rowed AICommandInterface::aiHunt,
// command source 2).
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Common/GameLogicObjectLookupView.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class UnleashSpecialPower;

class SlaveWatcherBehavior;

// 0x0030D377 is the ICF-folded 4-byte getter matched as NetWrapperCommandMsg::getDataLength.
#include "../../../../Include/GameNetwork/NetWrapperCommandMsg.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class Rva004CE18AAnswer
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5();
	virtual void rva004CE18ASlot6();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


class Object
{
protected:
	friend class UnleashSpecialPower;
	Module *findModule(NameKeyType key) const;
	char m_pad00[0x244];
public:
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x10];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x1DC];
	unsigned char m_438; // +0x438
	char m_pad439[0x3];
};


extern GameLogic *TheGameLogic;

class ModuleData;

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class UnleashSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
};

void UnleashSpecialPower::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	Object *obj = m_object;
	if (obj == 0)
		return;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	SlaveWatcherBehavior *watcher = (SlaveWatcherBehavior *)obj->findModule(key);
	if (watcher == 0)
		return;
	Object *slaver = TheGameLogic->findObjectByID((ObjectID)((NetWrapperCommandMsg *)watcher)->getDataLength());
	if (slaver == 0)
		return;
	for (BehaviorModule **behaviorModule = slaver->m_behaviors; *behaviorModule; ++behaviorModule)
	{
		Rva004CE18AAnswer *answer = static_cast<Rva004CE18AAnswer *>(static_cast<BehaviorModuleInterface &>(**behaviorModule).slot26());
		if (answer)
		{
			answer->rva004CE18ASlot6();
			AIUpdateInterface *ai = slaver->m_ai;
			if (ai)
				ai->aiHunt(CMD_FROM_AI);
		}
	}
}
