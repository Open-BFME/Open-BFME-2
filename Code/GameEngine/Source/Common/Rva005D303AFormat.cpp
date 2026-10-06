// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?Rva005D303AFormat@@YA?AVUnicodeString@@HH@Z @0x005D303A 99B: by-value "%d/%d" formatter via g_00C380FC and UnicodeString::format 0x006CB5D0 with StringBase copy 0x00037050 and release 0x00036E70. Evidence: callers 0x005D3113 0x005D3178 0x005D31DD plus 0x005D3591 0x005D35C4 0x005D35F3; LINK BONUS for Rva005D30EEAptCounters; prev 0x005D2FD0 next 0x005D309D same flags.
#include "unicode_string.h"

extern const unsigned short g_00C380FC[];

UnicodeString __cdecl Rva005D303AFormat(int a, int b)
{
	UnicodeString tmp;
	if (b > 0)
		tmp.format(g_00C380FC, a, b);
	return tmp;
}
