// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ??0Rva00204A83@@QAE@ABU?$pair@VAsciiString@@V1@@_STL@@AB_J@Z @0x00204A83 33B: pair plus int64 ctor.
// Evidence: same pair-copy shape as siblings 0x00204AA4 and 0x00204ABF via rowed pair 0x0020492B;
// qword at +8 from second arg; caller 0x00205655 wrapper.

#include "ascii_string.h"

namespace _STL
{

template <class T1, class T2> struct pair
{
    T1 first;
    T2 second;
    pair(const pair<T1, T2> &other);
};

}

struct Rva00204A83
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    __int64 m_val;
    Rva00204A83(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v);
};

Rva00204A83::Rva00204A83(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v)
    : m_pair(p), m_val(v)
{
}
