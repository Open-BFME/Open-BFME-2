// cl: /MD /Ireference/shims/moduledata
// Each class redeclares its public virtual destructor and defines it locally,
// which emits the scalar deleting destructor in this TU; the dtor call inside
// resolves through that destructor's own row (same pattern as spec_gdtor).

#include "Common/Snapshot.h"

struct EmitVtableTag;

// ??_GPassiveAreaEffectBehaviorModuleData@@UAEPAXI@Z @0x484e8d
class PassiveAreaEffectBehaviorModuleData : public Snapshot { public: PassiveAreaEffectBehaviorModuleData(EmitVtableTag *); virtual ~PassiveAreaEffectBehaviorModuleData(); };
// ?<PassiveAreaEffectBehaviorModuleData::PassiveAreaEffectBehaviorModuleData> absent-from-retail
PassiveAreaEffectBehaviorModuleData::PassiveAreaEffectBehaviorModuleData(EmitVtableTag *) {}

