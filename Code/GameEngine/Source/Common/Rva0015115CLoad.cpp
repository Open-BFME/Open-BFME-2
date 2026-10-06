// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0015115C@Rva0015115C@@QAE_NPAVChunkLoadClass@@@Z at 0x0015115C (231B).
// Chunk load with version at +4: reads version then first string at +0 via
// rowed Read 0x006151A0 plus pinned getBufferForRead 0x00036640, branches on
// version 1 second string at +8, 2-5 raw block at +0x0C, 6 dword at +0x1C,
// 7 byte at +0x20. Caller 0x00152F42 proves load shape. Layout mirrors
// Rva00151288 string plus versioned tail.
template <typename T>
class StringBase
{
public:
	char *getBufferForRead(int len);
private:
	void *m_data;
};

class ChunkLoadClass
{
public:
	unsigned long Read(void *buf, unsigned long len);
};

class Rva0015115C
{
public:
	bool rva0015115C(ChunkLoadClass *chunk);
private:
	StringBase<char> m_str00; // +0
	int m_version; // +4
	StringBase<char> m_str08; // +8
	char m_buf0C[0x10]; // +0x0C..+0x1B
	int m_1C; // +0x1C
	unsigned char m_20; // +0x20
};

bool Rva0015115C::rva0015115C(ChunkLoadClass *chunk)
{
	m_version = 0;
	if (chunk->Read(&m_version, 4) != 4)
		return false;
	int len = 0;
	if (chunk->Read(&len, 4) != 4)
		return false;
	if (chunk->Read(m_str00.getBufferForRead(len - 1), len) != (unsigned long)len)
		return false;
	if (m_version == 1) {
		if (chunk->Read(&len, 4) != 4)
			return false;
		if (chunk->Read(m_str08.getBufferForRead(len - 1), len) != (unsigned long)len)
			return false;
	} else if (m_version >= 2 && m_version <= 5) {
		int n = m_version * 4 - 4;
		if (chunk->Read(m_buf0C, n) != (unsigned long)n)
			return false;
	} else if (m_version == 6) {
		if (chunk->Read(&m_1C, 4) != 4)
			return false;
	} else if (m_version == 7) {
		if (chunk->Read(&m_20, 1) != 1)
			return false;
	} else
		return false;
	return true;
}
