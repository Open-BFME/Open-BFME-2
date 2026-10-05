// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva005F1A5FGet@@YA_NPBDPAH@Z @0x005F1A5F 150B: free cdecl bool const-char plus int-out with index GetParam plus empty plus isdigit plus atoi 0-5.
// Evidence: unlock lane; string index plus atoi plus releaseBuffer; pin Rva004128F0GetParam plus IAT isdigit atoi; extern g_Rva0107301CEmptyString; callers 0x005F1B02 0x005F1B25.
#include "ascii_string.h"

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr005F1A5F(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

bool __cdecl Rva005F1A5FGet(const char *params, int *out)
{
	if (params == 0)
		return false;
	AsciiString tmp;
	if (!Rva004128F0GetParam(params, "index", tmp))
		return false;
	char *t = *(char * *)(void *)&tmp;
	if (t == 0 || *(unsigned short *)(t + 4) == 0)
		return false;
	if (!isdigit(t[8]))
		return false;
	int v = atoi(GetStr005F1A5F(tmp));
	if (v < 0 || v >= 6)
		return false;
	*out = v;
	return true;
}
