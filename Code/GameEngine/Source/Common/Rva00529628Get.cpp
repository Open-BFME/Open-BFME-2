// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00529628Get@@YA_NPBDPAH@Z @0x00529628 112B evidence: free cdecl bool const-char plus int-out like caller 0x005297A0; GetParam index plus atoi 0-5 plus AsciiString temp; pin Rva004128F0GetParam plus IAT atoi plus releaseBuffer; string index; unblocks 6 callers
#include "ascii_string.h"

bool Rva004128F0GetParam(const char *a, const char *b, AsciiString &out);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

bool __cdecl Rva00529628Get(const char *section, int *out)
{
	AsciiString value;
	if (!Rva004128F0GetParam(section, "index", value))
		return false;
	const char *s = value.str();
	int v = atoi(s);
	if (v < 0 || v >= 6)
		return false;
	*out = v;
	return true;
}
