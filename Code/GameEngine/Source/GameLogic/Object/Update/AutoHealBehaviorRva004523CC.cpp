// cl: /MD
//
// ?rva004523CC@AutoHealBehavior@@QAEXXZ, retail 0x004523CC, 29 bytes.
// Gap between 0x004523B6 (stopHealing) and 0x004523F5 (Rva ctor).
// Clears m_stopped at +0x30 then UpgradeMux member at +0x20 via rowed
// giveSelfUpgrade 0x45230C then UpdateModule wake via rowed setWakeFrame
// 0x44DF71 with NONE (1). Caller at 0x451A2D finds AutoHealBehavior by
// nameToKey cached key then calls this when non-null. Layout mirrors the
// rowed AutoHealBehavior ctor 0x452592 (UpdateModule base plus UpgradeMux
// member plus m_28/m_2C/m_30/m_34). Honest address name: method purpose
// unproven beyond activation opposite of stopHealing.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpgradeMux
{
public:
	UpgradeMux();
	void giveSelfUpgrade();

private:
	void *m_vtable;
	unsigned int m_executed;
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class AutoHealBehavior : public UpdateModule
{
public:
	void rva004523CC();

private:
	UpgradeMux m_20;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned char m_30;
	unsigned int m_34;
};

void AutoHealBehavior::rva004523CC()
{
	m_30 = 0;
	m_20.giveSelfUpgrade();
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
