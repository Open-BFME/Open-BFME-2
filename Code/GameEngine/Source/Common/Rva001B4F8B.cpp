// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva001B4F8B@Rva001B4F8B@@QAEPAXABV?$StringBase@D@@@Z RVA 0x001B4F8B 45B
// Evidence: unlock lane; 8-byte-entry scan of [this+0, this+4) comparing the
//   StringBase<char> at object+8 via rowed 0x000069D6 compare, returns object or 0;
//   callers 0x0002D025 in 0x0002CF86; neighbours GameEngineDeletingBaseDtor /O1 /MD.
#include "ascii_string.h"

struct Rva001B4F8BEntry
{
	void *m_obj; // +0 dereferenced, StringBase at object+8
	int m_pad; // +4 keeps 8-byte stride
};

class Rva001B4F8B
{
public:
	void *rva001B4F8B(const StringBase<char> &name);

private:
	Rva001B4F8BEntry *m_begin; // +0
	Rva001B4F8BEntry *m_end; // +4
};

void *Rva001B4F8B::rva001B4F8B(const StringBase<char> &name)
{
	for (Rva001B4F8BEntry *p = m_begin; p != m_end; ++p) {
		StringBase<char> *sb = (StringBase<char> *)((char *)p->m_obj + 8);
		if (sb->compare(name) == 0)
			return p->m_obj;
	}
	return 0;
}
