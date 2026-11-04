// cl: /DNDEBUG /MD /GX
// platformsdk
//
// ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00497ED0,
// 261 bytes. Zero Hour's BattlePlanUpdate::BattlePlanUpdate (GeneralsMD
// GameLogic/Object/Update/BattlePlanUpdate.cpp), reshaped by BFME 2.
// Target evidence: the body runs the rowed UpdateModule ctor 0x00253390 and
// the implicit ctor of the abstract interface at +0x20 (vtable 0x0086F248,
// every slot _purecall 0x0003B810), then stores the vtables the rowed dtor
// 0x004978A3 restores: 0x0084FBAC primary, whose slot 0 is the rowed
// deleting dtor 0x00497FD7 and slot 2 the rowed BattlePlanUpdate name
// getter 0x0049795A, 0x0084FBA0 for UpdateModuleInterface and 0x0084FB7C
// at +0x20. The member order and the stores follow ZH: plan and status
// fields at +0x24..+0x34, the special power module at +0x38, the two flags
// at +0x3C/+0x3D, the bonuses record at +0x40 allocated with operator new
// (0x4C bytes, the rowed record ctor 0x002AA14D) and filled from the
// module data's kind-of masks at +0x54/+0x70, the vision object ID at
// +0x88. BFME 2 replaces ZH's audio events with sixteen ref-counted
// handles at +0x44 (element ctor at the ICF-folded 0x00326BE6 nulls the
// pointer, element dtor 0x0010F149 releases it, both through __ehvec_ctor)
// and adds an int at +0x84 initialised to 1, the value the rowed dtor
// passes to TheAudio.
#include <windows.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;
class SpecialPowerModuleInterface;

enum ObjectID
{
	INVALID_ID = 0
};

enum BattlePlanStatus
{
	PLANSTATUS_NONE
};

enum TransitionStatus
{
	TRANSITIONSTATUS_IDLE
};

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


// update is pure here as in the rest of the module hierarchy; this unit
// names no override, like BattlePlanUpdateRva004978A3Dtor.cpp, so the two
// units emit one ??_7BattlePlanUpdate@@6BUpdateModule@@@.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


// The abstract interface at +0x20 (ZH's SpecialPowerUpdateInterface slot).
#include "../../../../Include/GameLogic/Module/SpecialPowerUpdateInterface.h"

// The 0x1C-byte kind-of mask; its ctor is the rowed clear at 0x0024C7B3.
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

// The bonuses record, rowed under its ctor's address name.
class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses() throw();

	Real m_armorScalar; // +0x00
	Int m_bombardment; // +0x04
	Int m_searchAndDestroy; // +0x08
	Int m_holdTheLine; // +0x0C
	Real m_sightRangeScalar; // +0x10
	Rva0024C7B3Member m_validKindOf; // +0x14
	Rva0024C7B3Member m_invalidKindOf; // +0x30
};

// The ref-counted handle BFME 2 keeps sixteen of; named after its
// destructor's address.
class Rva0010F149Handle
{
public:
	Rva0010F149Handle();
	~Rva0010F149Handle();
private:
	void *m_ptr;
};

class BattlePlanUpdateModuleData
{
public:
	unsigned char m_pad00[0x54];
	Rva0024C7B3Member m_validMemberKindOf; // +0x54
	Rva0024C7B3Member m_invalidMemberKindOf; // +0x70
};

// Retail's tables, each slot the ledger row at the native address.
extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_GBattlePlanUpdate@@UAEPAXI@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?bfmeTransition@Gen_002854E0@@QAEXHHHIH@Z")();
void __identifier("?cleanUp@SpectreGunshipUpdate@@QAEXXZ")();
void __identifier("?equals@Rva002857B0Object@@QAE_NH@Z")();
void __identifier("?get@Rva004543A9LeaNegSbbField@@UBEHXZ")();
void __identifier("?get@Rva00497960CmpBoolField@@QBE_NXZ")();
void __identifier("?getCommandOption@BattlePlanUpdate@@UBE?AW4CommandOption@@XZ")();
void __identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?getModuleNameKey@BattlePlanUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva0049795ANamed@@QBEPBDXZ")();
void __identifier("?onObjectCreated@BattlePlanUpdate@@UAEXXZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?update@Rva0049862B@@QAEHXZ")();
void __identifier("?xfer@BattlePlanUpdate@@MAEXPAVXfer@@@Z")();
}

