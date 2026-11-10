// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// CurseSpecialPower's slot 17 (0x004CCEEE; SpecialAbilityUpdate's slot 17
// first), its per-target curse (0x004CCE85) and the kind filter's implicit
// copy constructor the slot emits (0x004CCE4C), beside the matched
// CurseSpecialPower ctor 0x004CCD7F and pool key 0x004CCDEB.
//
//   0x004CCEEE  with no +0x40 target, curse every alive object of kind 90
//               relationship 1 to the owner within the special power
//               template's radius of +0x44 (BFME2's partition filter chain,
//               the view AIStructureCreepTactic.cpp documents) and, when any
//               was, FXList::doFXPos the module data's +0xC8 there; with one,
//               curse the object 0x00049DC5 finds for it and do the same FX
//   0x004CCE85  skip the owner, objects whose template lacks +0x110 bit 26,
//               non-enemies and status 3 or 2; then Object::rva0028B701 of
//               the data's +0xD0 and FXList::doFXObj of its +0xCC
class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second. Its implicit copy constructor is
// 0x004CCE4C.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// Inherited mask resolves to the real implementation in
// ActionManagerSpecialPowerChecks.cpp (retail 0x0036CC7A).

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../Common/GameLogicObjectLookupView.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004CCE85_2 = 2,
	OBJECT_STATUS_RVA004CCE85_3 = 3
};

enum Relationship
{
	ENEMIES = 0
};

class Matrix3D;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx,
		float speed, const Coord3D *secondary);	// 0x00094C29
};

#include "../../../../Include/Common/ThingTemplate.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"
// ?getRadius@SpecialPowerTemplate@@QBEMXZ 0x0029B6E2: this unit emits the row's
// body, the final override's cursor radius at +0x54.
inline float SpecialPowerTemplate::getRadius() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_radiusCursorRadius;
}

// Native 29B6D9..29B6E2 (9B), just before the getRadius copy at 0x0029B6E2:
// the final override's +0x59 flag, the same getFO() accessor shape. Which
// Zero Hour flag it is (publicTimer, sharedNSync, shortcutPower...) is not
// proven for BFME2's layout; address-derived name.
bool SpecialPowerTemplate::rva0029B6D9() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_sharedSyncedTimer;
}

#include "../../../../Include/GameLogic/Module/CurseSpecialPowerModuleData.h"

// 0x005F6B0B (module data +0x38) is rowed as Rva005F6B0BPtrChaseField::get.
class Rva005F6B0BPtrChaseField
{
public:
	int get() const;
};

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class CurseSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	void rva004CCE85(Object *obj);
private:
	const CurseSpecialPowerModuleData *getCurseSpecialPowerModuleData() const
	{
		return (const CurseSpecialPowerModuleData *)m_moduleData;
	}
};

void CurseSpecialPower::rva004CCE85(Object *obj)
{
	Object *owner = m_object;
	const CurseSpecialPowerModuleData *data = getCurseSpecialPowerModuleData();
	if (obj == owner)
		return;
	if (!(obj->m_template->m_kindof[2] & 0x04000000))
		return;
	if (owner->getRelationship(obj) != ENEMIES)
		return;
	if (obj->testStatus(OBJECT_STATUS_RVA004CCE85_3))
		return;
	if (obj->testStatus(OBJECT_STATUS_RVA004CCE85_2))
		return;
	obj->rva0028B701(data->m_cursePercentage);
	FXList::doFXObj(data->m_CC, obj, 0);
}

void CurseSpecialPower::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const CurseSpecialPowerModuleData *data = getCurseSpecialPowerModuleData();
	Object *owner = m_object;
	if (m_targetID == INVALID_OBJECT_ID) {
		const SpecialPowerTemplate *power = (const SpecialPowerTemplate *)((const Rva005F6B0BPtrChaseField *)this)->get();
		if (!power)
			return;
		float radius = power->getRadius();
		Rva0004584D kind(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 90),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_targetPos, radius, 0,
			Rva0026119DFilter().link(Rva0004584D(kind).link(&Rva00260EB1Filter(owner, 1, false))), 0);
		Object *other = hits.next();
		if (other) {
			do {
				rva004CCE85(other);
			} while ((other = hits.next()) != 0);
			FXList::doFXPos(data->m_C8, &m_targetPos, 0, 0.0f, 0);
		}
	} else {
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target) {
			rva004CCE85(target);
			FXList::doFXPos(data->m_C8, &m_targetPos, 0, 0.0f, 0);
		}
	}
}
