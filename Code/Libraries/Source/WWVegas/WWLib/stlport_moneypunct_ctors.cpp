// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
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
namespace _STL {
inline void _Classic_monetary_formats(money_base::pattern& positive,money_base::pattern& negative) {
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
}
