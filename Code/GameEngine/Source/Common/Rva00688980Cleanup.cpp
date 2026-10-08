// cl: /O2 /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/Bfme5HandOffClears.cpp, Gen_0081DBE0::bfmeClear.
// Target: native 006888D0..0068893C deletes the pointer range at +14/+18,
// clears the two four-byte strings at +8/+C, and resets +10. Its caller
// 00688980 is the owned-object teardown called from Rva001D28F0Element.
// Address-derived owner retained; donor application names are unproven.
#include "ascii_string.h"

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned int);

class Rva006888D0Owned
{
public:
    virtual ~Rva006888D0Owned();
};

inline Rva006888D0Owned **copyOwned(Rva006888D0Owned **destination,
    Rva006888D0Owned **first, Rva006888D0Owned **last)
{
    if (first == last)
        return destination;
    int bytes = (char *)last - (char *)first;
    return (Rva006888D0Owned **)((char *)memmove(destination, first, bytes) + bytes);
}

struct Rva006888D0Vector
{
    Rva006888D0Owned **begin;
    Rva006888D0Owned **end;
    Rva006888D0Owned **capacity;
    void clear() { end = copyOwned(begin, end, end); }
};

class Rva00688980
{
public:
    void rva006888D0();
private:
    unsigned char m_pad[8];
    AsciiString m_nameA;
    AsciiString m_nameB;
    int m_count;
    Rva006888D0Vector m_vector;
};

void Rva00688980::rva006888D0()
{
    Rva006888D0Owned **it = m_vector.begin;
    Rva006888D0Owned **last = m_vector.end;
    while (it != last) {
        if (*it != 0)
            ::delete *it;
        last = m_vector.end;
        ++it;
    }
    m_vector.clear();
    m_nameA.clear();
    m_nameB.clear();
    m_count = 0;
}
