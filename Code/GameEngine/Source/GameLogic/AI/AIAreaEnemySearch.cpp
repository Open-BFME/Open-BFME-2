// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva002FF8DD@AI@@QAEPAVObject@@PBVPolygonTrigger@@PAV2@PBVAttackPriorityInfo@@@Z,
// retail 0x002FF8DD (919 bytes): the forward-pinned area enemy search
// AIAttackAreaState::update (0x0034680D) calls thiscall on TheAI with the
// area to guard, the owner and the owner AI's +0x70 attack info.
// WorldBuilder twin 0x00D78F00 (callgraph lead) has the same filter chain
// and flow. An owner that cannot attack finds nothing. The chain is the
// owner filter (vftable 0x00C071B4) -> possible-to-attack (owner, 2, 0) ->
// reject buildings (0x002611F2) -> player filter (0x00261058) -> status
// masks 0x32 / none (0x002FDF1C) -> alive (0x0026119D); the polygon filter
// (0x00261723 vftable 0x00C07184) on the area is linked or asked
// separately. A garrisoned owner (status 0x25) first asks its container's
// slot 55 for a target and keeps it when the chain and area allow it and
// a non-default priority info rates it above zero. Otherwise the area's
// bounds become a region: without priority info the closest object in it
// (within 9999.9) is adjusted (pinned Object::adjustVictim) and returned;
// with one every object in the region is rated by priority (raised by its
// contents through the rowed Rva002FDB93Callback) less its distance over
// the AI data's +0x54 (at least 1) and the best one inside the area wins.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members.
#include "Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"

typedef float Real;
typedef int Int;

class Object;
class Player;
class PolygonTrigger;

extern PartitionManager *ThePartitionManager;

#include <math.h>

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00C071B4: +0x08 the owner.
class Rva002FE13DFilter : public Rva000421C8
{
public:
	Rva002FE13DFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BF8FF0; the out-of-line ctor 0x002611F2: +0x08 the object,
// +0x0C whether its controlling player's +0x5C is 1.
class PartitionFilterRejectBuildings : public Rva000421C8
{
public:
	PartitionFilterRejectBuildings(Object *obj);	// 0x002611F2
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00BF8FE4; the out-of-line ctor 0x00261058: +0x08 the object's
// controlling player, +0x0C whether a hit allows.
#include "../../../Include/GameLogic/Rva00261058.h"

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
class BfmeObject872Header
{
	unsigned int m_words[4];
};

class Rva0023DA79 : public BfmeObject872Header
{
public:
	Rva0023DA79 *rva0023DA79(int base, int bit) throw();	// 0x0023DA79
};

// vftable 0x00C071CC; the out-of-line ctor 0x002FDF1C: status must / must not.
class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b) throw();	// 0x002FDF1C
	virtual bool allow(Object *obj);
	BfmeObject872Header m_8;
	BfmeObject872Header m_18;
};

// vftable 0x00BF91B0, allow 0x00260FD0: +0x08 the object, +0x0C the attack
// type, +0x10 the command source.
class Rva00260FD0Filter : public Rva000421C8
{
public:
	Rva00260FD0Filter(const Object *obj, int attackType, int commandSource)
	: m_obj(obj), m_attackType(attackType), m_source(commandSource) {}
	virtual bool allow(Object *obj);
	const Object *m_obj; // +0x08
	int m_attackType; // +0x0C
	int m_source; // +0x10
};

// vftable 0x00C07184, allow 0x00261723: +0x08 the polygon trigger (Zero
// Hour's PartitionFilterPolygonTrigger).
class Rva00261723Filter : public Rva000421C8
{
public:
	Rva00261723Filter(const PolygonTrigger *trigger) : m_trigger(trigger) {}
	virtual bool allow(Object *obj);
	const PolygonTrigger *m_trigger;
};

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"

#include "../../../Include/GameLogic/PolygonTrigger.h"

// The partition manager's region queries behind +0x10 (address-named rows).
// 0x006253C0 is rowed as a void forwarder with int arguments, yet it hands
// back the implementation's closest object in EAX: its typed signature is
// reached through a member-pointer cast so the call keeps the row's name.
class BfmeWideForwardB
{
public:
	BfmeWideResult bfmeForwardWideB(int region, int distType, int filters, int order);	// 0x00625690
};

class BfmeC1050
{
public:
	void bfmeGo1050C(int a, int b, int c, int d, int e);	// 0x006253C0
};
typedef Object *(BfmeC1050::*Go1050Typed)(const Coord3D *pos, const Region3D *region, Real maxDist, Int distType,
		Rva000421C8 *filters);

