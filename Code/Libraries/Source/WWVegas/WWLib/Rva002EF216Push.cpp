// cl: /O1 /MD
// ?Rva002EF216Push@@YAXPAPAU_Rva002EBB53Wrap@@0PAXHH@Z @0x002EF216 35B
// Push wrapper calling rowed SiftUp 0x002EBB53 with extra passthrough.
// Evidence: caller 0x002F0D45 pushes 5; callee rowed SiftUp 0x002EBB53.
struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
void Rva002EBB53SiftUp(_Rva002EBB53Wrap **base, int hole, int top, _Rva002EBB53Wrap *val, void *extra);
void __cdecl Rva002EF216Push(_Rva002EBB53Wrap **first, _Rva002EBB53Wrap **last, void *extra, int d1, int d2)
{
    (void)d1; (void)d2;
    _Rva002EBB53Wrap *val = *(last - 1);
    int hole = int(last - first) - 1;
    Rva002EBB53SiftUp(first, hole, 0, val, extra);
}
