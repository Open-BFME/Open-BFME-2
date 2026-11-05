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

// The retail table at RVA 0x008409DC: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GBridgeBehavior@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?GetSnapshotName@BridgeBehavior@@MBEPBDXZ")();
void __identifier("?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?rva00456A3E@Rva00456A3E@@QAEXXZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C409DC[13] = {
	(const void *)&__identifier("??_GBridgeBehavior@@UAEPAXI@Z"), // slot 0 0x00457536
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?GetSnapshotName@BridgeBehavior@@MBEPBDXZ"), // slot 2 0x004571EE
	(const void *)&__identifier("?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z"), // slot 3 0x00457E72
	(const void *)&__identifier("?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x004571A9
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("?rva00456A3E@Rva00456A3E@@QAEXXZ"), // slot 8 0x00456A3E
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};

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

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState) = 0;
};

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

	BridgeBehavior(Thing *thing, const ModuleData *moduleData);
public:
	// retail slot 4: the rowed ?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
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
