// cl: /MD /GX
//
// ?lookForInnerTarget@AIGuardRetaliateMachine@@QAE_NXZ, retail 0x005455E3,
// 362 bytes (the pinned name: REL32 callee of AIGuardRetaliateReturnState::
// update 0x00545810). Zero Hour AIGuardRetaliate.cpp's lookForInnerTarget,
// BFME2's version: nothing unless the owner (machine +0x14) can attack; the
// team's common target when its template asks for one; else the closest
// object to a copy of the owner's position within 0.3 of the AI data's
// +0xC8 that passes the chain enemy (relationship 1) -> attackable
// (ATTACK_NEW_TARGET, CMD_FROM_AI) -> same map status, then the 0x002611F2
// filter and the reject-kind-130 filter (Zero Hour's RejectBuildings). The
// nemesis id goes to +0x48. A sixth filter (vftable 0x00C172A8) is built and
// never linked, as retail does.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1). Retail updates the unwind state only after the kind mask filter
// is built, so the bitset and mask-filter ctors are declared throw() here.
class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
#include "../../../Include/GameLogic/Rva00260EB1Filter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1.
class PartitionFilterRejectBuildings : public Rva000421C8
{
public:
	PartitionFilterRejectBuildings(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00BF91B0, allow 0x00260FD0: +0x08 the object, +0x0C the attack
// type, +0x10 the command source.
class Rva00260FD0Filter : public Rva000421C8
{
public:
	Rva00260FD0Filter(const Object *obj, int attackType, int commandSource)
		: m_obj(obj), m_attackType(attackType), m_source(commandSource) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	int m_attackType;
	int m_source;
};

// Native C172A8 slot1 reaches260E01, the existing rowed
// PartitionFilterIsFlying::allow (airborne-locomotor test). Fieldless
// derived view and shared base/link layout are retained.
class PartitionFilterIsFlying : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};


#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectID
{
	INVALID_ID = 0
};

#include "../../../Include/Common/Team.h"


#include "../../../Include/Common/TeamBFME2.h"

class Object
{
public:
	bool isAbleToAttack() const;	// 0x00290B73
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0x304 - 0x78];
	Team *m_team;			// +0x304
};

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#include "../../../Include/GameLogic/TAiData.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

class AIGuardRetaliateMachine
{
public:
	bool lookForInnerTarget();
private:
	char m_pad00[0x14];
	Object *m_owner;	// +0x14
	char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisID;	// +0x48
};

bool AIGuardRetaliateMachine::lookForInnerTarget()
{
	Object *owner = m_owner;
	if (!owner->isAbleToAttack())
		return false;
	if (owner->m_team->m_proto->m_attackCommonTarget) {
		Object *teamVictim = owner->m_team->getTeamTargetObject();
		if (teamVictim) {
			m_nemesisID = teamVictim->m_id;
			return true;
		}
	}
	Rva00260EB1Filter f1(owner, 1, false);
	Rva00260FD0Filter f2(owner, 2, 0);
	PartitionFilterRejectBuildings f3(owner);
	Rva0004584D f8(*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
		*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x82));
	Rva002611BFFilter filterMapStatus(owner);
	PartitionFilterIsFlying filterIsFlying;
	f1.link(f2.link(&filterMapStatus));
	f1.link(&f3);
	f1.link(&f8);
	float visionRange = TheAI->m_aiData->m_maxRetaliateDistance * 0.3;
	Coord3D pos;
	pos.x = owner->m_pos.x;
	pos.y = owner->m_pos.y;
	pos.z = owner->m_pos.z;
	Object *target = ThePartitionManager->getClosestObject(&pos, visionRange, 1, &f1);
	if (target) {
		m_nemesisID = target->m_id;
		return true;
	}
	return false;
}
