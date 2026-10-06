// cl: /Ireference/shims/bfme2_ascii
// ?rva0033C807@Rva0033C807@@QAE_NABVAsciiString@@AAV2@@Z @0x0033C807 67B:
// vector scan by module tag with out-copy and erase; compares Nugget+4 tag
// via rowed StringBase compare, copies Nugget+0 name via pinned AsciiString
// assign, erases via rowed vector erase with 0x14 stride, returns whether any
// matched. Called 4x from the 0x33C8E8 helper with ThingTemplate +0x2e4 etc
// vectors; ret 8 matches two AsciiString params.

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
};

namespace _STL
{

template <class Type>
class allocator
{
};

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	typedef Type *iterator;
	iterator erase(iterator pos);
};

}

class Rva0033C807
{
public:
	bool rva0033C807(const AsciiString &tag, AsciiString &out);

private:
	ModuleInfo::Nugget *m_start;
	ModuleInfo::Nugget *m_finish;
	ModuleInfo::Nugget *m_end;
};

bool Rva0033C807::rva0033C807(const AsciiString &tag, AsciiString &out)
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
