// cl: /DNDEBUG /MD /D_CRTIMP=
// ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z, retail 0x006D4AA0 (336B,
// abuts Assign at 0x006D4BF0). BFME2 rewrite of the BFME1 EAStringCMid.cpp
// donor: two range asserts (EAString.cpp lines 0x7DD/0x7DE) plus Reserve,
// SetSize and FreeData calls in place of the donor's inline alloc/stores.
// Reserve 0x006D3760, SetSize 0x006D3BC0 and FreeData 0x006D2EB0 are rowed;
// memmove rides the 0x00629506 import thunk; memcpy is intrinsic (rep movs).
// Called by rowed Assign 0x006D6250.

#include <string.h>

#pragma intrinsic(memcpy)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../Apt/EAStringC.h"

extern EAStringC::StringDataC g_eaEmptyStringData; // 0x00DDC020

// ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z
void EAStringC::ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
	unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize)
{
	if (!(uSizeCopy + uOffsetCopy <= data->m_uSize)) {
		g_bfmeAptAssertAtE17734("uSizeCopy + uOffsetCopy <= GetLength()",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x7DD);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!(uSizeCopy <= uSizeToReserve)) {
		g_bfmeAptAssertAtE17734("uSizeCopy <= uSizeToReserve",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x7DE);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}

	StringDataC *oldData = data;
	if (oldData->m_uRefCount == 1 && uSizeToReserve <= oldData->m_uMaxSize) {
		if (uOffsetCopy != 0)
			memmove((char *)oldData + sizeof(StringDataC),
				(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		SetSize(uInternalSize);
		data->m_uHash = 0;
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)data + sizeof(StringDataC))[uInternalSize] = 0;
		return;
	}

	if (uSizeToReserve != 0) {
		Reserve(uSizeToReserve + (uSizeToReserve >> 3));
		SetSize(uInternalSize);
		data->m_uHash = 0;
		memcpy((char *)data + sizeof(StringDataC),
			(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)data + sizeof(StringDataC))[uInternalSize] = 0;
	} else {
		data = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}

	FreeData(oldData);
}
