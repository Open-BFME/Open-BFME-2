// cl: /MD
// ?get@Rva001F45DFSlot@@QBEHXZ @0x001F45DF 16B.
// Reads pointer at +0x3c, falls back to pinned ?Make001FCBD7@@YAPAVParticleSystem@@XZ
// when null, then returns dword at +0x7c through it. Caller at 0x001F4892.
// Honest Rva name; /O1 for the frameless null-or-Make chase.
class ParticleSystem;
ParticleSystem *Make001FCBD7();
struct Rva001F45DFInner {
    char m_pad[0x7c];
    int m_value;
};
class Rva001F45DFSlot {
public:
    int get() const;
    char m_lead[0x3c];
    Rva001F45DFInner *m_ptr;
};
int Rva001F45DFSlot::get() const
{
    Rva001F45DFInner *p = m_ptr;
    if (!p)
        p = (Rva001F45DFInner *)Make001FCBD7();
    return p->m_value;
}
