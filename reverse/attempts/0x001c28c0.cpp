// ?rva001C28C0Filter@@YAXPBURva001C28C0ContextPrefix@@PBEPAEHHPBHI@Z
// partial score=0.6515 date=2026-10-07
// cl: /O2 /G6 /MD /DNDEBUG
// Complete target1C28C0..1C2B7D701B scalar 8x8 neighbor filter.
// BF1ba7 9B1ED0 has the same701B boundary; only bytes17..20 (the
// edge-tag table address) differ. It has only a gen_asm body; no
// clean scalar donor is available. Related adaptive-filter donor9BE180
// supports the filter-table and signed edge-tag roles, not this scalar ABI.
// Target accesses contextword8 only; original owner/full size unknown.
// Existing owned Vp6FilterEdgeTagTable supplies the exact DB7A28 referent.
// Best O2/G6 trial emits705B with a56-byte frame versus native48.
// Column pointer scheduling and array placement still differ. O2/G7 emits
// 728B; O1/Os416B. Masked full-body SequenceMatcher score0.6515.
// Preserve signed border positions and the native conditional weight order.
extern "C" int Vp6FilterEdgeTagTable[];
struct Rva001C28C0ContextPrefix {
    unsigned char prefix[8];
    int strength;
};
void __cdecl rva001C28C0Filter(const Rva001C28C0ContextPrefix *context,
    const unsigned char *source, unsigned char *dest, int stride,
    int selector, const int *table, unsigned int variance) {
    int edgeTag=Vp6FilterEdgeTagTable[selector];
    int level=table[selector];
    int scale=4;
    if (context->strength>100) level=context->strength-100;
    if (variance>0x8000) scale=4;
    else if (variance>0x800) scale=8;
    int cap=3*level;
    if (cap>32) cap=32;
    const unsigned char *above=source-stride-1;
    const unsigned char *below=source+stride;
    unsigned int rows=8;
    do {
        int x=0;
        const unsigned char *current=above;
        do {
            int neighbors[8];
            neighbors[0]=*current++;
            neighbors[1]=*current++;
            neighbors[2]=current[0];
            neighbors[3]=current[stride-2];
            neighbors[4]=current[stride];
            neighbors[5]=below[x-1];
            neighbors[6]=below[x];
            neighbors[7]=below[x+1];
            int center=current[stride-1];
            int centerWeight=256;
            int sum=128;
            for (unsigned int n=0;n<8;++n) {
                int pixel=neighbors[n];
                int delta=center-pixel;
                if (delta<=0) delta=pixel-center;
                int weight=level-((delta*scale)>>2)+32;
                if (weight < -64) weight=edgeTag;
                else if (weight<0) weight=0;
                else if (weight>cap) weight=cap;
                sum+=pixel*weight;
                centerWeight-=weight;
            }
            int value=(center*centerWeight+sum)>>8;
            if (value<0) value=0;
            else if (value>255) value=255;
            dest[x]=(unsigned char)value;
            ++x;
            --current;
        } while ((unsigned int)x<8);
        above+=stride;below+=stride;dest+=stride;
    } while (--rows);
}
