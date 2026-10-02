// cl: /DNDEBUG /MD
// BFME1 donors at 4367fc698990427e26cc1c399989d074d8ee9bbe:
// game/Libraries/Source/string/StringBaseToLower.cpp (0x00887000/0x00887010)
// and StringBaseToUpper.cpp (0x00887020/0x00887030).
// BFME2 has four int3-bounded CRT forwarders at 0x000356A0..0x000356D0.
// Narrow bodies sign-extend AL; wide bodies forward EAX and return AX.
// Named PE imports identify the operations; original names and reachability
// remain unproven. Static scope reproduces MSVC's internal argument ABI.
// Unlike the donors' int results, wide results retain the CRT's 16-bit type:
// retail has no movzx eax,ax. VC7.1 ctype.h declares a 16-bit wchar_t result.

extern "C" __declspec(dllimport) int __cdecl tolower(int value);
extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short value);
extern "C" __declspec(dllimport) int __cdecl toupper(int value);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short value);

static int Rva000356A0(char value)
{
    return tolower(value);
}

static unsigned short Rva000356B0(unsigned short value)
{
    return towlower(value);
}

static int Rva000356C0(char value)
{
    return toupper(value);
}

static unsigned short Rva000356D0(unsigned short value)
{
    return towupper(value);
}

// Emission driver only; this helper has no retail claim.
// ?Rva000356A0Emit absent-from-retail
void Rva000356A0Emit(char value, unsigned short wide)
{
    Rva000356A0(value);
    Rva000356B0(wide);
    Rva000356C0(value);
    Rva000356D0(wide);
}
