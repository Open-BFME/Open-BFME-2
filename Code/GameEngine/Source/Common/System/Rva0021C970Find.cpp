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
	const AsciiString *rva0021C9D7(int key, unsigned int index);
};

void * g_00DFE354;	// retail RVA 0x009FE354 (.data, 4 bytes), defined here: nothing else owns it

const AsciiString *CreateAHeroManager::CreateAHeroSubClass::rva0021C970(int key, unsigned int index)
{
	if (!rva0021BC0D(key, (void **)&g_00DFE354))
		return &AsciiString::TheEmptyString;
	void *bling = GetBling(key, index);
	if (bling)
		return (const AsciiString *)((const char *)bling + 4);
	return &AsciiString::TheEmptyString;
}
void *CreateAHeroManager::CreateAHeroSubClass::rva0021C9A6(int key, unsigned int index)
{
	if (!rva0021BC0D(key, (void **)&g_00DFE354))
		return (void *)&AsciiString::TheEmptyString;
	void *bling = GetBling(key, index);
	if (bling)
		return bling;
	return (void *)&AsciiString::TheEmptyString;
}
// rva0021C9D7 0x0021C9D7 54B: the same lookup answering the bling's +8 name.
const AsciiString *CreateAHeroManager::CreateAHeroSubClass::rva0021C9D7(int key, unsigned int index)
{
	if (!rva0021BC0D(key, (void **)&g_00DFE354))
		return &AsciiString::TheEmptyString;
	void *bling = GetBling(key, index);
	if (bling)
		return (const AsciiString *)((const char *)bling + 8);
	return &AsciiString::TheEmptyString;
}
