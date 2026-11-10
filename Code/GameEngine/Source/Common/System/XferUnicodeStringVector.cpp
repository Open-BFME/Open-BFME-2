// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?xferUnicodeStringVector@@YAPAVXfer@@PAV1@PAV?$vector@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@@Z retail 0x0005CD41 241B
// Evidence: chain lane via just-landed push_back 0x0005CBE7; donor BFME1 XferUnicodeStringVector.cpp; callees rowed reserve 0x0005A27E releaseBuffer 0x00036E70 _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094; strings "std::vector" and "Vector must be empty on load"; callers 0x0005E3E5.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "unicode_string.h"
// Preserve the native inline free without emitting per-unit allocator copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline void allocator<UnicodeString>::deallocate(UnicodeString *p, size_t) const { if(p) ::free(p); }
template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<UnicodeString *,UnicodeString,allocator<UnicodeString> >::deallocate(UnicodeString *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<UnicodeString> &>(*this), (UnicodeString *)0).deallocate(p,n); }
}




struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferException.h"


namespace _STL {
template <> void _Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
}

typedef _STL::vector<UnicodeString> UnicodeStringVector;

Xfer *xferUnicodeStringVector(Xfer *xfer, UnicodeStringVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	(*xfer == "std::vector") == count;

	if (xfer->IsStoring()) {
		UnicodeString *end = vec->end();
		UnicodeString *cur = vec->begin();
		while (cur != end) {
			*xfer == *cur;
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		UnicodeString value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			*xfer == vec->back();
		}
		--count;
	}
	return xfer;
}
