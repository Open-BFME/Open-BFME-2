// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// STLport vector<ProductionPrerequisite>::push_back, retail 0x0033EA10.
//
// Retail advances the finish pointer by 0x24, so BFME 2's ProductionPrerequisite
// is 36 bytes: the Zero Hour header (a PrereqUnitRec vector plus a ScienceVec,
// 0x18 together) plus 0x0C unrecovered trailing bytes, most likely a third
// prerequisite list BFME 2 added. The replica below keeps the true size and
// the non-trivial copy semantics the push_back emission needs; it makes no
// claim about the trailing bytes. Copied with the mangled element name so the
// instantiation spells vector<ProductionPrerequisite> exactly.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	ProductionPrerequisite(const ProductionPrerequisite &other);
	~ProductionPrerequisite();
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);

private:
	void *m_unreconstructed[9];
};

typedef char ProductionPrerequisiteSizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

template class _STL::vector<ProductionPrerequisite>;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?dup_002cfbae@@YAXXZ=??$_Destroy@PAVProductionPrerequisite@@@_STL@@YAXPAVProductionPrerequisite@@0@Z")
#pragma comment(linker, "/alternatename:?dup_0033e0b7@@YAXXZ=??$__uninitialized_copy@PAVProductionPrerequisite@@PAV1@@_STL@@YAPAVProductionPrerequisite@@PAV1@00ABU__false_type@0@@Z")
