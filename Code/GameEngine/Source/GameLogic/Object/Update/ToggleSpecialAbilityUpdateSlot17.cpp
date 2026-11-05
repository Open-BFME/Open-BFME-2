// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Slot-17 overrides of ToggleHiddenSpecialAbilityUpdate (vftable 0x00C552D8)
// and ToggleDeploySpecialAbilityUpdate (vftable 0x00C55370), named by their
// slot-2 name getters (rowed pool keys 0x004AE1CC and 0x004AE502). Each runs
// the base SpecialAbilityUpdate slot 17 (pinned triggerAbilityEffect), then, with
// module data present and the ability state at +0x24 equal to 1, picks the
// class's own slot 23 or 24 by an owner test. The overrides carry the base
// slot's address name (as the HordeSiegeEngineContainRiders overrides do):
// cl 7.1 only places an override in slot 17 under the base's name; the
// method identity itself is not established.
//
// ?triggerAbilityEffect@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ, retail 0x004AE22D, 47 bytes.
// Status 0x10 set: slot 23 (0x004AE2D0), else slot 24 (0x004AE394), as tail
// calls.
//
// ?triggerAbilityEffect@ToggleDeploySpecialAbilityUpdate@@UAEXXZ, retail 0x004AE634, 53 bytes.
// Kind-of 0x64: slot 23 (0x004AE5B8), else slot 24 (0x004AE6D7), each given
// the owner.

class ModuleData;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

#include "../object.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class ToggleHiddenSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	virtual void turnOff();
	virtual void turnOn();
};

// ?triggerAbilityEffect@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ @0x004AE22D
void ToggleHiddenSpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	if (m_moduleData && m_24 == 1)
	{
		if (m_object->testStatus((ObjectStatusTypes)0x10))
			turnOff();
		else
			turnOn();
	}
}

class ToggleDeploySpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	virtual void rva004AE5B8(Object *obj);
	virtual void rva004AE6D7(Object *obj);
};

// ?triggerAbilityEffect@ToggleDeploySpecialAbilityUpdate@@UAEXXZ @0x004AE634
void ToggleDeploySpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	Object *obj = m_object;
	if (m_moduleData && m_24 == 1)
	{
		if (obj->isKindOf((KindOfType)0x64))
			rva004AE5B8(obj);
		else
			rva004AE6D7(obj);
	}
}
