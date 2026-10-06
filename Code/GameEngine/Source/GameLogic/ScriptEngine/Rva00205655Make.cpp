// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva00205655Make@@YA?AURva00204A83@@ABU?$pair@VAsciiString@@V1@@_STL@@AB_J@Z @0x00205655 27B
// Hidden-dest forwarder over rowed Rva00204A83 pair-plus-int64 ctor 0x00204A83.
// Same 27B shape as rowed make_pair 0x0032ACCF and sibling 0x002056A6.
// Callers at 0x0020879B 0x0020AACD.
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

struct Rva00204A83
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    __int64 m_val;
    Rva00204A83(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v);
    ~Rva00204A83();
};

Rva00204A83 Rva00205655Make(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v);

Rva00204A83 Rva00205655Make(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v)
{
    return Rva00204A83(p, v);
}
