// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?MultiByteToWideCharSingleLine@@YA?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@PBD@Z, retail 0x003288E9 (195B).
// Converts a narrow GameSpy string to a wide STLport string for chat and room
// responses, replacing LF/CR with spaces. Donor: BFME1
// Code/GameEngine/Source/GameNetwork/GameSpy/Thread/MultiByteToWideCharSingleLine.cpp
// (same shape, CP_UTF8 65001, double-length alloc, memset, wcschr loops).
// Callers: 0x005511E5 (wcsncpy into stack buffer), 0x0038BE17 (assign to
// PeerResponse::text), 0x000AA966 and 9 more waiting on this body.

#include <string>

extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" void *__cdecl memset(void *dest, int c, unsigned int n);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
	unsigned int codePage, unsigned long flags, const char *src, int srcLen,
	unsigned short *dest, int destLen);
// CRT <string.h> already declares ::wcschr (plain under /D_CRTIMP=); keep the
// dllimport IAT form retail uses in a separate scope to avoid C2375.
namespace WcschrIAT
{
extern "C" __declspec(dllimport) unsigned short *__cdecl wcschr(
	const unsigned short *s, unsigned short c);
}

_STL::wstring MultiByteToWideCharSingleLine(const char *orig)
{
	int len = strlen(orig);
	len += len;
	unsigned short *dest = new unsigned short[len + 1];
	memset(dest, 0, (len + 1) * sizeof(unsigned short));
	MultiByteToWideChar(65001, 0, orig, -1, dest, len);
	unsigned short *c = 0;
	do {
		c = WcschrIAT::wcschr(dest, L'\n');
		if (c)
			*c = L' ';
	} while (c);
	do {
		c = WcschrIAT::wcschr(dest, L'\r');
		if (c)
			*c = L' ';
	} while (c);
	_STL::wstring ret = dest;
	delete [] dest;
	return ret;
}
