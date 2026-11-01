// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?xferAsciiStringVector@@YAPAVXfer@@PAV1@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z retail 0x0005A170 241B
// Evidence: unlock lane; donor is the rowed XferUnicodeStringVector.cpp 0x0005CD41
// (same 241B shape); callees rowed reserve 0x00057E02 plus pin push_back
// 0x0002DBE6 plus releaseBuffer 0x00036410 plus _bfmeFormatText 0x0060C36E
// plus pin _CxxThrowException 0x00629094; strings "std::vector" and
// "Vector must be empty on load"; callers 0x0005E934 0x002CED3F 0x0049FD94
// 0x004E3A02.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void vector<AsciiString,_STL::allocator<AsciiString> >::reserve(unsigned int); }
// bfme link decl-only end


struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferException.h"


namespace _STL {
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
}

typedef _STL::vector<AsciiString> AsciiStringVector;

Xfer *xferAsciiStringVector(Xfer *xfer, AsciiStringVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	(*xfer == "std::vector") == count;

	if (xfer->IsStoring()) {
		AsciiString *end = vec->end();
		AsciiString *cur = vec->begin();
		while (cur != end) {
			*xfer == *cur;
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		AsciiString value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			*xfer == vec->back();
		}
		--count;
	}
	return xfer;
}
