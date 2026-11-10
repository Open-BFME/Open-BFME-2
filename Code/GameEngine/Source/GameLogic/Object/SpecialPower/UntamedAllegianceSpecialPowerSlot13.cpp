// cl: /DNDEBUG /MD
//
// UntamedAllegianceSpecialPower primary slot 13 (vtable 0x00C5E0E4), retail
// 0x004C7BB0 (83 bytes): nothing for an Object with status 0x39; otherwise
// the SpecialPowerModule slot-13 base 0x00493EA7 (pinned by address), then
// the Object is taken over for our Object: the pinned
// Object::defect(ours, false), Object 0x002930A9 with 0 (pinned by
// address; it starts from the Object's producer, +0x78), the rowed
// setProducer(ours) and status 0x3E cleared. Named by the base's address.
#include "../../../../Include/Common/BitFlagsTemplate.h"
enum ObjectStatusTypes
{
	OBJECT_STATUS_39 = 0x39,
	OBJECT_STATUS_3E = 0x3e
};
#include "../object.h"
class ModuleData;
class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void ApplyPowerToObject(Object *obj, int value, const BitFlags<11> *disabled);
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class UntamedAllegianceSpecialPower : public SpecialPowerModule
{
public:
	virtual void ApplyPowerToObject(Object *obj, int value, const BitFlags<11> *disabled);
};
void UntamedAllegianceSpecialPower::ApplyPowerToObject(Object *obj, int value, const BitFlags<11> *disabled)
{
	if (obj->testStatus(OBJECT_STATUS_39))
		return;
	SpecialPowerModule::ApplyPowerToObject(obj, value, disabled);
	Object *self = m_object;
	obj->defect(self, false);
	obj->rva002930A9(0);
	obj->setProducer(self);
	obj->setStatus(OBJECT_STATUS_3E, false);
}
