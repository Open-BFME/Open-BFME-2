// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// GiantBirdAIUpdate::onCollide, retail 0x003698CD (238 bytes, RET 0xC).
// Target evidence: it is slot 0 of ??_7GiantBirdAIUpdate@@6BAIUpdateInterface24@@@
// (0x00817A54), the subobject vtable at +0x24 whose six slots have Zero
// Hour's CollideModuleInterface shape (a three-argument slot 0, a one-
// argument false predicate 0x005CB9FF, then four folded false predicates
// 0x0047A699), so the body's this is the +0x24 subobject. It reads the
// module's Object (+0x08), the rowed AIUpdateInterface::getCurrentVictim
// and, when there is none, the +0x30 state machine's rowed getGoalObject;
// skips KindOf 0x9B owners, the goal itself and colliders whose template
// (+0x04) lacks bit 2 of byte +0x108. Unless bit 6 of the +0x4B8 word (the
// GiantBirdAIUpdate constructor's m_4B8) is set it requires the goal's rowed
// squared distance 0x00263763 to the collider to exceed the square of both
// +0xB8 radii, then adds the normalized vector 0x00261988 between the two
// objects to the +0x56C accumulator the constructor zeroes. The Object and
// template fields stay unnamed views; the callee names are the ledger's.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

inline void addCoord(Coord3D *a, const Coord3D *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

enum KindOfType { KINDOF_BFME_9B = 0x9B };

class ModuleData;
class Rva001E438B { public: float *rva00261988(float *out, Rva001E438B *other); };

class ThingTemplateView { public: unsigned char m_pad00[0x108]; unsigned char m_flags108; };

class Object
{
public:
	Bool isKindOf(KindOfType t) const;
	Real rva00263763(const void *other) const;
	const ThingTemplateView *getTemplateView() const { return m_template; }
	Real getRadiusB8() const { return m_B8; }
private:
	unsigned char m_pad00[4];
	const ThingTemplateView *m_template; // +0x04
	unsigned char m_pad08[0xB8 - 0x08];
	Real m_B8; // +0xB8
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface { public: virtual void getBody(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface { };
class UpdateModuleInterface { public: virtual void update(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};
class AICommandInterface { public: virtual void aiDoCommand(); };
class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};
class AIUpdateInterface : public UpdateModule, public AICommandInterface, public CollideModuleInterface
{
public:
	Object *getCurrentVictim() const;
	StateMachine *getStateMachine() const { return m_stateMachine; }
private:
	unsigned char m_pad28[0x30 - 0x28];
	StateMachine *m_stateMachine; // +0x30
	unsigned char m_pad34[0x3E4 - 0x34];
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
private:
	unsigned char m_pad3E4[0x4B8 - 0x3E4];
	UnsignedInt m_4B8; // +0x4B8
public:
	Bool testFlag(Int bit) const { return (m_4B8 >> bit) & 1; }
private:
	unsigned char m_pad4BC[0x56C - 0x4BC];
	Coord3D m_56C; // +0x56C
};

void GiantBirdAIUpdate::onCollide(Object *other, const Coord3D *loc, const Coord3D *normal)
{
	Object *obj = getObject();
	if (!obj || !other)
		return;
	if (obj->isKindOf(KINDOF_BFME_9B))
		return;
	Object *victim = getCurrentVictim();
	if (!victim)
	{
		if (!getStateMachine())
			return;
		victim = getStateMachine()->getGoalObject();
		if (!victim)
			return;
	}
	if (victim == other)
		return;
	if (!(other->getTemplateView()->m_flags108 & 4))
		return;
	if (!testFlag(6) && victim)
	{
		Real r = obj->getRadiusB8() + other->getRadiusB8();
		if (victim->rva00263763(other) <= r * r)
			return;
	}
	Coord3D v;
	((Rva001E438B *)other)->rva00261988(&v.x, (Rva001E438B *)obj);
	v.normalize();
	addCoord(&m_56C, &v);
}
