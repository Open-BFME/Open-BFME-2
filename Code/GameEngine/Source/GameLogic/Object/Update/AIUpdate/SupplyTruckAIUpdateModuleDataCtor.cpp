// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this data class under "ActiveBody" (addModule
// pairs the name with this factory); formerly misnamed SupplyTruckAIUpdateModuleData.
// stlport
//
// ??0ActiveBodyModuleData@@QAE@XZ, retail 0x004BF59F, 258 bytes.
// ActiveBodyModuleData ctor over the MaxHealth-led damage table
// 0xC5B228 (21 fields). All callees rowed: Vector_base 0x211E58,
// StringBase::set 0x55F5, clear/dtor fold 0x36410, isEmpty 0x1E2F,
// findFXList 0x1E281A. Factory 0x2513E8 news 0x64, sole caller.
// Empty UpdateModuleData base (inline-empty ctor + declared-only dtor)
// arms single-state EH with zero code (Topple precedent). Pre-vector
// stores (vtable, grab strings, cheer 200, remove/burning zeros) run in
// init-list order; post-vector stores follow retail body order.

// Vtable 0x00C5AFB8: the table whose slot 0 is ??_GActiveBodyModuleData (vftable_map); bound to the ??_7 the ledger's deleting-dtor unit emits.
extern "C" const void *__identifier("??_7ActiveBodyModuleData@@6B@")[];

#include <vector>

#include "../../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();
};

#include "../../../../../Include/Common/GlobalData.h"

extern class GlobalData *TheWritableGlobalData;

class FXList;
#include "../../../../../Include/GameClient/FXListStore.h"

extern FXListStore *TheFXListStore;

class ActiveBodyModuleData : public UpdateModuleData
{
public:
	ActiveBodyModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	float m_maxHealth; // +8
	float m_initialHealth; // +0xC
	float m_maxHealthDamaged; // +0x10
	float m_maxHealthReallyDamaged; // +0x14
	float m_dodgePercent; // +0x18
	int m_enteringDamaged; // +0x1C
	int m_enteringReallyDamaged; // +0x20
	int m_recoveryTime; // +0x24
	unsigned char m_useDefault; // +0x28
	unsigned char m_pad29[3];
	AsciiString m_grabObject; // +0x2C
	AsciiString m_damagedAttr; // +0x30
	AsciiString m_reallyDamagedAttr; // +0x34
	int m_grabFX; // +0x38
	float m_grabDamage; // +0x3C
	float m_grabOffsetX; // +0x40
	float m_grabOffsetY; // +0x44
	const FXList *m_healingBuffFx; // +0x48
	float m_cheerRadius; // +0x4C
	unsigned char m_removeUpgrades; // +0x50
	unsigned char m_burningBehavior; // +0x51
	unsigned char m_pad52[2];
	int m_burningFX; // +0x54
	_STL::vector<BfmeE16> m_damageCreation; // +0x58
};

// ??0ActiveBodyModuleData@@QAE@XZ @0x4BF59F
ActiveBodyModuleData::ActiveBodyModuleData()
	: m_vtable(reinterpret_cast<const void *>(__identifier("??_7ActiveBodyModuleData@@6B@")))
	, m_grabObject()
	, m_damagedAttr()
	, m_reallyDamagedAttr()
	, m_cheerRadius(200.0f)
	, m_removeUpgrades(0)
	, m_burningBehavior(0)
	, m_burningFX(0)
{
	m_maxHealth = 0.0f;
	m_maxHealthDamaged = 0.0f;
	m_maxHealthReallyDamaged = 0.0f;
	m_initialHealth = -1.0f;
	m_recoveryTime = 0;
	m_enteringDamaged = 0;
	m_enteringReallyDamaged = 0;
	m_dodgePercent = 0.0f;
	m_useDefault = 1;
	m_grabObject.set("EntThrownBuildingRock");
	m_grabDamage = 200.0f;
	m_grabFX = 0;
	m_healingBuffFx = 0;
	m_grabOffsetX = 0.0f;
	m_grabOffsetY = 0.0f;
	m_damagedAttr.clear();
	m_reallyDamagedAttr.clear();
	AsciiString &healingDefault = TheWritableGlobalData->m_defaultUnitHealingBuffFxList;
	if (!reinterpret_cast<const StringBase<char> *>(&healingDefault)->isEmpty())
		m_healingBuffFx = TheFXListStore->findFXList(healingDefault.str());
}
