// cl: /O1 /MD
// ??_GRandomSoundSelectorClientBehaviorModuleData@@UAEPAXI@Z @0x002578C2 28B
// Deleting dtor slot 0 of vtable 0x007F42A8; calls rowed ??1 at 0x002578DE then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class RandomSoundSelectorClientBehaviorModuleData { public: RandomSoundSelectorClientBehaviorModuleData(EmitVtableTag *); virtual ~RandomSoundSelectorClientBehaviorModuleData(); };
// ?<RandomSoundSelectorClientBehaviorModuleData::RandomSoundSelectorClientBehaviorModuleData> absent-from-retail
RandomSoundSelectorClientBehaviorModuleData::RandomSoundSelectorClientBehaviorModuleData(EmitVtableTag *) {}
// ??_GActiveBodyModuleData@@UAEPAXI@Z @0x004BF9B5 28B
// Deleting dtor slot 0 of vtable 0x0085AFB8; calls rowed ??1 at 0x00256CB0 then rowed operator delete at 0x0002FD60.
// Slot 7 is ActiveBodyModuleData's rowed `true` (ActiveBodyModuleData.h defines it).
class ActiveBodyModuleData : public ModuleData { public: ActiveBodyModuleData(EmitVtableTag *); virtual ~ActiveBodyModuleData(); virtual bool slot07() const; };
// ?<ActiveBodyModuleData::ActiveBodyModuleData> absent-from-retail
ActiveBodyModuleData::ActiveBodyModuleData(EmitVtableTag *) {}
