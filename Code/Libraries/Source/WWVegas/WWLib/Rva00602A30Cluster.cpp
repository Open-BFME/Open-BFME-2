// cl: /GR- /GX- /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// ??0strstreambuf@_STL@@QAE@PADH0@Z, retail 0x00602A30 (105 B).
// strstreambuf(char* __get, streamsize __n, char* __put): zero the allocator
// hooks and the dynamic/frozen/constant bits, then _M_setup(__get, __put, __n).
// The basic_streambuf<char,char_traits<char> > base constructor is the inline
// specialization of _streambuf.h (its _M_get/_M_put FILE areas at +0xC/+0x2C
// and _M_locale at +0x4C), and _M_setup is the 105 B body at 0x00602740.
// Exceptions are off (/GX-) because the retail body carries no __ehhandler;
// with /EHsc the same source emits a 149 B frame. Callee _M_setup is pinned.

#include <strstream>

namespace _STL {

strstreambuf::strstreambuf(char *__get, streamsize __n, char *__put)
{
	_M_alloc_fun = 0;
	_M_free_fun = 0;
	_M_dynamic = false;
	_M_frozen = false;
	_M_constant = false;
	_M_setup(__get, __put, __n);
}

}
