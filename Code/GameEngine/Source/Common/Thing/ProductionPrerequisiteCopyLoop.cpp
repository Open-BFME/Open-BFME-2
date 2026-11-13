// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PAVProductionPrerequisite@@PAV1@H@_STL@@YAPAVProductionPrerequisite@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x0033E9DE 50B: STLport random-access __copy (formerly spelled Rva0033E9DECopy), copy loop over ProductionPrerequisite via rowed rva assign 0x002D0C44. Evidence: caller 0x002D0F36 pushes tag plus 0 plus 3 pointers; stride 0x24 per copy ctor 0x002D08DA; twin of dup 0x0042830D which is ZH 0x18 stride.
#include <vector>

#include "ascii_string.h"

struct BfmeStringRecord002CF5B1
{
	unsigned int word0;
	unsigned int word1;
	AsciiString text;
	BfmeStringRecord002CF5B1();
	BfmeStringRecord002CF5B1(const BfmeStringRecord002CF5B1 &other);
	~BfmeStringRecord002CF5B1();
};

class UpgradeTemplate;

class ProductionPrerequisite
{
public:
	ProductionPrerequisite &rva002D0C44(const ProductionPrerequisite &other);
private:
	_STL::vector<BfmeStringRecord002CF5B1> m_vec0;
	_STL::vector<int> m_vecC;
	_STL::vector<const UpgradeTemplate *> m_prereqUpgrades;
};

// Spelled as the STLport instantiation the caller 0x002D0F36 names (tag and
// null distance are pushed but unused), so the link resolves that call here.
namespace _STL {
template <>
ProductionPrerequisite *__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>(ProductionPrerequisite *first, ProductionPrerequisite *last, ProductionPrerequisite *result, const random_access_iterator_tag &, int *)
{
	for (int n = last - first; n > 0; --n, ++first, ++result)
		result->rva002D0C44(*first);
	return result;
}
}
