// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva00216787Free@@YGXPAURva00216787Node@@@Z 0x00216787 28B evidence: custom free destroys Rva00216108 at +4 via rowed dtor then _free on non-null; chain from 0x00216108 landing; caller 0x00216B17

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>

#include "ascii_string.h"
class Gen_003A8BE0 {
public:
 __forceinline Gen_003A8BE0() {}
 Gen_003A8BE0(const Gen_003A8BE0 &);
 ~Gen_003A8BE0();
 AsciiString first,second,third;
};
class Rva00216108 {
    AsciiString m_0;
    Gen_003A8BE0 m_4;
public:
    ~Rva00216108();
};
struct Rva00216787Node {
    int m_head;
    Rva00216108 m_strs;
};
void __stdcall Rva00216787Free(Rva00216787Node *node)
{
    node->m_strs.~Rva00216108();
    if (node)
        free(node);
}
