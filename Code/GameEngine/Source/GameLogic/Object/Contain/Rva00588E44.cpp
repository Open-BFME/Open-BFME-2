// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

typedef _STL::list<int, _STL::allocator<int> > IntList;

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

class Rva0036AE51ListView
{
public:
	void *a;
	void *b;
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

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Object
{
public:
	void rva0029004B();
	void kill(DamageType damage, DeathType death);
	Drawable *getDrawable() const;
};

class Rva00588E44Contain
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
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
	void rva00588E44(void *contain);
};

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
