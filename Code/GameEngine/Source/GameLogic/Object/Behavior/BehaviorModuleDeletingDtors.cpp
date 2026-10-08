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

// TerrainResourceClientBehavior's verified deleting wrapper now comes from
// TerrainResourceClientBehaviorSlots.cpp, alongside its real destructor.
// Removing the empty scaffold also removes its conflicting vtable copy.

// ??_GCastleBehavior@@UAEPAXI@Z @0x00399354 28B: slot 0 of vtable 0x00C1A780; calls ??1 at 0x0039857D.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x00398538 uses class-name string "CastleBehavior".
class CastleBehavior { public: __declspec(noinline) virtual ~CastleBehavior(); };
// ??1CastleBehavior@@UAE@XZ present-unmatched
CastleBehavior::~CastleBehavior() {}
void CastleBehavior_Delete(CastleBehavior *p) { delete p; }

// ??_GInstantDeathBehaviorModuleData@@UAEPAXI@Z @0x0045D271 28B: slot 0 of vtable 0x00C41F28; calls ??1 at 0x0045D28D.
// Owner evidence (audited 2026-09-26): retail registration InstantDeathBehavior -> data factory RVA 0x0024B213 -> ctor RVA 0x0045D176; primary vptr store RVA 0x0045D189.
class InstantDeathBehaviorModuleData { public: __declspec(noinline) virtual ~InstantDeathBehaviorModuleData(); };
// ??1InstantDeathBehaviorModuleData@@UAE@XZ present-unmatched
InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData() {}
void InstantDeathBehaviorModuleData_Delete(InstantDeathBehaviorModuleData *p) { delete p; }

// ??_GStancesBehavior@@UAEPAXI@Z @0x0045F068 28B: slot 0 of vtable 0x00C424DC; calls ??1 at 0x0045F001.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0045EFBC uses class-name string "StancesBehavior".
class StancesBehavior { public: __declspec(noinline) virtual ~StancesBehavior(); };
// ??1StancesBehavior@@UAE@XZ present-unmatched
StancesBehavior::~StancesBehavior() {}
void StancesBehavior_Delete(StancesBehavior *p) { delete p; }

// ??_GPropagandaTowerBehaviorModuleData@@UAEPAXI@Z @0x00481BB2 28B: slot 0 of vtable 0x00C49288; calls ??1 at 0x00481BCE.
// Owner evidence (audited 2026-09-26): retail registration PropagandaTowerBehavior -> data factory RVA 0x0024C21B -> ctor RVA 0x0048197C; primary vptr store RVA 0x00481988.
class PropagandaTowerBehaviorModuleData { public: __declspec(noinline) virtual ~PropagandaTowerBehaviorModuleData(); };
// ??1PropagandaTowerBehaviorModuleData@@UAE@XZ present-unmatched
PropagandaTowerBehaviorModuleData::~PropagandaTowerBehaviorModuleData() {}
void PropagandaTowerBehaviorModuleData_Delete(PropagandaTowerBehaviorModuleData *p) { delete p; }

// ??_GSlaveWatcherBehaviorModuleData@@UAEPAXI@Z @0x004846DE 28B: slot 0 of vtable 0x00C4A298; calls ??1 at 0x004846FA.
// Owner evidence (audited 2026-09-26): retail registration SlaveWatcherBehavior -> data factory RVA 0x0024C660 -> ctor RVA 0x004846C7; primary vptr store RVA 0x004846CB.
class SlaveWatcherBehaviorModuleData { public: __declspec(noinline) virtual ~SlaveWatcherBehaviorModuleData(); };
// ??1SlaveWatcherBehaviorModuleData@@UAE@XZ present-unmatched
SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData() {}
void SlaveWatcherBehaviorModuleData_Delete(SlaveWatcherBehaviorModuleData *p) { delete p; }
