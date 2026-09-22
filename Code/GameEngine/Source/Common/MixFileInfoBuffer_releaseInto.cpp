// cl: /O1 /DNDEBUG /MD /EHsc
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
	void releaseInto(void *head);

private:
	void bfmeUnlink(void);
	void bfmeLinkInto(MixFileInfoBuffer **head);

	char m_bfmeHead[0x34];
	MixFileInfoBuffer *m_bfmeNext; // +0x34
	MixFileInfoBuffer **m_bfmePrevNext; // +0x38
};

extern int TheMixFileInfoCount;

// ?bfmeLinkInto@MixFileInfoBuffer@@AAEXPAPAV1@@Z @0x52DBA4
void MixFileInfoBuffer::bfmeLinkInto(MixFileInfoBuffer **head)
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
