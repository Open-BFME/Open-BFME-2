// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Reconstructed STLport 4.5.3 facet destruction from the vendor layouts and
// retail code. Destructor identities independently follow PE vtable RTTI
// (.?AV?$messages@D@_STL@@ at 0x007BC8C0, .?AV?$messages@G@_STL@@ at
// 0x007BC8EC). Twin of stlport_messages_ctors.cpp: the constructor TU proves
// the _Messages-impl layout (impl pointer at +0x0C, _M_delete flag at its
// +0x04); this TU proves the guarded-release teardown.
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
messages<char>::~messages() { if (_M_impl && _M_impl->_M_delete) delete _M_impl; }
messages<wchar_t>::~messages() { if (_M_impl && _M_impl->_M_delete) delete _M_impl; }
}
