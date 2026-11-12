// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../GameEngine/Include/Common/Rva00293486Record.h"
// The record's placement copy is retail 0x002927CB, rowed as the typed
// ?Rva002927CBConstruct (an EH frame around the {int, AsciiString} copy ctor
// 0x000CF475); _M_create_node 0x00293486 calls it. This TU's 8-byte
// template copy is not that body, so the call binds to the row instead.
struct TreeKey00242F5E;
void Rva002927CBConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva00293486Record *dest, const Rva00293486Record &source)
{
    Rva002927CBConstruct(reinterpret_cast<TreeKey00242F5E *>(dest),
                         *reinterpret_cast<const TreeKey00242F5E *>(&source));
}
}
#include <list>





// Retail's loop calls the rowed placement-copy owner
// Rva002927CBConstruct 0x002927CB (stlport_construct_game_structs.cpp).
struct TreeKey00242F5E;
void __cdecl Rva002927CBConstruct(TreeKey00242F5E *, const TreeKey00242F5E &);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00293486Record, Rva00293486Record>(Rva00293486Record *__p, const Rva00293486Record &__val)
{ Rva002927CBConstruct(reinterpret_cast<TreeKey00242F5E *>(__p), *reinterpret_cast<const TreeKey00242F5E *>(&__val)); }
}

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_List_node<Rva00293486Record> * _STL::list<Rva00293486Record, _STL::allocator<Rva00293486Record> >::_M_create_node(Rva00293486Record const &);
