// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?__stl_string_hash@_STL@@YAIABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@1@@Z at retail 0x0060C9F0 (36B).
// Verbatim STLport 4.5.3 stl/_string_hash.h __stl_string_hash loop (unsigned long
// accumulator, signed-char summand, length-based): size() then data() then
// imul-5 loop over [start, finish). /G7 selects imul for the x5 step where the
// default /O1 strength-reduces it to lea (same as stlport_hash_string.cpp).
// Callers 0x0060CAEA 0x0060CD16 hash string keys then div to bucket then walk
// via basic_string operator== (0x00007780).

#include <string>

namespace _STL
{

// Donor stl/_string_hash.h __stl_string_hash verbatim for string (size_t is
// 32-bit here). Takes const string& (start at +0, finish at +4, len via sub).
size_t __stl_string_hash(const string &__s)
{
	unsigned long __h = 0;
	size_t __len = __s.size();
	const char *__data = __s.data();
	for (size_t __i = 0; __i < __len; ++__i)
		__h = 5 * __h + __data[__i];
	return size_t(__h);
}

}
