// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva002DC081@@YA?AVUnicodeString@@USYSTEMTIME@@H@Z @0x002DC081 233B evidence: GetVersionExA GetTimeFormatA-W IAT; UnicodeString translate 0x006CB5F0; StringBase wide copy 0x00037050 set 0x0000565D release 0x00036E70 rowed; callers 4 one 183B shows SYSTEMTIME by value plus int flag; neighbours Rva002DBFADFormat and Rva002DC267Get same flags
// Private StringBase copy like neighbour Rva002DBFADFormat.cpp which byte-matches the same call sequence; shared ascii header holds no UnicodeString translate with these row names so private copy is kept for gate parity.

typedef int Int;
typedef unsigned short WideChar;
typedef unsigned int DWORD;
typedef unsigned short WORD;
#define NULL 0

struct SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};

struct OSVERSIONINFOA
{
	DWORD dwOSVersionInfoSize;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	DWORD dwBuildNumber;
	DWORD dwPlatformId;
	char szCSDVersion[128];
};

extern "C" __declspec(dllimport) Int __stdcall GetVersionExA(OSVERSIONINFOA *info);
extern "C" __declspec(dllimport) Int __stdcall GetTimeFormatA(
	DWORD Locale, DWORD dwFlags, const SYSTEMTIME *lpDate,
	const char *lpFormat, char *lpDateStr, Int cchDate);
extern "C" __declspec(dllimport) Int __stdcall GetTimeFormatW(
	DWORD Locale, DWORD dwFlags, const SYSTEMTIME *lpDate,
	const WideChar *lpFormat, WideChar *lpDateStr, Int cchDate);

#include "ascii_string.h"


#include "unicode_string.h"

UnicodeString Rva002DC081(SYSTEMTIME date, int flag)
{
	OSVERSIONINFOA ver;
	UnicodeString out;
	ver.dwOSVersionInfoSize = 148;
	if (GetVersionExA(&ver) != 0 && ver.dwPlatformId == 1) {
		char buf[256];
		int fmt = 12;
		if (flag != 1)
			fmt = 14;
		GetTimeFormatA(0x800, fmt, &date, NULL, buf, 0x100);
		out.translate(buf);
		return out;
	}
	WideChar wbuf[256];
	int fmtW = 0;
	if (flag != 1)
		fmtW = 2;
	GetTimeFormatW(0x800, fmtW, &date, NULL, wbuf, 0x200);
	out.set(wbuf);
	return out;
}
