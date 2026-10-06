// cl: /MD
// ?Rva002EBB53SiftUp@@YAXPAPAU_Rva002EBB53Wrap@@HHPAU1@@Z, retail 0x002EBB53, 72 bytes.
// Binary-heap sift-up over wrapper slots ordered by the payload key at +0x10.
// Evidence: stlport WWLib neighbours (same /O1 area, horde rank set family);
// (hole-1)/2 parent chain with top bound; both child and value keys read
// through slot +0; unblocks 0x002EBB9B/0x002EF216.
struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
void Rva002EBB53SiftUp(_Rva002EBB53Wrap **base, int hole, int top, _Rva002EBB53Wrap *val)
{
    int parent = (hole - 1) / 2;
    while (hole > top) {
        _Rva002EBB53Wrap *child = base[parent];
        if (child->m_inner->m_key <= val->m_inner->m_key)
            break;
        base[hole] = child;
        hole = parent;
        parent = (hole - 1) / 2;
    }
    base[hole] = val;
}
