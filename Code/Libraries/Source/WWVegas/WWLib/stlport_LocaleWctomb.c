// platformsdk
// stlport46
// STLport 4.5.3 Win32 _Locale_wctomb (retail 0x00020D50, 92B).
// Distinct TU under WWLib: Code/stlport/ is not an allowed root for a new
// source. Donor-verbatim; T1 clean transfer.
#include <wchar.h>
#include <windows.h>

typedef struct _Locale_ctype_t
{
    unsigned long lcid;
    unsigned int cp;
} _Locale_ctype_t;

unsigned int _Locale_wctomb(_Locale_ctype_t *ltype, char *to, unsigned int n,
    const unsigned short c, mbstate_t *st)
{
    int size;

    size = WideCharToMultiByte(ltype->cp, 0x220, &c, 1, 0, 0, 0, 0);
    if ((unsigned int)size > n)
        return (unsigned int)-2;

    size = WideCharToMultiByte(ltype->cp, 0x220, &c, 1, to, n, 0, 0);
    if (size == 0)
        return (unsigned int)-1;
    return (unsigned int)size;
}
