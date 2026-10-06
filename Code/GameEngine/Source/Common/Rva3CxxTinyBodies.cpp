// cl: -DNDEBUG -MD -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?set@Rva003D5630@@QAEPAV1@HEHH@Z 0x002E7067, 32 bytes.
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva3CxxTinyBodies.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not -- the donor's own line is
// /O2, which does not place it. Only this one placed body is defined here; the
// donor's other 24 definitions stay out, so the unmatched-definition gate
// passes.
//
// A __thiscall body that stores its four arguments and hands back this. The
// second is an unsigned char followed by three pad bytes, which is why the
// third argument lands at +0x08 and the fourth at +0x0C.
//
// IDENTITY IS NOT RECOVERED.  The name is address-derived.

class Rva003D5630
{
public:
    Rva003D5630 *set(int first, unsigned char second, int third, int fourth);

private:
    int m_first;
    unsigned char m_second;
    char m_padding[3];
    int m_third;
    int m_fourth;
};

// ?set@Rva003D5630@@QAEPAV1@HEHH@Z 0x002E7067
Rva003D5630 *Rva003D5630::set(int first, unsigned char second, int third, int fourth)
{
    m_first = first;
    m_second = second;
    m_third = third;
    m_fourth = fourth;
    return this;
}