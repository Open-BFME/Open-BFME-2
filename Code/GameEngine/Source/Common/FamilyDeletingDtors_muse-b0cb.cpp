// cl: /MD
// ??_GStatusBitsUpgradeIfEldestKindofModuleData@@UAEPAXI@Z @0x00255740 28B
// Deleting dtor slot 0 of vtable 0x00BF25D8; calls the rowed ??1 at 0x0025575C.
struct EmitVtableTag;

// Retail's table is the UpgradeModuleData shape: ModuleData's 30 slots with slot 10 true.
#include "../../Include/GameLogic/Module/Rva00253487Base.h"

class StatusBitsUpgradeIfEldestKindofModuleData : public Rva00253487Base { public: StatusBitsUpgradeIfEldestKindofModuleData(EmitVtableTag *); virtual ~StatusBitsUpgradeIfEldestKindofModuleData(); };
// ?<StatusBitsUpgradeIfEldestKindofModuleData::StatusBitsUpgradeIfEldestKindofModuleData> absent-from-retail
StatusBitsUpgradeIfEldestKindofModuleData::StatusBitsUpgradeIfEldestKindofModuleData(EmitVtableTag *) {}
