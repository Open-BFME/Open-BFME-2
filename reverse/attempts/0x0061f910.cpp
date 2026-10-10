// ?subtract@Rva0061F910Set@@QAEAAV1@ABV1@@Z
// partial score=0.894149 date=2026-10-10
// cl: /O2 /G7 /DNDEBUG /MD /G6 /D_STLP_USE_MALLOC /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BFME 2 complete bodies 0x0061F910..0x0061FA91 and 0x0061FAA0..0x0061FC21.
// Native comparisons establish an unsigned four-byte key, 12-byte set at +0,
// an untouched word at +0xC and changed flag +0x10. Source guide: BFME 1
// game/GameEngine/Source/Common/Bfme/Rva009EC5B0Set.cpp and Rva009EC770Set.cpp
// at committed donor 575ba2b04. The original wrapper/key names remain unknown.
// Native vector overflow reaches 0x002DFCF6, iterator increment 0x00024250,
// erase range 0x0061F7B0 and temporary-buffer release 0x00030830. Current
// source is banked: allocator/EH shape and two typed call providers unresolved.

#include <set>
#include <vector>

struct Rva0061F910Key
{
	unsigned int a;
};

inline bool operator<(const Rva0061F910Key &left,
	const Rva0061F910Key &right)
{
	return left.a < right.a;
}

typedef _STL::set<Rva0061F910Key> Rva0061F910Tree;

class Rva0061F910Set
{
public:
	Rva0061F910Set &subtract(const Rva0061F910Set &other);

private:
	Rva0061F910Tree m_set;
	int dword_C;
	bool m_changed;
};

// ?subtract@Rva0061F910Set@@QAEAAV1@ABV1@@Z
Rva0061F910Set &Rva0061F910Set::subtract(const Rva0061F910Set &other)
{
	_STL::vector<unsigned int> found;
	for (Rva0061F910Tree::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (other.m_set.find(*it) != other.m_set.end())
			found.push_back(it->a);
	}
	if (!found.empty())
	{
		for (_STL::vector<unsigned int>::iterator v = found.begin();
			v != found.end(); ++v)
		{
			m_set.erase(reinterpret_cast<const Rva0061F910Key &>(*v));
		}
		m_changed = true;
	}
	return *this;
}
