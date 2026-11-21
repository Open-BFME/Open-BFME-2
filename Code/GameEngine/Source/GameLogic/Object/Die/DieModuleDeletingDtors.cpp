// cl: /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// Minimal declarations emit the deleting wrappers without claiming destructor
// bodies; CreateCrateDieModuleData uses its canonical DestroyDieModuleData base
// so its 31-slot vtable matches CreateCrateDieModuleDataCtor/Dtor.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"

struct EmitVtableTag;

// ??_GCreateCrateDieModuleData@@UAEPAXI@Z @0x00257339 28B: slot 0 of vtable 0x00BF40A8; calls ??1 at 0x00257355.
// Owner evidence (audited 2026-09-26): retail registration CreateCrateDie -> data factory RVA 0x0025739D -> ctor RVA 0x002572EE; primary vptr store RVA 0x00257313.
class CreateCrateDieModuleData : public DestroyDieModuleData { public: CreateCrateDieModuleData(EmitVtableTag *); virtual ~CreateCrateDieModuleData(); };
// ?<CreateCrateDieModuleData::CreateCrateDieModuleData> absent-from-retail
CreateCrateDieModuleData::CreateCrateDieModuleData(EmitVtableTag *) {}
