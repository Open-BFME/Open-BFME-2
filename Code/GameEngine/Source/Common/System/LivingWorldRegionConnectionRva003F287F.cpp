// cl: /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F287F@Rva003F287F@@QAEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x003F287F 92B.
// Filters the vector at this+0x170: pushes entry+0x20 (ModuleData const *) into out when nonzero and byte at entry+0x34 is zero.
// Evidence: callees rowed push_back 0x004DFCB0; callers 0x002B7717 0x004EEFBD 0x005037B1; neighbours LivingWorldRegionConnection dtor/construct give TU and flags.
// ?rva003F28DB@Rva003F287F@@QAEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x003F28DB 103B.
// Same filter plus rowed const getter 0x004E0632 on entry+0x20; callers 0x002B6E17 0x002B6ECA 0x002E2DB6.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

#include "../../../Include/GameLogic/Rva004E0632.h"

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

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ModuleData const * * _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void Rva003F287F::rva003F287F(_STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *connectionEntry = m_items[i];
		if (connectionEntry->m_data != 0 && connectionEntry->m_flag == 0) {
			const ModuleData *moduleData = connectionEntry->m_data;
			out.push_back(moduleData);
		}
	}
}

void Rva003F287F::rva003F2818(int filter, _STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *connectionEntry = m_items[i];
		if (connectionEntry->m_data != 0 && connectionEntry->m_flag == 0) {
			const ModuleData *moduleData = connectionEntry->m_data;
			if (moduleData->m_keyPtr->m_key == filter) {
				out.push_back(moduleData);
			}
		}
	}
}

void Rva003F287F::rva003F28DB(_STL::vector<const ModuleData *> &out)
{
	for (unsigned i = 0; i < m_items.size(); ++i) {
		Rva003F287FEntry *connectionEntry = m_items[i];
		if (connectionEntry->m_data != 0 && connectionEntry->m_flag == 0) {
			const ModuleData *moduleData = connectionEntry->m_data;
			if (((const Rva004E0632 *)moduleData)->rva004E0632() != 0) {
				out.push_back(moduleData);
			}
		}
	}
}
