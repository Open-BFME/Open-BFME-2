// cl: /MD
// Date callbacks identified by target date-method dispatch keys and addresses;
// Godfather QA PDB supplies original sMethod names and static callback ABI.
// The interpreter declaration is only its already-established first stack.
// Per-clock names/offsets agree with target getters and recovered setDates.
// Hundredths is the donor label; no time-unit correction is introduced here.
// Repeated direct date casts preserve retail validation and argument order.
// setTime shares the already-landed getTime stub and has no second body claim.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_setters.
class AptValue;
class BfmeAptValue006DCD20 { public: BfmeAptValue006DCD20 *rva006DD160(); int toInteger() const; };
class AptInteger { public: static AptValue *Create(int); };
class AptBasePtrStack { public: BfmeAptValue006DCD20 *At(int); int count,capacity; BfmeAptValue006DCD20 **elements; };
struct AptActionInterpreter { AptBasePtrStack stack; };
// g_aptDateInterpreter: matched references place it at VA 0xe182e0 (zero-filled; a plain-data view).
AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
struct AptSysClock { int Second,Minute,Hour,Day,Date,Month,Year,Hundredths; };
class AptDate {
    char prefix[0x20];
    AptSysClock local,utc;
    int timezoneHours;
public:
    void setDates(AptSysClock *,AptSysClock *,int);
    static AptValue *sMethod_setDate(AptValue *,int);
    static AptValue *sMethod_setFullYear(AptValue *,int);
    static AptValue *sMethod_setHours(AptValue *,int);
    static AptValue *sMethod_setMilliseconds(AptValue *,int);
    static AptValue *sMethod_setMinutes(AptValue *,int);
    static AptValue *sMethod_setMonth(AptValue *,int);
    static AptValue *sMethod_setSeconds(AptValue *,int);
    static AptValue *sMethod_setUTCDate(AptValue *,int);
    static AptValue *sMethod_setUTCFullYear(AptValue *,int);
    static AptValue *sMethod_setUTCHours(AptValue *,int);
    static AptValue *sMethod_setUTCMilliseconds(AptValue *,int);
    static AptValue *sMethod_setUTCMinutes(AptValue *,int);
    static AptValue *sMethod_setUTCMonth(AptValue *,int);
    static AptValue *sMethod_setUTCSeconds(AptValue *,int);
    static AptValue *sMethod_setYear(AptValue *,int);
};
AptValue *AptDate::sMethod_setDate(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Date=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setFullYear(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Year=g_aptDateInterpreter.stack.At(0)->toInteger();
    if(argc>1)
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Month=g_aptDateInterpreter.stack.At(1)->toInteger();
    if(argc>2)
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Date=g_aptDateInterpreter.stack.At(2)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setHours(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Hour=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setMilliseconds(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Hundredths=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setMinutes(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Minute=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setMonth(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Month=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setSeconds(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Second=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCDate(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Date=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCFullYear(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Year=g_aptDateInterpreter.stack.At(0)->toInteger();
    if(argc>1)
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Month=g_aptDateInterpreter.stack.At(1)->toInteger();
    if(argc>2)
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Date=g_aptDateInterpreter.stack.At(2)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCHours(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Hour=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCMilliseconds(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Hundredths=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCMinutes(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Minute=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCMonth(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Month=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setUTCSeconds(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc.Second=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        -reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}
AptValue *AptDate::sMethod_setYear(AptValue *value,int argc)
{
    if(argc<1) return gpUndefinedValue;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local.Year=g_aptDateInterpreter.stack.At(0)->toInteger();
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->setDates(
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->local,
        &reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->utc,
        reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->timezoneHours);
    return AptInteger::Create(0);
}

// ?gpUndefinedValue@@3PAVAptValue@@A: the global at this VA is ?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?gpUndefinedValue@@3PAVAptValue@@A=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")
#pragma comment(linker, "/alternatename:?g_Va00E18078@@3HA=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")
#pragma comment(linker, "/alternatename:?g_Rva013379BC@@3PAVRva00898D60Target@@A=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")
// ?gpUndefinedValue@@3PAVAptValue@@A: the global at VA 0xe18078 is ?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A.
#pragma comment(linker, "/alternatename:?gpUndefinedValue@@3PAVAptValue@@A=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")
