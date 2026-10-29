// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <string>
// Canonical default construction is supplied by retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }
#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// Use the independently verified bool reader at retail RVA 0x000091D0.
namespace _STL {
template <> istreambuf_iterator<char, char_traits<char> >
num_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(
    istreambuf_iterator<char, char_traits<char> >,
    istreambuf_iterator<char, char_traits<char> >, ios_base &, int &, bool &) const;
}

// istreambuf_iterator<char>::equal is retail's 126-byte body at 0x0000FA00, owned by
// stlport_narrow_istreambuf_iterator_equal.cpp. This unit's copy (with _M_getc out of
// line) is not retail's and came before it in link order; the body still inlines
// here, imported, so the unit emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool istreambuf_iterator<char, char_traits<char> >::equal(const istreambuf_iterator<char, char_traits<char> >& __i) const {
  if (this->_M_buf)
    this->_M_getc();
  if (__i._M_buf)
    __i._M_getc();
  return this->_M_eof == __i._M_eof;
}
}
// The complete native float scanners are owned by the read_float units
// (F850 narrow;10420 wide). Keep this unit's generic copies out of the link.
namespace _STL {
template <> bool _M_read_float<istreambuf_iterator<char, char_traits<char> >, char>(
    string &, istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &, ios_base &, char *);
}
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// Use the complete retail scanner at 0x00007C90 rather than a competing
// generic header implementation.
namespace _STL {
template <> int _M_get_base_or_zero<istreambuf_iterator<char, char_traits<char> >, char>(
    istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &, ios_base &, char *);
}

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > num_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, ios_base &, int &, long double &) const; }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > _M_do_get_integer<istreambuf_iterator<char, char_traits<char> >, unsigned short, char>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, ios_base &, int &, unsigned short &, char *); }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > _M_do_get_integer<istreambuf_iterator<char, char_traits<char> >, long, char>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, ios_base &, int &, long &, char *); }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > _M_do_get_integer<istreambuf_iterator<char, char_traits<char> >, unsigned long, char>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, ios_base &, int &, unsigned long &, char *); }
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char, char_traits<char> >, unsigned short>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int, unsigned short &, int, bool, char, basic_string<char, char_traits<char>, allocator<char> > const &, __false_type const &); }
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char, char_traits<char> >, long>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int, long &, int, bool, char, basic_string<char, char_traits<char>, allocator<char> > const &, __true_type const &); }
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char, char_traits<char> >, unsigned long>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int, unsigned long &, int, bool, char, basic_string<char, char_traits<char>, allocator<char> > const &, __false_type const &); }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > num_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, ios_base &, int &, float &) const; }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > num_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, ios_base &, int &, double &) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__get_integer@V?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@_K@_STL@@YA_NAAV?$i:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char,char_traits<char> >,unsigned __int64>(istreambuf_iterator<char,char_traits<char> > &,istreambuf_iterator<char,char_traits<char> > &,int,unsigned __int64 &,int,bool,char,basic_string<char,char_traits<char>,allocator<char> > const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__get_integer@V?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@_J@_STL@@YA_NAAV?$i:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char,char_traits<char> >,__int64>(istreambuf_iterator<char,char_traits<char> > &,istreambuf_iterator<char,char_traits<char> > &,int,__int64 &,int,bool,char,basic_string<char,char_traits<char>,allocator<char> > const &,__true_type const &); }
// Suppress this TU's non-retail copy of ??$_M_do_get_integer@V?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@ID@_STL@@YA?AV?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> istreambuf_iterator<char,char_traits<char> > _M_do_get_integer<istreambuf_iterator<char,char_traits<char> >,unsigned int,char>(istreambuf_iterator<char,char_traits<char> > &,istreambuf_iterator<char,char_traits<char> > &,ios_base &,int &,unsigned int &,char *); }
// Suppress this TU's non-retail copy of ??$__get_integer@V?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@I@_STL@@YA_NAAV?$is:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool __get_integer<istreambuf_iterator<char,char_traits<char> >,unsigned int>(istreambuf_iterator<char,char_traits<char> > &,istreambuf_iterator<char,char_traits<char> > &,int,unsigned int &,int,bool,char,basic_string<char,char_traits<char>,allocator<char> > const &,__false_type const &); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// The 64-bit scanners have their own retail providers, like the 16/32-bit
// instances above. Keep this explicit class instantiation from emitting twins.
namespace _STL {
template <> bool __get_integer<istreambuf_iterator<char, char_traits<char> >, unsigned __int64>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int, unsigned __int64 &, int, bool, char, const string &, const __false_type &);
template <> bool __get_integer<istreambuf_iterator<char, char_traits<char> >, __int64>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int, __int64 &, int, bool, char, const string &, const __true_type &);
}
template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;

// Keep the two independently rowed string-termination helpers emitted.
template void _STL::basic_string<char>::_M_terminate_string();
template void _STL::basic_string<char>::_M_terminate_string_aux(const _STL::__true_type &);

// Taking these addresses preserves the three independently rowed header helpers
// formerly emitted only by the removed generic scanner. These constants are
// emission anchors, not claimed retail data.
void (*const bfmeNarrowFloatInitAnchor)(const _STL::ctype<char> &, char &, char &, char &, char &, char *) = &_STL::_Initialize_get_float;
bool (*const bfmeNarrowFloatDigitSeparatorAnchor)(char &, char, const char *) = &_STL::__get_fdigit_or_sep;
bool (*const bfmeNarrowFloatDigitAnchor)(char &, const char *) = &_STL::__get_fdigit;

// Native 18060..1806F: the out-of-line use_facet<ctype<char> > (push
// ctype<char>::id VA 0x00DA61E0, locale::_M_use_facet), an orphan .text hole
// beside this unit's empty() copy at 0x00018070.
template const _STL::ctype<char> &_STL::use_facet<_STL::ctype<char> >(const _STL::locale &);

// Emission anchors for independently rowed helpers; not claimed retail data.
_STL::string (_STL::numpunct<char>::*const bfmeNumGetTrueNameAnchor)() const = &_STL::numpunct<char>::truename;
_STL::string (_STL::numpunct<char>::*const bfmeNumGetFalseNameAnchor)() const = &_STL::numpunct<char>::falsename;
const char &(_STL::basic_string<char>::*const bfmeNumGetConstSubscriptAnchor)(size_t) const = &_STL::basic_string<char>::operator[];

// Retain the rowed helpers formerly emitted by the generic 64-bit scanners.
template bool _STL::operator!=<char, _STL::char_traits<char> >(const _STL::istreambuf_iterator<char, _STL::char_traits<char> > &, const _STL::istreambuf_iterator<char, _STL::char_traits<char> > &);
extern int (*const bfmeNumGetDigitTableAnchor)(unsigned int) = &_STL::__get_digit_from_table;
extern bool (_STL::string::*const bfmeNumGetEmptyAnchor)() const = &_STL::string::empty;
extern size_t (_STL::string::*const bfmeNumGetSizeAnchor)() const = &_STL::string::size;
extern __int64 (*const bfmeNumGetSignedMinAnchor)() = &_STL::numeric_limits<__int64>::min;
extern __int64 (*const bfmeNumGetSignedMaxAnchor)() = &_STL::numeric_limits<__int64>::max;
extern unsigned __int64 (*const bfmeNumGetUnsignedMaxAnchor)() = &_STL::numeric_limits<unsigned __int64>::max;
