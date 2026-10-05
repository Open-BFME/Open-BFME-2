// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@H@Z @0x001FA85C 129B
// STLport 4.5.3 basic_ostringstream<char> openmode ctor (mode default out).
// Donor vendor/stlport/stl/_sstream.c basic_ostringstream::__mode version.
// Evidence: ret 8 single openmode param plus virtual-base flag; callees
// basic_ios ctor 0x000134D0 and basic_ostream ctor 0x000163B0 and stringbuf
// ctor 0x001F6813 and init 0x000162F0; 34 writeINI-style callers.

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

#include <sstream>

template _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >::basic_ostringstream(_STL::ios_base::openmode);
