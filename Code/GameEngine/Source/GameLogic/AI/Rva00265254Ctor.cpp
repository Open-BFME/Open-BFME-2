// cl: /DNDEBUG /MD
// ??0Rva00265254@@QAE@IIII@Z retail 0x00265254 88B.
// Unlock lane: memset 0x4c plus three bit sets; callers pass 0 plus three ids.
// Evidence: callers at 0x00265B39 0x002671F1 pass 0 0x7b-0x7d 0x151-0x153.
// ??0Rva00265254@@QAE@IIIIIIIII@Z retail 0x002652AC 186B.
// Unlock lane: memset 0x4c plus eight bit sets; first arg ignored like sibling.
// Evidence: callers at 0x00267E46 0x0044F0B3 pass 0 plus eight ids.
// ??0Rva00265254@@QAE@IIIIIIIIIIII@Z retail 0x00265366 243B.
// Leaf: memset 0x4c plus eleven bit sets; first arg ignored like siblings.

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

class Rva00265254
{
public:
	Rva00265254(unsigned int unusedArgument, unsigned int firstBitIndex, unsigned int secondBitIndex, unsigned int thirdBitIndex);
	Rva00265254(unsigned int unusedArgument, unsigned int unlockId, unsigned int secondBitIndex, unsigned int thirdBitIndex, unsigned int fourthBitIndex, unsigned int fifthBitIndex, unsigned int sixthBitIndex, unsigned int seventhBitIndex, unsigned int eighthBitIndex);
	Rva00265254(unsigned int unusedArgument, unsigned int firstBitIndex, unsigned int secondBitIndex, unsigned int thirdBitIndex, unsigned int fourthBitIndex, unsigned int fifthBitIndex, unsigned int sixthBitIndex, unsigned int seventhBitIndex, unsigned int eighthBitIndex, unsigned int unlockId, unsigned int tenthBitIndex, unsigned int eleventhBitIndex);
private:
	unsigned int m_bits[19];
};

Rva00265254::Rva00265254(unsigned int unusedArgument, unsigned int firstBitIndex, unsigned int secondBitIndex, unsigned int thirdBitIndex)
{
	memset(this, 0, 0x4c);
	m_bits[firstBitIndex >> 5] |= 1u << (firstBitIndex & 31);
	m_bits[secondBitIndex >> 5] |= 1u << (secondBitIndex & 31);
	m_bits[thirdBitIndex >> 5] |= 1u << (thirdBitIndex & 31);
}

Rva00265254::Rva00265254(unsigned int unusedArgument, unsigned int unlockId, unsigned int secondBitIndex, unsigned int thirdBitIndex, unsigned int fourthBitIndex, unsigned int fifthBitIndex, unsigned int sixthBitIndex, unsigned int seventhBitIndex, unsigned int eighthBitIndex)
{
	memset(this, 0, 0x4c);
	m_bits[unlockId >> 5] |= 1u << (unlockId & 31);
	m_bits[secondBitIndex >> 5] |= 1u << (secondBitIndex & 31);
	m_bits[thirdBitIndex >> 5] |= 1u << (thirdBitIndex & 31);
	m_bits[fourthBitIndex >> 5] |= 1u << (fourthBitIndex & 31);
	m_bits[fifthBitIndex >> 5] |= 1u << (fifthBitIndex & 31);
	m_bits[sixthBitIndex >> 5] |= 1u << (sixthBitIndex & 31);
	m_bits[seventhBitIndex >> 5] |= 1u << (seventhBitIndex & 31);
	m_bits[eighthBitIndex >> 5] |= 1u << (eighthBitIndex & 31);
}

Rva00265254::Rva00265254(unsigned int unusedArgument, unsigned int firstBitIndex, unsigned int secondBitIndex, unsigned int thirdBitIndex, unsigned int fourthBitIndex, unsigned int fifthBitIndex, unsigned int sixthBitIndex, unsigned int seventhBitIndex, unsigned int eighthBitIndex, unsigned int unlockId, unsigned int tenthBitIndex, unsigned int eleventhBitIndex)
{
	memset(this, 0, 0x4c);
	m_bits[firstBitIndex >> 5] |= 1u << (firstBitIndex & 31);
	m_bits[secondBitIndex >> 5] |= 1u << (secondBitIndex & 31);
	m_bits[thirdBitIndex >> 5] |= 1u << (thirdBitIndex & 31);
	m_bits[fourthBitIndex >> 5] |= 1u << (fourthBitIndex & 31);
	m_bits[fifthBitIndex >> 5] |= 1u << (fifthBitIndex & 31);
	m_bits[sixthBitIndex >> 5] |= 1u << (sixthBitIndex & 31);
	m_bits[seventhBitIndex >> 5] |= 1u << (seventhBitIndex & 31);
	m_bits[eighthBitIndex >> 5] |= 1u << (eighthBitIndex & 31);
	m_bits[unlockId >> 5] |= 1u << (unlockId & 31);
	m_bits[tenthBitIndex >> 5] |= 1u << (tenthBitIndex & 31);
	m_bits[eleventhBitIndex >> 5] |= 1u << (eleventhBitIndex & 31);
}
