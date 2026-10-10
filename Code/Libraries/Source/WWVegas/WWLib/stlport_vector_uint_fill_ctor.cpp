// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<unsigned int>(n, value, allocator), retail 0x00511E1C
// (44 bytes), rowed here as an identical-code-folding alias of the
// vector<unsigned short> row at the same address. The element there is four
// bytes wide: the body calls the 4-byte _Vector_base(n, alloc) at 0x004F62A4
// (end of storage = start + n*4) and the 4-byte fill_n at 0x0007E48F, and
// AptMessenger's constructor 0x0051215B passes a dword zero; this spelling
// lets that caller bind the call without renaming the older row (whose name
// thousands of objects reference). unsigned int is the spelling the ledger
// already pins for both callees; the template argument itself is not
// recoverable from bytes.
#include <vector>

template _STL::vector<unsigned int, _STL::allocator<unsigned int> >::vector(
	unsigned int, const unsigned int &, const _STL::allocator<unsigned int> &);
