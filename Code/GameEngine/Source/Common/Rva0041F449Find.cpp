// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0041F449@Rva0041F449@@QAEPAV?$StringBase@D@@ABV2@@Z @0x0041F449 43B.
// Linear search over StringBase pointer range [+4,+8) via rowed compare
// 0x000069D6; returns matching element or 0. Evidence: caller at 0x005DA6BB
// passes Player+0x160 range plus field+0x64 key; layout begin+4 end+8.
#include "ascii_string.h"

class Rva0041F449
{
public:
	StringBase<char> *rva0041F449(const StringBase<char> &key);
private:
	void *m_00;
	StringBase<char> **m_begin;
	StringBase<char> **m_end;
};

StringBase<char> *Rva0041F449::rva0041F449(const StringBase<char> &key)
{
	StringBase<char> **begin = m_begin;
	StringBase<char> **end = m_end;
	for (StringBase<char> **it = begin; it != end; ++it)
	{
		if ((*it)->compare(key) == 0)
			return *it;
	}
	return 0;
}
