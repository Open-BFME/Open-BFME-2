// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _STL::__copy_backward worker for Rva00B6CF1 at 0x000B44C1, 47 bytes.
// 8-byte element (two AsciiStrings); count = (last-first)>>3, then
// decrement last/result and copy via rowed ??4Rva00B6CF1 at 0x000B433E.
// Caller wrapper at 0x000B67D9. Operator= declared only (rowed elsewhere).
#include <vector>

#include "ascii_string.h"

struct Rva00B6CF1
{
	~Rva00B6CF1();
	Rva00B6CF1 &operator=(const Rva00B6CF1 &o);
	AsciiString m_s0;
	AsciiString m_s1;
};

template Rva00B6CF1 *_STL::copy_backward<Rva00B6CF1 *, Rva00B6CF1 *>(Rva00B6CF1 *, Rva00B6CF1 *, Rva00B6CF1 *);
