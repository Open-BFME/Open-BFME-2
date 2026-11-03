// cl: /DNDEBUG /MD
// ?StartPathfind@PathfindCell@@QAE_NH@Z, retail 0x0052DA95, 47 bytes.
// Holder reset via rowed MixFileInfoBuffer::bfmeUnlink 0x002E6BE2 then field clears.
// Evidence: unlock lane unblocking 7 callers; callee rowed; offsets +8 +0x10 +0x12 +0x2c bits.
#include "../../Include/Common/MixFileInfoBuffer.h"

class PathfindCell
{
public:
	bool StartPathfind(int arg);
private:
	MixFileInfoBuffer *m_buf;
};

bool PathfindCell::StartPathfind(int)
{
	m_buf->bfmeUnlink();
	m_buf->field08 = 0;
	m_buf->field12 = 0;
	m_buf->field10 = 0;
	m_buf->m_flags &= ~8u;
	m_buf->m_flags &= ~16u;
	return true;
}
