// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// STLport 4.5.3 vector copy constructor, moved without reconstruction from
// stlport_uninitialized_copy.cpp. The complete 93-byte body and handler are
// byte-verified; this legacy element spelling and its pinned copy callee
// still need reconciliation, so keep its conflicting helper emissions out
// of the independently verified uninitialized-copy worker family.
#include <memory>
#include <vector>
#include "ascii_string.h"

#include "TreeKey00242F5E.h"
// The native eight-byte range copy calls the rowed placement-copy helper.
void Rva001D9B0FConstruct(void *, const void *);
namespace _STL {
template <> inline TreeKey00242F5E *__uninitialized_copy<const TreeKey00242F5E *, TreeKey00242F5E *>(
    const TreeKey00242F5E *first, const TreeKey00242F5E *last,
    TreeKey00242F5E *result, const __false_type &)
{
    TreeKey00242F5E *cur = result;
    for (; first != last; ++first, ++cur)
        Rva001D9B0FConstruct(cur, first);
    return cur;
}
}
namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
}
template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(const _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> > &);
