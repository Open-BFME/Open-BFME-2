// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// ??A?$map@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@UMapHelper@?$SparseMatchFinder@UModelConditionInfo@@V?$BitFlags@$0HF@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0HF@@@PBUModelConditionInfo@@@_STL@@@_STL@@@_STL@@QAEAAPBUModelConditionInfo@@ABV?$BitFlags@$0HF@@@@Z, retail 0x0033d142, 89 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport46
#define _STLP_NO_EXCEPTIONS
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <string.h>
// STLport map instantiation for the ModelCondition SparseMatchFinder.
// Target identity: rowed findBestInfo at 0x0033D46A calls operator[] at
// 0x0033D142; its tree calls the rowed lower_bound at 0x0033B798 and the
// ModelCondition comparator at 0x0033AD13. Native insertion calls establish
// the chain 0x0033CB90 -> 0x0033C485 -> 0x0033C03B / 0x0033BFA6.
// Target layout: four flag words, a pointer at payload +0x10, and a 0x24-byte
// node. Comparator's 104-bit limit is carried from the verified comparator;
// it is not inferred from the donor's nominal BitFlags<117> template count.
// Reference structure: repository STLport map/tree headers and the existing
// ModelCondition lower_bound and compare units. Retail's four-argument tree
// insertion variant is the same one used by W3DModelDrawO1Inlines.cpp.
// Allocation uses the verified byte allocator at 0x000307F0. The native copy
// chain 0x002CF35C -> 0x002CF120 -> 0x002CF108 copies 16 flag bytes and one
// pointer. All three and node creation 0x002CF84D already have neutral ledger
// rows; typed COMDAT copies here do not claim additional byte coverage.
struct ModelConditionInfo;
template <int BitCount>
class BitFlags
{
public:
	unsigned int m_flagWords[(BitCount + 31) / 32];
	// ?BitFlags::BitFlags present-unmatched
	__declspec(noinline) BitFlags(const BitFlags &that) { memcpy(this, &that, sizeof(*this)); }
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline pair<BitFlags<117> const ,ModelConditionInfo const *>::pair(BitFlags<117> const &a,ModelConditionInfo const * const &b) : first(a), second(b) {} }
template <class MatchableType, class FlagSet>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		// ?MapHelper::operator() present-unmatched
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
typedef _STL::pair<const ModelConditionFlags117, const ModelConditionInfo *> ModelConditionPair117;
typedef SparseMatchFinder<ModelConditionInfo, ModelConditionFlags117>::MapHelper ModelConditionMapHelper117;
typedef _STL::_Rb_tree<const ModelConditionFlags117, ModelConditionPair117,
	_STL::_Select1st<ModelConditionPair117>, ModelConditionMapHelper117,
	_STL::allocator<ModelConditionPair117> > ModelConditionTree117;

typedef _STL::map<const ModelConditionFlags117,const ModelConditionInfo *, ModelConditionMapHelper117,_STL::allocator<ModelConditionPair117> > ModelConditionMap117;
typedef _STL::_Rb_tree_node<ModelConditionPair117> ModelConditionNode117;
namespace _STL {
template<> class allocator<char> { public: static char *allocate(unsigned int, const void *); };
template<> class allocator<ModelConditionNode117> {
public:
 typedef ModelConditionNode117 value_type;
 typedef unsigned int size_type;
 typedef ModelConditionNode117 *pointer;
 // ?allocator::allocate present-unmatched
 static pointer allocate(unsigned int n, const void *hint=0) { return reinterpret_cast<pointer>(allocator<char>::allocate(n*sizeof(value_type),hint)); }
 static void deallocate(pointer, unsigned int);
};
}
template const ModelConditionInfo *&ModelConditionMap117::operator[](const ModelConditionFlags117 &);
