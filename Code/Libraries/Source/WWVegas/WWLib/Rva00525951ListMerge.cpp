// cl: /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include "Rva00525119.h"
// STLport4.5.3 _list.c supplies the merge algorithm. The native comparison
// at525976 calls the independently rowed29B pointer/float comparator525119.
// Its full EAX result is0 or1; narrowing to its observed low byte preserves
// the predicate and native AL test. Original list element identity is unknown.
struct Rva00525951Less {
    // ?Rva00525951Less::operator() present-unmatched
    bool operator()(Rva00525119 &a, Rva00525119 &b) const {
        return static_cast<unsigned char>(a.rva00525119(&b)) != 0;
    }
};
// Native [525951,5259B1),96B cdecl; two sentinel lists and unused empty
// comparator value. Node payload at8 is the same four-byte record view;
// both paths use the full91B rowed STLport _Transfer at24470.
template void _STL::_S_merge(_STL::list<Rva00525119, _STL::allocator<Rva00525119> > &,
                            _STL::list<Rva00525119, _STL::allocator<Rva00525119> > &,
                            Rva00525951Less);

// Native52611D344B sort calls the exact96B float-pointer merge; the old
// list<short> identity was contradicted by that comparator and is retired.
// ??$_S_sort@VRva00525119@@V?$allocator@VRva00525119@@@_STL@@URva00525951Less@@@_STL@@YAXAAV?$list@VRva00525119@@V?$allocator@VRva00525119@@@_STL@@@0@URva00525951Less@@@Z
template void _STL::_S_sort(_STL::list<Rva00525119, _STL::allocator<Rva00525119> > &,
                           Rva00525951Less);
namespace _STL {
template<> __declspec(noinline) void list<Rva00525119, allocator<Rva00525119> >::sort()
{ Rva00525951Less compare; _S_sort(*this, compare); }
}
template void _STL::list<Rva00525119, _STL::allocator<Rva00525119> >::sort();
