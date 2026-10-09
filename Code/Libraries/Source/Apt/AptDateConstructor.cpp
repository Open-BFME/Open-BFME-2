// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// WB17609C0 clock ctor structural guide. PC100B Date has clocks20/40,
// timezone60, whereas WB clock24/44 timezone64. Target setDates proves ABI.
#include "AptObject/AptScriptFunction.h"
// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices t):AptValue(t){}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices t,int n):AptValueGC(t),mNativeHash(n){}
class Rva006DBits {
protected: unsigned int m_bits;
public: Rva006DBits(){*(unsigned char *)&m_bits=0;m_bits&=0xFFFFFCFF;}
};
struct AptSysClock
{
    int Second;
    int Minute;
    int Hour;
    int Day;
    int Date;
    int Month;
    int Year;
    int Hundredths;
};
class AptDate
{
public:
    void setDates(AptSysClock *, AptSysClock *, int);
};
extern void (__cdecl *g_00E177B8)(AptSysClock *, int);
class Rva006FBF90 : public AptValueWithHash, public Rva006DBits
{
    AptSysClock m_local;
    AptSysClock m_utc;
    int m_timezone;
public:
    Rva006FBF90(int year, int month, int date, int hours, int minutes, int seconds, int ms);
};
Rva006FBF90::Rva006FBF90(int year, int month, int date, int hours, int minutes, int seconds, int ms) : AptValueWithHash((AptVirtualFunctionTable_Indices)0x1d, 8), Rva006DBits()
{
    m_timezone = 0;
    g_00E177B8(&m_local, 1);
    g_00E177B8(&m_utc, 0);
    if (m_local.Date > m_utc.Date || (m_local.Date == m_utc.Date && m_local.Hour > m_utc.Hour)) {
        if (m_local.Date > m_utc.Date) m_timezone=m_local.Hour-m_utc.Hour+24;
        else m_timezone=m_local.Hour-m_utc.Hour;
    } else if (m_local.Date < m_utc.Date || (m_local.Date == m_utc.Date && m_local.Hour < m_utc.Hour)) {
        if (m_local.Date < m_utc.Date) m_timezone=m_local.Hour-m_utc.Hour-24;
        else m_timezone=m_local.Hour-m_utc.Hour;
    }
    if (year == -1)
        year = m_local.Year;
    m_local.Year = year;
    if (month == -1)
        month = m_local.Month;
    m_local.Month = month;
    int selectedDate=m_local.Date;
    if (date != -1) selectedDate=date;
    m_local.Date=selectedDate;
    if (hours == -1)
        hours = m_local.Hour;
    m_local.Hour = hours;
    if (minutes == -1)
        minutes = m_local.Minute;
    m_local.Minute = minutes;
    if (seconds == -1)
        seconds = m_local.Second;
    m_local.Second = seconds;
    if (ms == -1)
        ms = m_local.Hundredths;
    m_local.Hundredths = ms;
    reinterpret_cast<AptDate *>(this)->setDates(&m_local, &m_utc, m_timezone);
}
