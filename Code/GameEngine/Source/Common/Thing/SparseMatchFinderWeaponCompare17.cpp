// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
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
typedef SparseMatchFinder<WeaponTemplateSet, WeaponFlags17>::MapHelper WeaponMapHelper17;
template bool WeaponMapHelper17::operator()(const WeaponFlags17 &, const WeaponFlags17 &) const;
