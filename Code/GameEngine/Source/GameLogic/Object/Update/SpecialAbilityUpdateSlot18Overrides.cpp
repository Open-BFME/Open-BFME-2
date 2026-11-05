// cl: /DNDEBUG /MD
//
// Slot-18 overrides of the two SpecialAbilityUpdate subclasses whose slot-22
// overrides live in SpecialAbilityUpdateSlot22Overrides.cpp (same placeholder
// class names: matched ctors Rva00492179 and Rva00492402; their slot-2 name
// getters return "HeroModeSpecialAbilityUpdate" and
// "WeaponSetSpecialAbilityUpdate"). The SpecialAbilityUpdate vtable
// 0x00C3FBA8 holds the ICF-shared +0x2C clearer 0x004C12CB in slot 18; each
// override clears +0x2C itself and then drops the weapon set flag its slot 22
// raised. Slot 18 keeps address names (its base slot is a folded clearer);
// the slot-17 override below is triggerAbilityEffect (calls the base first).
// Retail 0x0049226C (15 bytes): Rva00492179 clears flag 0x1B.
// Retail 0x0049251D (38 bytes): Rva00492402 clears flag 0x12 or 0x13 for
// module data +0xCC == 1 or 2.
// Rva00492402 also overrides slot 17 (retail 0x004924BA, 31 bytes): the base
// SpecialAbilityUpdate slot 17 (pinned triggerAbilityEffect) and then +0x2C = frame +
// module data +0xC8.

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
#include "../object.h"
class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerUpdateInterface.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void triggerAbilityEffect();
protected:
	unsigned char m_pad24[0x2C - 0x24];
	unsigned int m_2C; // +0x2C
	unsigned char m_pad30[0x88 - 0x30];
};
class Rva00492179 : public SpecialAbilityUpdate
{
public:
	virtual void rva0049226C();
};
// ?rva0049226C@Rva00492179@@UAEXXZ @0x0049226C
void Rva00492179::rva0049226C()
{
	m_2C = 0;
	m_object->clearWeaponSetFlag((WeaponSetType)0x1B);
}
class Rva00492402ModuleData
{
public:
	unsigned char m_pad[0xC8];
	unsigned int m_C8; // +0xC8
	int m_CC; // +0xCC
};
class Rva00492402 : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	virtual void rva0049251D();
};
// ?triggerAbilityEffect@Rva00492402@@UAEXXZ @0x004924BA
void Rva00492402::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const Rva00492402ModuleData *data = (const Rva00492402ModuleData *)m_moduleData;
	m_2C = data->m_C8 + TheGameLogic->getFrame();
}
// ?rva0049251D@Rva00492402@@UAEXXZ @0x0049251D
void Rva00492402::rva0049251D()
{
	m_2C = 0;
	const Rva00492402ModuleData *data = (const Rva00492402ModuleData *)m_moduleData;
	Object *object = m_object;
	if (data->m_CC == 1)
		object->clearWeaponSetFlag((WeaponSetType)0x12);
	else if (data->m_CC == 2)
		object->clearWeaponSetFlag((WeaponSetType)0x13);
}
