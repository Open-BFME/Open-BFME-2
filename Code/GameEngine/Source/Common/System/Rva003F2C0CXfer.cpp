// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva003F2C0CXfer@@YAPAVXfer@@PAV1@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@@Z @0x003F2C0C (202B):
// Free Xfer vector<BfmeE8> helper version {1,1} via slot 0x28, size via slot
// 0x2C/0x78, isSaving via slot 0x08, saving walks 8B elements via slot 0x50,
// loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094 then
// reserve 0x0030B876 plus push_back 0x00539A2E. Mirrors landed XferVectorBool
// 0x0060C253 and XferAsciiStringVector 0x0005A170. Caller 0x003F308C.
// Evidence: unlock lane, all callees rowed or pinned, unblocks 0x003F3054.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct BfmeE8 { int a; int b; };

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferException.h"


typedef _STL::vector<BfmeE8> VectorE8;

Xfer *Rva003F2C0CXfer(Xfer *xfer, VectorE8 *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = (UnsignedInt)vec->size();
	(*xfer == "std::vector") == count;

	if (xfer->IsStoring()) {
		BfmeE8 *end = vec->end();
		BfmeE8 *cur = vec->begin();
		while (cur != end) {
			*xfer == reinterpret_cast<Coord2D &>(*cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		vec->reserve(count);
		BfmeE8 value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			*xfer == reinterpret_cast<Coord2D &>(vec->back());
		}
	}
	return xfer;
}
