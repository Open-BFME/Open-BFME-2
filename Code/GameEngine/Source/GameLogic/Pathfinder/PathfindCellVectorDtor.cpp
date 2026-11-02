// cl: /O1 /DNDEBUG /MD /EHsc
// Native2E70E8..2E7133: vector deleting destructor for 16-byte PathfindCell.
// The scalar callback is52DD64; source identity is independently established
// by the shipped WorldBuilder PathfindCell::Info::Free assertion/callback chain.
#include <new>
#include "../../../Include/GameLogic/PathfindCell.h"
// Existing delete-array emission anchor, renamed with the corrected type.
// ?bfmeEmitPathfindCellVectorDtor@@YAXPAVPathfindCell@@@Z absent-from-retail
void bfmeEmitPathfindCellVectorDtor(PathfindCell *pathfindCell) { delete[] pathfindCell; }
