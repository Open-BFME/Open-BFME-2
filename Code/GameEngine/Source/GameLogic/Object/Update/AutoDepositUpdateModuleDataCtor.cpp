char g_00BF1BC8;

// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// ??0AutoDepositUpdateModuleData@@QAE@XZ, retail 0x002540ED (84 bytes).
// The module-data half of AutoDeposit: vtable immediate (unsigned int)&g_00BF1BC8 modelled
// as an explicit first member (ToppleUpdateModuleDataCtor precedent, so no
// vtable is emitted and no dtor row is owed), the deposit timing at +0x08,
// the deposit amount at +0x0C, the initial capture bonus at +0x10, the
// upgrade template at +0x14, the bonus percent at +0x18 (1.0f from the shared
// literal at 0x00BBB8D8, ProneUpdate precedent), the required upgrade at
// +0x1C constructed through the ledger-known member ctor (rowed pin at
// 0x3623E5, AnimationSteering precedent) and the two flags at +0x20/+0x21
// defaulting to false. Field identity is retail's own eight-entry INI table
// at 0x00BF1CC8 (landed buildFieldParse row) joined to the BFME1
// AutoDepositUpdate donor (deposit frame, deposit amount, initial capture
// bonus; BFME2 extends it with the upgrade fields). The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor) is
// load-bearing for the EH state machine (GrantUpgrade precedent).

class UpgradeTemplate;

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class AutoDepositUpdateModuleData : public UpdateModuleData
{
public:
	AutoDepositUpdateModuleData();

private:
	const void *m_vtable;				// +0x00
	unsigned int m_unused04;			// +0x04
	unsigned int m_depositTiming;			// +0x08
	int m_depositAmount;				// +0x0C
	int m_initialCaptureBonus;			// +0x10
	UpgradeTemplate *m_upgrade;			// +0x14
	float m_upgradeBonusPercent;			// +0x18
	Rva003623E5Member m_upgradeMustBePresent;	// +0x1C
	bool m_giveNoXP;				// +0x20
	bool m_onlyWhenGarrisoned;			// +0x21
};

inline AutoDepositUpdateModuleData::AutoDepositUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>((unsigned int)&g_00BF1BC8))
	, m_depositTiming(0)
	, m_depositAmount(0)
	, m_initialCaptureBonus(0)
	, m_upgrade(0)
	, m_upgradeBonusPercent(1.0f)
	, m_upgradeMustBePresent()
{
	m_giveNoXP = false;
	m_onlyWhenGarrisoned = false;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeAutoDepositUpdateModuleDataInlineAnchor@@YAXPAVAutoDepositUpdateModuleData@@@Z absent-from-retail
void _bfmeAutoDepositUpdateModuleDataInlineAnchor(AutoDepositUpdateModuleData *autoDepositUpdateModuleData)
{
    autoDepositUpdateModuleData->AutoDepositUpdateModuleData::AutoDepositUpdateModuleData();
}
#pragma inline_depth()
