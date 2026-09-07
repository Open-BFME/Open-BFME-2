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
ctype<char>::ctype(const mask* table,bool del,size_t refs)
 : locale::facet(refs), _M_ctype_table(table ? table : classic_table()),
   _M_delete(table && del) {}
}
