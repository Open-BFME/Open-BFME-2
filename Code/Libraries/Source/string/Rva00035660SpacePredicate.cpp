// cl: /DNDEBUG /MD
// BFME1 donor: 4367fc698990427e26cc1c399989d074d8ee9bbe,
// game/Libraries/Source/string/StringBaseIsSpace.cpp, RVA 0x00886FC0.
// BFME2 RVA 0x00035660 is 20 bytes between int3 runs. Retail sign-extends
// AL, calls msvcr71.dll!isspace through IAT VA 0x00BBA5FC, then returns 0/1.
// The donor is ICF-folded; the original name and reachability are unproven.
// File-static scope reproduces MSVC's internal AL argument convention.

extern "C" __declspec(dllimport) int __cdecl isspace(int value);

static bool Rva00035660(char value)
{
    return isspace(value) != 0;
}

// Emission driver only; this helper has no retail claim.
// ?Rva00035660Emit absent-from-retail
void Rva00035660Emit(char value)
{
    Rva00035660(value);
}
