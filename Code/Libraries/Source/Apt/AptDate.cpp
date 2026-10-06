// cl: /O2 /MD
// AptDate.cpp (retail __FILE__ names it; tu_map approved). The clock and
// calendar units that shared these flags are folded in below; setDates is
// defined before dateGetNumDaysInMonth so the rowed call stays a call.
// The getter and setter units stay split until their callees link.
//
// CleanNativeFunctions:
// Cleans the 37 native callback caches identified by the target date dispatch
// table at VA DDC730 and jump table at AF643C. Each cache is constructed by
// its own corresponding named dispatch case, then AddRef-ed through slot0.
// Release slot4 agrees with existing target AptNativeHash/AptValue recoveries.
// This TU groups adjacent cache slots for access; it does not claim that the
// original source declared them as one struct. Field labels are target keys.
// Donor PDB supplies AptDate::CleanNativeFunctions and static void() signature.
// Provenance: reverse/godfather_disk_evidence.json, apt_date_cleanup.
class AptValue { public: virtual void AddRef(); virtual void Release(); };
struct AptDateNativeCache {
    AptValue *getDate;
    AptValue *getDay;
    AptValue *getFullYear;
    AptValue *getHours;
    AptValue *getMilliseconds;
    AptValue *getMinutes;
    AptValue *getMonth;
    AptValue *getSeconds;
    AptValue *getTime;
    AptValue *getTimezoneOffset;
    AptValue *getUTCDate;
    AptValue *getUTCDay;
    AptValue *getUTCFullYear;
    AptValue *getUTCHours;
    AptValue *getUTCMilliseconds;
    AptValue *getUTCMinutes;
    AptValue *getUTCMonth;
    AptValue *getUTCSeconds;
    AptValue *getYear;
    AptValue *setDate;
    AptValue *setFullYear;
    AptValue *setHours;
    AptValue *setMilliseconds;
    AptValue *setMinutes;
    AptValue *setMonth;
    AptValue *setSeconds;
    AptValue *setTime;
    AptValue *setUTCDate;
    AptValue *setUTCFullYear;
    AptValue *setUTCHours;
    AptValue *setUTCMilliseconds;
    AptValue *setUTCMinutes;
    AptValue *setUTCMonth;
    AptValue *setUTCSeconds;
    AptValue *setYear;
    AptValue *toString;
    AptValue *UTC;
};
// g_aptDateNativeCache: matched references place it at VA 0xe18248 (zero-filled; a plain-data view).
AptDateNativeCache g_aptDateNativeCache;
struct AptSysClock {
    int Second,Minute,Hour,Day,Date,Month,Year,Hundredths;
};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptDate {
public:
    static void CleanNativeFunctions();
    bool dateIsYearLeap(int);
    int dateGetNumDaysInMonth(int month,int year);
    void setDates(AptSysClock *,AptSysClock *,int);
};

