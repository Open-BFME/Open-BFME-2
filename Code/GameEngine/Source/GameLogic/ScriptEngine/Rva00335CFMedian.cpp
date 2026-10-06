// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// ?Rva00335CFMedian@@YAPBVAsciiString@@PBV1@00@Z, retail 0x00335CFD 94B.
// Median of three AsciiStrings via rowed StringBase compare 0x000069D6.
// Caller 0x00337D5A.
#include "ascii_string.h"

const AsciiString *Rva00335CFMedian(const AsciiString *a, const AsciiString *b, const AsciiString *c)
{
	const StringBase<char> &ra = (const StringBase<char> &)*a;
	const StringBase<char> &rb = (const StringBase<char> &)*b;
	const StringBase<char> &rc = (const StringBase<char> &)*c;
	if (ra.compare(rb) < 0)
	{
		if (rb.compare(rc) < 0)
			return b;
		if (ra.compare(rc) < 0)
			return c;
		return a;
	}
	else
	{
		if (ra.compare(rc) < 0)
			return a;
		if (rb.compare(rc) < 0)
			return c;
		return b;
	}
}
