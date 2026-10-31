// cl: /O1 /arch:SSE /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The existing reserve provider at 30B96B proves the eight-byte vector
// elements at +0. The native constructor stores zero floats at +1C/+20,
// sets +24, and calls that provider with the initial capacity argument.
// Owner names remain address-derived; AreaPolygonBase is the existing
// reserve provider's name, rather than a new identity claim for the ctor.
#include "../../Include/Common/AreaPolygonBase.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<BfmeE8>::deallocate(BfmeE8* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<BfmeE8*,BfmeE8,allocator<BfmeE8> >::deallocate(BfmeE8* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<BfmeE8>&>(*this),(BfmeE8*)0).deallocate(__p,__n);
}
template <> __declspec(dllimport) __forceinline
_Vector_base<BfmeE8,allocator<BfmeE8> >::~_Vector_base() {
 if (_M_start != 0) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start);
}
}



class Rva0030B980 : public AreaPolygonBase
{
public:
	Rva0030B980(int capacity);
private:
};

Rva0030B980::Rva0030B980(int capacity)
{
 m_innerRadius=0.0f;
 m_radius=0.0f;
 m_dirty=true;
	reserve(capacity);
}

// Native 30B9DD..30B9F3: same receiver is passed to the base ctor and
// the additional field at +28 is zeroed. The caller at 330CA8 places
// this complete 2C-byte object at +8 inside its virtual-inheritance owner.
class Rva0030B9DD : public Rva0030B980
{
public:
	Rva0030B9DD(int capacity);
private:
	int unknown28;
};

Rva0030B9DD::Rva0030B9DD(int capacity)
	: Rva0030B980(capacity), unknown28(0)
{
}
