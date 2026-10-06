// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00171024@@QAE@HH@Z retail 0x00171024 67B unlock lane ctor with two ints
// clamp first to 0x800 and cache map begin. Evidence: calls rowed map<long
// LadderPref> ctor 0x00242F01 at +8; ret 8 two args; unblocks 0x000E6AC0.

#include "unicode_string.h"

// Retail copies each string through its matching narrow or wide StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString();
};

// Names agree with upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    LadderPref();
    __declspec(noinline) LadderPref(const LadderPref &source);
    ~LadderPref();

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

#include <map>

typedef _STL::map<long, LadderPref> LadderPrefMap;

class Rva00171024
{
public:
    Rva00171024(int a, int b);

private:
    int m_00;
    int m_04;
    LadderPrefMap m_map;
    LadderPrefMap::iterator m_current;
    int m_18;
    bool m_1c;
    bool m_1d;
};

Rva00171024::Rva00171024(int a, int b) : m_00(a), m_04(b), m_map(), m_current(), m_18(0), m_1c(false), m_1d(false)
{
    if ((unsigned int)m_00 > 2048u)
        m_00 = 2048;
    m_current = m_map.begin();
}
