// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<FlightDeckBehavior::FlightDeckInfo>::_M_insert_overflow
// at 0x00627BC0 and the __uninitialized_fill_n it calls at 0x00626E90.  Split
// out of FlightDeckBehavior.cpp because retail built these without /G7 --
// shl eax,3 for the 24-byte stride and a byte load plus test where that unit
// writes three adds and a compare against memory -- as it did the
// vector<AngleFXInfo> growth path at 0x00626150 next to them.  The
// __uninitialized_copy at 0x00626E40 stays a call, as FlightDeckBehavior.cpp
// already has it.

// Capture the existing GameMemory release binding before STLport imports ::free.
namespace _STL { void __cdecl free(void *); }
static __forceinline void releaseFlightDeckStorage(void *storage)
{
    _STL::free(storage);
}
#include <vector>

enum ObjectID
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	struct FlightDeckInfo
	{
		Coord3D m_prep;
		float m_orientation;
		int m_runway;
		ObjectID m_objectInSpace;
	};
};

// Retail growth releases through GameMemory at RVA 0x00030830.
namespace _STL {
template <> inline void allocator<FlightDeckBehavior::FlightDeckInfo>::deallocate(
    FlightDeckBehavior::FlightDeckInfo *storage, size_type) const
{
    if (storage != 0) releaseFlightDeckStorage(storage);
}
}

// These operations bind to the copies in FlightDeckBehavior.cpp.
namespace _STL {
template <> void vector<FlightDeckBehavior::FlightDeckInfo>::reserve(unsigned int);
template <> template <> FlightDeckBehavior::FlightDeckInfo *vector<FlightDeckBehavior::FlightDeckInfo>::_M_allocate_and_copy<FlightDeckBehavior::FlightDeckInfo *>(unsigned int, FlightDeckBehavior::FlightDeckInfo *, FlightDeckBehavior::FlightDeckInfo *);
}

template class _STL::vector<FlightDeckBehavior::FlightDeckInfo, _STL::allocator<FlightDeckBehavior::FlightDeckInfo> >;
