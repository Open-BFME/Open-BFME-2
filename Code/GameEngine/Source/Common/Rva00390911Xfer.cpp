// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00390911XferCoordVector@@YAPAVXfer@@PAV1@PAUAICommandCoordVector@@@Z @0x00390911 205B evidence: Version 1 1 via slot 0x28 plus count via slots 0x2C 0x78 plus isSaving via 0x08 plus per-element via slot 0x60 plus reserve 0x390729 plus push_back 0x2CE7DC plus FormatText 0x60C36E plus Throw 0x629094 plus strings std-vector Vector-must-be-empty. Callers 0x390E29 0x45CB3A 0x48E57C 0x48E5CF. Donor Rva00426F17Xfer.cpp shape. Pin return void is wrong, retail returns Xfer.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include "../../../Libraries/Include/Lib/Coord3D.h"

// Call the canonical 12-byte allocator and keep only the inline proxy forwarding.
namespace _STL {
template <> Coord3D * allocator<Coord3D>::allocate(size_t, const void *) const;
template <> __declspec(dllimport) __forceinline
Coord3D * _STLP_alloc_proxy<Coord3D*,Coord3D,allocator<Coord3D> >::allocate(size_t count) {
 return __stl_alloc_rebind(static_cast<allocator<Coord3D>&>(*this),(Coord3D*)0).allocate(count,0);
}
}

#include "../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../Include/Common/Rva00390729Element.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<Rva00390729Element,allocator<Rva00390729Element> >::reserve(unsigned int); }

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see System/XferException.cpp).
#include "../../Include/Common/XferException.h"


struct AICommandCoordVector : public _STL::vector<Coord3D>
{
};

Xfer * __cdecl Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	UnsignedInt count = (UnsignedInt)vec->size();
	((*xfer == "std::vector") == count);
	if (xfer->IsStoring()) {
		Coord3D *end = vec->end();
		Coord3D *cur = vec->begin();
		while (cur != end) {
			(*xfer == reinterpret_cast<Coord3DBase &>(*cur));
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
		}
		reinterpret_cast<_STL::vector<Rva00390729Element> *>(vec)->reserve(count);
		Coord3D value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			(*xfer == reinterpret_cast<Coord3DBase &>(vec->back()));
		}
	}
	return xfer;
}
