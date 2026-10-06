// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _STLP_NO_EXCEPTIONS
#include <map>
class WeaponTemplateSet;
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
typedef BitFlags<17> WeaponFlags17;
typedef _STL::pair<const WeaponFlags17, const WeaponTemplateSet *> WeaponPair17;
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags17>::MapHelper WeaponMapHelper17;
typedef _STL::_Rb_tree<const WeaponFlags17, WeaponPair17,
	_STL::_Select1st<WeaponPair17>, WeaponMapHelper17,
	_STL::allocator<WeaponPair17> > WeaponTree17;
WeaponTree17::const_iterator findLowerBoundForWeaponKey(const WeaponTree17 &tree, const WeaponFlags17 &key)
{
	return tree.lower_bound(key);
}
