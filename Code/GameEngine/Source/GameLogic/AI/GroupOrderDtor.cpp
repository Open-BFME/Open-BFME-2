// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/moduledata
// stlport
// ??1GroupOrder@@UAE@XZ at retail 0x00548948 (60B). Base lineage
// proven by the two vtable installs (own 0xC6A520 then Snapshot 0xBBB554) and
// by ten callers including three tail-jmp derived dtors in
// GroupOrderDerivedDtors.cpp. (Formerly rowed
// as SpecialPowerModuleData; its only users are the six group orders.) retail frees
// the +4 vector buffer via _free at 0x30830. Member layout follows the
// matched copy ctor (vector<ScienceType> at +4). /EHs (not /EHsc) forces the
// single-state EH frame around the lone free; /EHsc stays frameless.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};


// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<::ScienceType >::deallocate(::ScienceType *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

#include "Common/Snapshot.h"

class GroupOrder : public Snapshot
{
public:
	virtual ~GroupOrder();

private:
	_STL::vector<ScienceType> m_sciences; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

inline GroupOrder::~GroupOrder()
{
}

// This destructor is a header inline in the copier units; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeGroupOrderDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeGroupOrderDtorInlineAnchor()
{
	static_cast<GroupOrder *>(0)->GroupOrder::~GroupOrder();
}
#pragma inline_depth()
