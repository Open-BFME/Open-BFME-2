// cl: /O1 /arch:SSE /G7 /MD /ICode/Libraries/Include/Lib
#include "ArmyPlacerWaypoints.h"
#include "ArmyPlacerRecords.h"

// Native record queries 0x0037F6EA..0x0037F71F and 0x0037F87A..0x0037F8AC.
// Region id +0, coordinate outputs +4/+0x10, validity +0x1c. The
// context is the ArmyPlacer receiver, as both native and WB callers prove.
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
class LivingWorldLogic { public: char opaque[0xb0]; Rva0020EAF6View *lookup; };
extern LivingWorldLogic *TheLivingWorldLogic;
void Rva0037F4EA::rva0037F87A(void *context) {
    Rva0020E89C *record=TheLivingWorldLogic->lookup->rva0020EAF6(m_00);
    if(record) m_1c=static_cast<ArmyPlacer*>(context)->GetWalkOnWaypointLocations(
        reinterpret_cast<Rva0037F7B6Record*>(record),
        reinterpret_cast<Coord3D*>(&m_04),reinterpret_cast<Coord3D*>(&m_10));
}
void Rva0037F4EA::rva0037F6EA(void *context, int player) {
    Rva0020E89C *record=TheLivingWorldLogic->lookup->rva0020EAF6(m_00);
    if(record) m_1c=static_cast<ArmyPlacer*>(context)->GetStartPosWaypointLocations(
        player,reinterpret_cast<Coord3D*>(&m_04),reinterpret_cast<Coord3D*>(&m_10));
}
