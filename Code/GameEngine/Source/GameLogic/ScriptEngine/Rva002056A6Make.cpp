// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva002056A6Make@@YA?AURva00204ABF@@ABU?$pair@VAsciiString@@V1@@_STL@@ABH@Z @0x002056A6 27B
// Hidden-dest forwarder over rowed Rva00204ABF pair-plus-int ctor 0x00204ABF.
// Same 27B shape as rowed make_pair 0x0032ACCF and forwarder 0x0033BEF5.
// Callers at 0x0020899E 0x0032D1A0 plus 8 waiting free functions.
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

// ?Rva002056C1Make@@YA?AURva003004C1@@ABVAsciiString@@ABE@Z @0x002056C1 27B
// Hidden-dest forwarder over rowed Rva003004C1 AsciiString-plus-byte ctor 0x003004C1.
// Same 27B shape as sibling 0x002056A6 above; unblocks 0x00209811.
struct Rva003004C1
{
	AsciiString m_key;
	unsigned char m_flag;
	Rva003004C1(const AsciiString &key, const unsigned char &flag);
};
Rva003004C1 Rva002056C1Make(const AsciiString &key, const unsigned char &flag);
Rva003004C1 Rva002056C1Make(const AsciiString &key, const unsigned char &flag)
{
	return Rva003004C1(key, flag);
}
