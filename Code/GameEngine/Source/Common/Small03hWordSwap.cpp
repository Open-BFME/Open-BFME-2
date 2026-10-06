// cl: /DNDEBUG /MD /EHsc
//
// Provenance: Open-BFME-1 game/GameEngine/Source/Common/Small03hWordSwap.cpp at
// 10af19f44a (BFME1 byte-identical donor, b1 0x009CC290, here 0x006038EF). Only
// the free function is carried: the donor's two this-loading twins (BFME 1
// 0x009CC2C0 / 0x009CC2F0) are not placed in game.dat.
//
// The cdecl word shuffle: ((v & 0xFF00) + (v << 16)) << 8, plus the
// (v >> 16) & 0xFF byte at bit 8, plus v >> 24 (35 B, plain ret). The
// split-hi spelling (hi = v >> 16 masked and shifted in its own statements)
// is what emits retail's xor-edx + mov-dh tail; the folded single-expression
// spelling mis-allocates registers. IDENTITY IS NOT RECOVERED: it keeps the
// donor's address token.
unsigned int __cdecl Rva009CC290Swap(unsigned int v)
{
	unsigned int a = (v & 0xFF00) + (v << 16);
	a <<= 8;
	unsigned int hi = v >> 16;
	hi &= 0xFF;
	hi <<= 8;
	return a + hi + (v >> 24);
}
