// cl: /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva0041EA2C@Rva0041EA2C@@QAEXPAX@Z @0x0041EA2C 28B via hashtable node free twin
// Retail 28B: esi=node arg, lea ecx [esi+4], call rowed Locomotor pair dtor
// (ICF twin of Science pair at +4), test esi, free via rowed _free, ret 4.
// Caller 0x0041EA88 passes this in ecx plus node push; unblocks 0x0041EA88.

#include <vector>
#include <map>

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/LocomotorSetType.h"













class LocomotorTemplate;

typedef _STL::vector<const LocomotorTemplate *> LocomotorVec;
typedef _STL::pair<const LocomotorSetType, LocomotorVec> LocoPair;

#include <stdlib.h>

class Rva0041EA2C
{
public:
	void rva0041EA2C(void *);
};

void Rva0041EA2C::rva0041EA2C(void *p)
{
	((LocoPair *)((char *)p + 4))->~LocoPair();
	if (p)
		free(p);
}
