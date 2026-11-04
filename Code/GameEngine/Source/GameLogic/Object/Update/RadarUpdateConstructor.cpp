// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here every member store precedes the vtable stores, so the members are plain
// and the vptr stores sink past the whole run. MSVC groups by value: the zeros
// at 0x14, 0x25, 0x20 and 0x24 first, then the two -1s at 0x18 and 0x1c. The
// derived stores are written in retail's order, which is not offset order.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/Common/ObjectModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// Target table at RVA 0x00851A0C has 13 primary slots: RadarUpdate owns
// GetSnapshotName (0x004A0C27), xfer (0x004A0CC3), and getModuleNameKey
// (0x004A0C2D). Its +0x10 interface table at 0x00851A00 owns update
// (0x004A0D5F). The getter owner is still rowed under a placeholder name, so
// the constructor stores retail's tables itself.
// Retail's tables, each slot the ledger row at the native address.
extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_GRva004A0C0E@@UAEPAXI@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")();
void __identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?getModuleNameKey@RadarUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?name@Rva004A0C27Named@@QBEPBDXZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
void __identifier("?update@RadarUpdate@@UAE?AW4UpdateSleepTime@@XZ")();
void __identifier("?xfer@RadarUpdate@@MAEXPAVXfer@@@Z")();
}

// VA 0x00C51A0C
extern "C" const void *const g_radarUpdateTable00[13] = {
	(const void *)&__identifier("??_GRva004A0C0E@@UAEPAXI@Z"), // slot 0, RVA 0x004A0CA7
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1, RVA 0x00497805
	(const void *)&__identifier("?name@Rva004A0C27Named@@QBEPBDXZ"), // slot 2, RVA 0x004A0C27
	(const void *)&__identifier("?xfer@RadarUpdate@@MAEXPAVXfer@@@Z"), // slot 3, RVA 0x004A0CC3
	(const void *)&__identifier("?getModuleNameKey@RadarUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4, RVA 0x004A0C2D
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 5, RVA 0x000B3FD0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 6, RVA 0x000B3FD0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 7, RVA 0x000B3FD0
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 8, RVA 0x000B3FD0
	(const void *)&__identifier("?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z"), // slot 9, RVA 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10, RVA 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11, RVA 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12, RVA 0x0022C4CB
};

// VA 0x00BEFF90
extern "C" const void *const g_radarUpdateTable0C[47] = {
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
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25, RVA 0x000D43D0
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

// VA 0x00C51A00
extern "C" const void *const g_radarUpdateTable10[3] = {
	(const void *)&__identifier("?update@RadarUpdate@@UAE?AW4UpdateSleepTime@@XZ"), // slot 0, RVA 0x004A0D5F
	(const void *)&__identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ"), // slot 1, RVA 0x00253376
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z"), // slot 2, RVA 0x0044DF8D
};

class __declspec(novtable) RadarUpdate : public UpdateModule
{
public:
	RadarUpdate(Thing *, const ModuleData *);

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:

	int m_value20;							///< 0x20
	bool m_flag24;							///< 0x24
	bool m_flag25;							///< 0x25
};

// ??0RadarUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RadarUpdate::RadarUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_flag25 = false;
	m_value20 = 0;
	m_flag24 = false;
	*(const void *const **)this = g_radarUpdateTable00;
	*(const void *const **)((char *)this + 0x0C) = g_radarUpdateTable0C;
	*(const void *const **)((char *)this + 0x10) = g_radarUpdateTable10;
}
