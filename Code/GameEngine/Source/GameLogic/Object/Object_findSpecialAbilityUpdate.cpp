// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?findSpecialAbilityUpdate@Object@@QBEPAVSpecialAbilityUpdate@@W4SpecialPowerType@@@Z
// @0x0028BD92 69B: Zero Hour's and BFME1's Object::findSpecialAbilityUpdate
// (BFME1 0x001BF750: same getSpecialPowerType test over the behavior modules). Object scan of +0x244
// module array; each +0x0C sub-object slot25 (+0x64) yields B; when B non-null
// and its slot1 (+0x04) bool true, B-0x20 is SpecialAbilityUpdate whose rowed int
// getter is compared to the int arg, returning adjusted B on match else null.
// Evidence: same +0x244/+0x0C/slot25 shape as rowed rva0028BD5D at 0x0028BD5D
// and siblings rva0028BD3A/BD17/BCF4; retail lea ecx [eax+0x0C] plus calls
// [eax+0x64] [eax+0x04] 0x0044EF2C plus cmp [esp+0x0C] prove slots and arg.
class Rva0028BD92Result
{
public:
	virtual void slot00();
	virtual bool slot01();
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"



enum SpecialPowerType {};
#include "../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
};

SpecialAbilityUpdate *Object::findSpecialAbilityUpdate(SpecialPowerType type) const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		Rva0028BD92Result *r = static_cast<Rva0028BD92Result *>((*behaviorModule)->slot25());
		if (r != 0 && r->slot01())
		{
			SpecialAbilityUpdate *adj = reinterpret_cast<SpecialAbilityUpdate *>(reinterpret_cast<char *>(r) - 0x20);
			if (adj->getSpecialPowerType() == type)
				return adj;
		}
	}
	return 0;
}
