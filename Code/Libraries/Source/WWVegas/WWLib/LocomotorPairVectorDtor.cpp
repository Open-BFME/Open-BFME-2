// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??1?$vector@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@@_STL@@QAE@XZ RVA 0x004C7767 size 63
// Evidence: calls _Destroy folded at 0x004C7542 plus _free rowed at 0x00030830 plus EH_prolog; caller at 0x004C7AD5; chain lane; explicit dtor exact mod reloc.
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
typedef _STL::vector<LocoPair, _STL::allocator<LocoPair> > LocoPairVec;

template LocoPairVec::~vector();
