// cl: /DNDEBUG /MD /EHsc
//
// MixFileInfoBuffer intrusive-list file-unit: ?releaseInto (retail 0x0052DD41,
// 35 bytes) unlinks the buffer when linked, links it into the given pool
// list and decrements the live-buffer count; ?bfmeLinkInto (retail
// 0x0052DBA4, 39 bytes) detaches first only when linked, then reattaches at
// the head it is handed. Ported from Open-BFME-1
// Code/GameEngine/Source/Common/MixFileInfoBuffer_releaseInto.cpp, whose
// __forceinline helpers are outlined calls here (BFME2 retail calls them),
// with the link fields shifted +8 (next at +0x34, backlink at +0x38). The
// helpers stay declared-only in this TU: same-TU definitions let the compiler
// trust ecx across the call, while retail homes this in esi (declare-only
// proves the shape). Their bodies live in MixFileInfoBufferUnlink.cpp, which
// rows ?bfmeUnlink. Rowed releaseInto supersedes the bare pin at 0x0052DD41.

class MixFileInfoBuffer
{
public:
	MixFileInfoBuffer();
	void releaseInto(void *head);

private:
	void bfmeUnlink(void) throw();
	void bfmeLinkInto(MixFileInfoBuffer **head) throw();
	friend void Rva0052DBCDInit(void);

	char m_bfmeHead[0x34];
	MixFileInfoBuffer *m_bfmeNext; // +0x34
	MixFileInfoBuffer **m_bfmePrevNext; // +0x38
};

extern int TheMixFileInfoCount;
// TheMixFileInfoCount: VA 0xe049d4 (zero-filled .bss).
int TheMixFileInfoCount;
extern int TheMixFileInfoPool; // 0x00A049D0

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

MixFileInfoBuffer::MixFileInfoBuffer()
{
	m_bfmeNext = 0;
	m_bfmePrevNext = 0;
}

// ?bfmeLinkInto@MixFileInfoBuffer@@AAEXPAPAV1@@Z @0x52DBA4
void MixFileInfoBuffer::bfmeLinkInto(MixFileInfoBuffer **head) throw()
{
	if (m_bfmePrevNext)
		bfmeUnlink();

	m_bfmePrevNext = head;
	m_bfmeNext = *head;

	if (m_bfmeNext)
		m_bfmeNext->m_bfmePrevNext = &m_bfmeNext;

	*head = this;
}

// ?releaseInto@MixFileInfoBuffer@@QAEXPAX@Z @0x52DD41
void MixFileInfoBuffer::releaseInto(void *head)
{
	if (m_bfmePrevNext)
		bfmeUnlink();

	bfmeLinkInto((MixFileInfoBuffer **)head);

	--TheMixFileInfoCount;
}

// ?Rva0052DBCDInit@@YAXXZ @0x52DBCD 92B: pool initializer. Allocates 256
// MixFileInfoBuffer (0x3c00 bytes) via new[], constructs them through the
// vector ctor iterator (ctor at 0x52DB99 zeroes the link fields), then links
// each into TheMixFileInfoPool at 0x00A049D0 via bfmeLinkInto. Evidence:
// callers at 0x002E8BAC and 0x002F45A7 call it only when both the node and
// the pool head are null, then take from the pool; element size 0x3c matches
// the class layout (next +0x34 backlink +0x38); callees rowed.
void Rva0052DBCDInit(void)
{
	MixFileInfoBuffer *buffers = new MixFileInfoBuffer[256];
	for (int i = 0; i < 256; ++i)
		buffers[i].bfmeLinkInto((MixFileInfoBuffer **)&TheMixFileInfoPool);
}
