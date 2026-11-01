// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
// stlport
// ?rva0035B750@Rva0035B750@@QAEXPBVModuleData@@@Z retail 0x0035B750 45B
// Empty-or-first setter over ModuleData vector at +0xec storing to +0xfc.
// Evidence: unlock lane, callers 0x0031BE58 0x0053D355, rowed push_back 0x004DFCB0.
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

#include "ascii_string.h"

#include "../../Include/Common/ModuleData.h"

class Rva0035B750
{
public:
	void rva0035B750(const ModuleData *arg);

private:
	char m_pad[0xec];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec;
	char m_pad2[0x4];
	int m_selected;
};

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void Rva0035B750::rva0035B750(const ModuleData *moduleData)
{
	if (m_vec.empty()) {
		m_selected = 0;
		m_vec.push_back(moduleData);
	} else {
		m_vec[0] = moduleData;
	}
}
