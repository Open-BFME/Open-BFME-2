// cl: /MD /EHsc
// Target date dispatch key toString reaches this formatter through callback
// 0x006F5080. Target calls and literals establish date formatting behavior;
// original method spelling and EAStringC-reference ABI come from Godfather
// QA PDB Apt.obj procedure/type records. No donor source is available.
// Fields are the same target access view as the verified date getters.
// Preserve retail Jly spelling, unbounded sprintf and four-byte numeric slot;
// this is a recovery, including its year-buffer overflow, not a safety repair.
// The scoped EAStringC temp reproduces target construction/unwind lifetime.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_string_formatter.
extern "C" int __cdecl sprintf(char *,const char *,...);
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
class EAStringC {
    void *data;
public:
    EAStringC(const char *);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    EAStringC &Rva006D50A0Append(const char *);
};
class AptDate {
    char prefix[0x20];
    int seconds,minutes,hours,unused2c,date,month,year,subsecond;
    int utc[8];
    int timezoneHours;
public:
    int getDayOfWeek(int,int,int);
    void toString(EAStringC &);
};
void AptDate::toString(EAStringC &out)
{
    char days[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    char months[12][4]={"Jan","Feb","Mar","Apr","May","Jun","Jly","Aug","Sep","Oct","Nov","Dec"};
    char buffer[4];
    { EAStringC weekday(days[getDayOfWeek(year,month,date)]); out=weekday; }
    out.Rva006D50A0Append(" ");
    out.Rva006D50A0Append(months[month]);
    out.Rva006D50A0Append(" ");
    sprintf(buffer,"%d",date);
    out.Rva006D50A0Append(buffer);
    out.Rva006D50A0Append(" ");
    sprintf(buffer,"%02d",hours);
    out.Rva006D50A0Append(buffer);
    out.Rva006D50A0Append(":");
    sprintf(buffer,"%02d",minutes);
    out.Rva006D50A0Append(buffer);
    out.Rva006D50A0Append(":");
    sprintf(buffer,"%02d",seconds);
    out.Rva006D50A0Append(buffer);
    out.Rva006D50A0Append(" GMT");
    out.Rva006D50A0Append(timezoneHours<0?"-":"+");
    sprintf(buffer,"%02d",abs(timezoneHours));
    out.Rva006D50A0Append(buffer);
    out.Rva006D50A0Append("00 ");
    sprintf(buffer,"%d",year);
    out.Rva006D50A0Append(buffer);
}
