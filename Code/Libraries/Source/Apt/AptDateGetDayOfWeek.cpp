// cl: /O2 /arch:SSE /G6 /MD /D_CRTIMP=
// ?getDayOfWeek@AptDate@@QAEHHHH@Z @0x006F4290 450B (RET 0xC)
//
// Weekday of a year/month/day triple: century anchor table {3 2 0 5},
// month doomsday anchors (February through the inlined leap test, the zero
// month through the pinned AptDate::dateIsYearLeap at 0x006F4080), then the
// year-in-century quarter via floor (direct call to the msvcr71 floor thunk
// 0x00629940, pinned _floor) and __ftol2. Callers: AptDate::sMethod_getDay and
// sMethod_getUTCDay in AptDateGetters.cpp. math.h is included without
// dllimport (/D_CRTIMP=): retail calls the import thunk directly, and the
// header's float floor overload gives retail's tail association order.
#include <stdlib.h>
#include <math.h>
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
    int anchor=month+1;
    unsigned long remainder=year%100;
    int century=year/100;
    int nCentury;
    unsigned int aCentury[4] = {3,2,0,5};
    if (century < 19) nCentury=4-abs(century-19)%4;
    else nCentury=abs(century-19)%4;
    nCentury=aCentury[nCentury];
    long base=year-remainder;
    if (month==1) anchor=28+(febLeap(year)?1:0);
    else if (month%2==0) {
        if (month==8) anchor=5;
        else if (4 == month) anchor=9;
        else if (month==6) anchor=11;
        else if (month==10) anchor=7;
        else if (month==2) anchor=7;
        else if (month==0) anchor=31+(dateIsYearLeap(year)?1:0);
    }
    if (nCentury<0 || anchor<0) return -1;
    int d=day;
    if (anchor>d) d=anchor-(anchor-d)%7+7;
    int result = (((int)floor((year-base)*0.25f)-base+nCentury+year)%7+(d-anchor)%7)%7;
    return result;
}
