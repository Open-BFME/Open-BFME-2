// platformsdk
// stlport46
/* STLport 4.5.3 c_locale_win32.c: _Locale_unshift and _Locale_strwcmp.
   Transferred unchanged in code from Open-BFME-1 5cae4bdff
   game/Libraries/Source/STLport/LocaleUnshiftStrwcmp.c (BFME1 0x0084DAF0 63 B,
   0x0084DB30 58 B). BFME2 target: 0x00020DB0 and 0x00020DF0, byte-identical to
   BFME1 once relocation slots are masked, directly after the matched
   _Locale_wctomb (0x00020D50) exactly as in BFME1. Donor note: in BFME1 neither
   body has a reference left in retail; _Locale_unshift ends at a ret plus int3
   padding and _Locale_strwcmp starts at the next 16-byte boundary. */
#include <windows.h>
#include <string.h>
#include <wchar.h>

struct _Locale_ctype;
struct _Locale_collate { LCID lcid; };

size_t _Locale_unshift(struct _Locale_ctype *ltype, mbstate_t *st,
                       char *buf, size_t n, char **next)
{
  if (*st == 0) {
    *next = buf;
    return 0;
  }
  else {
    if (n < 1) { *next = buf; return (size_t)-2; }
    *next = buf + 1;
    return 1;
  }
}

int _Locale_strwcmp(struct _Locale_collate *lcol,
                    const wchar_t *s1, size_t n1, const wchar_t *s2, size_t n2)
{
  int result;
  result = CompareStringW(lcol->lcid, 0, s1, n1, s2, n2);
  if (result == CSTR_EQUAL) return 0;
  return result == CSTR_LESS_THAN ? -1 : 1;
}
