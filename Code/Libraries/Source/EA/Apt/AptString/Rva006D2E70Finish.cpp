// cl: /DNDEBUG /MD
// ?rva006D2E70@EAStringC@@QAEXXZ, retail 0x006D2E70 (60B).
// EAStringC refcount retain worker: validates the shared data refcount
// against the 0xFFFE cap unless it is the immortal empty singleton at
// 0x00DDC020, then takes one reference. Assertion triple is the EAString.inl
// 0xE1 "m_pData->m_uRefCount <= 0xfffe" check shared with the copy ctor.
// The cap test is a guarded fallthrough, not an early-return pair: with one
// retain site reached through `this`, VC7 keeps the object pointer in esi and
// emits retail's closing `mov esi,[esi]` / `inc word [esi]` rather than
// re-deriving the data pointer in eax.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../Apt/EAStringC.h"

// Retail empty singleton at VA 0x00DDC020, defined in EAStringCRefCount.cpp.
extern char g_eaEmptyStringData[16];

void EAStringC::rva006D2E70()
{
	StringDataC *current = data;
	if (current != (EAStringC::StringDataC *)g_eaEmptyStringData && current->m_uRefCount > 0xFFFE) {
		g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
		if (!g_bfmeAptBreakOnAssertAtDDC01C) {
			this->data->m_uRefCount++;
			return;
		}
		__debugbreak();
	}
	this->data->m_uRefCount++;
}