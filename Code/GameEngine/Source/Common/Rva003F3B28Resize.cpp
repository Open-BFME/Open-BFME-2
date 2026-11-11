// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Gy
// stlport
//
// ?rva003F3B28@Rva003F3AB5@@QAEXI@Z @0x003F3B28 39B: the single-argument
// resize of the 12-byte DynamicPortalLink array vector: builds the default
// (empty) element in the outgoing by-value argument through the rowed empty
// vector-base constructor 0x00211E58, then calls the rowed two-argument
// resize/append 0x003F3AB5 (ret 0x10 with the index plus the 12B value).
//
// Evidence for the shape: retail passes the allocator temporary as
// lea eax,[ebp+0xb] with no stack slot of its own, and no local frame beyond
// the saved ESP. cl only drops the dead empty-temporary slot (and its
// zeroing) when it can see the constructor body, so the STLport
// _Vector_base<BfmeE16> constructor (the rowed 0x00211E58, same instantiation
// stlport_vector_e16_o1.cpp emits) is instantiated here, out of line and
// ahead of the caller; /Gy makes this copy a COMDAT identical to the rowed one.
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"

template _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >::_Vector_base(const _STL::allocator<BfmeE16> &);

struct DynamicPortalLink : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
	__forceinline DynamicPortalLink(const _STL::allocator<BfmeE16> &a = _STL::allocator<BfmeE16>()) throw()
		: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >(a) {}
	DynamicPortalLink(const DynamicPortalLink &);
	~DynamicPortalLink() throw();
};

#include "../../Include/Common/Rva003F3AB5.h"

void Rva003F3AB5::rva003F3B28(unsigned n) { rva003F3AB5(n, DynamicPortalLink()); }
