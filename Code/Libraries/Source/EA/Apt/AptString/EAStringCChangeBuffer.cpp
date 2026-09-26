// cl: /O2 /DNDEBUG /MD
// ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z, retail 0x006D4AA0 (336B,
// abuts Assign at 0x006D4BF0). BFME2 rewrite of the BFME1 EAStringCMid.cpp
// donor: two range asserts (EAString.cpp lines 0x7DD/0x7DE) plus Reserve,
// SetSize and FreeData calls in place of the donor's inline alloc/stores.
// Reserve 0x006D3760, SetSize 0x006D3BC0 and FreeData 0x006D2EB0 are rowed;
// memmove rides the 0x00629506 import thunk; memcpy is intrinsic (rep movs).
// Called by rowed Assign 0x006D6250.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

#pragma intrinsic(memcpy)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
public:
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

	void SetSize(int size);
	void Reserve(int size);
	static void FreeData(StringDataC *data);

private:
	StringDataC *m_pData;

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);
};

extern EAStringC::StringDataC g_eaEmptyStringData; // 0x00DDC020

// ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z
void EAStringC::ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
	unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize)
{
	if (!(uSizeCopy + uOffsetCopy <= m_pData->m_uSize)) {
		g_bfmeAptAssertAtE17734("uSizeCopy + uOffsetCopy <= GetLength()",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x7DD);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!(uSizeCopy <= uSizeToReserve)) {
		g_bfmeAptAssertAtE17734("uSizeCopy <= uSizeToReserve",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x7DE);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}

	StringDataC *oldData = m_pData;
	if (oldData->m_uRefCount == 1 && uSizeToReserve <= oldData->m_uMaxSize) {
		if (uOffsetCopy != 0)
			memmove((char *)oldData + sizeof(StringDataC),
				(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		SetSize(uInternalSize);
		m_pData->m_uHash = 0;
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)m_pData + sizeof(StringDataC))[uInternalSize] = 0;
		return;
	}

	if (uSizeToReserve != 0) {
		Reserve(uSizeToReserve + (uSizeToReserve >> 3));
		SetSize(uInternalSize);
		m_pData->m_uHash = 0;
		memcpy((char *)m_pData + sizeof(StringDataC),
			(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)m_pData + sizeof(StringDataC))[uInternalSize] = 0;
	} else {
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}

	FreeData(oldData);
}
