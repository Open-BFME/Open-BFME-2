// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _STLP_NO_EXCEPTIONS
#include <map>
// ?_M_lower_bound ModelCondition 117 @0x0033B798 56B
// Evidence: byte-twin of Weapon _M_lower_bound at 0x0033B7D0 (SparseMatchFinderWeaponLowerBound17.cpp);
// calls rowed ModelCondition MapHelper 0x0033AD13; caller is map::operator[] 0x0033D142.
struct ModelConditionInfo;
template <int BitCount>
class BitFlags
{
public:
	unsigned int m_flagWords[(BitCount + 31) / 32];
};
template <class MatchableType, class FlagSet>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()(const FlagSet &a, const FlagSet &b) const;
	};
};
typedef BitFlags<117> ModelConditionFlags117;
typedef _STL::pair<const ModelConditionFlags117, const ModelConditionInfo *> ModelConditionPair117;
typedef SparseMatchFinder<ModelConditionInfo, ModelConditionFlags117>::MapHelper ModelConditionMapHelper117;
typedef _STL::_Rb_tree<const ModelConditionFlags117, ModelConditionPair117,
	_STL::_Select1st<ModelConditionPair117>, ModelConditionMapHelper117,
	_STL::allocator<ModelConditionPair117> > ModelConditionTree117;
ModelConditionTree117::const_iterator findLowerBoundForModelConditionKey(const ModelConditionTree117 &tree, const ModelConditionFlags117 &key)
{
	return tree.lower_bound(key);
}
