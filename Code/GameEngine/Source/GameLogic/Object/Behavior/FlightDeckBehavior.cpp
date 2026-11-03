// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// BFME 2 has no FlightDeckBehavior: game.dat holds no "FlightDeckBehavior"
// module string and no FlightDeckBehavior row is native to it. This unit used
// to carry Zero Hour's port; its out-of-line destructor emitted Zero Hour's
// FlightDeckBehavior and AIUpdateInterface vtables, whose 49 slots no object
// defines (the real link's largest unresolved group). What retail does hold
// are the two generic bodies that port happened to emit:
//
// - 0x004624A7, ExitInterface's base getNaturalRallyPoint (slot 9 of the
//   interface table 0x00C430B4): zero the three output floats, return false,
//   pop eight bytes. Defined out of line here against the canonical
//   ExitInterface.h, which declares it so.
// - 0x0008A64A, the range-destroy thunk over the 0xB8-byte runway element:
//   load the element, jump to its destructor (0x00089851, rowed in
//   FlightDeckBehaviorRunwayInfoDestructor.cpp). Emitted by explicit
//   instantiation over the same minimal element view that file uses.
#include <stl/_construct.h>
#include "../../../../Include/GameLogic/Module/ExitInterface.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	struct RunwayInfo
	{
		~RunwayInfo(void);
	};
};

bool ExitInterface::getNaturalRallyPoint(Coord3D &rallyPoint, bool offset) const
{
	rallyPoint.x = rallyPoint.y = rallyPoint.z = 0.0f;
	return false;
}

template void _STL::_Destroy<FlightDeckBehavior::RunwayInfo>(FlightDeckBehavior::RunwayInfo *);
