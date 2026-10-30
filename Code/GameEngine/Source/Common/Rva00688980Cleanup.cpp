// cl: /O2 /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/Bfme5HandOffClears.cpp, Gen_0081DBE0::bfmeClear.
// Target: native 006888D0..0068893C deletes the pointer range at +14/+18,
// clears the two four-byte strings at +8/+C, and resets +10. Its caller
// 00688980 is the owned-object teardown called from Rva001D28F0Element.
// Address-derived owner retained; donor application names are unproven.
#include "ascii_string.h"

#include <string.h>
// STLport's allocator calls the C++-linkage free owned by GameMemory.cpp.
// Its existing binding selects the game allocator rather than the CRT thunk.
namespace _STL { void __cdecl free(void *); }

class Rva006888D0Owned
{
public:
    virtual ~Rva006888D0Owned();
};

inline Rva006888D0Owned **copyOwned(Rva006888D0Owned **destination,
    Rva006888D0Owned **first, Rva006888D0Owned **last);

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
    ~Rva006888D0Vector() { if (begin != 0) _STL::free(begin); }
    Rva006888D0Owned **begin;
    Rva006888D0Owned **end;
    Rva006888D0Owned **capacity;
    void clear() { end = copyOwned(begin, end, end); }
};

class Rva00688980
{
public:
	~Rva00688980();
	void rva006888D0();
	void rva006889F0(const char *path);
private:
	char prefix[8]; // +0x00
	AsciiString m_nameA; // +0x08
	AsciiString m_nameB; // +0x0C
	int m_count; // +0x10
	Rva006888D0Vector m_vector; // +0x14
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

// Native 00688980..006889EC and its unwind states destroy the vector then
// the two strings in reverse order. This proves destruction despite the
// older consumer's provisional 'teardown' method spelling.
Rva00688980::~Rva00688980()
{
    rva006888D0();
}
