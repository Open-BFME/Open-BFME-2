// cl: /O1 /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F287F@Rva003F287F@@QAEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x003F287F 92B.
// Filters the vector at this+0x170: pushes entry+0x20 (ModuleData const *) into out when nonzero and byte at entry+0x34 is zero.
// Evidence: callees rowed push_back 0x004DFCB0; callers 0x002B7717 0x004EEFBD 0x005037B1; neighbours LivingWorldRegionConnection dtor/construct give TU and flags.
// ?rva003F28DB@Rva003F287F@@QAEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x003F28DB 103B.
// Same filter plus rowed const getter 0x004E0632 on entry+0x20; callers 0x002B6E17 0x002B6ECA 0x002E2DB6.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData
{
public:
	char _pad[0x28];
	struct Key
	{
		char _pad[0x2c];
		int m_key; // +0x2c
	} *m_keyPtr; // +0x28
};

class Rva004E0632
{
public:
	int rva004E0632() const; // rowed 0x004E0632, declared only
};

struct Rva003F287FEntry
{
	char _pad0[0x20];
	const ModuleData * volatile m_data; // +0x20 reloads for cmp then mov per shape lever 66
	char _pad1[0x34 - 0x24];
	unsigned char m_flag; // +0x34
};

class Rva003F287F
{
public:
	void rva003F287F(_STL::vector<const ModuleData *> &out);
	void rva003F2818(int filter, _STL::vector<const ModuleData *> &out);
	void rva003F28DB(_STL::vector<const ModuleData *> &out);

private:
	unsigned char m_pad[0x170];
	_STL::vector<Rva003F287FEntry *> m_items; // +0x170
};

void Rva003F287F::rva003F287F(_STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *e = m_items[i];
		if (e->m_data != 0 && e->m_flag == 0) {
			const ModuleData *tmp = e->m_data;
			out.push_back(tmp);
		}
	}
}

void Rva003F287F::rva003F2818(int filter, _STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *e = m_items[i];
		if (e->m_data != 0 && e->m_flag == 0) {
			const ModuleData *tmp = e->m_data;
			if (tmp->m_keyPtr->m_key == filter) {
				out.push_back(tmp);
			}
		}
	}
}

void Rva003F287F::rva003F28DB(_STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *e = m_items[i];
		if (e->m_data != 0 && e->m_flag == 0) {
			const ModuleData *tmp = e->m_data;
			if (((const Rva004E0632 *)tmp)->rva004E0632() != 0) {
				out.push_back(tmp);
			}
		}
	}
}