void AptDate::CleanNativeFunctions()
{
    if(g_aptDateNativeCache.getDate) {
        g_aptDateNativeCache.getDate->Release();
        g_aptDateNativeCache.getDate=0;
    }
    if(g_aptDateNativeCache.getDay) {
        g_aptDateNativeCache.getDay->Release();
        g_aptDateNativeCache.getDay=0;
    }
    if(g_aptDateNativeCache.getFullYear) {
        g_aptDateNativeCache.getFullYear->Release();
        g_aptDateNativeCache.getFullYear=0;
    }
    if(g_aptDateNativeCache.getHours) {
        g_aptDateNativeCache.getHours->Release();
        g_aptDateNativeCache.getHours=0;
    }
    if(g_aptDateNativeCache.getMilliseconds) {
        g_aptDateNativeCache.getMilliseconds->Release();
        g_aptDateNativeCache.getMilliseconds=0;
    }
    if(g_aptDateNativeCache.getMinutes) {
        g_aptDateNativeCache.getMinutes->Release();
        g_aptDateNativeCache.getMinutes=0;
    }
    if(g_aptDateNativeCache.getMonth) {
        g_aptDateNativeCache.getMonth->Release();
        g_aptDateNativeCache.getMonth=0;
    }
    if(g_aptDateNativeCache.getSeconds) {
        g_aptDateNativeCache.getSeconds->Release();
        g_aptDateNativeCache.getSeconds=0;
    }
    if(g_aptDateNativeCache.getTime) {
        g_aptDateNativeCache.getTime->Release();
        g_aptDateNativeCache.getTime=0;
    }
    if(g_aptDateNativeCache.getTimezoneOffset) {
        g_aptDateNativeCache.getTimezoneOffset->Release();
        g_aptDateNativeCache.getTimezoneOffset=0;
    }
    if(g_aptDateNativeCache.getUTCDate) {
        g_aptDateNativeCache.getUTCDate->Release();
        g_aptDateNativeCache.getUTCDate=0;
    }
    if(g_aptDateNativeCache.getUTCDay) {
        g_aptDateNativeCache.getUTCDay->Release();
        g_aptDateNativeCache.getUTCDay=0;
    }
    if(g_aptDateNativeCache.getUTCFullYear) {
        g_aptDateNativeCache.getUTCFullYear->Release();
        g_aptDateNativeCache.getUTCFullYear=0;
    }
    if(g_aptDateNativeCache.getUTCHours) {
        g_aptDateNativeCache.getUTCHours->Release();
        g_aptDateNativeCache.getUTCHours=0;
    }
    if(g_aptDateNativeCache.getUTCMilliseconds) {
        g_aptDateNativeCache.getUTCMilliseconds->Release();
        g_aptDateNativeCache.getUTCMilliseconds=0;
    }
    if(g_aptDateNativeCache.getUTCMinutes) {
        g_aptDateNativeCache.getUTCMinutes->Release();
        g_aptDateNativeCache.getUTCMinutes=0;
    }
    if(g_aptDateNativeCache.getUTCMonth) {
        g_aptDateNativeCache.getUTCMonth->Release();
        g_aptDateNativeCache.getUTCMonth=0;
    }
    if(g_aptDateNativeCache.getUTCSeconds) {
        g_aptDateNativeCache.getUTCSeconds->Release();
        g_aptDateNativeCache.getUTCSeconds=0;
    }
    if(g_aptDateNativeCache.getYear) {
        g_aptDateNativeCache.getYear->Release();
        g_aptDateNativeCache.getYear=0;
    }
    if(g_aptDateNativeCache.setDate) {
        g_aptDateNativeCache.setDate->Release();
        g_aptDateNativeCache.setDate=0;
    }
    if(g_aptDateNativeCache.setFullYear) {
        g_aptDateNativeCache.setFullYear->Release();
        g_aptDateNativeCache.setFullYear=0;
    }
    if(g_aptDateNativeCache.setHours) {
        g_aptDateNativeCache.setHours->Release();
        g_aptDateNativeCache.setHours=0;
    }
    if(g_aptDateNativeCache.setMilliseconds) {
        g_aptDateNativeCache.setMilliseconds->Release();
        g_aptDateNativeCache.setMilliseconds=0;
    }
    if(g_aptDateNativeCache.setMinutes) {
        g_aptDateNativeCache.setMinutes->Release();
        g_aptDateNativeCache.setMinutes=0;
    }
    if(g_aptDateNativeCache.setMonth) {
        g_aptDateNativeCache.setMonth->Release();
        g_aptDateNativeCache.setMonth=0;
    }
    if(g_aptDateNativeCache.setSeconds) {
        g_aptDateNativeCache.setSeconds->Release();
        g_aptDateNativeCache.setSeconds=0;
    }
    if(g_aptDateNativeCache.setTime) {
        g_aptDateNativeCache.setTime->Release();
        g_aptDateNativeCache.setTime=0;
    }
    if(g_aptDateNativeCache.setUTCDate) {
        g_aptDateNativeCache.setUTCDate->Release();
        g_aptDateNativeCache.setUTCDate=0;
    }
    if(g_aptDateNativeCache.setUTCFullYear) {
        g_aptDateNativeCache.setUTCFullYear->Release();
        g_aptDateNativeCache.setUTCFullYear=0;
    }
    if(g_aptDateNativeCache.setUTCHours) {
        g_aptDateNativeCache.setUTCHours->Release();
        g_aptDateNativeCache.setUTCHours=0;
    }
    if(g_aptDateNativeCache.setUTCMilliseconds) {
        g_aptDateNativeCache.setUTCMilliseconds->Release();
        g_aptDateNativeCache.setUTCMilliseconds=0;
    }
    if(g_aptDateNativeCache.setUTCMinutes) {
        g_aptDateNativeCache.setUTCMinutes->Release();
        g_aptDateNativeCache.setUTCMinutes=0;
    }
    if(g_aptDateNativeCache.setUTCMonth) {
        g_aptDateNativeCache.setUTCMonth->Release();
        g_aptDateNativeCache.setUTCMonth=0;
    }
    if(g_aptDateNativeCache.setUTCSeconds) {
        g_aptDateNativeCache.setUTCSeconds->Release();
        g_aptDateNativeCache.setUTCSeconds=0;
    }
    if(g_aptDateNativeCache.setYear) {
        g_aptDateNativeCache.setYear->Release();
        g_aptDateNativeCache.setYear=0;
    }
    if(g_aptDateNativeCache.toString) {
        g_aptDateNativeCache.toString->Release();
        g_aptDateNativeCache.toString=0;
    }
    if(g_aptDateNativeCache.UTC) {
        g_aptDateNativeCache.UTC->Release();
        g_aptDateNativeCache.UTC=0;
    }
}

