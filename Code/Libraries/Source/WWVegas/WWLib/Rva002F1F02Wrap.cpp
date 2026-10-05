// cl: /O1 /MD
// ?Rva002F1F02Wrap@@YAXPAPAU_Rva002EBB53Wrap@@0H@Z @0x002F1F02 23B
// Pop-wrapper forwarder to rowed 0x002F0EE4 with NULL result. Evidence: caller 0x002F302B passes 3 args and cleans 12; callee rowed.
struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
void __cdecl Rva002F0EE4Wrap(_Rva002EBB53Wrap **base, _Rva002EBB53Wrap **end, _Rva002EBB53Wrap **result, int extra);
void __cdecl Rva002F1F02Wrap(_Rva002EBB53Wrap **base, _Rva002EBB53Wrap **end, int extra)
{
    Rva002F0EE4Wrap(base, end, 0, extra);
}
