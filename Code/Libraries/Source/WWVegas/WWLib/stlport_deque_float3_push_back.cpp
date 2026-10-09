// ?_M_push_back_aux_v@?$deque@URva00585B1EFloat3@@V?$allocator@URva00585B1EFloat3@@@_STL@@@_STL@@IAEXABURva00585B1EFloat3@@@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Target585B1E..585B8B: STLport4.5.3 _M_push_back_aux_v copies a three-float
// value before reserving a map slot, allocating a120B node and advancing end.
// The nontrivial member-wise copy is a compiler-shape inference from native
// MOVSS instructions; the element name is opaque and not the POD BfmeE12
// type whose different auxiliary body already lives at423558.
// Reserve and Construct use existing verified storage views: deque map
// reservation depends only on the identical32B header, and the29B construct
// provider is a null-checked bitwise12B copy. Casts do not assert original
// inheritance or pair identity. No new callee aliases or pins.
#include <deque>
#include <utility>
struct Rva00585B1EFloat3 {float x,y,z;Rva00585B1EFloat3(const Rva00585B1EFloat3&v):x(v.x),y(v.y),z(v.z){}};
struct BfmeE12 {float x,y,z;};
namespace _STL { template<> void deque<BfmeE12>::_M_reserve_map_at_back(size_type); }
class Rva00585B1EReserveView : public _STL::deque<BfmeE12> {
public:__forceinline void reserveOne(unsigned n){_M_reserve_map_at_back(n);}
};
struct Rva002CA82CElement {short words[4];};
typedef _STL::pair<const Rva002CA82CElement,int> Rva002CA82CPair;
namespace _STL {
template<> __forceinline void deque<Rva00585B1EFloat3>::_M_reserve_map_at_back(size_type n){((Rva00585B1EReserveView*)this)->reserveOne(n);}
template<> void _Construct<Rva002CA82CPair,Rva002CA82CPair>(Rva002CA82CPair*,const Rva002CA82CPair&);
template<> __forceinline void _Construct<Rva00585B1EFloat3,Rva00585B1EFloat3>(Rva00585B1EFloat3*p,const Rva00585B1EFloat3&v){_Construct((Rva002CA82CPair*)p,(const Rva002CA82CPair&)v);}
}
template void _STL::deque<Rva00585B1EFloat3,_STL::allocator<Rva00585B1EFloat3> >::_M_push_back_aux_v(const Rva00585B1EFloat3&);
