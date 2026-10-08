// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00077BF8Get@@YG_NABVAsciiString@@PBD@Z @0x00077BF8 33B: FileSystem existence wrapper extracting str with empty fallback then forwarding to 0x00600E3A. Evidence: callers 0x00077C19 0x00077E05 0x002E5D62; callee rowed; empty global g_Rva0107301CEmptyString.
#include "ascii_string.h"
bool __stdcall Rva00600E3AGet(const char *a, const char *b);
bool __stdcall Rva00077BF8Get(const AsciiString &a, const char *b)
{
	const char *t = *(const char *const *)&a;
	if (t)
		t += 8;
	else
		t = "";
	return Rva00600E3AGet(t, b);
}
