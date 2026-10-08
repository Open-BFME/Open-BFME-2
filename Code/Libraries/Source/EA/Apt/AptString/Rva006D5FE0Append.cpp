// cl: /DNDEBUG /MD
// ?rva006D5FE0@EAStringC@@QAEAAV1@PAXH@Z @ 0x006D5FE0, 136 bytes.
// Target evidence: this exact body is called by the matched 0x006D7350 Apt
// value-to-display-string worker with the looked-up string pointer and count 1.
// Its retail boundary decodes up to count UTF-8 code points with rowed
// rva006d4280, stops at a decoded zero or the requested count, clips the
// resulting byte span at the source NUL, then appends those bytes through the
// rowed ChangeBuffer with CB_PUSH_ZERO. The address-derived identity is kept.
// Donor context: BFME1 EAStringAppendBounded.cpp at reference commit
// 6583b3c1ff21db4a561285717028fdafc780b7db uses the same append/ChangeBuffer/
// copy pattern with a byte limit. Retail target evidence supplies the
// codepoint-count adaptation here; donor layout is not treated as target fact.

extern const char *rva006d4280(const char *pBuffer, int *pUnicode);
extern "C" void *__cdecl memcpy(void *destination, const void *source,
	unsigned int count);
#pragma intrinsic(memcpy)

class EAStringC
{
public:
	struct StringDataC
	{
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	EAStringC &rva006D5FE0(void *pSource, int nCodepoints);

private:
	StringDataC *m_pData;
	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero,
		unsigned int uInternalSize);
};

EAStringC &EAStringC::rva006D5FE0(void *pSource, int nCodepoints)
{
	const char *pText = static_cast<const char *>(pSource);
	const char *pEnd = pText;
	int codepoint;
	int decoded = 0;
	if (nCodepoints > 0)
	{
		do
		{
			pEnd = rva006d4280(pEnd, &codepoint);
			if (codepoint == 0)
				break;
			++decoded;
		} while (decoded < nCodepoints);
	}

	decoded = 0;
	unsigned int decodedBytes = static_cast<unsigned int>(pEnd - pText);
	const char *pScan = pText;
	if (decodedBytes != 0)
	{
		while ((*pScan++ != 0) && (static_cast<unsigned int>(++decoded) < decodedBytes))
			;
	}

	if (decoded != 0)
	{
		unsigned int oldSize = m_pData->m_uSize;
		unsigned int newSize = oldSize + decoded;
		ChangeBuffer(newSize, 0, oldSize, CB_PUSH_ZERO, newSize);
		memcpy(reinterpret_cast<char *>(m_pData) + sizeof(StringDataC) + oldSize,
			pText, static_cast<unsigned int>(decoded));
	}
	return *this;
}
