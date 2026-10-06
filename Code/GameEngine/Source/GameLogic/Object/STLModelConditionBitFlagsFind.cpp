// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/reference/shims/asciistring_downloadmanager /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ??$_M_find@V?$BitFlags@$0HF@@@@?$_Rb_tree@$$CBV?$BitFlags@$0HF@@@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@UModelConditionInfo@@V?$BitFlags@$0HF@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@1@ABV?$BitFlags@$0HF@@@@Z @0x0033AF03 92B
// Evidence: byte-twin of Weapon _M_find at 0x0033AF5F (STLWeaponTemplateSetBitFlagsHintedInsertUnique.cpp);
// calls rowed ModelCondition MapHelper 0x0033AD13; callers 0x0033B80C and findBestInfo 0x0033D46A.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define BitFlags RealBitFlags   // keep the reference header's template out of the way
#include "PreRTS.h"
#include "Common/AsciiString.h"
#undef BitFlags

struct ModelConditionInfo;

template <int Bits>
class BitFlags
{
public:
	unsigned int m_bits;
};

template <class Set, class Flags>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		__declspec(noinline) bool operator()(const Flags &a, const Flags &b) const
		{
			return a.m_bits < b.m_bits;
		}
	};
};

typedef BitFlags<117> ModelConditionSetFlags;
typedef SparseMatchFinder<ModelConditionInfo, ModelConditionSetFlags>::MapHelper ModelConditionMapHelper;
typedef _STL::pair<const ModelConditionSetFlags, const ModelConditionInfo *> ModelConditionPair;
typedef _STL::_Rb_tree<const ModelConditionSetFlags, ModelConditionPair,
	_STL::_Select1st<ModelConditionPair>, ModelConditionMapHelper,
	_STL::allocator<ModelConditionPair> > ModelConditionTree;

const ModelConditionPair *bfmeFindAnchorModelConditionTree(const ModelConditionTree &tree, const ModelConditionSetFlags &key)
{
	ModelConditionTree::const_iterator it = tree.find(key);
	if (it == tree.end())
		return 0;
	return &(*it);
}
