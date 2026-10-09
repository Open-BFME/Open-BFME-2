#ifndef ARMY_PLACER_WAYPOINTS_H
#define ARMY_PLACER_WAYPOINTS_H
#include "Coord3D.h"
class Rva0037F7B6Record;
// WB ArmyPlacer names and native ECX receivers; no instance layout is asserted.
class ArmyPlacer {
public:
    bool GetStartPosWaypointLocations(int, Coord3D*, Coord3D*);
    bool GetWalkOnWaypointLocations(Rva0037F7B6Record*, Coord3D*, Coord3D*);
};
#endif
