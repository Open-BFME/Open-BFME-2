// ?rva00211505@Rva00211505Owner@@QAEXXZ
// partial score=0.75 date=2026-10-08
// Stash 0x00211505 (60 B): vector loop of thiscall element calls; see re_log partial.
// Retail 0x00211505..0x00211540 (60 B), straight after rva00211494: loop over the
// object-pointer vector at +0x24C/+0x250, calling each element's thiscall method
// at 0x003FD849 (ecx = element), re-reading the bounds on every pass.
class Rva003FD849 { public: void rva003FD849(); };
struct Rva00211505Owner
{
    unsigned char m_pad[0x24C];
    Rva003FD849 **m_begin; // +0x24C
    Rva003FD849 **m_end; // +0x250
    void rva00211505();
};

void Rva00211505Owner::rva00211505()
{
    unsigned int i = 0;
    while (i < (unsigned int)(m_end - m_begin))
    {
        m_begin[i]->rva003FD849();
        ++i;
    }
}