// VA 0x00C4FBAC
extern "C" const void *const g_battlePlanTable00[13] = {
	(const void *)&__identifier("??_GBattlePlanUpdate@@UAEPAXI@Z"), // slot 0, RVA 0x00497FD7
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1, RVA 0x00497805
	(const void *)&__identifier("?name@Rva0049795ANamed@@QBEPBDXZ"), // slot 2, RVA 0x0049795A
	(const void *)&__identifier("?xfer@BattlePlanUpdate@@MAEXPAVXfer@@@Z"), // slot 3, RVA 0x00498517
	(const void *)&__identifier("?getModuleNameKey@BattlePlanUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4, RVA 0x00497915
	(const void *)&__identifier("?onObjectCreated@BattlePlanUpdate@@UAEXXZ"), // slot 5, RVA 0x0049797F
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 6, RVA 0x000B3FD0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 7, RVA 0x000B3FD0
	(const void *)&__identifier("?cleanUp@SpectreGunshipUpdate@@QAEXXZ"), // slot 8, RVA 0x004984CC
	(const void *)&__identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z"), // slot 9, RVA 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11, RVA 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12, RVA 0x0022C4CB
};

// VA 0x00C4D640
extern "C" const void *const g_battlePlanTable0C[47] = {
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 0, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 1, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 2, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 3, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 4, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 5, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 6, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 7, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 8, RVA 0x000D43D0
	(const void *)&__identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ"), // slot 9, RVA 0x002533D3
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 12, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 13, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 14, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 15, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24, RVA 0x000D43D0
	(const void *)&__identifier("?get@Rva004543A9LeaNegSbbField@@UBEHXZ"), // slot 25, RVA 0x004543A9
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 30, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 31, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 32, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 33, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 34, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 35, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 36, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 37, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 38, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 39, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 40, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 41, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 42, RVA 0x000D43D0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 43, RVA 0x0047A69C
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 44, RVA 0x000B3FD0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 45, RVA 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 46, RVA 0x0047A69C
};

// VA 0x00C4FBA0
extern "C" const void *const g_battlePlanTable10[3] = {
	(const void *)&__identifier("?update@Rva0049862B@@QAEHXZ"), // slot 0, RVA 0x0049862B
	(const void *)&__identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ"), // slot 1, RVA 0x00253376
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z"), // slot 2, RVA 0x0044DF8D
};

// VA 0x00C4FB7C
extern "C" const void *const g_battlePlanTable20[9] = {
	(const void *)&__identifier("?bfmeTransition@Gen_002854E0@@QAEXHHHIH@Z"), // slot 0, RVA 0x004976DB
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 1, RVA 0x0047A699
	(const void *)&__identifier("?get@Rva00497960CmpBoolField@@QBE_NXZ"), // slot 2, RVA 0x00497960
	(const void *)&__identifier("?getCommandOption@BattlePlanUpdate@@UBE?AW4CommandOption@@XZ"), // slot 3, RVA 0x0049771E
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4, RVA 0x0047A699
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 5, RVA 0x0047A69C
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 6, RVA 0x005CB9FF
	(const void *)&__identifier("?equals@Rva002857B0Object@@QAE_NH@Z"), // slot 7, RVA 0x00497969
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 8, RVA 0x005CB9FA
};

class __declspec(novtable) BattlePlanUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	BattlePlanUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BattlePlanUpdate();
private:
	const BattlePlanUpdateModuleData *getBattlePlanUpdateModuleData() const { return (const BattlePlanUpdateModuleData *)m_moduleData; }

	BattlePlanStatus m_currentPlan; // +0x24
	BattlePlanStatus m_desiredPlan; // +0x28
	BattlePlanStatus m_planAffectingArmy; // +0x2C
	TransitionStatus m_status; // +0x30
	UnsignedInt m_nextReadyFrame; // +0x34
	SpecialPowerModuleInterface *m_specialPowerModule; // +0x38
	Bool m_invalidSettings; // +0x3C
	Bool m_centeringTurret; // +0x3D
	Rva002AA14DBonuses *m_bonuses; // +0x40
	Rva0010F149Handle m_handles[16]; // +0x44
	Int m_84; // +0x84
	ObjectID m_visionObjectID; // +0x88
};

BattlePlanUpdate::BattlePlanUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_bonuses((*(const void *const **)this = g_battlePlanTable00,
		*(const void *const **)((char *)this + 0x0C) = g_battlePlanTable0C,
		*(const void *const **)((char *)this + 0x10) = g_battlePlanTable10,
		*(const void *const **)((char *)this + 0x20) = g_battlePlanTable20,
		(Rva002AA14DBonuses *)NULL))
	, m_84(1)
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();

	m_status = TRANSITIONSTATUS_IDLE;
	m_currentPlan = PLANSTATUS_NONE;
	m_desiredPlan = PLANSTATUS_NONE;
	m_planAffectingArmy = PLANSTATUS_NONE;
	m_nextReadyFrame = 0;
	m_invalidSettings = false;
	m_centeringTurret = false;

	//Default the bonuses to no change.
	m_bonuses = new Rva002AA14DBonuses;
	m_bonuses->m_armorScalar = 1.0f;
	m_bonuses->m_sightRangeScalar = 1.0f;
	m_bonuses->m_bombardment = 0;
	m_bonuses->m_searchAndDestroy = 0;
	m_bonuses->m_holdTheLine = 0;
	m_bonuses->m_validKindOf = data->m_validMemberKindOf;
	m_bonuses->m_invalidKindOf = data->m_invalidMemberKindOf;

	m_visionObjectID = INVALID_ID;

	m_specialPowerModule = NULL;
}