// ?setDates@AptDate@@QAEXPAUAptSysClock@@0H@Z 0x006F41B0 (216B).
// Target date setters pass local/UTC clocks at date+20/+40 and offset+60.
// Copies calendar fields, adjusts hours/date, then copies sub-hour fields.
// Preserve the retail negative-hour expression 24-offset and its single-day
// rollover behavior. Day(+0C) remains untouched. Hundredths is the donor
// field name; this routine does not establish the sub-second unit itself.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_clock.
void AptDate::setDates(AptSysClock *source,AptSysClock *destination,int offset)
{
    destination->Year=source->Year;
    destination->Month=source->Month;
    destination->Date=source->Date;
    destination->Hour=source->Hour-offset;
    if(source->Hour-offset>23) {
        destination->Hour%=24;
        int daysInMonth=dateGetNumDaysInMonth(destination->Month,destination->Year);
        if(++destination->Date>daysInMonth) {
            destination->Date=1;
            if(++destination->Month>11) {
                destination->Month=0;
                ++destination->Year;
            }
        }
    } else if(source->Hour-offset<0) {
        destination->Hour=24-offset;
        if(--destination->Date<1) {
            if(--destination->Month<0) {
                destination->Month=11;
                --destination->Year;
            }
            destination->Date=dateGetNumDaysInMonth(destination->Month,destination->Year);
        }
    }
    destination->Minute=source->Minute;
    destination->Second=source->Second;
    destination->Hundredths=source->Hundredths;
}

// ?dateGetNumDaysInMonth@AptDate@@QAEHHH@Z 0x006F4120 (136B).
// Calendar helper named by Godfather PDB and target AptDate.cpp assertion.
// One inline int3 preserves the retail assertion barrier. __debugbreak()
// hoists mov eax,esi before the branch; explicit-return and reset variants
// also fail. No other instruction is supplied as assembly.
// The 110-byte code body is followed by 2 padding bytes and 24 bytes of
// switch data, independently checked against the compiled labels/indices.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_calendar.
int AptDate::dateGetNumDaysInMonth(int month,int year)
{
    int days=31;
    switch(month) {
    case 0: case 2: case 4: case 6: case 7: case 9: case 11:
        days=31; break;
    case 1:
        days=28+(dateIsYearLeap(year)?1:0); break;
    case 3: case 5: case 8: case 10:
        days=30; break;
    default:
        g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDate.cpp",166);
        if(g_bfmeAptBreakOnAssertAtDDC01C) __asm int 3;
    }
    return days;
}
