// Target facts: retail init (RVA 0x000B3F84) stores the borrowed pointer at +0
// and strlen (or zero) at +4; initWide (0x002342D5) stores the same two words
// using wcslen. Neither stores a vptr. This class has no retail virtual functions.
// makeStringRef (0x002343F7) and Rva00108B93Make (0x00108B93) use an 8-byte
// local and copy only +0/+4 to a hidden result. WinMainTitlePair's writer
// (0x00234828) places its second pair at +8: sizeof is 8, with no base or table.
// The empty user constructor preserves the hidden-result ABI; the copies in
// 0x002343F7 and 0x00234324 are scalar stores, with no out-of-line copy call.
// write (0x000B44F0) copies +4 bytes from the pointer at +0 and returns +4;
// copyBytes (0x0023428D) copies from that pointer plus a byte offset.
// copyWchars (0x002342A7) copies twice +4 bytes and returns +4.
// convertToWide (0x0023436C), convertToWideBuffer (0x002343AB) and operator
// UnicodeString (0x00234788) are rowed out-of-line methods reading length +4.
// The length accessor represents those same reads; m_ptr and m_len describe
// the observed pointer and count, without asserting original source spellings.
#pragma once

#ifndef BFME2_RVA000B3F84PAIR_H
#define BFME2_RVA000B3F84PAIR_H

class UnicodeString;

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	Rva000B3F84Pair *initWide(const unsigned short *src);
	void copyBytes(void *dst, int off, int len);
	void convertToWide(unsigned short *dst, int off, int len);
	int convertToWideBuffer(unsigned short *dst);
	int copyWchars(unsigned short *dst);
	int write(char *dst);
	operator UnicodeString();
	int length() const { return m_len; }

	const char *m_ptr;
	int m_len;
};

#endif
