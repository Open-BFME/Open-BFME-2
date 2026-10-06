// cl: /MD
// Calendar helper named by Godfather PDB and target AptDate.cpp assertion.
// One inline int3 preserves the retail assertion barrier. __debugbreak()
// hoists mov eax,esi before the branch; explicit-return and reset variants
// also fail. No other instruction is supplied as assembly.
// The 110-byte code body is followed by 2 padding bytes and 24 bytes of
// switch data, independently checked against the compiled labels/indices.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_calendar.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptDate { public: bool dateIsYearLeap(int); int dateGetNumDaysInMonth(int month,int year); };
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
