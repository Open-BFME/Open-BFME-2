// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include <vector>

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
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

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;


// Reuse verified provider definitions instead of emitting competing STL copies.
namespace _STL {
template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType&);
template<> BfmeLocomotorTemplateVector::iterator BfmeLocomotorTemplateVector::erase(iterator, iterator);
template<> void BfmeLocomotorTemplateVector::push_back(const value_type&);
}
// Reference: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24.
// Source guide: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp,
// parseLocomotorSet clear/push operation. Identity/layout below are target evidence.
// Target 33E17D/59 receives key and TEMPLATE POINTER BY VALUE, not a reference.
// The caller at1EA390 passes the result of LocomotorStore name lookup directly.
// Target receiver has same ThingTemplate map+3AC as its separately observed refill.
// Original member name unknown.
class ThingTemplate {
public: void rva0033E17D(LocomotorSetType key, const LocomotorTemplate *value);
private: unsigned char unknown00[0x3ac]; BfmeLocomotorSetMap locomotors;
};
void ThingTemplate::rva0033E17D(LocomotorSetType key, const LocomotorTemplate *value) {
 locomotors[key].clear();
 locomotors[key].push_back(value);
}
