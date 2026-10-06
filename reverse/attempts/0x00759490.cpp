// ?rva00759490@Rva009A3540PairOwner@@QAEXPAURva009A3540OpaqueOwner@@0@Z
// partial score=0.6238 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc
//
// ?rva00759490@Rva009A3540PairOwner@@QAEXPAURva009A3540OpaqueOwner@@0@Z retail 0x00759490 363B
// Evidence: same Owner layout as removePair 0x00759130 (buckets +0x18 divisor 0x2b7b freeList +0xae04 small table +0xae10 limit +0xc068) same param offsets +0x9c +0xa0 +0x20 same Node size 0x34 same callee insert 0x00759360; callers 0x00759600 x4.
#include <string.h>
#pragma intrinsic(memcpy)

void *__cdecl operator new(unsigned int bytes);

struct Rva009A3540PairNode
{
    struct Link
    {
        Link **backlink;
        Link *next;
    };

    unsigned char pad00[8];
    unsigned int key0;
    unsigned int key1;
    unsigned int counter;
    Link link14;
    unsigned int pad1c;
    Link link20;
    unsigned char pad28[8];
    Rva009A3540PairNode *next;
};

struct Rva009A3770Node
{
    unsigned char m_head[0x2c];
    void *m_backSlot;
    Rva009A3770Node *m_next;
};

class Rva009A3770HashTable
{
public:
    Rva009A3770Node *insert(Rva009A3770Node *src);

    Rva009A3770Node *m_buckets[0x493];
    Rva009A3770Node *m_freeList;
};

struct Rva009A3540OpaqueOwner
{
    unsigned char pad00[0x18];
    Rva009A3540PairNode *buckets[0x2b7b];
};

class Rva009A3540PairOwner
{
public:
    void rva00759490(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
};

// ?rva00759490@Rva009A3540PairOwner@@QAEXPAURva009A3540OpaqueOwner@@0@Z present-unmatched
void Rva009A3540PairOwner::rva00759490(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b)
{
    unsigned int aGroup = *(unsigned int *)((char *)a + 0xa0);
    if (aGroup != 0 && aGroup == *(unsigned int *)((char *)b + 0xa0))
        return;

    if (*(unsigned int *)((char *)a + 0x9c) > *(unsigned int *)((char *)b + 0x9c))
    {
        Rva009A3540OpaqueOwner *swap = a;
        a = b;
        b = swap;
    }

    unsigned int aId = *(unsigned int *)((char *)a + 0x9c);
    unsigned int bId = *(unsigned int *)((char *)b + 0x9c);
    unsigned int bucket = ((aId << 16) + bId) % 0x2b7b;

    unsigned char buf[44];
    *(unsigned int *)(buf + 8) = aId;
    *(unsigned int *)(buf + 0xc) = bId;
    Rva009A3540PairNode *node = ((Rva009A3540PairNode **)((char *)this + 0x18))[bucket];
    while (node != 0 && (node->key0 != aId || node->key1 != bId))
        node = *(Rva009A3540PairNode **)((char *)node + 0x30);
    if (node == 0)
    {
        Rva009A3540PairNode *fresh = *(Rva009A3540PairNode **)((char *)this + 0xae04);
        if (fresh != 0)
            *(Rva009A3540PairNode **)((char *)this + 0xae04) = *(Rva009A3540PairNode **)((char *)fresh + 0x30);
        else
            fresh = (Rva009A3540PairNode *)operator new(0x34);

        *(Rva009A3540OpaqueOwner **)buf = a;
        *(Rva009A3540OpaqueOwner **)(buf + 4) = b;
        *(unsigned int *)(buf + 0x10) = 1;
        memcpy(fresh, buf, 0x2c);

        Rva009A3540PairNode **slot = &((Rva009A3540PairNode **)((char *)this + 0x18))[bucket];
        *(Rva009A3540PairNode ***)((char *)fresh + 0x2c) = slot;
        Rva009A3540PairNode *old = *slot;
        fresh->next = old;
        if (old != 0)
            *(Rva009A3540PairNode ***)((char *)old + 0x2c) = &fresh->next;
        *slot = fresh;

        Rva009A3540PairNode::Link **headA = (Rva009A3540PairNode::Link **)((char *)a + 0x20);
        fresh->link14.backlink = headA;
        fresh->link14.next = *headA;
        if (*headA != 0)
            (*headA)->backlink = &fresh->link14.next;
        *headA = &fresh->link14;

        Rva009A3540PairNode::Link **headB = (Rva009A3540PairNode::Link **)((char *)b + 0x20);
        fresh->link20.backlink = headB;
        fresh->link20.next = *headB;
        if (*headB != 0)
            (*headB)->backlink = &fresh->link20.next;
        *headB = &fresh->link20;

        *(Rva009A3540PairNode **)((char *)fresh + 0x28) = fresh;
        fresh->pad1c = (unsigned int)fresh;
        return;
    }

    unsigned int count = node->counter + 1;
    node->counter = count;
    if (count != *(unsigned int *)((char *)this + 0xc068))
        return;

    *(Rva009A3540OpaqueOwner **)buf = a;
    *(Rva009A3540OpaqueOwner **)(buf + 4) = b;
    *(unsigned int *)(buf + 8) = aId;
    *(unsigned int *)(buf + 0xc) = bId;
    *(unsigned int *)(buf + 0x10) = 0;
    ((Rva009A3770HashTable *)((char *)this + 0xae10))->insert((Rva009A3770Node *)buf);
}
