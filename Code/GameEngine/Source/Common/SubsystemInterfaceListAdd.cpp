// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001B5018@SubsystemInterfaceList@@QAEXPAVSubsystemInterface@@@Z, retail 0x001B5018 (71 bytes, ret 4).
// Same list as the rowed rva001B4FE9 (SubsystemInterfaceListRva001B4FE9.cpp): register a subsystem once. A
// null one is ignored, one already in the 8-byte records at +0x00 is ignored, and otherwise it is appended
// to the pointer list at +0x0C unless that already holds it (the search is the folded 4-byte find, rowed
// under its int spelling at 0x0020E873). Zero Hour has no equivalent; the method keeps its address token.
// vector<>::_M_insert_overflow inlines max(size(), n). Retail never calls
// _STL::max<unsigned> (0x00013740 has no call site), but cl 13.10 still emits
// the template's COMDAT, and under /O1 /G7 it is not retail's blend body. A
// file-static unsigned overload takes the call instead: no external max copy
// (the SubsystemInterface.cpp recipe).
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class SubsystemInterface;
class ModuleData;

#include "../../Include/Common/SubsystemInterfaceList.h"

void SubsystemInterfaceList::rva001B5018(SubsystemInterface *subsystem)
{
	if (subsystem == 0)
		return;
	for (_STL::vector<_STL::pair<SubsystemInterface *, void *> >::iterator it = m_subsystems.begin(); it != m_subsystems.end(); ++it) {
		if (it->first == subsystem)
			return;
	}
	const ModuleData *&item = (const ModuleData *&)subsystem;
	const ModuleData **last = (const ModuleData **)m_allSubsystems.end();
	if ((const ModuleData **)_STL::find((int *)m_allSubsystems.begin(), (int *)last, (const int &)item) == last)
		reinterpret_cast<_STL::vector<const ModuleData *> &>(m_allSubsystems).push_back(item);
}
