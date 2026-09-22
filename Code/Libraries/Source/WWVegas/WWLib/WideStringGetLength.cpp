// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// Emit the inline member from the GPL-3.0-or-later EA/Westwood donor header.
// Retail 0x615EF0/47B checks the empty singleton and cached length, then calls
// wcslen and caches its result. The data anchor only retains the member body.
#include "widestring.h"

int (WideStringClass::* volatile wide_string_get_length_anchor)() const = &WideStringClass::Get_Length;
