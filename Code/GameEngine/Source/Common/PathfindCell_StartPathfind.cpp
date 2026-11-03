// cl: /DNDEBUG /MD
// ?StartPathfind@PathfindCell@@QAE_NH@Z, retail 0x0052DA95, 47 bytes.
// Holder reset via rowed MixFileInfoBuffer::bfmeUnlink 0x002E6BE2 then field clears.
// Evidence: unlock lane unblocking 7 callers; callee rowed; offsets +8 +0x10 +0x12 +0x2c bits.
#include "../../Include/Common/MixFileInfoBuffer.h"
#include "../../Include/GameLogic/PathfindCell.h"

bool PathfindCell::StartPathfind(int)
{
	((MixFileInfoBuffer *)m_info)->bfmeUnlink();
	((MixFileInfoBuffer *)m_info)->field08 = 0;
	((MixFileInfoBuffer *)m_info)->field12 = 0;
	((MixFileInfoBuffer *)m_info)->field10 = 0;
	((MixFileInfoBuffer *)m_info)->m_flags &= ~8u;
	((MixFileInfoBuffer *)m_info)->m_flags &= ~16u;
	return true;
}
