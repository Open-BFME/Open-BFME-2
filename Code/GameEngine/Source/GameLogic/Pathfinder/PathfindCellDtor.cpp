// cl: /DNDEBUG /MD /EHsc
// Native52DD64..52DD75; WB AllocateCells passes its counterpart as the
// 16-byte PathfindCell destructor. WB Info::Free asserts in pathfinder_cell.inl
// independently identify the first-word info release. See five-link evidence.
#include "../../../Include/Common/MixFileInfoBuffer.h"
extern int TheMixFileInfoPool;
class PathfindCell {
public:
 ~PathfindCell();
 MixFileInfoBuffer *m_info;
 unsigned char m_rest[12];
};
inline PathfindCell::~PathfindCell() {
 if (m_info) m_info->releaseInto(&TheMixFileInfoPool);
}
// Preserve the existing inline destructor emission policy after identity repair.
#pragma inline_depth(0)
// ?bfmeEmitPathfindCellDtor@@YAXPAVPathfindCell@@@Z absent-from-retail
void bfmeEmitPathfindCellDtor(PathfindCell *pathfindCell) { pathfindCell->PathfindCell::~PathfindCell(); }
#pragma inline_depth()
