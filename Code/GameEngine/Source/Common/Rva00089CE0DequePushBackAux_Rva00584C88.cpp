// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// Open-BFME5: STLport deque<POD>::_M_push_back_aux_v, byte-twin of the
// int specialization at 0x006472C0 (Rva006472C0DequeIntPushBackAux.cpp) --
// same 101 bytes once relocations are masked; only the per-caller ILT reloc
// (the leading branch to the sizing check thunk) differs.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <deque>

struct Gen_t_00089ce0_p4pod { int a; };

template class _STL::deque<Gen_t_00089ce0_p4pod, _STL::allocator<Gen_t_00089ce0_p4pod> >;
