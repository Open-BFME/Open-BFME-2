// cl: /DNDEBUG /MD
//
// Two DevastateSpecialPower overrides on the special-power interface vtable
// 0x00C5E430 its matched ctor 0x004C81E3 installs at +0x10, compiled with that
// subobject this. Names are by address.
//
// ?doSpecialPower@DevastateSpecialPower@@UAEXH@Z, retail 0x004C822C, 68 bytes:
// slot 10 (the argument unread); the untargeted use only reports "Error!
// Devastate Power requires either a target object or location" through the
// Debug singleton (the GameLODManagerGetAudioLODIndex.cpp reporting shape).
// ?doSpecialPowerAtObject@DevastateSpecialPower@@UAEXPAVObject@@H@Z, retail 0x004C82D1,
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

class SpecialPowerModuleInterface
{
public:
	virtual void gap0() = 0; virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0;
	virtual void gap4() = 0; virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void gap8() = 0; virtual void gap9() = 0;
	virtual void doSpecialPower(int options) = 0;
	virtual void doSpecialPowerAtObject(Object *target, int options) = 0;
	virtual void slot12(const Coord3D *pos, int options) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
};

class DevastateSpecialPower : public SpecialPowerModule
{
public:
	using SpecialPowerModuleInterface::slot12;
	virtual void doSpecialPower(int options);
	virtual void doSpecialPowerAtObject(Object *target, int options);
};

// ?doSpecialPower@DevastateSpecialPower@@UAEXH@Z @0x004C822C
void DevastateSpecialPower::doSpecialPower(int)
{
	if (bfmeRva000387C0())
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Error! Devastate Power requires either a target object or location").CrashDone(2);
	}
}

// ?doSpecialPowerAtObject@DevastateSpecialPower@@UAEXPAVObject@@H@Z @0x004C82D1
void DevastateSpecialPower::doSpecialPowerAtObject(Object *target, int options)
{
	slot12(target->getPosition(), options);
}
