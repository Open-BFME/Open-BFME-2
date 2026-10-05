// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?erase@?$list@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@QAE?AU?$_List_iterator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$_Nonconst_traits@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@2@U32@@Z
// retail 0x00424363, 42 bytes. list<basic_string<char>>::erase single-iterator
// via rowed basic_string dtor 0x0007FAB3 plus _free 0x00030830. Evidence:
// unlock lane; caller 0x004246E7 in 0x004246D7; unblocks 0x004246D7.
// ?pop_back@?$list@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@QAEXXZ
// retail 0x004246D7, 23 bytes. list<basic_string<char>>::pop_back via rowed
// erase 0x00424363. Evidence: chain lane (calls 0x00424363 just landed);
// caller 0x00424982 in 0x0042481E; unblocks 0x0042481E.
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

#include <list>
#include <string>

template class _STL::list<_STL::basic_string<char> >;
