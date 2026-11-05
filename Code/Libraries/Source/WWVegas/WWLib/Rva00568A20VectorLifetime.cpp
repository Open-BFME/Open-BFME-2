// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Displaced audio record: native56A4AA accesses the ref at0, cell at4,
// flag8 and advances12; established copy568A20/reserve569E1D users agree.
void __cdecl Rva00030830FreeAllocation(void *);
#include <cstdlib>
#include <vector>
#include "OpaqueRefCounted.h"
#include "../../../../GameEngine/Include/Common/BfmePoolRef10.h"
class HostClass005C8E0A;
class Rva00568A20 {
public:
 __declspec(noinline) ~Rva00568A20();
 BfmePoolRef10 ref;HostClass005C8E0A *cell;unsigned char flag;
};
// The vector release calls the GameMemory free wrapper directly.
namespace _STL {
template<> inline void allocator<Rva00568A20>::deallocate(Rva00568A20 *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
}
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00568A20::~Rva00568A20(){}

// ?bfmeAnchorRva00568A20Dtor absent-from-retail
void bfmeAnchorRva00568A20Dtor(Rva00568A20 *p)
{
	p->Rva00568A20::~Rva00568A20();
}
template _STL::_Vector_base<Rva00568A20,_STL::allocator<Rva00568A20> >::_Vector_base(const _STL::allocator<Rva00568A20>&);
template _STL::vector<Rva00568A20>::~vector();
