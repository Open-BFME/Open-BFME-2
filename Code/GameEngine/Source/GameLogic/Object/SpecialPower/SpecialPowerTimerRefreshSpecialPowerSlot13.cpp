// cl: /DNDEBUG /MD
//
// SpecialPowerTimerRefreshSpecialPower primary slot 13 (vtable 0x00BEFDB4),
// retail 0x004C38B3 (29 bytes): the SpecialPowerModule slot-13 base 0x00493EA7
// (the slot-13 entry of 23 special-power vtables, SpecialPowerModule's own
// 0x00C4E868 among them; it works on the Object it is given, pinned by
// address), then the rowed Object::rva0028B72A on that Object. Named by the
// base's address.
#include "../../../../Include/Common/BitFlagsTemplate.h"
#include "../object.h"
class ModuleData;
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleClass.h"
class SpecialPowerTimerRefreshSpecialPower : public SpecialPowerModule
{
public:
	virtual void ApplyPowerToObject(Object *obj, int value, const BitFlags<11> *disabled);
};
void SpecialPowerTimerRefreshSpecialPower::ApplyPowerToObject(Object *obj, int value, const BitFlags<11> *disabled)
{
	SpecialPowerModule::ApplyPowerToObject(obj, value, disabled);
	obj->rva0028B72A();
}
