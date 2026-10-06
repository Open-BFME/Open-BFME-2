// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// ?Rva00335CAELowerBound@@YAPAURva00335CAERec@@PAU1@0ABVAsciiString@@@Z, retail 0x00335CAE 79B.
// Binary lower_bound over 20B records with AsciiString at +0 via rowed
// StringBase compare 0x000069D6. Callers 0x00336295 0x00337E6A.
#include "ascii_string.h"

struct Rva00335CAERec
{
	AsciiString name; // +0
	char _pad04[16]; // +4..+13 (sizeof 20)
};

const Rva00335CAERec *Rva00335CAELowerBound(Rva00335CAERec *first, Rva00335CAERec *last, const AsciiString &needle)
{
	int count = (int)(last - first);
	while (count > 0)
	{
		int half = count >> 1;
		Rva00335CAERec *mid = first + half;
		if (((const StringBase<char> &)mid->name).compare((const StringBase<char> &)needle) < 0)
		{
			first = mid + 1;
			count -= half + 1;
		}
		else
		{
			count = half;
		}
	}
	return first;
}
