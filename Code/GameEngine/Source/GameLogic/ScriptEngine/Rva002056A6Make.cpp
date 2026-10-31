// cl: /Ireference/shims/bfme2_ascii /EHsc
// stlport
// ?Rva002056A6Make@@YA?AURva00204ABF@@ABU?$pair@VAsciiString@@V1@@_STL@@ABH@Z @0x002056A6 27B
// Hidden-dest forwarder over rowed Rva00204ABF pair-plus-int ctor 0x00204ABF.
// Same 27B shape as rowed make_pair 0x0032ACCF and forwarder 0x0033BEF5.
// Callers at 0x0020899E 0x0032D1A0 plus 8 waiting free functions.
#include "ascii_string.h"
#include <utility>

struct Rva00204ABF
{
    _STL::pair<AsciiString, AsciiString> m_pair;
    int m_val;
    Rva00204ABF(const _STL::pair<AsciiString, AsciiString> &p, const int &v);
    ~Rva00204ABF();
};

Rva00204ABF Rva002056A6Make(const _STL::pair<AsciiString, AsciiString> &p, const int &v);

Rva00204ABF Rva002056A6Make(const _STL::pair<AsciiString, AsciiString> &p, const int &v)
{
    return Rva00204ABF(p, v);
}
