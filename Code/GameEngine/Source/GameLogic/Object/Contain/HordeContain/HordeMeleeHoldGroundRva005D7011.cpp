// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva005D7011@Rva00583794@@QAE_NPAVObject@@@Z @0x005D7011 (377B, RET 4):
// slot 10 of the HordeMeleeHoldGround code-pointer table at 0x0086FC40 (the
// same table as the rowed Rva00583794 bodies in HordeMeleeHoldGround.cpp;
// two more tables share it). Target facts (retail and the WorldBuilder twin
// 0x01594170): it fails a null target; "close" is the horde's +8 squared
// distance (0x00263763) under 10000; the target's container is its +0x274
// or, while status 0x26 holds, the object its +0x78 ID names. Over the
// horde's member list (0x0046247D) it succeeds -- after forwarding the target
// to slot 89 of the horde's +0x11C interface -- for the first member whose
// AI (slot 111) is engaged and either is close or whose current victim is
// the target, is inside it, or shares its container; a close idle member
// (unless its +0x140 test 0x001E3591 holds) is idled (slot 113 gate, then
// aiIdle(2)), released (0x00295F05) and counts once engaged. Names stay
// address-derived.
// Codegen notes: the ObjectID lookup chain (ObjectIdMap::find and
// GameLogic::findObjectByID 0x00049DC5, the rowed COMDAT copies as in
// HordeMeleeSwarmFindMeleeAttackPosition.cpp) is visible in this unit, and the
// victim's container is read through the accessor in both tests; together
// they give retail's copy of that load into EDI before its null test.
#include "../../../../../Include/GameLogic/ContainmentListView.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

// Keep the node comparison local rather than emitting the conflicting
// out-of-line list-base comparison alongside the already inlined loop test.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef float Real;

enum ObjectStatusTypes
{
	RVA_OBJECT_STATUS_26 = 0x26
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

#include "../../../../../Include/Common/Rva001E3591.h"

template <int N> class Rva005D7011Slots : public Rva005D7011Slots<N - 1>
{
public:
	virtual void gap(char (*slot)[N]) = 0;
};

template <> class Rva005D7011Slots<0>
{
};

class AIUpdateInterface : public Rva005D7011Slots<111>
{
public:
	virtual Bool isEngaged() = 0;		// +0x1BC
	virtual void slot112() = 0;
	virtual Bool slot113() = 0;		// +0x1C4
	Object *getCurrentVictim() const;	// 0x00268D71
	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commands;		// +0x20
	char m_pad21[0x140 - 0x21];
	Rva001E3591 *m_140;			// +0x140
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes status) const;
	void rva00295F05(bool value);
	Real rva00263763(const void *other) const;
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	ObjectID getContainerID() const { return m_containerID; }
private:
	char m_pad000[0x78];
	ObjectID m_containerID;			// +0x78
	char m_pad07C[0x258 - 0x7C];
	AIUpdateInterface *m_ai;		// +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;			// +0x274
};

extern GameLogic *TheGameLogic;

struct D7LookupNode { D7LookupNode *next; ObjectID key; Object *object; };
struct D7LookupBuckets {
 D7LookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 D7LookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct D7LookupMap { unsigned char hashEqual[4]; D7LookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 D7LookupMap *map=(D7LookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 D7LookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

#include "../../../../../Include/Common/Rva0046247DDescriptor.h"

template <int N> class Rva005D7011HordeSlots : public Rva005D7011HordeSlots<N - 1>
{
public:
	virtual void gap(char (*slot)[N]);
};

template <> class Rva005D7011HordeSlots<0>
{
};

class Rva005D7011HordeIface : public Rva005D7011HordeSlots<89>
{
public:
	virtual void onTargetEngaged(Object *target);	// +0x164
};

struct Rva005D7011Horde
{
	char m_pad000[0x08];
	void *m_08;				// +0x08
	char m_pad00C[0x11C - 0x0C];
	Rva005D7011HordeIface m_11C;		// +0x11C
};

class Rva00583794
{
public:
	bool rva005D7011(Object *target);

private:
	void *m_vtable;
	Rva005D7011Horde *m_horde;		// +0x04
};

static __forceinline Object *containerOf(Object *obj)
{
	Object *container = obj->getContainedBy();
	if (!container && obj->testStatus(RVA_OBJECT_STATUS_26))
		container = TheGameLogic->findObjectByID(obj->getContainerID());
	return container;
}

bool Rva00583794::rva005D7011(Object *target)
{
	if (!target)
		return false;

	bool close = target->rva00263763(m_horde->m_08) < 10000.0f;
	Object *targetContainer = containerOf(target);

	bool engaged = false;
	Rva0036AE51ListView members = ((Rva0046247DDescriptor *)m_horde)->rva0046247D();
	for (ContainmentList::const_iterator it = members.b->begin(); it != members.b->end(); ++it)
	{
		Object *member = (Object *)containmentFirstWord(*it);
		AIUpdateInterface *ai = member->getAI();
		if (!ai)
			continue;

		if (ai->isEngaged())
		{
			if (close)
			{
				engaged = true;
				break;
			}
			Object *victim = ai->getCurrentVictim();
			if (!victim)
				continue;
			if (victim == target)
			{
				engaged = true;
				break;
			}
			if (victim->getContainedBy() == target)
			{
				engaged = true;
				break;
			}
			if (targetContainer)
			{
				Object *victimContainer = victim->getContainedBy();
				if (!victimContainer && victim->testStatus(RVA_OBJECT_STATUS_26))
				{
					victimContainer = TheGameLogic->findObjectByID(victim->getContainerID());
					if (victimContainer == targetContainer)
					{
						engaged = true;
						break;
					}
				}
				if (victimContainer == targetContainer)
				{
					engaged = true;
					break;
				}
			}
		}
		else if (close)
		{
			if (ai->m_140 && ai->m_140->rva001E3591())
				continue;
			if (ai->slot113())
				ai->m_commands.aiIdle(CMD_FROM_AI);
			member->rva00295F05(false);
			if (ai->isEngaged())
			{
				engaged = true;
				break;
			}
		}
	}

	if (engaged)
	{
		m_horde->m_11C.onTargetEngaged(target);
		return true;
	}
	return false;
}
