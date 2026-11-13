// cl: /MD
// ?rva002B4509@Rva002B4509@@QAEXPAUNode002B4509@@@Z @0x002B4509 45B.
// Unlock lane; sibling of 0x002B4360 identical recursive child (+0xC) plus next (+8) free.
// Calls self and rowed free 0x00030830; unblocks 0x002B57D5. ret 4.
// TU-local honest-address class.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Node002B4509.h"
class Rva002B4509 {
public:
    void rva002B4509(Node002B4509 *head);
};
void Rva002B4509::rva002B4509(Node002B4509 *head)
{
    if (head == 0)
        return;
    for (Node002B4509 *p = head; p != 0;) {
        rva002B4509(p->m_childC);
        Node002B4509 *next = p->m_next8;
        free(p);
        p = next;
    }
}
