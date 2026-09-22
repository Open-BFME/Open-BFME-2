// cl: /O2 /DNDEBUG /MD
// Donor: BFME1 EAStringCAssign.cpp at 0x008A0480.
// Target: 0x006D6250 calls ChangeBuffer and SetSize; uses length/hash at +2/+6
// and payload at +8. Preserve the donor copy operation with that SetSize call.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

class EAStringC
{
	class StringDataC
	{
	public:
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

	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	void SetSize(int size);
	EAStringC &Assign(const EAStringC &other);
};

EAStringC &EAStringC::Assign(const EAStringC &other)
{
	unsigned otherSize = other.m_pData->m_uSize;
	unsigned n = m_pData->m_uSize;
	if (n > otherSize)
		n = otherSize;
	ChangeBuffer(otherSize, 0, n, CB_PUSH_ZERO, n);
	char *dst = GetInternalBuffer();
	memcpy(dst, other.GetInternalBuffer(), otherSize);
	dst[otherSize] = 0;
	SetSize(otherSize);
	m_pData->m_uHash = other.m_pData->m_uHash;
	return *this;
}
