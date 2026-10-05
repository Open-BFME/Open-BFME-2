// ??0Rva006FBF90@@QAE@HHHHHHH@Z
// partial score=0.93 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc
// ??0Rva006FBF90@@QAE@HHHHHHH@Z @0x006FBF90 337B. AptDate 7-int ctor (year month date hours minutes seconds ms).
// Evidence: calls rowed ??0BfmeAptValue006DCD20@@QAE@H@Z with 0x1d and rowed ??0AptNativeHash@@QAE@H@Z
// with 8 for member at +8; base vtable 0x008EA228 then own vtable 0x008ED8BC; clears byte +0x1C
// and bits 8-9; zeroes timezone at +0x60; inits local/utc clocks via g_00E177B8 with 1/0;
// computes timezone from date/hour diffs with day rollover +-24; -1 params keep clock values;
// calls rowed ?setDates@AptDate@@QAEXPAUAptSysClock@@0H@Z. Layout matches AptDateGetters/Setters
// prefix 0x20 plus local/utc AptSysClock plus timezone.
class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
    void setTypeAt006DBBC0(int type);
public:
    BfmeAptValue006DCD20(int type);
    virtual ~BfmeAptValue006DCD20();
};
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
class AptNativeHash
{
    struct Entry { void *key; AptValue *value; };
    int mnTotalSize;
    Entry *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
public:
    AptNativeHash(int size);
    ~AptNativeHash();
};
class Rva006D6360 : public BfmeAptValue006DCD20
{
    AptNativeHash m_hash;
public:
    Rva006D6360(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size)
    {
    }
    virtual ~Rva006D6360();
};
class Rva006DBits
{
protected:
    unsigned int m_bits;
public:
    Rva006DBits()
    {
        *(unsigned char *)&m_bits = 0;
        m_bits &= 0xFFFFFCFF;
    }
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
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva006FBF90 : public Rva006D6360, public Rva006DBits
{
    AptSysClock m_local;
    AptSysClock m_utc;
    int m_timezone;
public:
    Rva006FBF90(int year, int month, int date, int hours, int minutes, int seconds, int ms);
};
// ??0Rva006FBF90@@QAE@HHHHHHH@Z present-unmatched
Rva006FBF90::Rva006FBF90(int year, int month, int date, int hours, int minutes, int seconds, int ms) : Rva006D6360(0x1d, 8), Rva006DBits()
{
    m_timezone = 0;
    g_00E177B8(&m_local, 1);
    g_00E177B8(&m_utc, 0);
    int localDate = m_local.Date;
    _ReadWriteBarrier();
    if (m_local.Date > m_utc.Date)
        m_timezone = m_local.Hour - m_utc.Hour + 24;
    _ReadWriteBarrier();
    if (m_local.Date < m_utc.Date)
        m_timezone = m_local.Hour - m_utc.Hour - 24;
    _ReadWriteBarrier();
    if (localDate == m_utc.Date) {
        if (m_local.Hour > m_utc.Hour)
            m_timezone = m_local.Hour - m_utc.Hour;
        if (m_local.Hour < m_utc.Hour) {
            if (m_local.Date >= m_utc.Date)
                m_timezone = m_local.Hour - m_utc.Hour;
        }
    }
    if (year == -1)
        year = m_local.Year;
    m_local.Year = year;
    if (month == -1)
        month = m_local.Month;
    m_local.Month = month;
    if (date == -1)
        date = m_local.Date;
    m_local.Date = date;
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
