// cl: /MD
// Sibling of U2AllocatedRangeCopies.cpp at 0x0083F2F0 / 0x0083F330, same
// allocator import slot, but eight-byte elements copied inline instead of
// through the three-argument copy import.  Retail shifts the count by three
// for the allocation, arithmetic-shifts it back, and walks the destination
// with the source-minus-destination offset hoisted out of the loop.

// Retail slot 0xBBA6EC is msvcr71!malloc (import-ref verified); the BFME1
// donor's u2_import_0135944C alias for the same slot fails the check here.
#include <stdlib.h>

struct U2Elem8
{
	int m_a;
	int m_b;
};

void *Rva0083F3B0Duplicate(const U2Elem8 *src, int count)
{
	unsigned int bytes = (unsigned int)count << 3;
	U2Elem8 *u2Elem8 = (U2Elem8 *)malloc(bytes);
	if (u2Elem8 != 0)
	{
		int n = (int)bytes >> 3;
		unsigned int dst = (unsigned int)u2Elem8;
		if (n > 0)
		{
			int off = (int)src - (int)u2Elem8;
			do
			{
				*(U2Elem8 *)dst = *(U2Elem8 *)(off + dst);
				dst += 8;
				--n;
			}
			while (n);
		}
	}
	return u2Elem8;
}
