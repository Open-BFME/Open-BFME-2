// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1LivingWorldBattle@@UAE@XZ, retail 0x003F6A91..0x003F6B19 (136 bytes, EH).
// LivingWorldBattle's destructor (LivingWorldBattleCtor.cpp has the full
// class and the scalar deleting destructor 0x003F6CDD that calls this one;
// this unit keeps a destructor-only view). Both constructors store vftables
// 0x00C3709C/0x00C37088 and this body restores the same pair. Target facts: the bases are
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
#include <vector>
namespace _STL {
template<> inline void allocator<void *>::deallocate(void **__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
}
#include "Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
// bfme link decl-only end

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

#include "../../../../Include/Common/LivingWorldBattleListener.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// Keep vector<void*>'s destructors inline-only: nothing here calls them out of
// line, and this TU's /O1 copies are not retail's /Od bodies (0x00027370, 0x000251F0).
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_Vector_base<void *, allocator<void *> >::~_Vector_base()
{ if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
vector<void *, allocator<void *> >::~vector() { _Destroy(this->_M_start, this->_M_finish); }
}

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

#include "../../../../Include/Common/Rva003F498ACallback.h"

class LivingWorldBattle;

class Rva003F424F : public Rva003F498ACallback
{
public:
	explicit Rva003F424F(LivingWorldBattle *owner) : m_owner(owner) {}
	virtual bool invoke(int);
	virtual ~Rva003F424F() {}

private:
	LivingWorldBattle *m_owner;
};

class LivingWorldBattle : public Snapshot, public Rva00330757List, public LivingWorldBattleListener
{
public:
	virtual ~LivingWorldBattle();
	void rva003F498A(Rva003F498ACallback *cb);
	// Same listener slot 0 as LivingWorldBattleCtor.cpp's view, so both
	// units emit one ??_7LivingWorldBattle@@6BLivingWorldBattleListener@@@.
	virtual void onArmyRemoved(void *army) = 0;

private:
	_STL::vector<BfmeStringRecord00111ACF> m_sides; // +0x18
};

LivingWorldBattle::~LivingWorldBattle()
{
	{
		Rva003F424F visitor(this);
		rva003F498A(&visitor);
	}
	((Rva003F5206List *)static_cast<Rva00330757List *>(this))->forEach(&Rva003F5206Listener::notify, this);
}
