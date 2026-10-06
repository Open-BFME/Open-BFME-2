// cl: /MD
// ?rva0002BB1C@SaveDate@@QAEXXZ @0x0002BB1C 85B
// Refreshes this SaveDate from GetLocalTime, swapping wDay/wDayOfWeek to
// SaveDate order (year month day dayOfWeek hour minute second milliseconds).
// Caller at 0x0002BBCE passes global g_00DDF5B8 as this. Prev row 0x0002BAF8
// is SaveDate ctor in GameState.cpp.
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
