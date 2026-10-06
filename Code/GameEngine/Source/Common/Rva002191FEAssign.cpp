// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??4Rva002191FE@@QAEAAV0@ABV0@@Z @0x002191FE 59B
// Honest-address copy-assignment for int plus three AsciiStrings.
// Retail: self-check (cmp esi,edi je skip), dword copy at +0, three
// StringBase<char>::set calls at +4/+8/+0xC via rowed 0x000366F0, return
// *this (mov eax,esi ret 4). Caller 0x0021DEA2 in 56B body; neighbours
// 0x0021915B/0x0021929D share flags. No donor; honest Rva name.
#include "ascii_string.h"

class Rva002191FE
{
public:
    Rva002191FE &operator=(const Rva002191FE &other);
private:
    int m_0;
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
};

Rva002191FE &Rva002191FE::operator=(const Rva002191FE &other)
{
    if (this != &other) {
        m_0 = other.m_0;
        m_4 = other.m_4;
        m_8 = other.m_8;
        m_C = other.m_C;
    }
    return *this;
}
