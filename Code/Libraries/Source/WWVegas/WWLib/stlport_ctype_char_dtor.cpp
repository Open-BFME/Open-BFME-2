// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.5.3 src/ctype.cpp: ctype<char>'s destructor, retail 0x00016B60
// (36 bytes): vtable 0x00BBC3E4, the _M_delete test, delete[] of the table,
// then a tail jump to locale::facet's destructor 0x000072E0, which stays out
// of line here (stlport_ctype_char_ctor.cpp sees it inline for ??_Gfacet).
// Modified reconstruction: only this definition is taken from ctype.cpp.
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
ctype<char>::~ctype() {
  if (_M_delete)
    delete[] __CONST_CAST(mask *, _M_ctype_table);
}
}
