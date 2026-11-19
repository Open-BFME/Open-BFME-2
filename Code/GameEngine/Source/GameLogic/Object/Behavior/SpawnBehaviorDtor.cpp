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


class DamageInfo;
struct Coord3D;
enum ObjectID;
enum CommandSourceType;
enum CanAttackResult;
enum AbleToAttackType;

class SpawnBehaviorInterface
{
public:
	virtual void spawnBehaviorAnchor() = 0;
	// Retail table 0x00C42518: 12 __purecall entries follow. Slots 1 to 8, 10 and
	// 12 take the signatures of the rowed SpawnBehavior overrides retail's table
	// 0x00C425AC holds there (Zero Hour's SpawnBehaviorInterface order for 1 to 8).
	virtual void onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo) = 0;
	virtual Object *getClosestSlave(const Coord3D *pos) = 0;
	virtual void orderSlavesToAttackTarget(Object *target, int maxShotsToFire, CommandSourceType cmdSource) = 0;
	virtual void orderSlavesToAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource) = 0;
	virtual CanAttackResult getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType, const Object *target, CommandSourceType cmdSource) = 0;
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType cmdSource) = 0;
	virtual bool canAnySlavesAttack() = 0;
	virtual void orderSlavesToGoIdle(CommandSourceType cmdSource) = 0;
	virtual void slot9() = 0;
	virtual void rva0045FD9F() = 0;
	virtual void slot11() = 0;
	virtual void rva004601CC() = 0;
};

#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

enum BodyDamageType;
#include "../../../../Include/GameLogic/Module/DamageModuleInterface.h"

typedef int (__cdecl *Rva0045FE4ACallback)(Object *obj, void *data);

// Retail's interface table 0x00C42598 holds SpawnBehavior::rva0045FE4A in slot 0.
#include "../../../../Include/Common/SpawnExtraBase.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class ThingTemplate;

struct UpgradeMaskType;
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
	// DamageModuleInterface 0x00C4259C: the rowed onDamage 0x0045FDF3, the shared
	// `ret 4` 0x0047A69C (Zero Hour's empty onHealing) and the rowed
	// onBodyDamageStateChange 0x004604D5.
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo) {}
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
	virtual int rva0045FE4A(Rva0045FE4ACallback func, void *data);
	// SpawnBehaviorInterface table 0x00C425AC, slots 1 to 8, 10 and 12: the rowed
	// overrides 0x0045FCFB, 0x0045F87C, 0x0046070E, 0x00460757, 0x0045F8E0,
	// 0x0045F93D, 0x0045F99E, 0x004607A0, 0x0045FD9F and 0x004601CC. Slots 0, 9
	// and 11 (0x0045F2F8, 0x0045F37D, 0x00498802) are rowed under other classes.
	virtual void onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo);
	virtual Object *getClosestSlave(const Coord3D *pos);
	virtual void orderSlavesToAttackTarget(Object *target, int maxShotsToFire, CommandSourceType cmdSource);
	virtual void orderSlavesToAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
	virtual CanAttackResult getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType, const Object *target, CommandSourceType cmdSource);
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *victim, const Coord3D *pos, CommandSourceType cmdSource);
	virtual bool canAnySlavesAttack();
	virtual void orderSlavesToGoIdle(CommandSourceType cmdSource);
	virtual void rva0045FD9F();
	virtual void rva004601CC();
	// Primary table 0x00C426AC, slot 8: the rowed onDelete 0x0045F75D.
	virtual void onDelete();
	// BehaviorModuleInterface table 0x00C425F0: the null-preserving conversions of
	// the +0x0C receiver retail holds in slots 4 (0x004523A9, the +0x28 interface),
	// 7 (0x003730FC, +0x24), 10 (0x0039852B, +0x30) and 42 (0x004647C0, +0x2C).
	virtual DamageModuleInterface *getDamage() { return this; }
	virtual DieModuleInterface *getDie() { return this; }
	virtual UpgradeModuleInterface *getUpgrade() { return reinterpret_cast<UpgradeModuleInterface *>(static_cast<UpgradeMux *>(this)); }
	virtual void *slot42() { return static_cast<SpawnExtraBase *>(this); }
protected:
	// Primary table 0x00C426AC, slots 1 and 3: the rowed loadPostProcess 0x0045F382
	// and xfer 0x00460586.
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
	virtual void getUpgradeActivationMasks(struct UpgradeMaskType &, struct UpgradeMaskType &) const;
};

SpawnBehavior::~SpawnBehavior()
{
	m_replacementTimes.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
// (SpawnBehaviorCtor.cpp binds the public ?unused@BehaviorModuleOther@@UAEXXZ.)
