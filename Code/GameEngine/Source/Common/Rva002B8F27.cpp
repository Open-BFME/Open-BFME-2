// cl: /O1 /arch:SSE /G7 /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Address-derived method at 0x002B8F27, boundary and size from Ghidra. The
// target walks the vector header at this+8 and appends qualifying objects to
// the caller's vector<const ModuleData*>. The ModuleData base relation is
// inferred from that append; the +0x54 field and calls are direct target facts.
#include <vector>

class ModuleData
{
public:
	virtual void unused() = 0;
};
class Rva003195C9Owner : public ModuleData
{
public:
	void rva00319831(void *arg);
	unsigned char pred();
};
class Mbr002E0B30 : public Rva003195C9Owner
{
public:
	unsigned char pred();
	char m_pad[0x50];
	int m_54;
};
class Rva002B2B66
{
public:
	int rva002B2B66();
};
extern Rva002B2B66 *TheLivingWorldLogic;

class Rva002B8F27
{
public:
	void rva002B8F27(_STL::vector<const ModuleData *> *out);
private:
	char m_pad[8];
	_STL::vector<Mbr002E0B30 *> m_entries;
};

void Rva002B8F27::rva002B8F27(_STL::vector<const ModuleData *> *out)
{
	for (unsigned i = 0; i < m_entries.size(); ++i)
	{
		Mbr002E0B30 *entry = m_entries[i];
		const ModuleData *module = entry;
		if (entry->pred())
		{
			entry->rva00319831(0);
			if (entry->m_54 == TheLivingWorldLogic->rva002B2B66())
				out->push_back(module);
		}
	}
}
