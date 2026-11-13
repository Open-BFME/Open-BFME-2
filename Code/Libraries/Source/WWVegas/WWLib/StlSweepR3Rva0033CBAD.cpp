// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// SparseMatchFinder weapon-map identity is established by the native chain
// operator[] 0x0033D19B -> map::insert 0x0033CBAD -> hinted tree insertion
// 0x0033C646. Zero Hour SparseMatchFinder.h supplies map<const BITSET,
// const MATCHABLE*, MapHelper>; native 0x002CF86F allocates a 24-byte node
// containing an 8-byte key/pointer value. The old float/int views were wrong.
// BitFlags<17> retains the existing ledger spelling; the native comparator
// independently examines 21 bits. This does not recover the original count.
// Reference: pinned BFME1 92f6bbe8 and its GeneralsMD SparseMatchFinder.h;
// generic insertion comes from this repository's STLport 4.5.3 _tree.c.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
class WeaponTemplateSet;
#include "../../../../GameEngine/Include/Common/BfmeFixedStorage002CF0F0.h"

#include "../../../../GameEngine/Include/Common/BitFlagsTemplate.h"
template <class MatchableType, class FlagSet>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()(const FlagSet &a, const FlagSet &b) const
		{
			for (int i = 0; i < 21; ++i)
			{
				bool aBit = (a.m_flagWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
				bool bBit = (b.m_flagWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
				if (aBit && bBit)
					continue;
				if (!aBit && !bBit)
					continue;
				if (!aBit)
					return true;
				return false;
			}
			return false;
		}
	};
};
typedef BitFlags<17> WeaponFlags17;
typedef _STL::pair<const WeaponFlags17,const WeaponTemplateSet *> WeaponPair17;
typedef SparseMatchFinder<WeaponTemplateSet,WeaponFlags17>::MapHelper WeaponMapHelper17;
typedef _STL::_Rb_tree<const WeaponFlags17,WeaponPair17,_STL::_Select1st<WeaponPair17>,WeaponMapHelper17,_STL::allocator<WeaponPair17> > WeaponTree17;
template <> WeaponTree17::iterator WeaponTree17::insert_unique(WeaponTree17::iterator, const WeaponPair17 &);
typedef _STL::map<const WeaponFlags17,const WeaponTemplateSet *,WeaponMapHelper17,_STL::allocator<WeaponPair17> > WeaponMap17;
template WeaponMap17::iterator WeaponMap17::insert(WeaponMap17::iterator, const WeaponPair17 &);
