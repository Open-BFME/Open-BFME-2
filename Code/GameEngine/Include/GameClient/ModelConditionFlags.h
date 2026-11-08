// Target facts: 0x000B3EB3 scans 19 dwords starting at this+0; 0x000B3FA5 and 0x0025330B update this+4*(bit>>5). ModelConditionFlags is a nonvirtual value in retail; its storage starts with flag bits.
// 0x0028CFF5 copies 19 dwords to Object+0x10C; 0x002791E7 copies the same 0x4C bytes to Drawable+0x258. The complete value is 0x4C bytes with words at +0x00..+0x48, without a vptr.
// The ledger names rva000B3EB3 (0x000B3EB3), rva000B3FA5 (0x000B3FA5) and clear(unsigned) (0x0025330B); 0x001E49C8 tests and 0x001E49D8 sets the indexed word inline, 0x001E49A8 clears it inline, and no call reaches 0x0025330B. Zero Hour ModelState.h and BitFlags.h supply m_bits, test and set names and Boolean test(int); 0x000C2E3A consumes Boolean condition tests.
#pragma once

#ifndef BFME2_MODELCONDITIONFLAGS_H
#define BFME2_MODELCONDITIONFLAGS_H

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
	void rva000B3FA5(int bit, int value);

	unsigned int test(unsigned int bit) const
	{
		return m_bits[bit >> 5] & (1U << (bit & 31));
	}
	bool test(int bit) const
	{
		return ((m_bits[bit >> 5] >> (bit & 31)) & 1) != 0;
	}
	void set(unsigned int bit)
	{
		m_bits[bit >> 5] |= 1U << (bit & 31);
	}
	void clear(unsigned int bit)
	{
		m_bits[bit >> 5] &= ~(1U << (bit & 31));
	}

	unsigned int m_bits[19];
};

#endif