#include "../../../Include/GameLogic/AttackPriorityInfo.h"

// The script engine's default attack priority info.
class Rva0020391FLeaGetter
{
public:
	void *get() const;	// 0x0020391F
};
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

typedef void (*ContainIterateFunc)(Object *obj, void *userData);
void Rva002FDB93Callback(Object *target, void *userData);	// 0x002FDB93

struct Rva002FDB93Best
{
	Real m_bestPriority;	// +0x00
	const AttackPriorityInfo *m_info;	// +0x04
	const Object *m_hunter;	// +0x08
};

#include "../../../Include/GameLogic/Module/ContainModule.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_25 = 0x25
};

#include "../Object/object.h"

#include "../../../Include/GameLogic/TAiData.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

Object *AI::rva002FF8DD(const PolygonTrigger *area, Object *owner, const AttackPriorityInfo *info)
{
	if (!owner->isAbleToAttack())
		return 0;


	Rva002FE13DFilter filterOwner(owner);
	Rva0026119DFilter filterAlive;
	PartitionFilterRejectBuildings filterBuildings(owner);
	Rva00261058 filterPlayer(owner, false);
	Rva002FDF1C filterStatus(*Rva0023DA79().rva0023DA79(0, 0x32), *Rva0023DA79().rva0023DA79(0, 0));
	Rva00260FD0Filter filterAttack(owner, 2, 0);
	filterOwner.link(&filterAttack);
	filterOwner.link(&filterBuildings);
	filterOwner.link(&filterPlayer);
	filterOwner.link(&filterStatus);
	filterOwner.link(&filterAlive);
	Rva00261723Filter filterArea(area);

	if (owner->testStatus(OBJECT_STATUS_25))
	{
		Object *container = owner->getContainedBy();
		if (container)
		{
			ContainModuleInterface *contain = container->getContain();
			if (contain)
			{
				Object *target;
				if (contain->slot55(owner, &target))
				{
					if (!target)
						return 0;
					filterOwner.link(&filterArea);
					if (!filterOwner.allows(target))
						return 0;
					if (target && info && info != ((const Rva0020391FLeaGetter *)TheScriptEngine)->get() &&
						info->getPriority(owner, target, false) == 0.0f)
						return 0;
					return target;
				}
			}
		}
	}

	IRegion2D bounds;
	const_cast<PolygonTrigger *>(area)->getBounds(&bounds);
	Region3D region;
	region.lo.x = (Real)bounds.lo.x;
	region.lo.y = (Real)bounds.lo.y;
	region.hi.x = (Real)bounds.hi.x;
	region.hi.y = (Real)bounds.hi.y;

	if (!info)
	{
		filterOwner.link(&filterArea);
		Object *found = (((BfmeC1050 *)ThePartitionManager)->*reinterpret_cast<Go1050Typed>(&BfmeC1050::bfmeGo1050C))(owner->getPosition(), &region, 9999.9f, 1, &filterOwner);
		return found ? found->adjustVictim(owner, 1, 0) : 0;
	}

	BfmeWideResult iter = ((BfmeWideForwardB *)ThePartitionManager)->bfmeForwardWideB((int)&region, 1, (int)&filterOwner, 0);
	Object *best = 0;
	Real bestPriority = 0.0f;
	Real bestRawPriority = 0.0f;
	for (Object *obj = iter.next(); obj; obj = iter.next())
	{
		Real priority = info->getPriority(owner, obj, true);
		if (priority == 0.0f)
			continue;
		ContainModuleInterface *contain = obj->getContain();
		if (contain)
		{
			Rva002FDB93Best data;
			data.m_bestPriority = priority;
			data.m_info = info;
			data.m_hunter = owner;
			contain->iterateContained(Rva002FDB93Callback, &data, true);
			if (data.m_bestPriority > priority)
				priority = data.m_bestPriority;
		}
		Real dist = sqrt(owner->rva00263763(obj));
		Int adjustedPriority = (Int)(priority - (Int)(dist / TheAI->getAiData()->m_attackPriorityDistanceModifier));
		if (adjustedPriority < 1)
			adjustedPriority = 1;
		if (adjustedPriority > bestPriority || (adjustedPriority == bestPriority && priority > bestRawPriority))
		{
			if (filterArea.allows(obj))
			{
				bestPriority = (Real)adjustedPriority;
				bestRawPriority = priority;
				best = obj;
			}
		}
	}
	return best ? best->adjustVictim(owner, 1, 0) : 0;
}
