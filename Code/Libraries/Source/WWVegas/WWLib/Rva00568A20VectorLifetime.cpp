// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Displaced audio record: native56A4AA accesses the ref at0, cell at4,
// flag8 and advances12; established copy568A20/reserve569E1D users agree.
void __cdecl Rva00030830FreeAllocation(void *);
#include <cstdlib>
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
class OpaqueRefCounted {public:void Release_Ref();};
struct BfmePoolHolder88 {char pad[0x88];OpaqueRefCounted ref;};
class BfmePoolRef10 {public:BfmePoolHolder88 *target; ~BfmePoolRef10(){if(target)target->ref.Release_Ref();}};
class HostClass005C8E0A;
class Rva00568A20 {
public:
 __declspec(noinline) ~Rva00568A20();
 BfmePoolRef10 ref;HostClass005C8E0A *cell;unsigned char flag;
};
Rva00568A20::~Rva00568A20(){}
template _STL::_Vector_base<Rva00568A20,_STL::allocator<Rva00568A20> >::_Vector_base(const _STL::allocator<Rva00568A20>&);
template _STL::vector<Rva00568A20>::~vector();
