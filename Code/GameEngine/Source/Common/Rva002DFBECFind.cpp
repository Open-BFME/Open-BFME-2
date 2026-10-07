// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva002DFBECFind@@YAPAXPBURva002DFBECRange@@ABVAsciiString@@@Z at 0x002DFBEC (47B). Linear AsciiString search over a begin/end pointer array; each element points to a record with AsciiString at +4 compared via rowed StringBase compare 0x000069D6; returns the element pointer or null. Evidence: caller 0x002E016A in 0x002E012D (duplicate nugget tags Living World Building Template); prev 0x002DFA7A next 0x002DFC1B same dir; honest free-function name.
#include "ascii_string.h"

struct Rva002DFBECElem
{
	void *m_00;
	AsciiString m_04;
};

struct Rva002DFBECRange
{
	Rva002DFBECElem **m_begin;
	Rva002DFBECElem **m_end;
};

void *Rva002DFBECFind(const Rva002DFBECRange *range, const AsciiString &key)
{
	Rva002DFBECElem **begin = range->m_begin;
	Rva002DFBECElem **end = range->m_end;
	for (Rva002DFBECElem **cur = begin; cur != end; ++cur)
	{
		if (((const StringBase<char> &)(*cur)->m_04).compare((const StringBase<char> &)key) == 0)
			return *cur;
	}
	return 0;
}
