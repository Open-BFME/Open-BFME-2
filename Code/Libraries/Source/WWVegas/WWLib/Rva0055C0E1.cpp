// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
// ?Rva0055C0E1Write@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABURGBColor@@@Z at 0x0055C0E1 size 170
// Evidence: unlock lane; writes "R:"/"G:"/"B:" with int-scaled color components via
// _M_put_nowiden/_M_put_num/_M_put_char; caller 0x0055C263 writeINI; RGBColor layout red/green/blue floats.

#include <ostream>

// Numeric insertion calls the separately rowed long-output worker. Keep
// this unit's independently rowed facet lookup without emitting another worker.
namespace _STL {
template <> basic_ostream<char, char_traits<char> > &
_M_put_num<char, char_traits<char>, long>(basic_ostream<char, char_traits<char> > &, long);
}
template const _STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > > &
_STL::use_facet<_STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > > >(const _STL::locale &);

#include "../../../Include/Lib/RGBColor.h"
// bfme link decl-only begin
namespace _STL { template <> bool basic_ios<char, char_traits<char> >::_S_eof(int); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> bool ostreambuf_iterator<char, char_traits<char> >::failed() const; }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > num_put<char, ostreambuf_iterator<char, char_traits<char> > >::put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, long) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_put_char@?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@QAEXD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void basic_ostream<char,char_traits<char> >::_M_put_char(char); }

extern float g_00BC2900;
// g_00BC2900: matched references place it at VA 0xbc2900 (retail .rdata value 255.0f).
float g_00BC2900 = 255.0f;
extern float g_Va007C26F0;

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva0055C0E1Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    const RGBColor &color)
{
    os << "R:" << (int)(color.red * g_00BC2900 + g_Va007C26F0) << ' ';
    os << "G:" << (int)(color.green * g_00BC2900 + g_Va007C26F0) << ' ';
    os << "B:" << (int)(color.blue * g_00BC2900 + g_Va007C26F0);
    return os;
}
