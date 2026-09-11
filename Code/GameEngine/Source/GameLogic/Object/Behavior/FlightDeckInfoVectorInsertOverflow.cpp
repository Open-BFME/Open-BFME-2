// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <vector>

enum ObjectID
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

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

template class _STL::vector<FlightDeckBehavior::FlightDeckInfo, _STL::allocator<FlightDeckBehavior::FlightDeckInfo> >;
