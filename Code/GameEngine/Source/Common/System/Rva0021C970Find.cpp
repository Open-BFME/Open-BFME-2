// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// CreateAHeroManager::CreateAHeroSubClass::rva0021C970 0x0021C970 54B (unnamed in WB)
// Evidence: unlock lane; callees rva0021BC0D rowed rva0021BCA7 rowed; callers 0x21CB06; returns AsciiString at +4 or TheEmptyString; global g_00DFE354 out; this has map at +0x24 like Rva0021BCA7.
#include "ascii_string.h"

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass;
};

class CreateAHeroManager::CreateAHeroSubClass
{
public:
	unsigned char rva0021BC0D(int key, void **out);
	void *GetBling(int key, unsigned int index);
	const AsciiString *rva0021C970(int key, unsigned int index);
	void *rva0021C9A6(int key, unsigned int index);
};

extern void *g_00DFE354;

const AsciiString *CreateAHeroManager::CreateAHeroSubClass::rva0021C970(int key, unsigned int index)
{
	if (!rva0021BC0D(key, (void **)&g_00DFE354))
		return &AsciiString::TheEmptyString;
	void *p = GetBling(key, index);
	if (p)
		return (const AsciiString *)((const char *)p + 4);
	return &AsciiString::TheEmptyString;
}
void *CreateAHeroManager::CreateAHeroSubClass::rva0021C9A6(int key, unsigned int index)
{
	if (!rva0021BC0D(key, (void **)&g_00DFE354))
		return (void *)&AsciiString::TheEmptyString;
	void *p = GetBling(key, index);
	if (p)
		return p;
	return (void *)&AsciiString::TheEmptyString;
}
