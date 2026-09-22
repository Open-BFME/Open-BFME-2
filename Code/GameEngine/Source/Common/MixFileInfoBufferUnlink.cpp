// cl: /O1 /DNDEBUG /MD /EHsc
//
// MixFileInfoBuffer ?bfmeUnlink (retail 0x002E6BE2, 33 bytes): detaches a
// buffer through its backlink (+0x38) and next (+0x34) fields, zeroing both.
// Split from MixFileInfoBuffer_releaseInto.cpp, which must keep the helpers
// declared-only (same-TU definitions let the compiler trust ecx across the
// call; retail homes this in esi). The sibling ?bfmeLinkInto definition rides
// along present-unmatched; its row lives in the releaseInto TU. Donor:
// Open-BFME-1 Code/GameEngine/Source/Common/MixFileInfoBuffer_releaseInto.cpp
// with the link fields shifted +8.

class MixFileInfoBuffer
{
public:
	void releaseInto(void *head);

private:
	__declspec(noinline) void bfmeUnlink(void);
	__declspec(noinline) void bfmeLinkInto(MixFileInfoBuffer **head);

	char m_bfmeHead[0x34];
	MixFileInfoBuffer *m_bfmeNext; // +0x34
	MixFileInfoBuffer **m_bfmePrevNext; // +0x38
};

extern int TheMixFileInfoCount;

// ?bfmeUnlink@MixFileInfoBuffer@@AAEXXZ @0x2E6BE2
void MixFileInfoBuffer::bfmeUnlink(void)
{
	if (m_bfmePrevNext)
	{
		*m_bfmePrevNext = m_bfmeNext;

		if (m_bfmeNext)
			m_bfmeNext->m_bfmePrevNext = m_bfmePrevNext;

		m_bfmePrevNext = 0;
		m_bfmeNext = 0;
	}
}

// ?bfmeLinkInto@MixFileInfoBuffer@@AAEXPAPAV1@@Z (present-unmatched here)
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
