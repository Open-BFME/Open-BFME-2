// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva000B992CBuild@@YA?AVAsciiString@@ABV1@0_NH@Z 0x000B992C 198B
// Evidence: unlock lane; AsciiString locals via friend StringBase ctor copy release rows; isEmpty set concat via StringBase casts; sprintf IAT "%d"; empty-string extern; callers 0x000BE027 0x000BF7E8 unclaimed.

#include "ascii_string.h"
// sprintf stays a DLL import; the AsciiString code needs /D_CRTIMP=.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP

// Matched DIR32 references place this empty string at VA 0x00BBAC1C; its
// retail byte is 0x00. This TU already uses the string in AsciiString code.
extern const char g_Rva0107301CEmptyString[] = { 0 };

AsciiString Rva000B992CBuild(const AsciiString &asciiString, const AsciiString &a2, int dummy, bool flag, int num)
{
	AsciiString local(g_Rva0107301CEmptyString);
	char tmp[64];
	if (!((const StringBase<char> &)asciiString).isEmpty())
	{
		((StringBase<char> &)local).set((const StringBase<char> &)asciiString);
		sprintf(tmp, "%d", num);
		if (flag)
			((StringBase<char> &)local).concat(tmp);
		char dot[2];
		dot[0] = '.';
		((StringBase<char> &)local).concat(dot, 1);
		((StringBase<char> &)local).concat((const StringBase<char> &)a2);
		if (flag)
			((StringBase<char> &)local).concat(tmp);
	}
	else
		((StringBase<char> &)local).set((const StringBase<char> &)a2);
	return local;
}
