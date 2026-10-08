// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?rva002E0A9F@Rva002E0A9FElem@@QAEHPAX@Z, retail 0x002E0A9F, 75B.
// The name is the pin LivingWorldLogicRva002B488E.cpp already calls.
// Target evidence: walks the pointer vector at this+0x1B8/+0x1BC (size
// recomputed each pass) and returns the first entry whose dword at +0x20
// equals the key, else 0. The WorldBuilder twin (0xDE4350) reads +0x20
// through a getter the WB symbols name LivingWorldArmy::GetID, so the
// entries look like armies keyed by ID; that name is WB evidence only and
// the owner class is a placeholder.
#include <vector>

struct Rva002E0A9FEntry
{
	unsigned char m_pad0[0x20];
	int m_id;	// +0x20
};

class Rva002E0A9FElem
{
public:
	int rva002E0A9F(void *key);

private:
	unsigned char m_pad0[0x1B8];
	std::vector<Rva002E0A9FEntry *> m_entries;	// +0x1B8
};

int Rva002E0A9FElem::rva002E0A9F(void *key)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		if (m_entries[i]->m_id == (int)key)
			return (int)m_entries[i];
	}
	return 0;
}
