// cl: /DNDEBUG /MD /O2
// BFME1 donor 4367fc698990427e26cc1c399989d074d8ee9bbe:
// game/Libraries/Source/string/StringBaseFormatForwarders.cpp,
// RVA 0x00887040/0x00887060, both 18 bytes.
// BFME2 RVA 0x000356E0/0x00035700 are complete int3-bounded forwarders.
// Their PE imports distinguish identical instruction shapes: _vsnprintf
// and the C++ four-argument vswprintf overload. VC7.1 stdio.h declares
// that overload with C++ linkage, correcting the donor's extern "C".
// Static scope preserves the observed EAX/ECX/EDX argument convention.
// Original wrapper names and target reachability remain unproven.

#include <stdio.h>
#include <stdarg.h>

__declspec(dllimport) int __cdecl vswprintf(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args);

static int Rva000356E0Narrow(char *buffer, unsigned int size, const char *format, va_list args)
{
    return _vsnprintf(buffer, size, format, args);
}

static int Rva00035700Wide(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args)
{
    return vswprintf(buffer, size, format, args);
}

// Emission driver only; this helper has no retail claim.
// ?Rva000356E0Emit absent-from-retail
void Rva000356E0Emit(char *buffer, unsigned int size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Rva000356E0Narrow(buffer, size, format, args);
    Rva00035700Wide((unsigned short *)buffer, size, (const unsigned short *)format, args);
    va_end(args);
}
