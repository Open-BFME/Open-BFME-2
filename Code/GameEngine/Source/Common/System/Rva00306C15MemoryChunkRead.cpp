// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva00306C15@Rva00306C49@@QAEHPAXH@Z @0x00306C15 45B
// Slot 0 of the four-slot table at VA 0x00BEDAA8, whose other slots are the
// rowed 0x00306C42 (cursor minus base), 0x00306C49 (seek from base, true)
// and 0x00306C58 (cursor at or past end) -- the read/tell/absoluteSeek/eof
// shape of Zero Hour's ChunkInputStream over a memory buffer with base +4,
// cursor +8 and end +0xC. read clamps the request to what remains, copies
// it with the CRT memcpy (0x006291A8), advances the cursor and returns the
// count. Retail clamps with cmovg, which MSVC 7.1 emits only under
// /arch:SSE, so this slot lives apart from VtableSlotBodiesR3.cpp's /O1
// siblings. The class name follows those siblings; the original is unknown.
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);

class Rva00306C49
{
public:
	int rva00306C15(void *dst, int len);
private:
	char m_pad00[4];
	char *m_base04;
	char *m_cursor08;
	char *m_end0C;
};

int Rva00306C49::rva00306C15(void *dst, int len)
{
	int avail = m_end0C - m_cursor08;
	if (len > avail)
		len = avail;
	memcpy(dst, m_cursor08, len);
	m_cursor08 += len;
	return len;
}
