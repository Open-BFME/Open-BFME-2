// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// AIFlankAttackTacticImp::DoXfer @0x005AA4C1 156B (WorldBuilder: the route's
// m_positions count then each position, asserting the count at
// AIFlankAttackTactic.cpp:132; called from AIFlankAttackTactic's xfer). Identity: fill vector from virtual enumeration then zero-fill via push_back.
// Evidence: vector<Coord3D> at +4 div 12; virtual slots 0x78 0x8 0x60 0x4; rowed push_back 0x002CE7DC; caller 0x005AA622 same page.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "../../../Libraries/Include/Lib/Coord3D.h"

// Call the canonical 12-byte allocator and keep only the inline proxy forwarding.
namespace _STL {
template <> Coord3D * allocator<Coord3D>::allocate(size_t, const void *) const;
template <> __declspec(dllimport) __forceinline
Coord3D * _STLP_alloc_proxy<Coord3D*,Coord3D,allocator<Coord3D> >::allocate(size_t count) {
 return __stl_alloc_rebind(static_cast<allocator<Coord3D>&>(*this),(Coord3D*)0).allocate(count,0);
}
}


namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<Coord3D>::deallocate(Coord3D* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<Coord3D*,Coord3D,allocator<Coord3D> >::deallocate(Coord3D* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<Coord3D>&>(*this),(Coord3D*)0).deallocate(__p,__n);
}
}

// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}

#include "AIXferTypes.h"
#include "../../Include/Common/BfmeXfer.h"

// The existing destination route is Rva0015334F: next index at +0 and the
// points vector at +4. Its xfer forwarding wrapper passes this same address
// to DoXfer; do not require a second set of fields on the method-only owner.
class Rva0015334F
{
public:
	int m_next;
	_STL::vector<Coord3D> m_points;
};

class AIFlankAttackTacticImp
{
public:
	void DoXfer(Xfer *p);
};

void AIFlankAttackTacticImp::DoXfer(Xfer *xfer)
{
	// MSVC places the shared operator== overloads in reverse declaration order:
	// unsigned int is slot 0x78 and Coord3DBase is slot 0x60.
	*xfer == *reinterpret_cast<unsigned int *>(this);
	Rva0015334F *self = reinterpret_cast<Rva0015334F *>(this);
	_STL::vector<Coord3D> *vec = &self->m_points;
	unsigned int count = (unsigned int)(vec->end() - vec->begin());
	*xfer == count;
	if (xfer->IsStoring()) {
		_STL::vector<Coord3D>::iterator end = self->m_points.end();
		_STL::vector<Coord3D>::iterator it = vec->begin();
		for (; it != end; ++it)
			*xfer == *reinterpret_cast<Coord3DBase *>(&(*it));
		return;
	}
	if (!xfer->IsLoading())
		return;
	for (unsigned int i = 0; i < count; ++i) {
		Coord3D zero;
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		*xfer == *reinterpret_cast<Coord3DBase *>(&zero);
		vec->push_back(zero);
	}
}
