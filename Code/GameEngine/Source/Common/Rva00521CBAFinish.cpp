// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?Rva00521CBAAdvance@@YAXPAPAURva00521CBANode@@HPAX@Z retail 0x00521CBA 41B
// Evidence: caller 0x00521EC2 pushes 3 args; no callees; walks a doubly-linked
// node forward via +0 for positive count and via +4 for negative count. The
// bare do-while attempt needed /O2 to get count in eax/holder in ecx but then
// picked up a 4-byte loop-align NOP; materialising the loop variable as a
// shared local gives the same register split at /O1 with no alignment pad.
struct Rva00521CBANode
{
    struct Rva00521CBANode *m_next;
    struct Rva00521CBANode *m_prev;
};

void Rva00521CBAAdvance(struct Rva00521CBANode **holder, int count, void *unused)
{
    (void)unused;
    int i;
    if (count > 0) {
        for (i = count; i != 0; --i)
            *holder = (*holder)->m_next;
        return;
    }
    if (count == 0)
        return;
    i = -count;
    do {
        *holder = (*holder)->m_prev;
    } while (--i != 0);
}

// ?Rva00521EC2Advance@@YAXPAPAURva00521CBANode@@H@Z @0x00521EC2 24B: two-arg wrapper forwarding to three-arg Advance with dummy third. Evidence: caller 0x0052270A pushes holder+count; callee rowed 0x00521CBA takes unused third; unlocks 0x00522697.
void Rva00521EC2Advance(struct Rva00521CBANode **holder, int count)
{
	char dummy;
	Rva00521CBAAdvance(holder, count, &dummy);
}
