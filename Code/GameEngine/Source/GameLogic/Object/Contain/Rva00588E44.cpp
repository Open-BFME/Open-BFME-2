// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00588E44@Rva0047A040Base9E0@@QAEXPAX@Z @0x00588E44 285B (Ghidra
// FUN_00988e44 boundary 0x00588E44-0x00588F61).
// Target evidence: called only from HordeTransportContain::onDie 0x00477B98
// (ecx = outer+0x11D) and 0x00479D0F (ecx = outer+0x9E0, HordeGarrisonContain's
// empty second base), both passing the outer contain after a 0x00462785 gate;
// so it is a member of the same Rva0047A040Base9E0 helper as 0x00588BF3 and
// 0x00588D24. Body: asks the contain interface at arg+0x20 for its contained
// list (slot 0x118 view materialized by the pinned list-return helper
// 0x0036AE51), and for each entry asks 0x00588B8A (thiscall on this, called
// with ecx set at all 11 call sites) for a member object; when there is one its
// own slot 0x108 list is walked instead. Every reached object is passed to the
// contain's slot 0xA4 with false, then to Object 0x0029004B, kill(8, 0)
// (0x002984D4) and getDrawable()->setDrawableHidden(true) (0x005508E2,
// 0x00271601). Slot names are not established; address names are kept.
#include <list>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

class Rva0036AE51ListView
{
public:
	void *a;
	IntList *b;
	IntList rva0036AE51();
};

enum DamageType
{
	DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	DEATH_TYPE_0 = 0
};

enum CommandSourceType
{
	CMD_SOURCE_DUMMY = 0
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva00588E44Contain;

class Rva00588E44Body
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
	virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
	virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
	virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
	virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27();
	virtual void b28(); virtual void b29();
	virtual Rva00588E44Contain *slot78();
	virtual Rva00588E44Contain *slot7C();
};

class Object;

class AICommandInterface
{
public:
	void aiExit(Object *obj, CommandSourceType cmdSource);
};

class Rva00588E44UpdateModule
{
public:
	virtual ~Rva00588E44UpdateModule();
	char m_pad04[0x20 - 0x04];
};

class AIUpdateInterface : public Rva00588E44UpdateModule, public AICommandInterface
{
};

class Object
{
public:
	void rva0029004B();
	void kill(DamageType damage, DeathType death);
	Drawable *getDrawable() const;
	void rva0028DCC4();
	void rva0028BAC0();

	char m_pad00[0x38];
	float m_38;
	float m_3c;
	char m_pad40[0x250 - 0x40];
	Rva00588E44Body *m_250;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_258;
	char m_pad25C[0x454 - 0x25C];
	unsigned char m_454;
};


class Rva00588E44Contain
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05();
	virtual bool slot18(Object *obj);
	virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32();
	virtual void slot84(Object *obj, CommandSourceType cmdSource);
	virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40();
	virtual void slotA4(Object *obj, bool flag);
	virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
	virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
	virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
	virtual Rva0036AE51ListView slot108();
	virtual void s67(); virtual void s68(); virtual void s69();
	virtual Rva0036AE51ListView slot118();
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *obj);
	void rva00588BA8(Object *obj, bool flag);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	Object *rva00588C4E(void *contain, const Coord3D *pos);
	void rva00588E44(void *contain);
	void rva00588F61(void *contain, Object *obj, CommandSourceType cmdSource);
};

// ?rva00588BA8@Rva0047A040Base9E0@@QAEXPAVObject@@_N@Z @0x00588BA8 75B.
// HordeGarrisonContain's +0x20 interface slot 27 (0x00479C2A) tail-forwards
// here, HordeTransportContain calls it at 0x00477132. Tests the object's
// drawable (0x00270260 bool), then by the flag runs Object 0x0028DCC4 or
// 0x0028BAC0 under the +0x454 byte. Exact only with the drawable call written
// in each arm (cl merges them after the flag split's null test).
void Rva0047A040Base9E0::rva00588BA8(Object *obj, bool flag)
{
	if (Rva00270260 *d = (Rva00270260 *)obj->getDrawable()) {
		if (!flag) {
			if (d->rva00270260() == true && obj->m_454 == 0)
				obj->rva0028DCC4();
		} else {
			if (!d->rva00270260() && obj->m_454 != 0)
				obj->rva0028BAC0();
		}
	}
}
// ?rva00588BF3 @0x00588BF3 91B (pinned under its caller's void return name).
// Walks the contain's slot-0x118 list view without copying it (the list
// pointer is re-read from the view each step) and returns the first member
// 0x00588B8A hands out whose slot 0x18 accepts the object.
Rva00588E44Contain *Rva0047A040Base9E0::rva00588BF3(void *contain, Object *obj)
{
	Rva0036AE51ListView view = ((Rva00588E44Contain *)((char *)contain + 0x20))->slot118();
	for (IntList::iterator it = view.b->begin(); it != view.b->end(); ++it) {
		Rva00588E44Contain *member = (Rva00588E44Contain *)rva00588B8A((void *)*it);
		if (member != 0 && member->slot18(obj) == true)
			return member;
	}
	return 0;
}

