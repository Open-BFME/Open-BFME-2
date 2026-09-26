// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x001BC390; the target body is bounded by int3 padding on both sides.
// BFME1 donors at 0x009AB950 and 0x009AB990 were ICF-folded; this name is RVA-derived.
// Retail accesses the table at 0x00BD8D00; context and output offsets follow target loads/stores.
// RVA 0x009AB950: select one 128-byte block and copy two short values.
struct Rva001BC390Context
{
    int m_unused;
    const unsigned short *m_wordTable;
    unsigned int m_wordIndex;
    void *m_blocks[1];
};

struct Rva001BC390Output
{
    unsigned char m_unused[4];
    void *m_block;
    unsigned short m_reference;
    unsigned short m_current;
};


void __cdecl Rva001BC390Select(Rva001BC390Context *context,
                               Rva001BC390Output *output, unsigned int block)
{
    output->m_block = context->m_blocks[block];
    output->m_current = context->m_wordTable[block * 64];
    output->m_reference = ((const unsigned short *)0x00BD8D00)[context->m_wordIndex * 2];
}
