// cl: /MD
// ??_GCivilianSpawnCollideModuleData@@UAEPAXI@Z @0x004BD70E
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class CivilianSpawnCollideModuleData : public ModuleData { public: CivilianSpawnCollideModuleData(EmitVtableTag *); virtual ~CivilianSpawnCollideModuleData(); };
// ?<CivilianSpawnCollideModuleData::CivilianSpawnCollideModuleData> absent-from-retail
CivilianSpawnCollideModuleData::CivilianSpawnCollideModuleData(EmitVtableTag *) {}
// ??_GRankInfo@@UAEPAXI@Z @0x0020021A
class RankInfo { public: RankInfo(EmitVtableTag *); virtual ~RankInfo(); };
// ?<RankInfo::RankInfo> absent-from-retail
RankInfo::RankInfo(EmitVtableTag *) {}
// ??_GSpecialDisguiseUpdateModuleData@@UAEPAXI@Z @0x004B044C
class SpecialDisguiseUpdateModuleData { public: SpecialDisguiseUpdateModuleData(EmitVtableTag *); virtual ~SpecialDisguiseUpdateModuleData(); };
// ?<SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData> absent-from-retail
SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData(EmitVtableTag *) {}
