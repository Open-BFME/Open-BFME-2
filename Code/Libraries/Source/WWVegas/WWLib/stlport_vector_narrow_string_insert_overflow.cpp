// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<basic_string<char> > growth path, dedicated TU:
// _M_insert_overflow (retail 0x0007A307, 183B) and push_back (0x0007A773, 55B).
// Target evidence: the retail calls read this element's matched helpers,
// _Construct 0x00079A41, __uninitialized_fill_n 0x00079A94,
// __uninitialized_copy 0x00079A6E and _M_clear 0x00079EF1; push_back is the
// only caller of _M_insert_overflow. /G7 is what emits retail's imul-by-12
// scaling (the AnimSet sibling's IMUL recipe; /G6 keeps the lea chain), and
// /Ireference/shims/bfmealloc keeps allocate a two-argument out-of-line call
// into the 12-byte ICF allocate at 0x00395928. _Construct is declared but not
// defined so the copies call its matched body.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>

namespace _STL
{
template <> void _Construct<basic_string<char>, basic_string<char> >(basic_string<char> *, const basic_string<char> &);
}

template void _STL::vector<_STL::basic_string<char> >::_M_insert_overflow(
	_STL::basic_string<char> *, const _STL::basic_string<char> &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<_STL::basic_string<char> >::push_back(const _STL::basic_string<char> &);
