// cl: /MD
// Target date dispatch keys and per-case native callbacks identify each getter.
// Godfather QA PDB supplies original sMethod names and the two-argument ABI.
// Reuse the already-matched checked date cast and existing AptInteger::Create
// pin. Repeated casts in weekday getters preserve retail validation order.
// Fields are a target access view; unused prefix/words are not donor layouts.
// getTime returns integer zero in retail and shares its callback with setTime.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_getters.
class AptValue;
class BfmeAptValue006DCD20 { public: BfmeAptValue006DCD20 *rva006DD160(); };
class AptInteger { public: static AptValue *Create(int); };
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
class AptDate {
    char prefix[0x20];
    int seconds,minutes,hours,unused2c,day,month,year,milliseconds;
    int utcSeconds,utcMinutes,utcHours,unused4c,utcDay,utcMonth,utcYear,utcMilliseconds;
    int timezoneHours;
public:
    int getDayOfWeek(int,int,int);
    static AptValue *sMethod_getDate(AptValue *,int);
    static AptValue *sMethod_getDay(AptValue *,int);
    static AptValue *sMethod_getFullYear(AptValue *,int);
    static AptValue *sMethod_getHours(AptValue *,int);
    static AptValue *sMethod_getMilliseconds(AptValue *,int);
    static AptValue *sMethod_getMinutes(AptValue *,int);
    static AptValue *sMethod_getMonth(AptValue *,int);
    static AptValue *sMethod_getSeconds(AptValue *,int);
    static AptValue *sMethod_getTime(AptValue *,int);
    static AptValue *sMethod_getTimezoneOffset(AptValue *,int);
    static AptValue *sMethod_getUTCDate(AptValue *,int);
    static AptValue *sMethod_getUTCDay(AptValue *,int);
    static AptValue *sMethod_getUTCFullYear(AptValue *,int);
    static AptValue *sMethod_getUTCHours(AptValue *,int);
    static AptValue *sMethod_getUTCMilliseconds(AptValue *,int);
    static AptValue *sMethod_getUTCMinutes(AptValue *,int);
    static AptValue *sMethod_getUTCMonth(AptValue *,int);
    static AptValue *sMethod_getUTCSeconds(AptValue *,int);
    static AptValue *sMethod_getYear(AptValue *,int);
};
AptValue *AptDate::sMethod_getDate(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->day);
}
AptValue *AptDate::sMethod_getDay(AptValue *value,int argc)
{
    int weekday=reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->getDayOfWeek(
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->year,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->month,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->day);
    return AptInteger::Create(weekday);
}
AptValue *AptDate::sMethod_getFullYear(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->year);
}
AptValue *AptDate::sMethod_getHours(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->hours);
}
AptValue *AptDate::sMethod_getMilliseconds(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->milliseconds);
}
AptValue *AptDate::sMethod_getMinutes(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->minutes);
}
AptValue *AptDate::sMethod_getMonth(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->month);
}
AptValue *AptDate::sMethod_getSeconds(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->seconds);
}
AptValue *AptDate::sMethod_getTime(AptValue *value,int argc)
{
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_getTimezoneOffset(AptValue *value,int argc)
{
    return AptInteger::Create(abs(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours)*60);
}
AptValue *AptDate::sMethod_getUTCDate(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcDay);
}
AptValue *AptDate::sMethod_getUTCDay(AptValue *value,int argc)
{
    int weekday=reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->getDayOfWeek(
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcYear,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcMonth,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcDay);
    return AptInteger::Create(weekday);
}
AptValue *AptDate::sMethod_getUTCFullYear(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcYear);
}
AptValue *AptDate::sMethod_getUTCHours(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcHours);
}
AptValue *AptDate::sMethod_getUTCMilliseconds(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcMilliseconds);
}
AptValue *AptDate::sMethod_getUTCMinutes(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcMinutes);
}
AptValue *AptDate::sMethod_getUTCMonth(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcMonth);
}
AptValue *AptDate::sMethod_getUTCSeconds(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utcSeconds);
}
AptValue *AptDate::sMethod_getYear(AptValue *value,int argc)
{
    return AptInteger::Create(reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->year-1900);
}
