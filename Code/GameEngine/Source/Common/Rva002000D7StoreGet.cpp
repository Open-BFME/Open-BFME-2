// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?get@Rva002000D7Store@@QAEPAURva002000D7Config@@H@Z retail 0x002000D7, 52 B
// (the pin name its callers use). Shape: Zero Hour's
// RankInfoStore::getRankInfo -- a 1-based level checked against the pointer
// vector at +0x0C (signed compare), then the entry's final override, the
// first step of Overridable::getFinalOverride inline and the recursion out
// of line (0x001E35DF). Closed from the 0.95 bank with the real STLport
// vector (end minus begin) and the inline first override step.
#include <vector>

// The ledger rows 0x001E35DF (Zero Hour's recursive
// Overridable::getFinalOverride) under this TU-scoped view's spelling.
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride() const;	// 0x001E35DF
	const Rva001E35DFView *finalOverride() const
	{
		if (m_next)
			return m_next->getFinalOverride();
		return this;
	}

private:
	void *m_vtbl;
	Rva001E35DFView *m_next;		// +0x04
};

struct Rva002000D7Config : public Rva001E35DFView
{
};

class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int level);

private:
	char m_pad00[0x0C];
	std::vector<Rva002000D7Config *> m_infos;	// +0x0C
};

Rva002000D7Config *Rva002000D7Store::get(int level)
{
	if (level >= 1 && level <= (int)m_infos.size())
	{
		Rva002000D7Config *info = m_infos[level - 1];
		if (info)
			return (Rva002000D7Config *)info->finalOverride();
	}
	return 0;
}
