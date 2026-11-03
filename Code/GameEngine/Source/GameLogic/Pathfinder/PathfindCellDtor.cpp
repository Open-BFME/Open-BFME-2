// cl: /DNDEBUG /MD /EHsc
// Native52DD64..52DD75; WB AllocateCells passes its counterpart as the
// 16-byte PathfindCell destructor. WB Info::Free asserts in pathfinder_cell.inl
// independently identify the first-word info release. See five-link evidence.
#include "../../../Include/Common/MixFileInfoBuffer.h"
extern int TheMixFileInfoPool;
#include "../../../Include/GameLogic/PathfindCell.h"
inline PathfindCell::~PathfindCell() {
 if (m_info) ((MixFileInfoBuffer *)m_info)->releaseInto(&TheMixFileInfoPool);
}
// Preserve the existing inline destructor emission policy after identity repair.
#pragma inline_depth(0)
// ?bfmeEmitPathfindCellDtor@@YAXPAVPathfindCell@@@Z absent-from-retail
void bfmeEmitPathfindCellDtor(PathfindCell *pathfindCell) { pathfindCell->PathfindCell::~PathfindCell(); }
#pragma inline_depth()
