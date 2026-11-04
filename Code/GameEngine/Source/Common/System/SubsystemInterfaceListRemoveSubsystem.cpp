// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// SubsystemInterfaceList::removeSubsystem, retail 0x001B4E82 (41 bytes,
// RET4), guided by Zero Hour's GameEngine/Source/Common/System/
// SubsystemInterface.cpp (GeneralsMD tree vendored under reference/
// open-bfme-1/inputs/reference). ZH compiles the loop only under
// DUMP_PERF_STATS; BFME 2's body is an unconditional find-and-erase of the
// given subsystem in the second subsystem vector (ZH m_allSubsystems, +0x0C;
// m_subsystems at +0x00 as in ZH's header).
//
// Target evidence: both callers (0x0020DF3B, 0x0031DF18) load the list
// singleton 0x00DFD940, test it and pass their own this -- ZH's
// ~SubsystemInterface `if (TheSubsystemList) TheSubsystemList->
// removeSubsystem(this)`. The body sits beside the matched
// SubsystemInterfaceList::postProcessLoadAll (0x001B4E49) and calls the
// rowed pointer find 0x0020E873 and pointer-vector erase 0x001FF51F. Same
// instruction skeleton as the matched Rva004DFB55 (find + erase at +0x2C).
// This TU also carries ICF alias rows for the SubsystemInterface** find
// (0x0020E873) and __find (0x005250A5) instantiations it emits.
#include <vector>
#include <algorithm>
// bfme link decl-only begin
namespace _STL { template <> void * * __copy_ptrs<void * *,void * *>(void * *,void * *,void * *,_STL::__true_type); }
namespace _STL { template <> void * * vector<void *,_STL::allocator<void *> >::erase(void * *); }
// bfme link decl-only end
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

#include "../../../Include/Common/SubsystemInterfaceList.h"

void SubsystemInterfaceList::removeSubsystem(SubsystemInterface *sys)
{
	_STL::vector<SubsystemInterface *>::iterator it =
		_STL::find(m_allSubsystems.begin(), m_allSubsystems.end(), sys);
	if (it != m_allSubsystems.end()) {
		((_STL::vector<void *> *)&m_allSubsystems)->erase((void **)it);
	}
}
