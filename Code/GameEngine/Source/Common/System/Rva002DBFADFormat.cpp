// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva002DBFAD@@YA?AVUnicodeString@@PBX@Z @0x002DBFAD 212B evidence: GetVersionExA GetDateFormatA-W IAT; UnicodeString translate 0x006CB5F0; StringBase wide copy 0x00037050 set 0x0000565D release 0x00036E70 rowed; callers 5

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
extern "C" __declspec(dllimport) Int __stdcall GetDateFormatA(
	DWORD Locale, DWORD dwFlags, const SYSTEMTIME *lpDate,
	const char *lpFormat, char *lpDateStr, Int cchDate);
extern "C" __declspec(dllimport) Int __stdcall GetDateFormatW(
	DWORD Locale, DWORD dwFlags, const SYSTEMTIME *lpDate,
	const WideChar *lpFormat, WideChar *lpDateStr, Int cchDate);

#include "ascii_string.h"


#include "unicode_string.h"

UnicodeString Rva002DBFAD(SYSTEMTIME date)
{
	OSVERSIONINFOA ver;
	UnicodeString out;
	ver.dwOSVersionInfoSize = 148;
	if (GetVersionExA(&ver) != 0 && ver.dwPlatformId == 1) {
		char buf[256];
		GetDateFormatA(0x800, 1, &date, NULL, buf, 0x100);
		out.translate(buf);
		return out;
	}
	WideChar wbuf[256];
	GetDateFormatW(0x800, 1, &date, NULL, wbuf, 0x200);
	out.set(wbuf);
	return out;
}
