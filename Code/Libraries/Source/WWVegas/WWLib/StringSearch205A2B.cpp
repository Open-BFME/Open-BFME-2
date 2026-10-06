// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00205A2B@Rva00205A2B@@QAEXPAUArg205A2B@@@Z @0x00205A2B 98B
// String search over 0x257 entries stride 0x80 at +0x2c via rowed
// StringBase compare 0x69D6; on hit copies three AsciiStrings via pinned
// operator= 0x366F0 from arg+4/+8/+0x7c to entry+0x24/+0x28/+0x9c.
// Evidence: caller 0x206E43; callees rowed/pinned; unblocks 0x206DFF.
#include "ascii_string.h"


struct Arg205A2B
{
    char _pad0[4];
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
    char _pad10[0x7c - 0x10];
    AsciiString m_7c;
};

class Rva00205A2B
{
public:
    void rva00205A2B(Arg205A2B *arg);
private:
    char m_pool[0x257 * 0x80 + 0xa0];
};

void Rva00205A2B::rva00205A2B(Arg205A2B *arg)
{
    for (int i = 0; i < 0x257; ++i) {
        StringBase<char> *name = (StringBase<char> *)(m_pool + 0x2c + i * 0x80);
        if (name->compare(*(StringBase<char> *)&arg->m_C) == 0) {
            *(AsciiString *)(m_pool + i * 0x80 + 0x24) = arg->m_4;
            *(AsciiString *)(m_pool + i * 0x80 + 0x28) = arg->m_8;
            *(AsciiString *)(m_pool + i * 0x80 + 0x9c) = arg->m_7c;
            return;
        }
    }
}
