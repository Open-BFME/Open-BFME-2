// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
//
// ??1SpawnBehavior@@UAE@XZ, retail 0x0045F6D3, 138 bytes. Virtual dtor.
// Restores the eight MI vptrs (+0 0xC426AC +0x0C 0xC425F0 +0x10 0xC425E0
// +0x20 0xC425AC +0x24 0xC425A8 +0x28 0xC4259C +0x2C 0xC42598 +0x30 0xC42550
// DIR32) then clears m_replacementTimes at +0x48 through the rowed
// 0x23DAA5 List_base clear, destroys m_spawnIDs at +0x4C and
// m_replacementTimes at +0x48 through the rowed 0x4EC395 List_base dtor,
// then calls the UpdateModule base dtor (pinned ??1UpdateModule@@UAE@XZ
// at 0x0024A797 rowed as ??1Rva0024A797@@UAE@XZ). Layout follows the ctor
// at 0x0045F581 (UpdateModule base size 0x20 plus four empty interfaces
// at +0x20..+0x2C plus UpgradeMux at +0x30 size 8 plus ptr+3 ints at
// +0x38..+0x44 plus two lists at +0x48/+0x4C, factory 0x0024B405 news
// 0x64) and the ZH donor SpawnBehavior.h (SpawnBehaviorInterface plus
// DieModuleInterface plus DamageModuleInterface plus UpgradeMux from
// UpgradeModule.h). BFME1 donor SpawnBehaviorDestructors.cpp proves the
// clear-then-destroy shape. Identity is the own vtable 0xC426AC plus slot
// 0 deleting dtor 0x004602D8 calling this body plus poolkey 0x0045F688
// with the SpawnBehavior literal.

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

class BehaviorModuleOther
{
public:
	virtual void unused();
};

// The canonical UpdateModule, as SpawnBehaviorCtor.cpp reads it, so both units emit the same
// SpawnBehavior primary, BehaviorModuleInterface and +0x10 tables (LINK-177).
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

#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

// Three slots, as the other DamageModuleInterface views (BridgeTowerBehavior.cpp,
// FireWeaponWhenDamagedBehaviorCtor.cpp, BoneFXDamage.cpp) lay out its vtable.
class DamageModuleInterface
{
public:
	virtual void damageAnchor() = 0;
	virtual void damageSlot1() = 0;
	virtual void damageSlot2() = 0;
};

typedef int (__cdecl *Rva0045FE4ACallback)(Object *obj, void *data);

// Retail's interface table 0x00C42598 holds SpawnBehavior::rva0045FE4A in slot 0.
class SpawnExtraBase
{
public:
	virtual int rva0045FE4A(Rva0045FE4ACallback func, void *data) = 0;
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ThingTemplate;

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	virtual ~SpawnBehavior();

private:
	const ThingTemplate *m_spawnTemplate; // +0x38
	int m_oneShotCountdown; // +0x3C
	int m_framesToWait; // +0x40
	int m_firstBatchCount; // +0x44
	_STL::list<int> m_replacementTimes; // +0x48
	_STL::list<int> m_spawnIDs; // +0x4C
	unsigned char m_pad50[0x14]; // +0x50..+0x63 trivial tail to news 0x64
public:
	// retail slot 4: the rowed ?getModuleNameKey@SpawnBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
	// The rowed overrides retail's interface tables hold in slot 0 (as SpawnBehaviorCtor.cpp).
	virtual UpdateSleepTime update();
	virtual void onDie(const DamageInfo *damageInfo);
	virtual int rva0045FE4A(Rva0045FE4ACallback func, void *data);
};

SpawnBehavior::~SpawnBehavior()
{
	m_replacementTimes.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
// (SpawnBehaviorCtor.cpp binds the public ?unused@BehaviorModuleOther@@UAEXXZ.)
