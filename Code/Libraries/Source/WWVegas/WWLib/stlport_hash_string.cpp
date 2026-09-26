// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?__stl_hash_string@_STL@@YAIPBD@Z, retail 0x0002BA61, 24 bytes.
// Verbatim STLport 4.5.3 stl/_hash_fun.h imul-5 loop (unsigned long
// accumulator, signed-char summand, test-first codegen): the sole hash leaf
// for the Eva string hashtable plus four string users (existing pin),
// reached from the AsciiString hash at 0x55056 among others.

namespace _STL
{

// Donor stl/_hash_fun.h lines 42-50 verbatim (_STLP_FIX_LITERAL_BUG is
// empty; size_t is 32-bit here so the signature stays YAIPBD). /G7 selects
// imul for the x5 step where the default /O1 strength-reduces it to lea.
unsigned int __cdecl __stl_hash_string(const char *__s)
{
	unsigned long __h = 0;
	for (; *__s; ++__s)
		__h = 5 * __h + *__s;

	return static_cast<unsigned int>(__h);
}

}
