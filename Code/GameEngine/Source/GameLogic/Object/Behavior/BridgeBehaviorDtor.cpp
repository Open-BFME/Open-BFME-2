// cl: /DNDEBUG /MD /EHsc
//
// ??1BridgeBehavior@@UAE@XZ, retail 0x00457113, 150 bytes (pinned; rowed
// deleting wrapper 0x00457536). The Zero Hour destructor body carries over:
// look up each of the four tower IDs through getTowerID (rowed 0x004565A5,
// called on the +0x20 BridgeBehaviorInterface subobject) and destroy any
// tower still alive. BFME2 deltas (target evidence): six vtables at
// +0x00/+0x0C/+0x10/+0x20/+0x24/+0x28, and a pool member at +0x100 released
// through the pinned PoolMember::Rva00268902 after the loop. Retail's unwind
// map holds the base 0x0024A797 (state 0) and that member (state 1, through
// the 0x00268AFF jmp), with no store between the loop and the release, as
// in BroadcastStealthUpdateDtor.cpp. Base layout as in Rva0024A797Derived.cpp.
class Object;
#include "../../../Common/GameLogicObjectLookupView.h"
enum BridgeTowerType { BRIDGE_TOWER_FROM_LEFT = 0, BRIDGE_MAX_TOWERS = 4 };


extern GameLogic *TheGameLogic;

// UpdateModule carries its own three vptrs (+0x00/+0x0C/+0x10), as in
// BroadcastStealthUpdateDtor.cpp, so the +0x10 UpdateModuleInterface table is
// ??_7BridgeBehavior@@6BUpdateModule@@@ as in the kept BridgeBehavior.cpp:
// retail's 0x00C40914 holds exactly update, getDisabledTypesToProcess and
// rva0044DF8D (rows 0x00456E8D, 0x00253376, 0x0044DF8D).
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
template <int NUMBITS> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class BridgeBehaviorInterface
{
public:
	// Slot order and signatures copied from ZH GameLogic/Module/BridgeBehavior.h
	// (the header the kept BridgeBehavior.cpp compiles): the {for
	// BridgeBehaviorInterface} vtable slice must hold these six refs.
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;
	virtual ObjectID getTowerID(BridgeTowerType towerType) = 0;
	virtual void createScaffolding() = 0;
	virtual void removeScaffolding() = 0;
	virtual bool isScaffoldInMotion() = 0;
	virtual bool isScaffoldPresent() = 0;
};

class DamageInfo;
enum BodyDamageType { BODY_PRISTINE = 0 }; // name fixes the W4BodyDamageType vtable relocs; values in ZH GameLogic/Damage.h

class DamageModuleInterface
{
public:
	// ZH GameLogic/Module/DamageModule.h: three slots, not one.
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState) = 0;
};

#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

class PoolMember
{
public:
	~PoolMember() { Rva00268902(); }
	void Rva00268902() throw();
private:
	void *m_ptr;
};

class BridgeBehavior : public UpdateModule,
	public BridgeBehaviorInterface, public DamageModuleInterface, public DieModuleInterface
{
public:
	virtual ~BridgeBehavior();
	virtual UpdateSleepTime update();
	// Other secondary-vtable members bind their existing providers. The flag
	// getter is defined here so the obsolete protected donor destructor can go.
	virtual void setTower(BridgeTowerType towerType, Object *tower);
	virtual ObjectID getTowerID(BridgeTowerType towerType);
	virtual void createScaffolding();
	virtual void removeScaffolding();
	virtual bool isScaffoldInMotion();
	// Native interface+20 receiver reads flag+DD (complete object+FD).
	// Retail table C408FC slot5 ->4571F4; ctor also clears byte+FD.
	virtual bool isScaffoldPresent() { return m_FD; }
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
	virtual void onDie(const DamageInfo *damageInfo);
private:
	char m_pad2C[0xFD - 0x2C];
	bool m_FD;
	char m_padFE[0x100 - 0xFE];
	PoolMember m_100;
public:
	// retail slot 4: the rowed ?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

BridgeBehavior::~BridgeBehavior()
{
	for (int i = 0; i < BRIDGE_MAX_TOWERS; ++i)
	{
		Object *tower = TheGameLogic->findObjectByID(getTowerID((BridgeTowerType)i));
		if (tower)
			TheGameLogic->destroyObject(tower);
	}
}
