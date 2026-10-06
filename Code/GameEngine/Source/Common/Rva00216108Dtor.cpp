// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2
// ??1Rva00216108@@QAE@XZ 0x00216108 53B evidence: outer dtor with AsciiString at +0 and Rva002160C4 at +4 via rowed inner dtor plus releaseBuffer; chain from 0x002160C4 landing; callers 0x002161C5 0x0021678F 0x00217008
#include "ascii_string.h"
class Rva002160C4 {
    AsciiString m_0;
    AsciiString m_4;
    AsciiString m_8;
public:
    ~Rva002160C4();
};
class Rva00216108 {
    AsciiString m_0;
    Rva002160C4 m_4;
public:
    ~Rva00216108();
};
Rva00216108::~Rva00216108()
{
}
