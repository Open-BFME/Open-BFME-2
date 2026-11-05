// cl: /DNDEBUG /MD
// Retail 0x004959FF (44 bytes), primary slot 5 of DemoTrapUpdate.
// Use the approved TU's module hierarchy and accessed Object/data prefixes.
// The callback reads module data at +4, Object at +8, and weapon slots at
// data+0x28/+0x30 selected by the flag at data+0x3C.
#include "../GameLogic/Object/Update/DemoTrapObjectView.h"
#include "../GameLogic/Object/Update/DemoTrapUpdateModuleDataView.h"
#include "../../Include/GameLogic/Module/UpdateModule.h"

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class DemoTrapUpdate : public UpdateModule
{
public:
	DemoTrapUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DemoTrapUpdate();				// 0x00495916, out of line
	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
protected:
	virtual void xfer(Xfer *xfer);				// slot 3
public:
	virtual NameKeyType getModuleNameKey() const;		// slot 4
	virtual void onObjectCreated();				// slot 5
	virtual UpdateSleepTime update();
	const DemoTrapUpdateModuleData *getDemoTrapUpdateModuleData() const
	{
		return (const DemoTrapUpdateModuleData *)m_moduleData;
	}
	Object *getObject() const { return m_object; }
private:
	int m_nextScanFrames;					// +0x20
	bool m_detonated;					// +0x24
};

void DemoTrapUpdate::onObjectCreated()
{
	const DemoTrapUpdateModuleData *data = (const DemoTrapUpdateModuleData *)m_moduleData;
	m_object->setWeaponSetFlag((WeaponSetType)0);
	if (data->m_defaultsToProximityMode)
		m_object->setWeaponLock((WeaponSlotType)data->m_proximityModeWeaponSlot, LOCKED_TEMPORARILY);
	else
		m_object->setWeaponLock((WeaponSlotType)data->m_manualModeWeaponSlot, LOCKED_TEMPORARILY);
}
