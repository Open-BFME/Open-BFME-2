// cl: /O1 /MD
// ??_GRva00497DD6@@UAEPAXI@Z @0x00497DBA 28B
// Deleting dtor calls rowed ??1Rva00497DD6@@UAE@XZ at 0x00497DD6 then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x00497DD6; retail push esi call ??1 test flag delete ret 4.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class BattlePlanUpdateModuleData : public ModuleData { public: BattlePlanUpdateModuleData(EmitVtableTag *); virtual ~BattlePlanUpdateModuleData(); };
// ?<BattlePlanUpdateModuleData::BattlePlanUpdateModuleData> absent-from-retail
BattlePlanUpdateModuleData::BattlePlanUpdateModuleData(EmitVtableTag *) {}
