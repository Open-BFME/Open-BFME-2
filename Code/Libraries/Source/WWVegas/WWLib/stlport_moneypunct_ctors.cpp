// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// Reconstructed STLport 4.5.3 facet construction from the vendor layouts and
// retail code. Constructor identities independently follow PE vtable RTTI.
// Modified reconstruction; no new address aliases are introduced.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
namespace _STL {
static void _Classic_monetary_formats(money_base::pattern& positive,money_base::pattern& negative) {
 positive.field[0] = (char)money_base::symbol;
 positive.field[1] = (char)money_base::sign;
 positive.field[2] = (char)money_base::none;
 positive.field[3] = (char)money_base::value;
 negative.field[0] = (char)money_base::symbol;
 negative.field[1] = (char)money_base::sign;
 negative.field[2] = (char)money_base::none;
 negative.field[3] = (char)money_base::value;
}
moneypunct<char,true>::moneypunct(size_t refs) : locale::facet(refs) { _Classic_monetary_formats(_M_pos_format,_M_neg_format); }
moneypunct<char,false>::moneypunct(size_t refs) : locale::facet(refs) { _Classic_monetary_formats(_M_pos_format,_M_neg_format); }
moneypunct<wchar_t,true>::moneypunct(size_t refs) : locale::facet(refs) { _Classic_monetary_formats(_M_pos_format,_M_neg_format); }
moneypunct<wchar_t,false>::moneypunct(size_t refs) : locale::facet(refs) { _Classic_monetary_formats(_M_pos_format,_M_neg_format); }
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@D$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_grouping@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ=?do_grouping@?$moneypunct@D$00@_STL@@MBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_curr_symbol@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_positive_sign@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ")
#pragma comment(linker, "/alternatename:?do_negative_sign@?$moneypunct@G$0A@@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ=?do_curr_symbol@?$moneypunct@G$00@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@XZ")
