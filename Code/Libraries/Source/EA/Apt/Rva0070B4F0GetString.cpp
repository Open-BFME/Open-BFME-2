// cl: /DNDEBUG /MD
// ?Rva0070B4F0GetString@@YAPAV..., retail 0x0070B4F0 (58B).
// StringPool constant accessor: asserts saConstant[eSC] non-empty via StringPool.inl:42 then returns its address.
// Evidence: own immediates "saConstant[eSC].IsEmpty() == false" + ".\string\StringPool.inl" line 0x2A;
// callers at 0x006DC9E7/0x006DCA07 push one int index and consume the return as EAStringC this;
// 0x0070A740 asserts StringPool::GetString(SC___proto__)->GetLength and UpdateHashValue.

#include <string.h>

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#pragma intrinsic(strlen)

#include "../../Apt/EAStringC.h"

extern "C" EAStringC bfmeObjDAE[178]; // existing owner at 0x00E18388

EAStringC *Rva0070B4F0GetString(int eSC)
{
	EAStringC *entry = &bfmeObjDAE[eSC];
	if (entry->IsEmpty()) {
		g_bfmeAptAssertAtE17734("saConstant[eSC].IsEmpty() == false", ".\\string\\StringPool.inl", 0x2A);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	return entry;
}

// ?Rva0070B530Find@@YAPAVEAStringC@@PBD@Z, retail 0x0070B530 (88B).
// Ghidra-unlisted reverse lookup over the same 178-entry constant table: the
// first entry whose length (rowed rva006D3750) equals strlen(text) and whose
// text matches case-insensitively (rowed rva006D3510); null when none does.
EAStringC *Rva0070B530Find(const char *text)
{
	unsigned int length = strlen(text);
	for (int i = 0; i < 178; ++i) {
		if (bfmeObjDAE[i].rva006D3750() == length && bfmeObjDAE[i].rva006D3510(text))
			return &bfmeObjDAE[i];
	}
	return 0;
}
