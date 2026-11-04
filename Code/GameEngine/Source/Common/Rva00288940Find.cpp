// cl: /DNDEBUG /MD /EHsc
// ?Rva00288940Find@@YGPBXPBX@Z retail 0x00288940 56 bytes.
// Free circular-list first-match scan via rowed Overridable::friend_getFinalOverride 0x00288609
// plus TU-local noinline Rva0028867DCheck copy for the static ESI call shape.
// Evidence: callers at 0x00288D0F and 0x0028D7CF pass one pointer with dead TheLevelSys this
// and consume +0x18 and +0xFC from the returned Overridable; same walk as Rva002897A8Find.
extern class GameLogic *TheGameLogic;
#include "../../Include/Common/Overridable.h"
struct Node
{
Node *m_prev;
Node *m_next;
Overridable m_over;
};
struct Sentinel
{
Node *m_head;
};
class BfmeGlob939D
{
public:
char bfmeCall939D();
};
#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)
struct Rva0028867DData
{
char m_pad[0x101];
unsigned char m_b101;
unsigned char m_b102;
};
__declspec(noinline) static bool Rva0028867DCheck(const void *p)
{
const Rva0028867DData *d = (const Rva0028867DData *)p;
if (TheBfmeGlob->bfmeCall939D())
return d->m_b101 == 0;
return d->m_b102 == 0;
}
const void * __stdcall Rva00288940Find(const void *arg)
{
Sentinel *sentinel = (Sentinel *)arg;
Node *node = sentinel->m_head;
if (node != *(Node **)node)
{
do
{
// Retail calls the const overload at 0x00288609.
const Overridable *overridable = ((const Overridable *)((char *)node->m_next + 8))->friend_getFinalOverride();
if (Rva0028867DCheck(overridable))
return overridable;
node = node->m_next;
} while (node != *(Node **)sentinel->m_head);
}
return 0;
}
