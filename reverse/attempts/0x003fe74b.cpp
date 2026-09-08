// ?_bfme_updateTimedOps@@YAIXZ
// partial score=0.96 date=2026-09-07
// BFME2 timed-operation pump, reconstructed from the exact BFME1 body and
// the BFME2 retail removal ABI at 0x003FE74B.

class BfmeTimedOpNode
{
public:
    virtual BfmeTimedOpNode *destroy(unsigned int flags);
    unsigned int update(void);
    BfmeTimedOpNode *m_next;
};

#define g_bfmeTimedOpHead (*(BfmeTimedOpNode **)0x00E02EC0)

extern void __cdecl operator delete(void *block);

unsigned int _bfme_updateTimedOps(void)
{
    unsigned int flags = 0;

    if (g_bfmeTimedOpHead != 0)
    {
        flags = g_bfmeTimedOpHead->update();

        if (flags & 2)
        {
            BfmeTimedOpNode *head = g_bfmeTimedOpHead;
            g_bfmeTimedOpHead = head->m_next;
            ::operator delete(head->destroy(0));

            if (g_bfmeTimedOpHead == 0)
                flags &= 4;
        }
    }

    return flags & 5;
}
