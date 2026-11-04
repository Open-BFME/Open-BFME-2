// ?onCollide@AIUpdateInterface@@UAEXPAVObject@@PBUCoord3D@@1@Z
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?onCollide@AIUpdateInterface@@UAEXPAVObject@@PBUCoord3D@@1@Z
// ?onCollide@AIUpdateInterface@@UAEXPAVObject@@PBUCoord3D@@1@Z
// ?onCollide@AIUpdateInterface@@UAEXPAVObject@@PBUCoord3D@@1@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIUpdateInterface-adjacent command/locomotor queue insert at 0x0026DF0D
// (359 B, RET 0xC). The +0x24 subobject is the AIUpdateInterface; its object at
// -0x1C is the controlled Object. Rejects while g_00DFE7A8 is set, the two
// +0x396/+0x397 gates are up, or the object frame +0x154 runs ahead of the
// game frame; then the relation filters, the +0x74 key search over the int
// arrays at +0x180/+0x184 and the +0x190/+0x194 age arrays, and finally the
// AIUpdateInterface 0x26CF11/0x262989 pair. All callees rowed; the two globals
// are the ledger's own TheGameLogic and g_00DFE7A8.
class Object;
class ObjectView { public: char m_pad[0x113]; unsigned char m_113; };
enum Relationship { RELATIONSHIP_ENUM_BASE = 0 };
enum ObjectStatusTypes { STATUS_3B = 0x3b };
#include "object.h"
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern unsigned char g_00DFE7A8;

struct Coord3D;

class AIUpdateInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
	bool rva0026CF11(Object *obj);
	void rva00262989(unsigned value);
};

void AIUpdateInterface::onCollide(Object *other, const Coord3D *loc, const Coord3D *normal)
{
	if (other == 0)
		return;
	if (g_00DFE7A8 != 0)
		return;
	if (*(unsigned char *)((char *)this + 0x396) != 0)
		return;
	if (*(unsigned char *)((char *)this + 0x397) != 0)
		return;
	if (*(unsigned *)((char *)this + 0x154) > TheGameLogic->getFrame())
		return;
	Object *self = *(Object **)((char *)this - 0x1c);
	if (self->rva002931BA())
		return;
	if (other->rva002931BA())
		return;
	if ((*(ObjectView **)((char *)self + 4))->m_113 & 0x20)
	{
		if (self->testStatus(STATUS_3B))
			return;
	}
	if (self->getRelationship(other) != 0)
		return;
	Object *rel = self->rva0028ACA0();
	if (rel != 0)
	{
		if (other == rel)
			return;
		if (*(Object **)((char *)other + 0x274) == rel)
			return;
	}
	rel = other->rva0028ACA0();
	if (rel != 0)
	{
		if (self == rel)
			return;
		if (*(Object **)((char *)self + 0x274) == rel)
			return;
	}
	int key = *(int *)((char *)other + 0x74);
	int i = 0;
	if (*(unsigned *)((char *)this + 0x1a4) > 0)
	{
		int *p = (int *)((char *)this + 0x184);
		do
		{
			if (*p == key)
				break;
			++i;
			++p;
		} while (i < *(volatile unsigned *)((char *)this + 0x1a4));
	}
	if ((unsigned)i < *(unsigned *)((char *)this + 0x1a4))
	{
		int *frameSlot = (int *)((char *)this + 0x194 + i * 4);
		if (*frameSlot + 1 == TheGameLogic->getFrame())
		{
			*frameSlot = *frameSlot + 1;
			return;
		}
		*frameSlot = *(int *)((char *)this + 0x190 + *(unsigned *)((char *)this + 0x1a4) * 4);
		*(int *)((char *)this + 0x184 + i * 4) = *(int *)((char *)this + 0x180 + *(unsigned *)((char *)this + 0x1a4) * 4);
		(*(unsigned *)((char *)this + 0x1a4))--;
	}
	AIUpdateInterface *ai = (AIUpdateInterface *)((char *)this - 0x24);
	if (ai->rva0026CF11(other))
		ai->rva00262989(key);
}
