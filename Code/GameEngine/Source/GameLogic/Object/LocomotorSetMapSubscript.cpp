// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
// retail 0x001EA05B (153 bytes).
//
// LocomotorSetType to template-vector map subscript (AIUpdate parse
// cluster). Miss path builds a default vector temp through the rowed
// _Vector_base 0x211E58, pairs it with the key through 0x796CB, and
// hint-inserts through the rowed wrapper 0x1E9066. /EHs (not /EHsc)
// keeps the post-insert EH state stores; the explicit-spec rvalue pair
// keeps the pair address in eax (no re-lea) and homes the hidden
// insert-result temp at [ebp-0x10].

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

template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType& __k)
{
	BfmeLocomotorSetMap::iterator __i = lower_bound(__k);
	if (__i == end() || key_comp()(__k, (*__i).first)) {
		BfmeLocomotorTemplateVector __tmp;
		__i = insert(__i, BfmeLocomotorSetMap::value_type(__k, __tmp));
	}
	return (*__i).second;
}

template class _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > >;
