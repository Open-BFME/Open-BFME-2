// ?getDayOfWeek@AptDate@@QAEHHHH@Z
// partial score=0.97 date=2026-10-04
// cl: /O2 /MD
extern "C" double __cdecl floor(double);
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
class AptDate {
public:
    bool dateIsYearLeap(int year);
    int getDayOfWeek(int year,int month,int day);
};
static bool febLeap(int year)
{
    bool result = false;
    if (year % 4 == 0) {
        if (year % 100 != 0) return true;
        result = year % 400 == 0;
    }
    return result;
}
int AptDate::getDayOfWeek(int year,int month,int day)
{
    int century=year/100;
    int remainder=year%100;
    int anchor=month+1;
    int aCentury[4] = {3,2,0,5};
    int nCentury;
    if (century<19) nCentury=4-abs(century-19)%4;
    else nCentury=abs(century-19)%4;
    nCentury=aCentury[nCentury];
    int base=year-remainder;
    if (month==1) anchor=28+(febLeap(year)?1:0);
    else if (month%2==0) {
        if (month==8) anchor=5;
        else if (month==4) anchor=9;
        else if (month==6) anchor=11;
        else if (month==10) anchor=7;
        else if (month==2) anchor=7;
        else if (month==0) anchor=31+(dateIsYearLeap(year)?1:0);
    }
    if (nCentury<0 || anchor<0) return -1;
    int d=day;
    if (anchor>d) d=anchor-(anchor-d)%7+7;
    return (((int)floor((year-base)*0.25f)-base+nCentury+year)%7+(d-anchor)%7)%7;
}
