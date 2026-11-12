// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
//
// ??0SpawnBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045F581, 263 bytes.
// SpawnBehavior ctor. UpdateModule base size 0x20 plus four empty interfaces
// at +0x20..+0x2C plus UpgradeMux at +0x30 size 8 plus ptr+3 ints at
// +0x38..+0x44 plus two lists at +0x48/+0x4C plus tail to 0x64 (factory
// 0x0024B405 news 0x64). Donor BFME1 SpawnBehavior.cpp:69 plus readable
// CtorThunk body. Identity is the own vtable 0xC426AC plus poolkey 0x0045F688
// with the SpawnBehavior literal plus caller friend_newModuleInstance.

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

class Thing;
class ModuleData;
class Object;
class ThingTemplate;
class AsciiString;

#include "../../../../Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

class BehaviorModuleOther
{
public:
	virtual void unused();
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"



class SpawnBehaviorInterface
{
public:
	virtual void spawnBehaviorAnchor() = 0;
	// Retail table 0x00C42518: 12 __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
};

class DieModuleInterface
{
public:
	virtual void dieAnchor() = 0;
};

// Three slots, as the other DamageModuleInterface views (BridgeTowerBehavior.cpp,
// FireWeaponWhenDamagedBehaviorCtor.cpp, BoneFXDamage.cpp) lay out its vtable.
class DamageModuleInterface
{
public:
	virtual void damageAnchor() = 0;
	virtual void damageSlot1() = 0;
	virtual void damageSlot2() = 0;
};

class SpawnExtraBase
{
public:
	virtual void spawnExtraAnchor() = 0;
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

struct SpawnBehaviorModuleDataView
{
	unsigned char pad00[8];
	int m_spawnNumberData;
	unsigned char pad0C[4];
	int m_initialBurst;
	bool m_isOneShotData;
	unsigned char pad15;
	bool m_aggregateHealth;
	unsigned char pad17[9];
	AsciiString *m_spawnTemplateBegin;
};

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	SpawnBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<int> m_spawnIDs;
	bool m_active;
	bool m_aggregateHealthFlag;
	bool m_initialBurstTimesInited;
	unsigned char m_pad53;
	int m_spawnCount;
	int m_selfTaskingSpawnCount;
	int m_initialBurstCountdown;
	AsciiString *m_templateNameIterator;
public:
	virtual ~SpawnBehavior();	// rowed elsewhere; declared so this unit binds to it
public:
	// retail slot 4: the rowed ?getModuleNameKey@SpawnBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

SpawnBehavior::SpawnBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const SpawnBehaviorModuleDataView *md = (const SpawnBehaviorModuleDataView *)m_moduleData;
	m_templateNameIterator = md->m_spawnTemplateBegin;
	m_spawnTemplate = TheThingFactory->findTemplate(*m_templateNameIterator);
	m_framesToWait = 0;
	m_firstBatchCount = 0;
	if (md->m_isOneShotData)
		m_oneShotCountdown = md->m_spawnNumberData;
	else
		m_oneShotCountdown = -1;
	m_active = true;
	m_replacementTimes.clear();
	m_initialBurstCountdown = md->m_initialBurst;
	m_initialBurstTimesInited = false;
	m_aggregateHealthFlag = md->m_aggregateHealth;
	m_spawnCount = -1;
	m_active = true;
	m_selfTaskingSpawnCount = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
