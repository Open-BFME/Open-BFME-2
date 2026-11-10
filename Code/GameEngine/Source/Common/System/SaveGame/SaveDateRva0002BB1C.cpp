// cl: /MD
// platformsdk
// ?rva0002BB1C@SaveDate@@QAEXXZ @0x0002BB1C 85B
// Refreshes this SaveDate from GetLocalTime, swapping wDay/wDayOfWeek to
// SaveDate order (year month day dayOfWeek hour minute second milliseconds).
// Caller at 0x0002BBCE passes global g_00DDF5B8 as this. Prev row 0x0002BAF8
// is SaveDate ctor in GameState.cpp.
#include <windows.h>

struct SaveDate
{
	WORD year;
	WORD month;
	WORD day;
	WORD dayOfWeek;
	WORD hour;
	WORD minute;
	WORD second;
	WORD milliseconds;
public:
	void rva0002BB1C();
};

void SaveDate::rva0002BB1C()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	year = st.wYear;
	month = st.wMonth;
	day = st.wDay;
	dayOfWeek = st.wDayOfWeek;
	hour = st.wHour;
	minute = st.wMinute;
	second = st.wSecond;
	milliseconds = st.wMilliseconds;
}
