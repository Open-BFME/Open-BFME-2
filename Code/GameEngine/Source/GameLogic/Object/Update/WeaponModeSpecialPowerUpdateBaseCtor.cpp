// cl: /DNDEBUG /MD /EHsc
//
// ??0WeaponModeSpecialPowerUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z
// retail 0x0058959A, 181 bytes (Ghidra FUN_0098959a). Its identity is
// supported by the pinned direct call from WeaponModeSpecialPowerUpdate at
// 0x00494B38 and by the same base in the SiegeDeploy and Deflect constructors.
// The interface layout follows the converted BFME1 DynamicGeometryInfoUpdate
// and the ZH SpecialPowerUpdateModule/UpdateModule family; BFME2 offsets and
// callees remain governed by retail bytes.

class Thing;
class ModuleData;
class Object;

// BFME2's Snapshot puts GetSnapshotName where Zero Hour spells crc (primary slot 2).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class SpecialPowerInterface
{
public:
	virtual void specialPowerAnchor() = 0;
	// Retail table 0x00C6F248: 8 __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"

class ModuleData
{
public:
	unsigned char m_pad00[8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_pad0C[8];
	unsigned char m_startsPaused;
};

class Rva005890A6
{
public:
	virtual void f0() = 0;
	virtual void f1() = 0;
	virtual float getPercentReady() const = 0;
	// Retail table 0x00C4E2B0: 22 __purecall entries follow.
	virtual void vslot03() = 0;
	virtual void vslot04() = 0;
	virtual void vslot05() = 0;
	virtual void vslot06() = 0;
	virtual void vslot07() = 0;
	virtual void vslot08() = 0;
	virtual void vslot09() = 0;
	virtual void vslot10() = 0;
	virtual void vslot11() = 0;
	virtual void vslot12() = 0;
	virtual void vslot13() = 0;
	virtual void vslot14() = 0;
	virtual void vslot15() = 0;
	virtual void vslot16() = 0;
	virtual void vslot17() = 0;
	virtual void vslot18() = 0;
	virtual void vslot19() = 0;
	virtual void vslot20() = 0;
	virtual void vslot21() = 0;
	virtual void vslot22() = 0;
	virtual void vslot23() = 0;
	virtual void vslot24() = 0;
	void rva0058943A(float value);
	void rva005890A6(bool pause);
	unsigned int m_availableOnFrame;
	int m_pausedCount;
	unsigned int m_pausedOnFrame;
	float m_pausedPercent;
};

class WeaponModeSpecialPowerUpdateBase : public UpdateModule,
	public SpecialPowerInterface,
	public Rva005890A6
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
	virtual ~WeaponModeSpecialPowerUpdateBase();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime when);
};

WeaponModeSpecialPowerUpdateBase::WeaponModeSpecialPowerUpdateBase(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_availableOnFrame = 0;
	m_pausedCount = 0;
	m_pausedOnFrame = 0;
	m_pausedPercent = 0.0f;
	if (!m_moduleData->m_specialPowerTemplate->isSharedNSync())
	{
		rva0058943A(1.0f);
	}
	if (m_moduleData->m_startsPaused != 0)
	{
		rva005890A6(true);
	}
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
