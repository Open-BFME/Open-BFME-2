// cl: /O1 /DNDEBUG /MD /GX
//
// slot 8 of the vtable 0x00C5FD98 that UnleashSpecialPower's ctor 0x004CE006
// installs at +0x20 (the argument unread). Through the owner's
// "SlaveWatcherBehavior" module (key cached in a function static, rowed
// nameToKey 0x00148E1A and Object::findModule 0x0028B6D6) it finds the
// watched slaver (the module's +0x20 ObjectID, getter 0x0030D377 pinned) and
// answers true when the slaver is alive (bit 0 of +0x438 clear) and none of
// its behavior modules (the null-terminated +0x244 list) hands out, from
// slot 26 of its +0x0C interface, an interface whose slot 7 answers true.
// Compiled with the +0x20 subobject this. Names by address.
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class UnleashSpecialPower;

class SlaveWatcherBehavior;

// 0x0030D377 is the ICF-folded 4-byte getter matched as NetWrapperCommandMsg::getDataLength.
#include "../../../../Include/GameNetwork/NetWrapperCommandMsg.h"

class Rva004CE0D9Answer
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual Bool rva004CE0D9Slot7();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


class AIUpdateInterface;
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


class ModuleData;

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class Rva004CE0D9Interface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual Bool rva004CE0D9(int unused) = 0;
};

class UnleashSpecialPower : public SpecialPowerModule, public Rva004CE0D9Interface
{
public:
	virtual Bool rva004CE0D9(int unused);
};

static inline Bool rva004CE0D9Free(Object *slaver)
{
	for (BehaviorModule **behaviorModule = slaver->m_behaviors; *behaviorModule; ++behaviorModule)
	{
		Rva004CE0D9Answer *answer = static_cast<Rva004CE0D9Answer *>(static_cast<BehaviorModuleInterface &>(**behaviorModule).slot26());
		if (answer && answer->rva004CE0D9Slot7())
			return false;
	}
	return true;
}

Bool UnleashSpecialPower::rva004CE0D9(int unused)
{
	Object *obj = m_object;
	if (obj == 0)
		return false;
	static NameKeyType key = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	SlaveWatcherBehavior *watcher = (SlaveWatcherBehavior *)obj->findModule(key);
	if (watcher == 0)
		return false;
	Object *slaver = TheGameLogic->findObjectByID((ObjectID)((NetWrapperCommandMsg *)watcher)->getDataLength());
	if (slaver == 0)
		return false;
	if (slaver->m_438 & 1)
		return false;
	return rva004CE0D9Free(slaver);
}
