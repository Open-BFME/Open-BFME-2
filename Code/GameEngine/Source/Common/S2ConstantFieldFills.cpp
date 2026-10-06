// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S2ConstantFieldFills.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only this one placed
// body is defined here; the donor's Rva00082A80::reset,
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
