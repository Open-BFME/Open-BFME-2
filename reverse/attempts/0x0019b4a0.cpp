// ?packedSize@Rva0019B4A0StringArray@@QBEHXZ
// partial score=1.0 date=2026-10-08
// cl: /O2 /arch:SSE /G7 /MD /EHsc /DNDEBUG
// Clean donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/Common/SmallGaps/Rva00978CC0PackedSize.cpp.
// Unchanged from 34f59164. Target 0019B4A0..0019B4DB is a complete
// INT3-delimited function with RET at 0019B4DA, no calls or relocations.
// The adjacent HLod serialization layout is a lead, not proof of this
// receiver's original class or member name. Only the accessed prefix is shown.
#include <string.h>
#pragma intrinsic(strlen)
class Rva0019B4A0StringArray
{
public:
    int packedSize() const;
    char m_00[4];
    int m_count;
    const char **m_strings;
};
int Rva0019B4A0StringArray::packedSize() const
{
    int total = m_count * 8 + 16;
    for (int i = 0; i < m_count; ++i)
        total += strlen(m_strings[i]) + 1;
    return total;
}