// ?rva00588C4E @0x00588C4E 214B. HordeGarrisonContain's +0x20 slot 61
// (0x00479BDD) calls it with the contain and a position: the closest (2D,
// squared, from FLT_MAX at 0x00BBB8E0) member object whose drawable test
// 0x00270260 is false, over every contained object's +0x250 slot-0x78
// member list. Returns the object in eax (the void-return pin is the caller's view).
Object *Rva0047A040Base9E0::rva00588C4E(void *contain, const Coord3D *pos)
{
	Rva0036AE51ListView view = ((Rva00588E44Contain *)((char *)contain + 0x20))->slot118();
	Object *best = 0;
	float bestDist = 3.402823466e+38F;
	for (IntList::iterator it = view.b->begin(); it != view.b->end(); ++it) {
		Rva00588E44Body *body = ((Object *)*it)->m_250;
		if (body == 0)
			continue;
		Rva00588E44Contain *member = body->slot78();
		if (member == 0)
			continue;
		Rva0036AE51ListView memberView = member->slot108();
		for (IntList::iterator jt = memberView.b->begin(); jt != memberView.b->end(); ++jt) {
			Object *o = (Object *)*jt;
			if (((Rva00270260 *)o->getDrawable())->rva00270260() == true)
				continue;
			float dx = pos->x - o->m_38;
			float dy = pos->y - o->m_3c;
			float dist = dx * dx + dy * dy;
			if (dist < bestDist) {
				best = o;
				bestDist = dist;
			}
		}
	}
	return best;
}

void Rva0047A040Base9E0::rva00588E44(void *contain)
{
	Rva00588E44Contain *c = (Rva00588E44Contain *)((char *)contain + 0x20);
	IntList items = c->slot118().rva0036AE51();
	for (IntList::iterator it = items.begin(); it != items.end(); ++it) {
		Rva00588E44Contain *member = (Rva00588E44Contain *)rva00588B8A((void *)*it);
		if (member != 0) {
			IntList inner = member->slot108().rva0036AE51();
			for (IntList::iterator jt = inner.begin(); jt != inner.end(); ++jt) {
				c->slotA4((Object *)*jt, false);
				((Object *)*jt)->rva0029004B();
				((Object *)*jt)->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
				((Object *)*jt)->getDrawable()->setDrawableHidden(true);
			}
		} else {
			c->slotA4((Object *)*it, false);
			((Object *)*it)->rva0029004B();
			((Object *)*it)->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
			((Object *)*it)->getDrawable()->setDrawableHidden(true);
		}
	}
}

// ?rva00588F61 @0x00588F61 153B. HordeGarrisonContain's +0x20 slot 32
// (0x00479BF3) calls it with the contain, an object and a value it passes on
// as aiExit's CommandSourceType: each contained object forwards both to its
// +0x250 slot-0x7C member's slot 0x84, or without one to
// AICommandInterface::aiExit (0x0036F39B) through its +0x258 AI.
void Rva0047A040Base9E0::rva00588F61(void *contain, Object *obj, CommandSourceType cmdSource)
{
	IntList items = ((Rva00588E44Contain *)((char *)contain + 0x20))->slot118().rva0036AE51();
	for (IntList::iterator it = items.begin(); it != items.end(); ++it) {
		Object *o = (Object *)*it;
		Rva00588E44Body *body = o->m_250;
		if (body != 0) {
			Rva00588E44Contain *member = body->slot7C();
			if (member != 0)
				member->slot84(obj, cmdSource);
		} else {
			AIUpdateInterface *ai = o->m_258;
			if (ai != 0)
				ai->aiExit(obj, cmdSource);
		}
	}
}
