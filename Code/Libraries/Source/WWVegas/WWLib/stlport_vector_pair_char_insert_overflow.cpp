// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@U?$pair@$$CBVAsciiString@@D@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@D@_STL@@@2@@_STL@@IAEXPAU?$pair@$$CBVAsciiString@@D@2@ABU32@ABU__false_type@2@I_N@Z @0x0021E356 178B: vector<pair<const AsciiString,char>> growth path, same 178B sar-3/lea-8 shape as BfmeStringRecord00426A5B overflow 0x00426DE2 in same flags; calls rowed allocate 0x523D6C via ICF pin plus rowed copy 0x21AA7A plus rowed Construct 0x21A9B7 plus rowed fill_n 0x21AAA0 plus shared clear 0x4C3D8B; caller push_back 0x21E70A.
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

#include <memory>
#include <vector>

#include "ascii_string.h"
namespace _STL {
template <> void _Construct<struct pair<const AsciiString, char>, struct pair<const AsciiString, char> >(struct pair<const AsciiString, char> *, const struct pair<const AsciiString, char> &);
}
template void _STL::vector<struct _STL::pair<const AsciiString, char> >::_M_insert_overflow(
	struct _STL::pair<const AsciiString, char> *,
	const struct _STL::pair<const AsciiString, char> &,
	const _STL::__false_type &,
	unsigned int,
	bool);
template void _STL::vector<struct _STL::pair<const AsciiString, char> >::push_back(
	const struct _STL::pair<const AsciiString, char> &);
