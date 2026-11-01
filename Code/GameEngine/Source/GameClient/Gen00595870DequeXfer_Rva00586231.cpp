// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
// ?Rva00586231Xfer@@YAPAVXfer@@PAV1@PAV?$deque@UGen_t_00595870_p12cd@@V?$allocator@UGen_t_00595870_p12cd@@@_STL@@@_STL@@@Z @0x00586231 212B: deque xfer std-deque then count then isSaving store-iterate else empty-check load-push_back. Evidence: rowed _M_subtract 0x004218A5 _M_increment 0x00421B1E push_back 0x00586204 _bfmeFormatText 0x0060C36E pin _CxxThrowException 0x00629094; strings std-deque Deque-must-be-empty-on-load; caller 0x00587075; sibling Gen00595870DequePushBackAux same flags.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <deque>
#include "ascii_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../../Libraries/Source/WWVegas/WWLib/Gen00595870Payload.h"

struct BfmeE12
{
	float x, y, z;
};

typedef _STL::deque<BfmeE12> E12Deque;

// The provider compiles the complete native push_back and its growth helper.
namespace _STL {
template<> void deque<Gen_t_00595870_p12cd>::push_back(const Gen_t_00595870_p12cd &);
}
typedef _STL::deque<Gen_t_00595870_p12cd> GenDeque;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../Common/System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferException.h"

Xfer *Rva00586231Xfer(Xfer *xfer, GenDeque *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	E12Deque *evec = (E12Deque *)vec;
	UnsignedInt count = (UnsignedInt)evec->size();
	(*xfer == "std::deque") == count;

	if (xfer->IsStoring()) {
		E12Deque::iterator end = evec->end();
		E12Deque::iterator cur = evec->begin();
		while (cur != end) {
			*xfer == reinterpret_cast<Coord3DBase &>((Gen_t_00595870_p12cd &)*cur);
			++cur;
		}
	} else {
		if (!evec->empty()) {
			throw XferException(4, "Deque must be empty on load");
		}
		Gen_t_00595870_p12cd value;
		while (count != 0) {
			--count;
			*xfer == reinterpret_cast<Coord3DBase &>(value);
			vec->push_back(value);
		}
	}
	return xfer;
}
