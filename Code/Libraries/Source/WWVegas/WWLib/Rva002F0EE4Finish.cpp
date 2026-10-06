// ?Rva002F0EE4Wrap@@YAXPAPAU_Rva002EBB53Wrap@@00H@Z
// partial score=0.92 date=2026-09-29
// ?Rva002F0EE4Wrap@@YAXPAPAU_Rva002EBB53Wrap@@00H@Z
// partial score=0.92 date=2026-09-29
// cl: /MD
// ?Rva002F0EE4Wrap@@YAXPAPAU_Rva002EBB53Wrap@@00H@Z, retail 0x002F0EE4, 30 bytes.
// Pop wrapper: last=end-1, pop base into result via rowed Pop.
// Evidence: calls rowed 0x002EF27D Pop; caller 0x002F1F02 pushes 4; unblocks 0x002F1F02.
struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
void Rva002EF27DPop(_Rva002EBB53Wrap **first, _Rva002EBB53Wrap **last, _Rva002EBB53Wrap **result, _Rva002EBB53Wrap *val, int comp, void *dist);
void Rva002F0EE4Wrap(_Rva002EBB53Wrap **base, _Rva002EBB53Wrap **end, _Rva002EBB53Wrap **result, int extra)
{
    _Rva002EBB53Wrap **last = end - 1;
    Rva002EF27DPop(base, last, last, *last, extra, 0);
}
