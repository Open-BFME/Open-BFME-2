// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
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

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

// StringBase<char>::str() (TheNullChr for an empty string) of a temporary.
static inline const char *Rva002162CFStr(const AsciiString &s)
{
	return ((const StringBase<char> *)&s)->str();
}

AsciiString __cdecl Rva00222834Get(int value);
char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00511C3AFlag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

int __cdecl Rva00511C3AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &a, const bool &b)
{
	return target->invoke(owner, name, 2, Rva002162CFStr(Rva00222834Get(a)), (void *)Rva00511C3AFlag(b), 0, 0, 0);
}
