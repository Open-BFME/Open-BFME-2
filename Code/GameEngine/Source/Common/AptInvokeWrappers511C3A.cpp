// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00511C3AInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABHAB_N@Z @0x00511C3A 122B
// Typed Apt invoke wrapper int+bool (same family as the 10 landed
// AptInvokeWrappers.cpp rows on primary): an int via rowed Rva00222834Get and
// a bool via rowed Rva004E678BGet, through rowed Rva00222A8BTarget::invoke.
// Names are address-derived; the argument conversions and argc=2 follow the
// rowed sibling wrappers. Retail body spans 0x00511C3A..0x00511CB4.
// /G7 reproduces the bool load at +0x20; the rowed bool-Get callers
// Rva004E6816Fire and Rva005277D9Fire also use /O1 /G7.
// Keep these flags local to this TU; rehoming requires fresh verification.
#include "ascii_string.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

// StringBase<char>::str() (TheNullChr for an empty string) of a temporary.
static inline const char *Rva002162CFStr(const AsciiString &asciiString)
{
	return ((const StringBase<char> *)&asciiString)->str();
}

AsciiString __cdecl Rva00222834Get(int value);
char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00511C3AFlag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

int __cdecl Rva00511C3AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &m_intValue, const bool &boolValue)
{
	return target->invoke(owner, name, 2, Rva002162CFStr(Rva00222834Get(m_intValue)), (void *)Rva00511C3AFlag(boolValue), 0, 0, 0);
}
