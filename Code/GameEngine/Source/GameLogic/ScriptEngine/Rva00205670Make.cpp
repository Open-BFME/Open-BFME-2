// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva00205670Make@@YA?AURva00204AA4@@ABU?$pair@VAsciiString@@V1@@_STL@@AB_N@Z @0x00205670 27B
// Hidden-dest forwarder over rowed Rva00204AA4 pair-plus-bool ctor 0x00204AA4.
// Same 27B shape as rowed make_pair 0x0032ACCF and siblings 0x002056A6 0x00205655.
// Callers at 0x002088E9 0x0020AB91.
#include "ascii_string.h"

namespace _STL {
template <class T1, class T2> struct pair
{
    T1 first;
    T2 second;
    pair(const pair<T1, T2> &other);
    pair(const T1 &a, const T2 &b);
};
}

struct Rva00204AA4
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    bool m_flag;
    Rva00204AA4(const _STL::pair<AsciiString, AsciiString> &p, const bool &f);
    ~Rva00204AA4();
};

Rva00204AA4 Rva00205670Make(const _STL::pair<AsciiString, AsciiString> &p, const bool &f);

Rva00204AA4 Rva00205670Make(const _STL::pair<AsciiString, AsciiString> &p, const bool &f)
{
    return Rva00204AA4(p, f);
}
