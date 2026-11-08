// cl: /DNDEBUG /MD
//
// ??0SpawnedModelConditionCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00250A1F, 40 bytes. Behavior-side ctor completing the
// SpawnedModelConditionCreate file-unit (poolkey rowed at 0x250A4E,
// name getter rowed at 0x250A93, behavior instance factory rowed at
// 0x25496D news 0x18 with this ctor as sole raw caller).
//
// Shape: frameless ctor over the rowed CreateModule base 0x4B8CF7. The compiler
// installs the class's three tables at +0/+0xC/+0x10.


#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

// Retail's tables: 0x00BEFA7C (12 slots), 0x00BEF9C0 at +0x0C (the table 15 classes fold onto) and
// 0x00BEF9B0 at +0x10: onCreate is empty (0x000B3FD0), the rest are CreateModule's shapes.
class SpawnedModelConditionCreate : public CreateModule
{
public:
	SpawnedModelConditionCreate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onCreate() {}
};

// ??0SpawnedModelConditionCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00250A1F
SpawnedModelConditionCreate::SpawnedModelConditionCreate(Thing *thing, const ModuleData *moduleData) :
	CreateModule(thing, moduleData)
{
}
