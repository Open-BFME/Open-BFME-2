// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00216787Free@@YGXPAURva00216787Node@@@Z 0x00216787 28B evidence: custom free destroys Rva00216108 at +4 via rowed dtor then _free on non-null; chain from 0x00216108 landing; caller 0x00216B17
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
struct Rva00216787Node {
    int m_head;
    Rva00216108 m_strs;
};
extern "C" void __cdecl free(void *block);
void __stdcall Rva00216787Free(Rva00216787Node *p)
{
    p->m_strs.~Rva00216108();
    if (p)
        free(p);
}
