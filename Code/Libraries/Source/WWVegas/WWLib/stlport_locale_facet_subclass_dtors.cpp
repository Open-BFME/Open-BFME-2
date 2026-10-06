// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 declares every standard facet's destructor in the header and
// leaves the body to the library, so this is the translation unit that has to
// supply the seven the image carries. Each body is the same eleven bytes: the
// class's own vftable store and a tail jump into locale::facet::~facet at
// 0x000072E0, because the subclass has nothing of its own to tear down.
//
// Defining the destructor is also what makes MSVC emit the vftable, and with
// it the scalar deleting destructor - the ??_G bodies the image parks
// together at 0x000074D0..0x00007650. Each identity was read from the RTTI
// type descriptor behind the vftable the body stores.

#include <locale>

namespace _STL
{

ctype<wchar_t>::~ctype()
{
}

codecvt<char, char, mbstate_t>::~codecvt()
{
}

codecvt<wchar_t, char, mbstate_t>::~codecvt()
{
}

collate<char>::~collate()
{
}

collate<wchar_t>::~collate()
{
}

numpunct<char>::~numpunct()
{
}

numpunct<wchar_t>::~numpunct()
{
}

}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?do_is@?$ctype@G@_STL@@MBEPBGPBG0PAW4mask@ctype_base@2@@Z=?isRange@T2WideCtype@@QBEPBGPBG0PAI@Z")
#pragma comment(linker, "/alternatename:?do_toupper@?$ctype@G@_STL@@MBEPBGPAGPBG@Z=?toUpperRange@T2WideCtype@@QBEPBGPAG0@Z")
#pragma comment(linker, "/alternatename:?do_tolower@?$ctype@G@_STL@@MBEPBGPAGPBG@Z=?toLowerRange@T2WideCtype@@QBEPBGPAG0@Z")
#pragma comment(linker, "/alternatename:?do_widen@?$ctype@G@_STL@@MBEPBDPBD0PAG@Z=?widenRange@T2WideCtype@@QBEPBDPBD0PAG@Z")
#pragma comment(linker, "/alternatename:?do_narrow@?$ctype@G@_STL@@MBEPBGPBG0DPAD@Z=?narrowRange@T2WideCtype@@QBEPBGPBG0DPAD@Z")
#pragma comment(linker, "/alternatename:?do_in@?$codecvt@DDH@_STL@@MBE?AW4result@codecvt_base@2@AAHPBD1AAPBDPAD3AAPAD@Z=?do_out@?$codecvt@DDH@_STL@@MBE?AW4result@codecvt_base@2@AAHPBD1AAPBDPAD3AAPAD@Z")
#pragma comment(linker, "/alternatename:?do_out@?$codecvt@GDH@_STL@@MBE?AW4result@codecvt_base@2@AAHPBG1AAPBGPAD3AAPAD@Z=?do_out@codecvt_wide_char@_STL@@QBEHAAHPBG1AAPBGPAD3AAPAD@Z")
#pragma comment(linker, "/alternatename:?do_in@?$codecvt@GDH@_STL@@MBE?AW4result@codecvt_base@2@AAHPBD1AAPBDPAG3AAPAG@Z=?do_in@codecvt_wide_char@_STL@@QBEHAAHPBD1AAPBDPAG3AAPAG@Z")
#pragma comment(linker, "/alternatename:?do_transform@?$collate@D@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@PBD0@Z=?init@Rva00017890StringInit@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@PAD0@Z")
