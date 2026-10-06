// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ??0Rva00204ABF@@QAE@ABU?$pair@VAsciiString@@V1@@_STL@@ABH@Z @0x00204ABF 27B: pair plus int ctor.
// Evidence: same pair-copy shape as Rva00204AA4 0x00204AA4 via rowed pair 0x0020492B;
// dword at +8 from second arg; caller 0x002056A6 wrapper.

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

struct Rva00204ABF
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    int m_val;
    Rva00204ABF(const _STL::pair<AsciiString, AsciiString> &p, const int &v);
};

Rva00204ABF::Rva00204ABF(const _STL::pair<AsciiString, AsciiString> &p, const int &v)
    : m_pair(p), m_val(v)
{
}
