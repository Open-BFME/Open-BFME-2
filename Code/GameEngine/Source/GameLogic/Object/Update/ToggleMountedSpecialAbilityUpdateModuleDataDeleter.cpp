// cl: /O1 /MD

// ??_GToggleMountedSpecialAbilityUpdateModuleData@@UAEPAXI@Z, retail 0x004AE0EF (28B).
// Scalar-deleting destructor slot 0 of vtable 0x00855220; calls rowed ??1 at
// 0x004AE10B then rowed operator delete at 0x0002FD60 (pop-ecx cleanup).
// Identity: vtable installed by rowed ctor at 0x004AE0AC, caller of ??1 is
// this body. The dtor is declared-not-defined so this TU calls it out of
// line through its row. The view derives from the canonical
// SpecialAbilityUpdateModuleData, as the constructor unit's does, so this unit's
// ??_7 is the same full 31-slot table (retail 0x00C55220) the constructor installs.

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

struct EmitVtableTag;

class ToggleMountedSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();
	ToggleMountedSpecialAbilityUpdateModuleData(EmitVtableTag *);
};

// ?<ToggleMountedSpecialAbilityUpdateModuleData::ToggleMountedSpecialAbilityUpdateModuleData> absent-from-retail
ToggleMountedSpecialAbilityUpdateModuleData::ToggleMountedSpecialAbilityUpdateModuleData(EmitVtableTag *)
{
}

void deleteToggleMountedSpecialAbilityUpdateModuleData(ToggleMountedSpecialAbilityUpdateModuleData *toggleMountedSpecialAbilityUpdateModuleData)
{
	delete toggleMountedSpecialAbilityUpdateModuleData;
}
