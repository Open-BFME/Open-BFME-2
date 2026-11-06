// cl: /DNDEBUG /MD
//
// ?findSpecialPowerModuleInterface@Object@@QBEPAVSpecialPowerModuleInterface@@W4SpecialPowerType@@@Z, retail 0x00290E22, 69 bytes.
// Object::findSpecialPowerModuleInterface: scans the null-terminated BehaviorModule
// list at +0x244 via the +0x0C interface sub-object (slot 0x20 getSpecialPower),
// then each SpecialPowerModuleInterface at slot 0x18 getSpecialPowerTemplate,
// chases Overridable::friend_getFinalOverride (rowed 0x00288609) and compares
// SpecialPowerTemplate type at +0x1C to the caller's SpecialPowerType.
// Donor is BFME1 Object::findSpecialPowerModuleInterface
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp,
// m_behaviors +0x1F0, getSpecialPower slot 7, getSpecialPowerTemplate slot 6,
// getSpecialPowerType virtual); BFME2 shifts behaviors to +0x244, getSpecialPower
// to slot 8, and inlines the type as final-override +0x1C (name at +0x10 per
// 0x003B11D2, type at +0x1C per 0x0033537F push). Callers pass small int types
// (0x2D at 0x003BCCF6 0x003C6A48, 0x8B at 0x002922B1, 0x1D at 0x0029CA39) and use
// the result as SpecialPowerModuleInterface (slot 1 isReady, slot 10
// doSpecialPower, slot 11 doSpecialPowerAtObject). Returns the first match or null.

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"

class SpecialPowerModuleInterface;

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../Include/GameLogic/Module/SpecialPowerModule.h"

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

SpecialPowerModuleInterface *Object::findSpecialPowerModuleInterface(SpecialPowerType type) const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		SpecialPowerModuleInterface *sp = (*behaviorModule)->getSpecialPower();
		if (!sp)
			continue;
		const SpecialPowerTemplate *specialPowerTemplate = sp->getSpecialPowerTemplate();
		if (!specialPowerTemplate)
			continue;
		const Overridable *finalOverride = specialPowerTemplate->friend_getFinalOverride();
		if (((const SpecialPowerTemplate *)finalOverride)->m_type == type)
			return sp;
	}
	return 0;
}
