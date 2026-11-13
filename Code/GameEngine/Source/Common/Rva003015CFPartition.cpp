// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva003015CFPartition@@YAPAPAURva00450B90Item@@VRva00450B90Predicate@@ABURva003015CFRange@@@Z
// retail 0x003015CF (24B): partition a pointer range by the predicate, through
// the rowed _STL::partition instantiation (0x00301295,
// stlport_partition_rva00450b90.cpp), and return its split point. Retail keeps
// this cdecl wrapper uncalled; names are address-derived and the predicate is
// that unit's view. The range ends are read into locals first, as retail
// loads both before pushing the predicate.
#include <algorithm>

struct Rva00450B90Item;

#include "../../Include/Common/Rva00450B90Predicate.h"

struct Rva003015CFRange
{
	Rva00450B90Item **m_begin;
	Rva00450B90Item **m_end;
};

Rva00450B90Item **Rva003015CFPartition(Rva00450B90Predicate pred, const Rva003015CFRange &range)
{
	Rva00450B90Item **last = range.m_end;
	Rva00450B90Item **first = range.m_begin;
	return _STL::partition(first, last, pred);
}
