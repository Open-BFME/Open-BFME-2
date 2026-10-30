// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?PushDynamicSetStack@FXShaderParameterBinder@@QAEXW4ScienceType@@@Z, retail 0x0015354E 23B.
// Null-checked Science push: if the +0x10 store exists, push the ScienceType
// arg into its vector at +4 via the rowed ThingTemplate push_back 0x002E01C6.
// Evidence: five callers in 0x0014FFF6 pass constant 1 with this from
// [ebp+0x10]; callee is vector<ScienceType>::push_back; stride and shape
// match the ProductionPrerequisite Science pattern; owner unproven so the
// name keeps the address token.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

#include <vector>
#include "../../../Include/Lib/BfmeE16.h"

// Bind the append to the rowed vector<ScienceType>::push_back 0x002E01C6
// instead of emitting this unit's own copy of the header's inline path.
namespace _STL
{
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
}

struct Rva0015354EStore
{
	unsigned char m_pad00[4];
	_STL::vector<ScienceType> m_sciences04; // +4
};

struct Rva001531E6Target;

class FXShaderParameterBinder
{
public:
    void PopDynamicSetStack();
    void PushDynamicSetStack(const char *name);
    void PushDynamicSetStack(ScienceType value);
    FXShaderParameterBinder(void *surface);
    void Init(struct ID3DXEffect *surface);
    void *m_ptr;
    _STL::vector<BfmeE16> m_vec;
    Rva001531E6Target *m_ParsingData;
};

void FXShaderParameterBinder::PushDynamicSetStack(ScienceType value)
{
	Rva0015354EStore *store = (Rva0015354EStore *)m_ParsingData;
	if (store == 0)
		return;
	store->m_sciences04.push_back(value);
}
