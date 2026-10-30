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


class ModuleData
{
};

class ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString m_first;
		AsciiString m_tag;
		const ModuleData *m_data;
		int m_interfaceMask;
		unsigned char m_a;
		unsigned char m_b;
		unsigned char m_c;
		unsigned char m_pad;
	};
	bool clearModuleDataWithTag(const AsciiString &tag, AsciiString &out);

private:
	Nugget *m_start;
	Nugget *m_finish;
	Nugget *m_end;
};

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
	for (ModuleInfo::Nugget *it = m_start; it != m_finish;)
	{
		if (it->m_tag.compare(tag) == 0)
		{
			out = it->m_first;
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
