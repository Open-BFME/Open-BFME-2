// Target facts (code addresses are RVAs): Rva005B61B3 has no virtual functions or base subobject. Comparator 0x005B61B3 saves this in EBX at 0x005B61C1 and reads signed sort selectors at +0 (0x005B61E5) and +4 (0x005B6256). Both words select cases 0..5; neither is a vptr.
// Retail passes exactly eight comparator bytes by value: 0x005B649A/0x005B649E push its two words, then 0x005B64AC calls 0x005B63E4 and 0x005B64B1 discards five dwords (two iterator pointers, one dummy pointer and the comparator). PopulateHeroList reads the two words from Manager+0x18/+0x1C at 0x005B67E3/0x005B67FC and pushes them at 0x005B67FF/0x005B6800 before sort 0x005B670C. No comparator lifetime calls or vtable stores occur in these paths.
// The ledger declares bool rva005B61B3(void *, void *) at 0x005B61B3; 0x005B6344 calls it directly, 0x005B6349 tests AL and 0x005B6264 returns with RET 8. Its body stays out of line. Size is 8; the two four-byte fields are exposed for the proven Manager sort-key accesses. No out-of-line constructor, destructor, copy or assignment row names this class.
#ifndef BFME2_RVA005B61B3_H
#define BFME2_RVA005B61B3_H

class Rva005B61B3
{
public:
    bool rva005B61B3(void *a, void *b);

    int m_key0;
    int m_key1;
};

typedef char BfmeRva005B61B3Extent[(sizeof(Rva005B61B3) == 8) ? 1 : -1];

#endif
