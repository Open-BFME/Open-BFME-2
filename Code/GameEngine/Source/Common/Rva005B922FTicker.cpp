// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
// ?rva005B9501@Rva005B922F@@QAEXXZ @0x005B9501 183B
// Ticker date/time rows: GetLocalTime, format date via rowed 0x002DBFAD and
// time via rowed 0x002DC081(flag 0), set under indices 0/1 through rowed
// rva005B9378, then numeric rows 2/3 through rowed rva005B942A gated on
// g_009C0758/g_009C075C. Evidence: vtable slot 3 of 0x00873B70 (class of
// ??1Rva005B922F), callees rowed, globals g_009C0758/g_009C075C in use.
typedef unsigned short WORD;

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

extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *st);

UnicodeString Rva002DBFAD(SYSTEMTIME date);
UnicodeString Rva002DC081(SYSTEMTIME date, int flag);

class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
	void rva005B942A(int index, int value);
};

extern int g_009C0758;
extern int g_009C075C;

class Rva005B922F
{
public:
	void rva005B9501();
};

void Rva005B922F::rva005B9501()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	((Rva005B9378 *)this)->rva005B9378(0, Rva002DBFAD(st));
	((Rva005B9378 *)this)->rva005B9378(1, Rva002DC081(st, 0));
	if (g_009C0758 > 0)
		((Rva005B9378 *)this)->rva005B942A(2, g_009C0758);
	if (g_009C075C > 0)
		((Rva005B9378 *)this)->rva005B942A(3, g_009C075C);
}
