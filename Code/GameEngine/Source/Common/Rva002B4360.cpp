// cl: /MD
// ?rva002B4360@Rva002B4360@@QAEXPAUNode002B4360@@@Z @0x002B4360 45B.
// Unlock lane; recursive child (+0xC) plus iterative next (+8) free loop.
// Calls self and rowed free 0x00030830; unblocks 0x002B54F9. ret 4 one stack arg.
// TU-local honest-address class.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Node002B4360.h"
class Rva002B4360 {
public:
    void rva002B4360(Node002B4360 *head);
};
void Rva002B4360::rva002B4360(Node002B4360 *head)
{
    if (head == 0)
        return;
    for (Node002B4360 *p = head; p != 0;) {
        rva002B4360(p->m_childC);
        Node002B4360 *next = p->m_next8;
        free(p);
        p = next;
    }
}
