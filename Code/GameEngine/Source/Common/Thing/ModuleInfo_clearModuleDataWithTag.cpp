// cl: /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
// ?clearModuleDataWithTag@ModuleInfo@@QAE_NABVAsciiString@@AAV2@@Z @0x0033C807 67B:
// vector scan by module tag with out-copy and erase; compares Nugget+4 tag
// via rowed StringBase compare, copies Nugget+0 name via pinned AsciiString
// assign, erases via rowed vector erase with 0x14 stride, returns whether any
// matched. Called 4x from the 0x33C8E8 helper with ThingTemplate +0x2e4 etc
// vectors; ret 8 matches two AsciiString params.

#include <vector>
#include "ascii_string.h"


#include "../../../Include/Common/ModuleData.h"

#include "../../../Include/Common/ModuleInfoClass.h"

namespace _STL
{

// Bind vector<ModuleInfo::Nugget>::erase to the rowed worker at 0x0033C3BC.
// Declaration only: the definition lives in the row owner.
template <class Type, class Allocator> class vector;
template <> class vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >
{
public:
	typedef ModuleInfo::Nugget *iterator;
	iterator erase(iterator pos);
};

}

bool ModuleInfo::clearModuleDataWithTag(const AsciiString &tag, AsciiString &out)
{
	bool found = false;
	for (ModuleInfo::Nugget *it = m_begin; it != m_end;)
	{
		if (it->m_moduleTag.compare(tag) == 0)
		{
			out = it->first;
			it = reinterpret_cast<_STL::vector<ModuleInfo::Nugget> *>(this)->erase(it);
			found = true;
		}
		else
		{
			++it;
		}
	}
	return found;
}
