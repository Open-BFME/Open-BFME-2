// cl: /O2 /GR /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_STLP_USE_STATIC_LIB /D_STLP_NO_FORCE_INSTANTIATE /TP
// stlport46
// platformsdk
// STLport 4.6 src/c_locale.c and the checked BFME Win32 locale patch.
// The extraction-name mappings below preserve existing identities; this migration
// does not rename the five inferred Rva wrappers or assert new upstream names.
#define _Locale_extract_ctype_name Rva00023100
#define _Locale_extract_numeric_name Rva00023210
#define _Locale_extract_time_name Rva00023320
#define _Locale_extract_collate_name Rva00023430
#define _Locale_extract_monetary_name Rva00023540
// Target calls at 0x22890 and 0x22F00 both reach the existing 0x21290 owner.
// Retain its current inferred identity and thiscall ABI; no second symbol pin.
class Rva0084E030Buffer {
public:
    void squash();
    char m_chars[1];
};

// Same includes and platform selection as upstream src/c_locale.c.
#include "../../../../../vendor/stlport-4.6/src/stlport_prefix.h"
#include <stdlib.h>
#ifdef _STLP_REAL_LOCALE_IMPLEMENTED
#include <limits.h>
#include "../../../../../vendor/stlport-4.6/src/c_locale.h"
// Retail's IAT spells this ANSI export lstrcmpi (without the A suffix).
#include <windows.h>
#undef lstrcmpi
extern "C" __declspec(dllimport) int __stdcall lstrcmpi(const char *, const char *);
#define lstrcmpiA lstrcmpi
// The matched split locale units own these 16 public workers. Keep their
// declarations and calls, but do not emit competing definitions here.
extern "C" const char *_Locale_common_default(char *);
#define _BFME_LOCALE_SPLIT_PROVIDERS
#include <src/c_locale_win32/c_locale_win32.c>
#undef _BFME_LOCALE_SPLIT_PROVIDERS
#undef lstrcmpiA
#endif
