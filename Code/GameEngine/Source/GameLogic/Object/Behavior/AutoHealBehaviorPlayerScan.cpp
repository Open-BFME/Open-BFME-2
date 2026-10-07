// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /ICode/GameEngine/Source/Common
//
// The file-static helpers retail places ahead of AutoHealBehavior::update
// (0x00452496..0x0045280B): the stretch BFME 1's AutoHealBehavior.cpp
// (reference/open-bfme-1 AutoHealBehavior_playerScan.cpp, retail 0x001EEDE0)
// compiles to. BFME 2 adds the contained-units collector, splits the
// in-combat test out of the eligibility test and passes the scan data's
// 28-byte kind-of mask. The combat and eligibility tests are not
// address-taken, so VC7.1 gives them its private register convention (the
// object in ESI for the combat test; the candidate in EBX and the scan data
// in EDI for the eligibility test); they stay in one unit with their callers
// for that reason. The two callbacks are what update (0x0045280B) hands to
// Player::iterateObjects and ContainModuleInterface::iterateContained.
//
// Layout facts are the target's: Object +0x250/+0x254/+0x258/+0x274/+0x438
// as the rowed Object accessors read them, the body module slots as the rowed
// BodyModule vftables order them. Names follow the BFME 1 donor and Zero Hour
// where the body agrees with them.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
extern Int g_Va00DBA4E4; // logic frames per second

// KindOf bits by the retail name table at 0x00DBBE18.
enum KindOfType
{
	KINDOF_HORDE = 0x6D
};

// The 28-byte kind-of mask.
template <int N> class BitFlags
{
private:
	UnsignedInt m_bits[7];
};
typedef BitFlags<69> KindOfMaskType;

// STLport list<Object*> as these helpers use it: push_back is retail's
// out-of-line instantiation (0x001EC03C).
namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &x);
private:
	void *_M_node;
};
}

class Object;
typedef _STL::list<Object *> ObjectPointerList;

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad00[0x108];
	unsigned char m_kindof[32]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline Bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	Bool isAnyKindOf(const KindOfMaskType &anyKindOf) const;
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x48 - 0x08];
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage();
	virtual void attemptHealing();
	virtual void estimateDamage();
	virtual void i03();
	virtual Real getHealth() const; // +0x10
	virtual Real getHealthRatio() const; // +0x14
	virtual Real getMaxHealth() const; // +0x18
	virtual void i07();
	virtual void i08();
	virtual void i09();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual UnsignedInt getLastDamageTimestamp() const; // +0x40
};

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

template <int N> class AutoHealSlots : public AutoHealSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class AutoHealSlots<0>
{
};

// Object +0x250: slot 68 is Zero Hour's iterateContained.
class ContainModuleInterface : public AutoHealSlots<68>
{
public:
	virtual void iterateContained(ContainIterateFunc func, void *userData, Bool reverse); // +0x110
};

class Object : public Thing
{
public:
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool isOffMap() const { return (m_privateStatus & 8) != 0; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
private:
	char m_pad48[0x250 - 0x48];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

// The scan data checkForAutoHeal and the radius scan hand the eligibility test.
struct AutoHealPlayerScanHelper
{
	KindOfMaskType m_kindOfToTest; // +0x00
	Object *m_theHealer; // +0x1C
	ObjectPointerList *m_objectList; // +0x20
	Bool m_healOnlyIfNotUnderAttack; // +0x24
	Bool m_healOnlyIfNotInCombat; // +0x25
	Bool m_healOnlyOthers; // +0x26
};

// ?Rva00452496Check@@YA_NPAVObject@@@Z @0x00452496
// True while obj's AI has a victim, or obj sits in a horde whose AI has one.
static Bool Rva00452496Check(Object *obj)
{
	if (!obj)
		return false;
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (ai && ai->getCurrentVictim() != 0)
		return true;
	Object *container = obj->getContainedBy();
	return container
		&& container->isKindOf(KINDOF_HORDE)
		&& container->getAIUpdateInterface() != 0
		&& container->getAIUpdateInterface()->getCurrentVictim() != 0;
}

// ?Rva004524E5ShouldHeal@@YA_NPAVObject@@PBUAutoHealPlayerScanHelper@@@Z @0x004524E5
// BFME 1's eligibility test (0x001EE670) with the in-combat test split out.
static Bool Rva004524E5ShouldHeal(Object *testObj, const AutoHealPlayerScanHelper *helper)
{
	if (helper->m_healOnlyOthers && testObj == helper->m_theHealer)
		return false;

	Object *healer = helper->m_theHealer;
	if (healer)
	{
		if (helper->m_healOnlyIfNotInCombat && Rva00452496Check(healer))
			return false;

		// Damaged within the last second (BFME 1 waits five frames).
		if (helper->m_healOnlyIfNotUnderAttack)
		{
			BodyModuleInterface *body = helper->m_theHealer->getBodyModule();
			UnsignedInt now = TheGameLogic->getFrame();
			if (body->getLastDamageTimestamp() < now)
			{
				body = helper->m_theHealer->getBodyModule();
				now = TheGameLogic->getFrame();
				if (body->getLastDamageTimestamp() + g_Va00DBA4E4 > now)
					return false;
			}
		}
	}

	if (testObj->isEffectivelyDead())
		return false;
	if (testObj->isOffMap())
		return false;
	if (!testObj->isAnyKindOf(helper->m_kindOfToTest))
		return false;

	BodyModuleInterface *body = testObj->getBodyModule();
	if (body->getHealth() >= body->getMaxHealth())
		return false;
	return true;
}

// ?Rva00452795CollectContained@@YAXPAVObject@@PAX@Z @0x00452795
// Gathers the hurt units of a container, descending into hordes.
void Rva00452795CollectContained(Object *obj, void *userData)
{
	if (obj->isKindOf(KINDOF_HORDE))
		obj->getContain()->iterateContained(Rva00452795CollectContained, userData, true);
	else if (obj->getBodyModule()->getHealthRatio() < 1.0f)
		((ObjectPointerList *)userData)->push_back(obj);
}

// ?checkForAutoHeal@@YAHPAVObject@@PAX@Z @0x004527E5
Int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (Rva004524E5ShouldHeal(testObj, helper))
		helper->m_objectList->push_back(testObj);
	return 1;
}
