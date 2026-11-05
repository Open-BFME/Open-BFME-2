// cl: /DNDEBUG /MD
//
// Two DevastateSpecialPower overrides on the special-power interface vtable
// 0x00C5E430 its matched ctor 0x004C81E3 installs at +0x10, compiled with that
// subobject this. Unsigned command options keep these overrides in the
// canonical interface's native slots and preserve that receiver.
//
// ?doSpecialPower@DevastateSpecialPower@@UAEXI@Z, retail 0x004C822C, 68 bytes:
// slot 10 (the argument unread); the untargeted use only reports "Error!
// Devastate Power requires either a target object or location" through the
// Debug singleton (the GameLODManagerGetAudioLODIndex.cpp reporting shape).
// ?doSpecialPowerAtObject@DevastateSpecialPower@@UAEXPAVObject@@I@Z, retail 0x004C82D1,
// 20 bytes: slot 11; slot 12 at the target Object's position (+0x38) with the
// same second argument.

typedef int Int;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../object.h"

#include "../../../Common/debug.h"
extern Debug *theDebug;

Bool bfmeRva000387C0(void);

class ModuleData;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
};

class DevastateSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *target, unsigned int options);
};

// ?doSpecialPower@DevastateSpecialPower@@UAEXI@Z @0x004C822C
void DevastateSpecialPower::doSpecialPower(unsigned int)
{
	if (bfmeRva000387C0())
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Error! Devastate Power requires either a target object or location").CrashDone(2);
	}
}

// ?doSpecialPowerAtObject@DevastateSpecialPower@@UAEXPAVObject@@I@Z @0x004C82D1
void DevastateSpecialPower::doSpecialPowerAtObject(Object *target, unsigned int options)
{
	doSpecialPowerAtLocation(target->getPosition(), options);
}
