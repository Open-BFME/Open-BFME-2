// cl: /DNDEBUG /MD
// ?StartPathfind@PathfindCell@@QAE_NH@Z, retail 0x0052DA95, 47 bytes.
// Holder reset via rowed MixFileInfoBuffer::bfmeUnlink 0x002E6BE2 then field clears.
// Evidence: unlock lane unblocking 7 callers; callee rowed; offsets +8 +0x10 +0x12 +0x2c bits.
class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class PathfindCell;
	char _pad00[8];
public:
	int m_08;
	char _pad0c[4];
	short m_10;
	short m_12;
	char _pad14[0x2c - 0x14];
	unsigned int m_2c;
};

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
	m_buf->m_08 = 0;
	m_buf->m_12 = 0;
	m_buf->m_10 = 0;
	m_buf->m_2c &= ~8u;
	m_buf->m_2c &= ~16u;
	return true;
}
