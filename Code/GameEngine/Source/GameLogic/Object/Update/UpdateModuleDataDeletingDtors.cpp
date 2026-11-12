// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// Transport uses the shared ModuleData interface. The other minimal views
// emit wrappers without claiming complete class layouts.
// Destructor definitions are supplied by their verified providers.

#include <new>
#include "../../../../Include/Common/ModuleData.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

struct EmitVtableTag;

// ??_GTransportAIUpdateModuleData@@UAEPAXI@Z @0x0026E67D 28B: slot 0 of vtable 0x00BFA288; calls ??1 at 0x0026E1FC.
// Owner evidence (audited 2026-09-26): retail registration TransportAIUpdate -> data factory RVA 0x0024BDF2 -> ctor RVA 0x0026E5D7; primary vptr store RVA 0x0026E5F2; constructor also used by AIUpdateInterface, HordeAIUpdate, HordeWorkerAIUpdate (no exclusive owner claim).
class TransportAIUpdateModuleData : public ModuleData { public: TransportAIUpdateModuleData(EmitVtableTag *); virtual ~TransportAIUpdateModuleData(); virtual bool isAiModuleData() const { return true; } };
// ?<TransportAIUpdateModuleData::TransportAIUpdateModuleData> absent-from-retail
inline TransportAIUpdateModuleData::TransportAIUpdateModuleData(EmitVtableTag *) {}
// ?_EmitVtable@TransportAIUpdateModuleData@@SAXPAU1@@Z absent-from-retail
void TransportAIUpdateModuleData_EmitVtable(TransportAIUpdateModuleData *p) { new (p) TransportAIUpdateModuleData(0); delete p; }

// ??_GDeployStyleAIUpdateModuleData@@UAEPAXI@Z @0x00255F54 28B: slot 0 of vtable 0x00BF3440; calls ??1 at 0x00255F70.
// Owner evidence (audited 2026-09-26): retail registration DeployStyleAIUpdate -> data factory RVA 0x0025517E -> ctor RVA 0x00255154; primary vptr store RVA 0x0025515E.
class DeployStyleAIUpdateModuleData : public TransportAIUpdateModuleData { public: DeployStyleAIUpdateModuleData(EmitVtableTag *); virtual ~DeployStyleAIUpdateModuleData(); };
// ?<DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData> absent-from-retail
inline DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData(EmitVtableTag *) : TransportAIUpdateModuleData(0) {}
// ?_EmitVtable@DeployStyleAIUpdateModuleData@@SAXPAU1@@Z absent-from-retail
void DeployStyleAIUpdateModuleData_EmitVtable(DeployStyleAIUpdateModuleData *p) { new (p) DeployStyleAIUpdateModuleData(0); delete p; }

// ??_GSlavedUpdateModuleData@@UAEPAXI@Z @0x00255FA5 28B: slot 0 of vtable 0x00BF34C0; calls ??1 at 0x00255FC1.
// Owner evidence (audited 2026-09-26): retail registration SlavedUpdate -> data factory RVA 0x00255340 -> ctor RVA 0x002552D7; primary vptr store RVA 0x002552DE.
class SlavedUpdateModuleData { public: SlavedUpdateModuleData(EmitVtableTag *); virtual ~SlavedUpdateModuleData(); };
// ?<SlavedUpdateModuleData::SlavedUpdateModuleData> absent-from-retail
SlavedUpdateModuleData::SlavedUpdateModuleData(EmitVtableTag *) {}

// ??_GLaserUpdateModuleData@@UAEPAXI@Z @0x003631CC 28B: slot 0 of vtable 0x00C17120; calls ??1 at 0x003631E8.
// Owner evidence (audited 2026-09-26): retail registration LaserUpdate -> data factory RVA 0x0024D55A -> ctor RVA 0x00363147; primary vptr store RVA 0x0036314E.
class LaserUpdateModuleData { public: LaserUpdateModuleData(EmitVtableTag *); virtual ~LaserUpdateModuleData(); };
// ?<LaserUpdateModuleData::LaserUpdateModuleData> absent-from-retail
LaserUpdateModuleData::LaserUpdateModuleData(EmitVtableTag *) {}

// ??_GArrowStormUpdateModuleData@@UAEPAXI@Z @0x00490679 28B: slot 0 of vtable 0x00C4D5A0; calls ??1 at 0x00490695.
// Owner evidence (audited 2026-09-26): retail registration ArrowStormUpdate -> data factory RVA 0x0024D601 -> ctor RVA 0x00490639; primary vptr store RVA 0x00490647.
class ArrowStormUpdateModuleData : public SpecialAbilityUpdateModuleData { public: ArrowStormUpdateModuleData(EmitVtableTag *); virtual ~ArrowStormUpdateModuleData(); };
// ?<ArrowStormUpdateModuleData::ArrowStormUpdateModuleData> absent-from-retail
inline ArrowStormUpdateModuleData::ArrowStormUpdateModuleData(EmitVtableTag *) {}
// ?_EmitVtable@ArrowStormUpdateModuleData@@SAXPAU1@@Z absent-from-retail
void ArrowStormUpdateModuleData_EmitVtable(ArrowStormUpdateModuleData *p) { new (p) ArrowStormUpdateModuleData(0); delete p; }

// ??_GAutoPickUpUpdateModuleData@@UAEPAXI@Z @0x00496460 28B: slot 0 of vtable 0x00C4F108; calls ??1 at 0x0049647C.
// Owner evidence (audited 2026-09-26): retail registration AutoPickUpUpdate -> data factory RVA 0x0024E099 -> ctor RVA 0x00496308; primary vptr store RVA 0x00496321.
class AutoPickUpUpdateModuleData : public ModuleData { public: AutoPickUpUpdateModuleData(EmitVtableTag *); virtual ~AutoPickUpUpdateModuleData(); };
// ?<AutoPickUpUpdateModuleData::AutoPickUpUpdateModuleData> absent-from-retail
AutoPickUpUpdateModuleData::AutoPickUpUpdateModuleData(EmitVtableTag *) {}

