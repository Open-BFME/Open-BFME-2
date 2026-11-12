// cl: /DNDEBUG /MD /Oi
// ??0BridgeBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00457472 196B.
// Recovered from the banked attempt reverse/attempts/0x00457472.cpp (0.97).
// That bank already carried the lever that finishes the body: writing the
// third Mid-slot store (+0x28) through a local int* instead of the volatile
// char-cast pins it ahead of the freelist call-setup cluster. With it in
// place the whole 196B matches retail byte for byte -- the "3 bytes at +0x01,
// base-ctor arg push order" wall recorded in the bank note is gone, because
// push [ebp+0xc] then push [ebp+8] was already the order this source emits.
// Evidence: base-ctor call 0x00253390, Rva0029FB3BMember::init 0x0029FB3B
// and reset 0x0026549E, six explicit secondary vtable installs, memset zero
// cluster at +0x2C, nested 4x3 loops over +0xA3C/+0xA6C/+0xA9C/+0xACC.
class Object;
#include "../../../Common/GameLogicObjectLookupView.h"
enum BridgeTowerType { BRIDGE_TOWER_FROM_LEFT = 0, BRIDGE_MAX_TOWERS = 4 };

// The primary table at RVA 0x008409DC (13 slots) is the compiler-emitted
// ??_7BridgeBehavior@@6BObjectModule@@@: every slot names a rowed owner.

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
template <int NUMBITS> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BridgeBehaviorInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;
	virtual ObjectID getTowerID(BridgeTowerType towerType) = 0;
	virtual void createScaffolding() = 0;
	virtual void removeScaffolding() = 0;
	virtual bool isScaffoldInMotion() = 0;
	virtual bool isScaffoldPresent() = 0;
};

class DamageInfo;
enum BodyDamageType { BODY_PRISTINE = 0 };

#include "../../../../Include/GameLogic/Module/DamageModuleInterface.h"

#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
	void *m_head;
};

#include <string.h>

class BridgeBehavior : public UpdateModule,
	public BridgeBehaviorInterface, public DamageModuleInterface, public DieModuleInterface
{
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_a3C[4][3];
	int m_a6C[4][3];
	int m_a9C[4][3];
	int m_aCC[4][3];
	bool m_FC;
	bool m_FD;
	char m_padFE[2];
	Rva0029FB3BMember m_free; // +0x100
	int m_104;
public:
	virtual ~BridgeBehavior();
	virtual UpdateSleepTime update();
	virtual void setTower(BridgeTowerType towerType, Object *tower);
	virtual ObjectID getTowerID(BridgeTowerType towerType);
	virtual void createScaffolding();
	virtual void removeScaffolding();
	virtual bool isScaffoldInMotion();
	virtual bool isScaffoldPresent() { return m_FD; }
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
	virtual void onDie(const DamageInfo *damageInfo);
	// Retail's BehaviorModuleInterface table 0x00C40920 overrides the damage (slot 4,
	// 0x003730FC), die (slot 7, 0x004523A9) and Zero Hour getBridgeBehaviorInterface
	// (slot 12, 0x004543A9) getters, each converting the +0x0C receiver to its interface.
	virtual DamageModuleInterface *getDamage() { return this; }
	virtual DieModuleInterface *getDie() { return this; }
	virtual void *slot12() { return static_cast<BridgeBehaviorInterface *>( this ); }
	// Primary table 0x00C409DC: slot 1 is 0x00497805 (the base call) and slot 8 is
	// 0x00456A3E (resets the +0x100 member); both are defined in BridgeBehaviorCtor.cpp.
	virtual void onDelete();

	BridgeBehavior(Thing *thing, const ModuleData *moduleData);
public:
	// retail slot 4: the rowed ?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual const char * GetSnapshotName() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
protected:
	// retail vftable slot 1: the base call 0x00497805 (BridgeBehaviorCtor.cpp)
	virtual void loadPostProcess();
};

BridgeBehavior::BridgeBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	void *context = (void *)((char *)&moduleData + 3);
	Rva0029FB3BMember *free = &m_free;
	free->init(context);
	free->reset();
	m_FD = false;
	memset(&m_2C, 0, 16);
	m_FC = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			m_a3C[i][j] = 0;
			m_a6C[i][j] = 0;
			m_a9C[i][j] = 0;
			m_aCC[i][j] = 0;
		}
	m_104 = 0;
}

// Slot 8 of the primary table 0x00C409DC, 0x00456A3E: Zero Hour's onDelete releases
// the scaffold pool member at +0x100 (Rva0029FB3BMember::reset 0x0026549E).
void BridgeBehavior::onDelete()
{
	m_free.reset();
}

// Slot 1 of the primary table 0x00C409DC, 0x00497805: the base call.
void BridgeBehavior::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}
