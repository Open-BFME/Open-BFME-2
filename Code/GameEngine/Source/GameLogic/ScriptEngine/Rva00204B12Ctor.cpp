// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ??0Rva00204B12@@QAE@ABU0@@Z @0x00204B12 33B: pair plus two-int copy ctor.
// Evidence: same pair-copy shape as siblings via rowed pair 0x0020492B;
// dwords at +8 and +0xC from same struct; callers 0x00205889 and 0x0020874B.

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

struct Rva00204B12
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    int m_a;
    int m_b;
    Rva00204B12(const Rva00204B12 &o);
};

Rva00204B12::Rva00204B12(const Rva00204B12 &o)
    : m_pair(o.m_pair), m_a(o.m_a), m_b(o.m_b)
{
}
