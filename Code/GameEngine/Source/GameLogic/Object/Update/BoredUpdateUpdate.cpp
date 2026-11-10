// cl: /O1 /DNDEBUG /MD /GX
//
// ?update@BoredUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x0049680F..0x0049699B (396 bytes): BoredUpdate::update, slot 0 of
// its UpdateModuleInterface vftable 0x0084F550 (the primary vftable 0x0084F55C
// holds the deleting dtor 0x004967F3 and the pool key 0x004966B9; the
// region sits between the ctor 0x00496791 and the data dtor 0x0049699B).
// WorldBuilder twin 0x011EF420 (callgraph score 3.0). With a special power
// template (+0x18) on a live object: counts the scan timer +0x20 down (the
// countdown 0x004B25AF reloads it from the data's +0x08) and unless the
// data's +0x14 flag is clear and the object is kind 0x25 or 0x3D; then if the
// data's +0x10 object filter is valid fires the power at the closest object
// within +0x0C passing 0x002614DF (not itself) relationship 4 and that filter
// (ActionManager::canDoSpecialPowerAtObject then Object 0x0028E01F) else at
// no target (canDoSpecialPower then Object 0x0028DF48). Never sleeps.
// The countdown is defined first in this unit: retail keeps the kind result
// in DL across its call, which cl only does for a callee it has already
// compiled. Its only caller is this body; ICF kept the identical copy in the
// EntEnragedUpdate region (0x004B25AF), rowed under its placeholder name.
class Object;
class Player;
class SpecialPowerTemplate;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
#include "../../../../Include/GameLogic/Rva00260EB1Filter.h"

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
#include "../../../../Include/GameLogic/Rva002614ECFilter.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

enum KindOfType
{
	KINDOF_0x25 = 0x25,
	KINDOF_0x3D = 0x3D
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

#include "../../../../Include/GameLogic/ActionManager.h"
extern ActionManager *TheActionManager;

#include "../object.h"

#include "../../../../Include/GameLogic/ObjectFilter.h"

class BoredUpdateModuleData
{
public:
	unsigned char m_pad00[0x08];
	int m_scanDelay;				// +0x08
	float m_scanRange;				// +0x0C
	ObjectFilter m_filter;				// +0x10
	bool m_ignoreKinds;				// +0x14
	const SpecialPowerTemplate *m_specialPower;	// +0x18
};

// The scan countdown 0x004B25AF (rowed under its placeholder name; ICF kept
// another unit's identical copy).
class BfmeOwnerCH
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeReload;					// +0x08
};

class Gen_00291BB0
{
public:
	unsigned char bfmeTick(void);

private:
	int m_bfmeTag;						// +0x00
	BfmeOwnerCH *m_bfmeOwner;				// +0x04
	int m_bfmeGap[6];					// +0x08
	int m_bfmeCount;					// +0x20
};

// ?bfmeTick@Gen_00291BB0@@QAEEXZ
unsigned char Gen_00291BB0::bfmeTick(void)
{
	int count = m_bfmeCount;

	if (count == 0)
	{
		m_bfmeCount = m_bfmeOwner->m_bfmeReload;

		return 1;
	}

	m_bfmeCount = count - 1;

	return 0;
}

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BoredUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	const BoredUpdateModuleData *getBoredUpdateModuleData() const
	{
		return (const BoredUpdateModuleData *)m_moduleData;
	}
	int m_scanTimer;				// +0x20
};

UpdateSleepTime BoredUpdate::update()
{
	const BoredUpdateModuleData *data = getBoredUpdateModuleData();
	if (data->m_specialPower == 0)
		return UPDATE_SLEEP_NONE;
	Object *obj = getObject();
	if (obj->isEffectivelyDead())
		return UPDATE_SLEEP_NONE;
	bool ok = data->m_ignoreKinds || !(obj->isKindOf(KINDOF_0x25) || obj->isKindOf(KINDOF_0x3D));
	if (!((Gen_00291BB0 *)this)->bfmeTick() || !ok)
		return UPDATE_SLEEP_NONE;
	if (data->m_filter.isValid())
	{
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), data->m_scanRange, 0,
			Rva002614ECFilter(&data->m_filter, obj->getControllingPlayer(), true)
				.link(&Rva00260EB1Filter(obj, 4, false))->link(&Rva002614DFFilter(obj)));
		if (target && TheActionManager->canDoSpecialPowerAtObject(getObject(), target, CMD_FROM_AI, data->m_specialPower, 2, true))
			obj->doSpecialPowerAtObject(data->m_specialPower, target, 2, false);
	}
	else
	{
		if (TheActionManager->canDoSpecialPower(getObject(), data->m_specialPower, CMD_FROM_AI, 2, true))
			obj->doSpecialPower(data->m_specialPower, 2, false);
	}
	return UPDATE_SLEEP_NONE;
}
