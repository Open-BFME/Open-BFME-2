// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva005D2505Get@@YA_NPBDPAH@Z @0x005D2505 112B
// Evidence: rowed Rva004128F0GetParam with index literal plus atoi import plus 0-6 range plus out int plus callers at 0x005D26D6 0x005D27CB 0x005D2809 0x005D2901 0x005D2943 0x005D2A34 plus AptRowListCallbacks OnRowHidden shape.
#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);

bool __cdecl Rva005D2505Get(const char *params, int *out)
{
	AsciiString indexText;
	if (!Rva004128F0GetParam(params, "index", indexText))
		return false;
	int index = atoi(indexText.str());
	if (index < 0 || index >= 6)
		return false;
	*out = index;
	return true;
}
