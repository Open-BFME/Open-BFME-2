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

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../../../Include/Common/ModuleData.h"

// ??_GSalvageCrateCollideModuleData@@UAEPAXI@Z @0x002563D3 28B: slot 0 of vtable 0x00BF3A40; calls ??1 at 0x002563EF.
// Owner evidence (audited 2026-09-26): retail registration SalvageCrateCollide -> data factory RVA 0x00255BD2 -> ctor RVA 0x00255B7E; primary vptr store RVA 0x00255BA3.
class SalvageCrateCollideModuleData : public ModuleData { public: SalvageCrateCollideModuleData(EmitVtableTag *); virtual ~SalvageCrateCollideModuleData(); };
// ?<SalvageCrateCollideModuleData::SalvageCrateCollideModuleData> absent-from-retail
SalvageCrateCollideModuleData::SalvageCrateCollideModuleData(EmitVtableTag *) {}
