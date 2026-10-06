// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva000B9596Fill@@YAPAVAsciiString@@PAV1@IABV1@@Z retail 0x000B9596 27B
// Three-argument __uninitialized_fill_n dispatcher for AsciiString: builds
// the __false_type tag temporary and tail-calls the rowed four-argument
// body at 0x0002C4D8. Evidence: unblocks 0x000C0697 plus string-record
// neighbours with same bfmealloc flags.
#include <memory>

#include "ascii_string.h"

namespace _STL
{
template <> AsciiString *__uninitialized_fill_n<AsciiString *, unsigned int, AsciiString>(AsciiString *, unsigned int, const AsciiString &, const __false_type &);
}

AsciiString *Rva000B9596Fill(AsciiString *first, unsigned int n, const AsciiString &x)
{
	_STL::__false_type tag;
	return _STL::__uninitialized_fill_n(first, n, x, tag);
}
