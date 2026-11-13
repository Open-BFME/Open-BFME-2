// cl: /MD
// ?rva002B43BA@Rva002B43BA@@QAEXPAUNode002B43BA@@@Z @0x002B43BA 45B.
// Unlock lane; sibling of 0x002B4360 identical recursive child (+0xC) plus next (+8) free.
// Calls self and rowed free 0x00030830; unblocks 0x002B5558. ret 4.
// TU-local honest-address class.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Node002B43BA.h"
class Rva002B43BA {
public:
    void rva002B43BA(Node002B43BA *head);
};
void Rva002B43BA::rva002B43BA(Node002B43BA *head)
{
    if (head == 0)
        return;
    for (Node002B43BA *p = head; p != 0;) {
        rva002B43BA(p->m_childC);
        Node002B43BA *next = p->m_next8;
        free(p);
        p = next;
    }
}
