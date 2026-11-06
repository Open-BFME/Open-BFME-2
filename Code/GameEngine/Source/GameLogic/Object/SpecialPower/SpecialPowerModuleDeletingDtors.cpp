// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No bases, member layout, or destructor implementation are claimed here.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

struct EmitVtableTag;

// InvisibilitySpecialPowerModuleData below derives from SpecialPowerModuleData, as its family
// unit declares it (MobNexusContainModuleDataCtor.cpp), so this unit's copy of its 31-slot
// vftable (retail 0x00C5C558) is the same table instead of a one-slot one that link order would
// keep. The Devastate, OCL, PlayerUpgrade, ProductionSpeedBonus, ElvenWood and WeaponChange
// wrappers are rowed in their own TUs, which emit them with the vtable first in link order.
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

// ??_GWeaponFireSpecialAbilityUpdateModuleData@@UAEPAXI@Z @0x004927EA 28B: slot 0 of vtable 0x00C4E108; calls ??1 at 0x00492806.
// Owner evidence (audited 2026-09-26): retail registration WeaponFireSpecialAbilityUpdate -> data factory RVA 0x0024DB56 -> ctor RVA 0x004926CA; primary vptr store RVA 0x004926D4.
class WeaponFireSpecialAbilityUpdateModuleData { public: WeaponFireSpecialAbilityUpdateModuleData(EmitVtableTag *); virtual ~WeaponFireSpecialAbilityUpdateModuleData(); };
// ?<WeaponFireSpecialAbilityUpdateModuleData::WeaponFireSpecialAbilityUpdateModuleData> absent-from-retail
WeaponFireSpecialAbilityUpdateModuleData::WeaponFireSpecialAbilityUpdateModuleData(EmitVtableTag *) {}

// ??_GAISpecialPowerUpdateModuleData@@UAEPAXI@Z @0x004B2FF3 28B: slot 0 of vtable 0x00C56F48; calls ??1 at 0x004B300F.
// Owner evidence (audited 2026-09-26): retail registration AISpecialPowerUpdate -> data factory RVA 0x0024FD76 -> ctor RVA 0x004B2FCD; primary vptr store RVA 0x004B2FD9.
class AISpecialPowerUpdateModuleData { public: AISpecialPowerUpdateModuleData(EmitVtableTag *); virtual ~AISpecialPowerUpdateModuleData(); };
// ?<AISpecialPowerUpdateModuleData::AISpecialPowerUpdateModuleData> absent-from-retail
AISpecialPowerUpdateModuleData::AISpecialPowerUpdateModuleData(EmitVtableTag *) {}

// ??_GInvisibilitySpecialPowerModuleData@@UAEPAXI@Z @0x004C24C3 28B: slot 0 of vtable 0x00C5C558; calls ??1 at 0x004C24DF.
// Owner evidence (audited 2026-09-26): retail registration InvisibilitySpecialPower -> data factory RVA 0x002518CB -> ctor RVA 0x004C244D; primary vptr store RVA 0x004C246C.
class InvisibilitySpecialPowerModuleData : public SpecialPowerModuleData { public: InvisibilitySpecialPowerModuleData(EmitVtableTag *); virtual ~InvisibilitySpecialPowerModuleData(); };
// ?<InvisibilitySpecialPowerModuleData::InvisibilitySpecialPowerModuleData> absent-from-retail
InvisibilitySpecialPowerModuleData::InvisibilitySpecialPowerModuleData(EmitVtableTag *) {}

// ??_GCashHackSpecialPowerModuleData@@UAEPAXI@Z @0x004C28C1 28B: slot 0 of vtable 0x00C5C688; calls ??1 at 0x004C28DD.
// Owner evidence (audited 2026-09-26): retail registration CashHackSpecialPower -> data factory RVA 0x00251957 -> ctor RVA 0x004C2889; primary vptr store RVA 0x004C289D.
class CashHackSpecialPowerModuleData { public: CashHackSpecialPowerModuleData(EmitVtableTag *); virtual ~CashHackSpecialPowerModuleData(); };
// ?<CashHackSpecialPowerModuleData::CashHackSpecialPowerModuleData> absent-from-retail
CashHackSpecialPowerModuleData::CashHackSpecialPowerModuleData(EmitVtableTag *) {}

// ??_GLevelGrantSpecialPower@@UAEPAXI@Z @0x004C2C5A 28B: slot 0 of vtable 0x00C5C920; calls ??1 at 0x004C2C76.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x004C2BC1 uses class-name string "LevelGrantSpecialPower".
class LevelGrantSpecialPower { public: LevelGrantSpecialPower(EmitVtableTag *); virtual ~LevelGrantSpecialPower(); };
// ?<LevelGrantSpecialPower::LevelGrantSpecialPower> absent-from-retail
LevelGrantSpecialPower::LevelGrantSpecialPower(EmitVtableTag *) {}

// ??_GCloudBreakSpecialPowerModuleData@@UAEPAXI@Z @0x004C47D7 28B: slot 0 of vtable 0x00C5D468; calls ??1 at 0x004C47F3.
// Owner evidence (audited 2026-09-26): retail registration CloudBreakSpecialPower -> data factory RVA 0x00251E58 -> ctor RVA 0x004C479A; primary vptr store RVA 0x004C47AA.
class CloudBreakSpecialPowerModuleData { public: CloudBreakSpecialPowerModuleData(EmitVtableTag *); virtual ~CloudBreakSpecialPowerModuleData(); };
// ?<CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData> absent-from-retail
CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData(EmitVtableTag *) {}

// ??_GTaintSpecialPowerModuleData@@UAEPAXI@Z @0x004C4AEB 28B: slot 0 of vtable 0x00C5D608; calls ??1 at 0x004C4B07.
// Owner evidence (audited 2026-09-26): retail registration TaintSpecialPower -> data factory RVA 0x00251EE4 -> ctor RVA 0x004C4AB8; primary vptr store RVA 0x004C4ACA.
class TaintSpecialPowerModuleData { public: TaintSpecialPowerModuleData(EmitVtableTag *); virtual ~TaintSpecialPowerModuleData(); };
// ?<TaintSpecialPowerModuleData::TaintSpecialPowerModuleData> absent-from-retail
TaintSpecialPowerModuleData::TaintSpecialPowerModuleData(EmitVtableTag *) {}
