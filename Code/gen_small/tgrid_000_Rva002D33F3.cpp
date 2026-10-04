// cl: -EHsc /Os -Ireference/open-bfme-1/game/gen_small
// stlport

// _STL::fill<Gen_p1pod*, Gen_p1pod> is the STLport <algorithm> fill over a
// one-byte POD. The BFME1 donor gen_small/tgrid_000.cpp only emits it through
// vector<Gen_p1pod>'s instantiation. Retail 0x002D33F3 is the byte-copy loop
// (first == last guard, then *first = *value); the function template is emitted
// here by explicit instantiation, the donor's containers omitted.
#include <algorithm>

struct Gen_p1pod { char a; };

template void _STL::fill<Gen_p1pod *, Gen_p1pod>(
	Gen_p1pod *__first, Gen_p1pod *__last, const Gen_p1pod &__value);
