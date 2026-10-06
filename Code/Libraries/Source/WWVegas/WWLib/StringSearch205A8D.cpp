// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00205A8D@Rva00205A8D@@QAEXPAUArg205A8D@@@Z @0x00205A8D 107B
// String search over 0xCA entries stride 0x80 at +0x12BAC via rowed
// StringBase compare 0x69D6; on hit copies three AsciiStrings via pinned
// operator= 0x366F0 from arg+4/+8/+0x7c to entry+0x12BA4/+0x12BA8/+0x12C1C.
// Evidence: caller 0x206E63 passes ScriptEngine table arg; same shape as
// StringSearch205A2B 0x00205A2B with 0x257 entries; callees rowed/pinned.
#include "ascii_string.h"


struct Arg205A8D
{
    char _pad0[4];
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
    char _pad10[0x7c - 0x10];
    AsciiString m_7c;
};

class Rva00205A8D
{
public:
    void rva00205A8D(Arg205A8D *arg);
private:
    char m_pool[0xCA * 0x80 + 0x12C20];
};

void Rva00205A8D::rva00205A8D(Arg205A8D *arg)
{
    for (int i = 0; i < 0xCA; ++i) {
        StringBase<char> *name = (StringBase<char> *)(m_pool + 0x12BAC + i * 0x80);
        if (name->compare(*(StringBase<char> *)&arg->m_C) == 0) {
            *(AsciiString *)(m_pool + i * 0x80 + 0x12BA4) = arg->m_4;
            *(AsciiString *)(m_pool + i * 0x80 + 0x12BA8) = arg->m_8;
            *(AsciiString *)(m_pool + i * 0x80 + 0x12C1C) = arg->m_7c;
            return;
        }
    }
}
