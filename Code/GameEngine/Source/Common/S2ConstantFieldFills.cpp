// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S2ConstantFieldFills.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. The independent raw
// store below has a separate target view; the donor's Rva00082A80::reset,
// Rva001073F0::reset and Rva00842650::adopt stay out, so the
// unmatched-definition gate passes.
//
// ??0Rva005A7A60@@QAE@XZ 0x004D95B2, 28 bytes
//   (the donor's own @-comment cites 0x005A7A60, its BFME 1 RVA)
//
// It is one of four call-free bodies that do nothing but write constants, or
// copy one field onto another, with no base, no vptr and no branch.
//
// This one is a constructor whose repeated constant is 80000000h; 7FFFFFFFh
// appears once and stays an immediate. The +4 store is a byte, the rest
// dwords.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, and the constants are
// written as the ints they encode.

class Rva005A7A60
{
public:
	Rva005A7A60();
	int m_00;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
};

// @??0Rva005A7A60@@QAE@XZ 0x004D95B2
Rva005A7A60::Rva005A7A60()
{
	m_00 = 0;
	m_04 = false;
	m_08 = (int)0x80000000;
	m_0C = 0x7FFFFFFF;
	m_10 = (int)0x80000000;
}

// Complete native 22C682..22C68C lies after RET 22C681 and before 22C68C.
// ECX supplies the accessed receiver prefix; EAX preserves it while the
// raw 32-bit value A590217B is stored at +4. RET consumes no stack words.
// BF1 f989 Q1ConstantFieldConstructors.cpp compiled O2/x87/G7 supplies
// two indistinguishable constructor-shaped leads. Original constructor
// role, owner, field meaning and complete size are not witnessed here.
// This ordinary method describes only the store and physical pointer
// result; the unaccessed four-byte prefix is intentionally opaque.
class Rva0022C682WordStore
{
public:
    Rva0022C682WordStore *initialize();
private:
    unsigned char unknown0[4];
    unsigned int word4;
};

Rva0022C682WordStore *Rva0022C682WordStore::initialize()
{
    word4 = 0xA590217Bu;
    return this;
}
