// cl: /MD
//
// ?rva002F301F@Rva002F301F@@QAEXXZ, retail 0x002f301f, 26 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Pop-style method that forwards base/end/extra to 0x002F1F02 then pops end by one pointer. Evidence: caller 0x002F3703 and 0x002F3726 as thiscall with no stack args; callee rowed. Row 0x002F1F02 declares int extra but retail mov al proves byte so declared unsigned char per code use.
struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
void __cdecl Rva002F1F02Wrap(_Rva002EBB53Wrap **base, _Rva002EBB53Wrap **end, unsigned char extra);
class Rva002F301F {
public:
    _Rva002EBB53Wrap **m_base;
    _Rva002EBB53Wrap **m_end;
    unsigned int m_pad08;
    unsigned char m_extra;
    void rva002F301F();
};
void Rva002F301F::rva002F301F()
{
    Rva002F1F02Wrap(m_base, m_end, m_extra);
    m_end--;
}
