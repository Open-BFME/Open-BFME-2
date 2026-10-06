// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??RMapHelper@?$SparseMatchFinder@UModelConditionInfo@@V?$BitFlags@$0HF@@@@@QBE_NABV?$BitFlags@$0HF@@@0@Z @0x0033AD13 73B
// Evidence: byte-twin of Weapon MapHelper at 0x0033AD5C (SparseMatchFinderWeaponCompare17.cpp loop 21);
// retail loops 0x68=104; callers are ModelCondition $0HF tree ops 0x0033AF03 0x0033B798 0x0033D142 0x0033BFA6 0x0033C03B 0x0033C485.
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
		bool operator()(const FlagSet &a, const FlagSet &b) const
		{
			for (int i = 0; i < 104; ++i)
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
typedef BitFlags<117> ModelConditionFlags117;
typedef SparseMatchFinder<ModelConditionInfo, ModelConditionFlags117>::MapHelper ModelConditionMapHelper117;
template bool ModelConditionMapHelper117::operator()(const ModelConditionFlags117 &, const ModelConditionFlags117 &) const;
