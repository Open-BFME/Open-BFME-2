// cl: /O1 /MD
// ??_GCommandPointsUpgradeModuleData@@UAEPAXI@Z @0x0025593D 28B
// Deleting dtor slot 0 of vtable 0x007F2658; calls rowed ??1 at 0x00255959 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Both classes derive from the canonical bases their constructor units use
// (CommandPointsUpgradeModuleDataCtor.cpp: Rva00253487Base.h;
// RefundDieModuleDataCtor.cpp: DestroyDieModuleData.h), so this unit's copies
// of their 31-slot vftables (retail 0x00BF2658, 0x00BF0660) are the same tables
// instead of one-slot ones.
#include "../../Include/GameLogic/Module/Rva00253487Base.h"
#include "../../Include/GameLogic/Module/DestroyDieModuleData.h"

class CommandPointsUpgradeModuleData : public Rva00253487Base { public: CommandPointsUpgradeModuleData(EmitVtableTag *); virtual ~CommandPointsUpgradeModuleData(); };
// ?<CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData> absent-from-retail
CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData(EmitVtableTag *) {}
// ??_GRefundDieModuleData@@UAEPAXI@Z @0x0025504B 28B
// Deleting dtor slot 0 of vtable 0x007F0660; calls rowed ??1 at 0x00255067 then rowed operator delete at 0x0002FD60.
class RefundDieModuleData : public DestroyDieModuleData { public: RefundDieModuleData(EmitVtableTag *); virtual ~RefundDieModuleData(); };
// ?<RefundDieModuleData::RefundDieModuleData> absent-from-retail
RefundDieModuleData::RefundDieModuleData(EmitVtableTag *) {}
