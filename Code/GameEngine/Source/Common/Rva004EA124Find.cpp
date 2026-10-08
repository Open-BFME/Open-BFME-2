#include "../GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"
// cl: /MD
// ?Rva004EA124Find@@YAPAXPAX@Z, retail 0x004EA124, 37 bytes.
// Free-function linear search over pointer table AIEconomyBuilder::m_farmList:
// each entry points at an object whose dword at +0x70 is compared to the key.
// Evidence: begin/end globals as immediates, +0x70 deref chain, caller at 0x004EAA2A.


void *__cdecl Rva004EA124Find(void *key)
{
	void **end = (void **)AIEconomyBuilder::m_farmList.finish;
	void **p = (void **)AIEconomyBuilder::m_farmList.first;
	while (p != end)
	{
		void *obj = *p;
		if (*(void **)((char *)obj + 0x70) == key)
			return *p;
		++p;
	}
	return 0;
}
