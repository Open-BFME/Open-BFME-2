// cl: /DNDEBUG /MD /D_CRTIMP=
// ?Find@EAStringC@@QAEHDH@Z, retail 0x006D38E0 (62B). Ported from Open-BFME-1
// Code/Libraries/Source/EA/Apt/AptString/EAStringCFind.cpp (BFME1 0x0089E230).
// Trimmed to the placed char-find body; the string-find overload is
// declared-only here. Callee strchr resolves via the existing ledger pin.

#include <string.h>
#pragma intrinsic(strlen)
#pragma intrinsic(memcmp)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../Apt/EAStringC.h"

// ?Find@EAStringC@@QAEHDH@Z
int EAStringC::Find(char c, int start)
{
	if (start >= (int)data->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strchr((reinterpret_cast<char *>(data) + sizeof(StringDataC)) + start, c);
	if (found)
		return found - (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	return -1;
}

// ?Find@EAStringC@@QAEHPBDH@Z, retail 0x006D3870 (102B). EAStringC
// string-find overload ported from BFME1 EAStringCFind donor plus BFME2
// null-text assert (EAString.cpp 0x286 via shared Apt triple). Uses rowed
// strstr thunk 0x00629850; callers at 0x006D60A2/0x006D7965; neighbours
// cmp 0x006D3860 and char-find 0x006D38E0 share /O2 /DNDEBUG /MD.
int EAStringC::Find(const char *s, int start)
{
	if (!(s != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x286);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (start >= (int)data->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strstr((reinterpret_cast<char *>(data) + sizeof(StringDataC)) + start, s);
	if (found)
		return found - (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	return -1;
}

// Gap bodies after Find (0x006D3920..0x006D3B96), all asserting through the
// shared Apt triple with EAString.cpp line numbers from retail. The original
// method names are not recovered: each keeps an address name. Four are
// unimplemented stubs (assert "false", return 0) whose argument counts come
// from their ret immediates; the last two are prefix/suffix tests.

// ?rva006D3920@EAStringC@@QAEHPBD@Z, retail 0x006D3920 (81B): text assert
// (line 0x2E7), then the "false" assert (0x2E8), returns 0.
int EAStringC::rva006D3920(const char *text)
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x2E7);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	g_bfmeAptAssertAtE17734("false",
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x2E8);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return 0;
}

// ?rva006D3980@EAStringC@@QAEHH@Z, retail 0x006D3980 (39B): "false" assert
// (line 0x300), returns 0; one unused stack argument (ret 4).
int EAStringC::rva006D3980(int)
{
	g_bfmeAptAssertAtE17734("false",
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x300);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return 0;
}

// ?rva006D39B0@EAStringC@@QAEHHPBD@Z, retail 0x006D39B0 (81B): asserts the
// second argument non-null (0x37B), then "false" (0x37C), returns 0.
int EAStringC::rva006D39B0(int, const char *text)
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x37B);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	g_bfmeAptAssertAtE17734("false",
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x37C);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return 0;
}

// ?rva006D3A10@EAStringC@@QAEHHH@Z, retail 0x006D3A10 (39B): "false" assert
// (line 0x395), returns 0; two unused stack arguments (ret 8).
int EAStringC::rva006D3A10(int, int)
{
	g_bfmeAptAssertAtE17734("false",
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x395);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return 0;
}

// ?Replace@EAStringC@@QAEHDD@Z, retail 0x006D3A40 (140B): asserts
// cOld/cNew non-zero (0x421/0x422), then replaces every cOld in the buffer
// with cNew through the rowed strchr thunk 0x0062984A; returns 0.
int EAStringC::Replace(char cOld, char cNew)
{
	if (!(cOld != '\0')) {
		g_bfmeAptAssertAtE17734("cOld != '\\0'",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x421);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (!(cNew != '\0')) {
		g_bfmeAptAssertAtE17734("cNew != '\\0'",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x422);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	char *cursor = (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	while ((cursor = strchr(cursor, cOld)) != 0)
		*cursor++ = cNew;
	return 0;
}

// ?startsWith@EAStringC@@QBE_NPBD@Z, retail 0x006D3AD0 (94B): text assert
// (0x5DE); true when the buffer starts with text.
bool EAStringC::startsWith(const char *text) const
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x5DE);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	unsigned int len = strlen(text);
	if ((unsigned int)data->m_uSize < len)
		return false;
	bool prefixMatches = memcmp((reinterpret_cast<char *>(data) + sizeof(StringDataC)), text, len) == 0;
	return prefixMatches;
}

// ?endsWith@EAStringC@@QBE_NPBD@Z, retail 0x006D3B30 (105B): text assert
// (0x602); true when the buffer ends with text.
bool EAStringC::endsWith(const char *text) const
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x602);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	unsigned int size = data->m_uSize;
	unsigned int len = strlen(text);
	if (size < len)
		return false;
	return memcmp((reinterpret_cast<char *>(data) + sizeof(StringDataC)) + size - len, text, len) == 0;
}
