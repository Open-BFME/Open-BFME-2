// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva003F6A91@@UAE@XZ, retail 0x003F6A91..0x003F6B19 (136 bytes, EH).
// LivingWorldBattle's destructor (LivingWorldBattleCtor.cpp has the full
// class; this unit keeps a destructor-only view under the opaque pin name the
// scalar deleting destructor 0x003F6CDD calls). Target facts: the bases are
// declared Snapshot, the +8 listener list, the +4 listener interface (MSVC
// lays the polymorphic interface out first yet constructs it last), then the
// 28-byte-record vector at +0x18. The body runs rowed 0x003F498A with a
// stack visitor (vtable 0x00C37080, ctor 0x003F424F; its scope ends before
// the broadcast), tells the listeners (forEach 0x003F5206, slot-0 vcall
// thunk 0x005FF3A9) and the members and bases unwind in reverse order.
// The +0x18 vector is spelled with the element type whose vector destructor
// owns 0x003F6936; the sides' own type is not recovered.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
#include "Common/Snapshot.h"

class Rva003F5206Listener
{
public:
	virtual void notify(void *);
};

class Rva003F5206List
{
public:
	void forEach(void (Rva003F5206Listener::*notify)(void *), void *arg);
};

class Rva00330757List : public _STL::vector<void *>
{
public:
	int m_flags;
};

class LivingWorldBattleListener
{
public:
	LivingWorldBattleListener() {}
	~LivingWorldBattleListener() {}
	virtual void onArmyRemoved(void *army);
	virtual void slot1(int a, int b);
	virtual void slot2(int a);
	virtual void slot3(int a);
	virtual void slot4(int a);
};

struct BfmeStringRecord00111ACF;

namespace _STL
{
template <> class vector<BfmeStringRecord00111ACF, allocator<BfmeStringRecord00111ACF> >
{
public:
	~vector();

private:
	BfmeStringRecord00111ACF *m_begin;
	BfmeStringRecord00111ACF *m_finish;
	BfmeStringRecord00111ACF *m_end;
};
}

class Rva003F498ACallback
{
public:
	virtual bool invoke(int) = 0;
	~Rva003F498ACallback() {}
};

class Rva003F6A91;

class LivingWorldBattle
{
public:
	void rva003F498A(Rva003F498ACallback *cb);
};

class Rva003F424F : public Rva003F498ACallback
{
public:
	explicit Rva003F424F(Rva003F6A91 *owner) : m_owner(owner) {}
	virtual bool invoke(int);
	virtual ~Rva003F424F() {}

private:
	Rva003F6A91 *m_owner;
};

class Rva003F6A91 : public Snapshot, public Rva00330757List, public LivingWorldBattleListener
{
public:
	virtual ~Rva003F6A91();

private:
	_STL::vector<BfmeStringRecord00111ACF> m_sides; // +0x18
};

Rva003F6A91::~Rva003F6A91()
{
	{
		Rva003F424F visitor(this);
		((LivingWorldBattle *)this)->rva003F498A(&visitor);
	}
	((Rva003F5206List *)static_cast<Rva00330757List *>(this))->forEach(&Rva003F5206Listener::notify, this);
}
