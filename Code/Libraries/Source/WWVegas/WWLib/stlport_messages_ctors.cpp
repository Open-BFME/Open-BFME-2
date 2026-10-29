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
class _Messages {
public:
 _Messages();
 virtual int do_open(const string&,const locale&) const;
 virtual string do_get(int,int,int,const string&) const;
 virtual wstring do_get(int,int,int,const wstring&) const;
 virtual void do_close(int) const;
 virtual ~_Messages();
 bool _M_delete;
};
messages<char>::messages(_Messages* implementation) : locale::facet(1), _M_impl(implementation) { _M_impl->_M_delete = false; }
messages<wchar_t>::messages(_Messages* implementation) : locale::facet(1), _M_impl(implementation) { _M_impl->_M_delete = false; }
}
