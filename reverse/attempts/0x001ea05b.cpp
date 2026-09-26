// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
// partial score=0.9 date=2026-09-26
// ?operator_at_locomotor_map
// partial score=0.9 date=2026-09-26
// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
// partial score=0.9 date=2026-09-26
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// map<LocomotorSetType, vector>::operator[] (AIUpdate parse cluster).
// Explicit specialization with named temps reproduces retail's 4.6-style
// miss path (lower_bound + _Vector_base temp + pair + hinted insert +
// two frees); the plain explicit instantiation emits 143B with a
// __default_constructed helper retail lacks. This body is 148/153B with the
// identical call sequence; remaining deltas are all in the insert-arg
// region: frame 0x1c vs 0x20 (missing -0x10 slot), mov [ebp+8],esp before
// mov [eax],esi (retail: after), lea [ebp+8] vs [ebp-0x10], missing
// mov byte [ebp-4],0 after insert (early __v teardown).
// Callees: lower_bound folds to rowed 0x382A92 (37B exact), pair folds to
// Rva 0x796CB (29B exact), _Vector_base folds to rowed 0x211E58 (29B exact),
// insert is rowed 0x1E9066, _free rowed 0x30830.
// Next: vary the insert statement spelling (named pair result temp,
// scoped __v, temp value_type) to force the -0x10 slot + esp spill + order.
//
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// LocomotorSetType to template-vector map instantiation (AIUpdate parse cluster).

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
		{
			BfmeLocomotorSetMap::value_type __v(__k, __tmp);
			__i = insert(__i, __v);
		}
	}
	return (*__i).second;
}

template class _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > >;
