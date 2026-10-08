// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva005E2D8AGet@@YAPAXPBD@Z retail 0x005E2D8A 97B
// Evidence: unlock lane; callers 0x005E2F49 and 0x005E3226; callees rowed 0x005E2CFA 0x00036410 plus pin 0x004128F0; string "id" plus empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"


bool __cdecl Rva004128F0GetParam(const char *a, const char *b, AsciiString &out);
void *__cdecl Rva005E2CFAGet(const char *s);

__forceinline const char *GetStr005E2D8A(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

void *Rva005E2D8AGet(const char *p)
{
	AsciiString tmp;
	if (!Rva004128F0GetParam(p, "id", tmp))
		return 0;
	return Rva005E2CFAGet(GetStr005E2D8A(tmp));
}
