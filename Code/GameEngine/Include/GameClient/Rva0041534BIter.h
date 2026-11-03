// Target facts: RVA 0x0041534B calls lookup 0x00056F61, stores its node pointer at result+0 (0x0041535B) and the input table pointer at result+4 (0x0041535D), then returns the hidden result pointer with RET 8.
// Callers 0x002130F6, 0x00213148, 0x00223CDB and 0x002AE98B reserve exactly 8 bytes for that result and read its node at +0; the complete two-pointer result has no base, vptr or virtual functions in retail.
// The row at 0x0041534B spells the return type as struct Rva0041534BIter; no constructor, destructor, copy or assignment row names this type. RVA 0x00216F77 also stores BannerUI+0x0C into the owner field, so its pointee remains opaque. The pointer constructor performs the two result stores; default construction leaves storage untouched.
#ifndef BFME2_RVA0041534BITER_H
#define BFME2_RVA0041534BITER_H

struct Rva0041534BIter
{
    void *m_node;
    void *m_table;

    Rva0041534BIter() {}
    Rva0041534BIter(void *node, void *table) : m_node(node), m_table(table) {}
};

#endif
