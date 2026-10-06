// cl: /MD /Ireference/shims/bfme2_ascii
// ?Rva00421263Find@@YGPBVModuleData@@PBURva00421263Vec@@ABV?$StringBase@D@@@Z @0x00421263 47B
// Linear search of vector<ModuleData*> for name match via rowed StringBase<char>::compare 0x000069D6.
// Evidence: unlock lane; __stdcall ret 8 with vec begin at [vec] end at [vec+4]; each element +0x10 compare; callers 0x004214C3/0x00421572 pass vec at this+0xc and ModuleData+0x10 key; neighbours share /O1.
#include "ascii_string.h"

class ModuleData
{
public:
	char m_pad[16];
	StringBase<char> m_name;
};

struct Rva00421263Vec
{
	const ModuleData **m_begin;
	const ModuleData **m_end;
};

const ModuleData *__stdcall Rva00421263Find(const Rva00421263Vec *vec, const StringBase<char> &key)
{
	for (const ModuleData **it = vec->m_begin; it != vec->m_end; ++it) {
		if ((*it)->m_name.compare(key) == 0)
			return *it;
	}
	return 0;
}
