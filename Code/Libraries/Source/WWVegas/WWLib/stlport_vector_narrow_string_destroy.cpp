// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@_STL@@YAXPAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@0@0@Z at retail 0x000798BE (25B).
// ?_M_clear@?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@IAEXXZ at retail 0x00079EF1 (30B).
// Range destroy over 12-byte narrow basic_string via rowed dtor 0x00142D70; stride 0x0C proves element width.
// Callers 0x00079EF1 0x0007A7AA 0x000C0399 are vector clear/dtor bodies awaiting this range.
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

#include <vector>
namespace _STL {
template <class T> class char_traits {};
template <class CharT, class Traits, class Alloc>
class basic_string {
public:
	~basic_string();
private:
	char m_pad[12];
};
}
template class _STL::vector<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, _STL::allocator<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > >;
