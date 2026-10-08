// ?rva006888D0@Rva00688980@@QAEXXZ
// partial score=0.91 date=2026-10-08
// cl: /O2 /G7
// Source lead: Open-BFME-1 game/GameEngine/Source/Common/Bfme5HandOffClears.cpp
// at ba7ddda7e8f; Gen_0081DBE0::bfmeClear. The donor supplies the owned
// vector-clear algorithm, not a target class identity.
// Target: Ghidra 0x006888D0..0x0068893C; matching WB 0x006BF4B0..0x006BF51C.
// Both prove strings +8/+C, count +10, vector +14/+18 and virtual destruction.
// Existing teardown pin 0x00688980 names the owning view; identity is opaque.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *, const void *, unsigned int);

class Rva00688980;
// This four-byte string-member view is already used by the owning element's
// rowed destructor. Its destructor resolves to the existing releaseBuffer fold.
class AsciiStringMember
{
public:
    ~AsciiStringMember();
private:
    void *m_data;
};

class Owned006888D0
{
public:
    // Retail calls slot zero with flag zero and frees its returned pointer.
    // Keep this ABI explicit rather than assume the donor's destructor type.
    virtual void *destroy(unsigned int flags);
};

inline Owned006888D0 **copyOwned006888D0(Owned006888D0 **destination,
    Owned006888D0 **first, Owned006888D0 **last)
{
    if (first == last)
        return destination;
    int bytes = (char *)last - (char *)first;
    return (Owned006888D0 **)((char *)memmove(destination, first, bytes) + bytes);
}

class OwnedVector006888D0
{
public:
    void erase(Owned006888D0 **first, Owned006888D0 **last)
    {
        m_finish = copyOwned006888D0(first, last, m_finish);
    }
    void clear() { erase(m_start, m_finish); }
    Owned006888D0 **m_start;
    Owned006888D0 **m_finish;
    Owned006888D0 **m_end;
};

class Rva00688980
{
public:
    void rva006888D0();
private:
    int m_head[2];
    AsciiStringMember m_nameA;
    AsciiStringMember m_nameB;
    int m_count;
    OwnedVector006888D0 m_vector;
};

void Rva00688980::rva006888D0()
{
    Owned006888D0 **it = m_vector.m_start;
    Owned006888D0 **last = m_vector.m_finish;
    while (it != last) {
        if (*it)
            operator delete((*it)->destroy(0));
        last = m_vector.m_finish;
        ++it;
    }
    m_vector.clear();
    m_nameA.~AsciiStringMember();
    m_nameB.~AsciiStringMember();
    m_count = 0;
}
