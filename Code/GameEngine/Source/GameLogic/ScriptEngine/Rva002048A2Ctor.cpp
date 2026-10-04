// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
//
// ??0Rva002048A2@@QAE@PAVAsciiString@@ABV1@@Z @0x002048A2 74B: virtual-class
// ctor storing vtable at +0, default-constructing AsciiString at +4, aliasing
// the input string at +8, then m_str = *a1 and *a1 = a2 via the operator= pin
// 0x000366F0. Evidence: 11 callers incl 0x00207D2B 0x0020A1EE 0x0020C1AC;
// unblocks 7 functions.
#include "ascii_string.h"


struct Rva002048A2
{
    virtual ~Rva002048A2();
    AsciiString m_str;
    AsciiString *m_alias;
    Rva002048A2(AsciiString *a1, const AsciiString &a2);
};

Rva002048A2::Rva002048A2(AsciiString *a1, const AsciiString &a2)
    : m_str()
{
    m_alias = a1;
    m_str = *a1;
    *a1 = a2;
}

// BFME1 donor1281192f68 BfmeConv1764.cpp supplies the restore-on-destruction
// operation. Target RVA 002048EC (63B) proves the alias at +8, string at +4,
// shared set worker366F0 and releaseBuffer36410. The existing ctor and slot-0
// deleting destructor independently establish this class's one-slot table.
// ??1Rva002048A2@@UAE@XZ
Rva002048A2::~Rva002048A2()
{
    AsciiString *target = m_alias;
    *target = m_str;
}
