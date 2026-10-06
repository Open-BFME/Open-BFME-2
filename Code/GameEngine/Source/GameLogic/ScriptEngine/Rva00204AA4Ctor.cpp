// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ??0Rva00204AA4@@QAE@ABU?$pair@VAsciiString@@V1@@_STL@@AB_N@Z @0x00204AA4 27B: pair plus bool ctor.
// Evidence: same pair-copy shape as Rva0020561C ctor 0x0020561C via rowed pair 0x0020492B;
// byte at +8 from second arg; caller 0x00205670 wrapper;_prev/next are pair helpers.

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

struct Rva00204AA4
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    bool m_flag;
    Rva00204AA4(const _STL::pair<AsciiString, AsciiString> &p, const bool &f);
};

Rva00204AA4::Rva00204AA4(const _STL::pair<AsciiString, AsciiString> &p, const bool &f)
    : m_pair(p), m_flag(f)
{
}
