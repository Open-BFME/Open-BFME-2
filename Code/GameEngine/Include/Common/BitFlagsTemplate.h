// BitFlags<N>: the one flag-set template retail instantiates per N.
//
// Target facts (retail game.dat; probes in the class-bitflags lane's notes):
// - Each N has its own NULL-terminated name table, and the table's length is
//   N: 6 (0xDBA9AC), 7 (0xDBE9B0, 0xDD263C, 0xDC17CC), 8 (0xDC85C4),
//   11 (0xDC828C), 12 (0xDBA9C8), 15 (0xDBAA00), 21 (0xDBAA40), 101 (0xDA5F30),
//   104 (0xDBC2C8), 154 (0xDC0B40), 218 (0xDBBE18), 591 (0xDBAA98).
// - The bodies use the same N. xfer loops to N (0x0B, 0x0F, 0x15, 0x65, 0x68,
//   0x9A, 0xDA, 0x24F) and clears (N + 31) / 32 words (4, 0x10, 0x14, 0x1C,
//   0x4C bytes); count, any, test and testSetAndClear loop over that many
//   words; xfer -> setBitByName -> getSingleBitFromName and xfer ->
//   getBitNameIfSet each read that N's table.
// - Storage is (N + 31) / 32 dwords and nothing else: no vptr. Object::xfer
//   0x00297684 transfers BitFlags<101> at Object+0x94, <591> at +0x10C,
//   <11> at +0x1C8, <104> at +0x370 and <154> at +0x3A4.
// - It is a word array, not an STLport bitset: count is a SWAR popcount
//   (0x000B6586), where STLport's _M_do_count reads a byte table, and <11>::any
//   0x0023C58B loops with bound 1, where _Base_bitset<1UL>::_M_is_any is a
//   single compare.
// - Out of line, once per N: xfer, count, any, test(mask), testSetAndClear,
//   countIntersection, countInverseIntersection, getSingleBitFromName,
//   setBitByName, getBitNameIfSet, getBitNamesList, the raw-bits transfer
//   (xferRawBits), buildDescription, clear() and the four constructors. Bodies
//   that depend only on the word count are shared across N (ICF): one 1-word
//   count 0x0028F528 for 11 and 15, one 4-word count 0x0028F6EB for 101 and
//   104. Bit test, set and clear of one index are inlined at their callers.
//   Not every N has every member; a declaration emits nothing until a unit
//   defines or calls it.
//
// Spelling: the members keep the names their rows carry today. getBitNameIfSet
// and xferRawBits are bound to address-named rows; the units that call them
// supply the binding. Zero Hour's Common/BitFlags.h (xfer, set, clear,
// setBitByName, getBitNameIfSet) and WorldBuilder's symbols (DoXfer, SetBit,
// ClearBit, test, testNameArray) are leads for these names, not proof.
//
// Unproven:
// - The upgrade mask is 32 words (0x00046827, 0x00406F9C, 0x0033A453 loop 0x20),
//   but has no name table, so retail does not fix its N. WorldBuilder, a
//   separate binary, names it BitFlags<1024, UpgradeID>.
// - WorldBuilder spells every instance with a second template parameter,
//   BitFlags<N, enum E>. Mangled names are not in retail, so nothing in its
//   bytes can prove that parameter, and this header has one. That is a naming
//   decision for later.
// - This file's name is new and stands for no retail path. WorldBuilder's line
//   information cites Common/BitFlags.h and Common/BitFlagsIO.h, and Zero Hour's
//   Common/BitFlags.h, a different template, is still what 248 units resolve.
#pragma once

#ifndef BFME2_BITFLAGSTEMPLATE_H
#define BFME2_BITFLAGSTEMPLATE_H

class Xfer;
class AsciiString;

template <int NUMBITS> class BitFlags
{
public:
	enum { NUMWORDS = (NUMBITS + 31) / 32 };
	enum BogusInitType { kInit = 0 };

	BitFlags();
	BitFlags(BogusInitType, int bit);
	BitFlags(BogusInitType, int bit1, int bit2);
	BitFlags(BogusInitType, int bit1, int bit2, int bit3, int bit4);

	bool test(int bit) const
	{
		return (m_bits[(unsigned int)bit >> 5] & (1U << (bit & 31))) != 0;
	}
	void set(int bit)
	{
		m_bits[(unsigned int)bit >> 5] |= 1U << (bit & 31);
	}
	void clear(int bit)
	{
		m_bits[(unsigned int)bit >> 5] &= ~(1U << (bit & 31));
	}

	void clear();
	bool any() const;
	int count() const;
	bool test(const void *mask) const;
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
	int countIntersection(const BitFlags &that) const;
	int countInverseIntersection(const BitFlags &that) const;

	static int getSingleBitFromName(const char *token);
	static const char **getBitNamesList();
	const char *getBitNameIfSet(int i) const;
	bool setBitByName(const char *token);
	void buildDescription(AsciiString *str, int) const;

	void xferRawBits(Xfer *xfer);
	void xfer(Xfer *xfer);

private:
	unsigned int m_bits[NUMWORDS];
};

#endif
