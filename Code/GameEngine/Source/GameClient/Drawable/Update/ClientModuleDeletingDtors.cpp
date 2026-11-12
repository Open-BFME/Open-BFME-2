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

// ??_GUpgradeSoundSelectorClientBehaviorModuleData@@UAEPAXI@Z @0x004CBACE 28B: slot 0 of vtable 0x00C5F250; calls ??1 at 0x004CBAEA.
// Owner evidence (audited 2026-09-26): retail registration UpgradeSoundSelectorClientBehavior -> data factory RVA 0x00252C64 -> ctor RVA 0x004CB9F3; primary vptr store RVA 0x004CB9FF.
class UpgradeSoundSelectorClientBehaviorModuleData : public ModuleData { public: UpgradeSoundSelectorClientBehaviorModuleData(EmitVtableTag *); virtual ~UpgradeSoundSelectorClientBehaviorModuleData(); };
// ?<UpgradeSoundSelectorClientBehaviorModuleData::UpgradeSoundSelectorClientBehaviorModuleData> absent-from-retail
UpgradeSoundSelectorClientBehaviorModuleData::UpgradeSoundSelectorClientBehaviorModuleData(EmitVtableTag *) {}

