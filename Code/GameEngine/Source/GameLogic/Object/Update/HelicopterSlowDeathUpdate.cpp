// cl: /O1 /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
// BFME 2 has no HelicopterSlowDeathBehavior: game.dat holds no
// "HelicopterSlowDeathBehavior" module string and no native row of the class
// (LINK-072). This unit used to carry Zero Hour's port. Its unrowed bodies
// referenced 16 names no object defines, among them three Zero Hour
// SlowDeathBehavior members retail does not have under those names: the
// destructor (retail's is rowed at 0x0045D39E), crc (slot 1 of the primary
// table 0x00C42040 is the shared 0x00497805) and loadPostProcess.
//
// The one retail body the port emitted is SlowDeathBehavior::isDieApplicable,
// 0x0045D49E (22 B), slot 2 of the slow-death interface table 0x00C42020 that
// retail's destructor 0x0045D39E installs at +0x24: `this` is that interface,
// so the module data and the object are read at -0x20 and -0x1C, and the call
// goes to DieMuxData::isDieApplicable (0x004CE588) on the module data's
// DieMuxData at +8. It is defined here as an ordinary out-of-line override over
// bounded declarations (the HordeUpdate repair under LINK-072); this unit emits
// no vtable. The interface's member names follow the Zero Hour donor.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"
#include "../../../../Include/GameLogic/Module/SlowDeathBehaviorModuleData.h"

class DamageInfo;

class SlowDeathBehaviorInterface
{
public:
	virtual void beginSlowDeath(const DamageInfo *damageInfo) = 0;
	virtual int getProbabilityModifier(const DamageInfo *damageInfo) const = 0;
	virtual bool isDieApplicable(const DamageInfo *damageInfo) const = 0;
};

class SlowDeathBehavior : public UpdateModule, public DieModuleInterface, public SlowDeathBehaviorInterface
{
public:
	virtual bool isDieApplicable(const DamageInfo *damageInfo) const;

protected:
	const SlowDeathBehaviorModuleData *getSlowDeathBehaviorModuleData() const
	{
		return (const SlowDeathBehaviorModuleData *)getModuleData();
	}
};

bool SlowDeathBehavior::isDieApplicable(const DamageInfo *damageInfo) const
{
	return getSlowDeathBehaviorModuleData()->m_dieMuxData.isDieApplicable(getObject(), damageInfo);
}
