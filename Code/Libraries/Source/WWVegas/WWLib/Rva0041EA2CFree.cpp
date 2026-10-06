// cl: /MD /DNDEBUG
// stlport
// ?rva0041EA2C@Rva0041EA2C@@QAEXPAX@Z @0x0041EA2C 28B via hashtable node free twin
// Retail 28B: esi=node arg, lea ecx [esi+4], call rowed Locomotor pair dtor
// (ICF twin of Science pair at +4), test esi, free via rowed _free, ret 4.
// Caller 0x0041EA88 passes this in ecx plus node push; unblocks 0x0041EA88.

#include <vector>
#include <map>

enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,
	LOCOMOTORSET_COUNT
};

class LocomotorTemplate;

typedef _STL::vector<const LocomotorTemplate *> LocomotorVec;
typedef _STL::pair<const LocomotorSetType, LocomotorVec> LocoPair;

extern "C" void __cdecl free(void *);

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
