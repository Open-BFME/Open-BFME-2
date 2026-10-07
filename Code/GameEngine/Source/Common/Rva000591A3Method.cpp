// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Oi /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva000591A3@Rva000591A3@@QAEXABVAsciiString@@@Z @ 0x000591A3 76B: thiscall
// inserts AsciiString into set at +0xA0 via row 0x0005897D then if inserted
// and float at +0x9C != 1.0f fills 48B at +0x188 with 0x02.
// Caller 0x00059A5C in 0x00059A25.
#include <set>
#include <cstring>


template <typename T> struct BfmeStringData
{
    int refCount;
    unsigned short length;
    unsigned short capacity;
    T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left < right;
    }
};
}

class Rva000591A3
{
public:
    void rva000591A3(const AsciiString &name);
    void rva000591EF();
private:
    char m_pad[0x9C];
    float m_9C;
    _STL::set<AsciiString> m_A0;
    char m_padAC[0x188 - 0xAC];
    unsigned char m_188[48];
};

void Rva000591A3::rva000591A3(const AsciiString &name)
{
    if (!m_A0.insert(name).second)
        return;
    if (m_9C != 1.0f)
    {
        for (int i = 0; i < 12; ++i)
            ((int *)m_188)[i] = 0x02020202;
    }
}

// ?rva000591EF@Rva000591A3@@QAEXXZ at 0x000591EF (62B).
// Sibling of 0x000591A3: if set empty return else if float != global fill 48B
// then tail-jmp tree clear. Evidence: cmp [edx+0xA4] via empty() plus movss/
// ucomiss vs 1.0f plus rep stosd 0xC then lea+jmp 0x57B4B. Caller 0x59AB0.
void Rva000591A3::rva000591EF()
{
    if (m_A0.empty())
        return;
    if (m_9C != 1.0f)
    {
        for (int i = 0; i < 12; ++i)
            ((int *)m_188)[i] = 0x02020202;
    }
    m_A0.clear();
}
