// cl: -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /D_STLP_USE_MALLOC
// Retail asset-list insertion at RVA 0x0006C950.
// The registry lookup and set insertion use their existing rowed providers.

// cl: /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_create_node(Rva001408C0Target *const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }


struct Rva001408C0Target;
void *bfmeGoEMEb(void *name);

struct AssetList00208F90
{
public:
	AssetList00208F90 &operator=(const AssetList00208F90 &other)
	{
		m_prototypes = other.m_prototypes;
		m_treeLayoutPad = other.m_treeLayoutPad;
		m_changed = other.m_changed;
		return *this;
	}
	// ??6AssetList00208F90@@QAEAAU0@ABVAsciiString@@@Z
	AssetList00208F90 &operator <<(const AsciiString &name);
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	_STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > m_prototypes; // +0x00
	unsigned int m_treeLayoutPad; // +0x0C
	bool m_changed; // +0x10
	char m_pad11[0x3];
};


AssetList00208F90 &AssetList00208F90::operator <<(const AsciiString &name)
{
	if (m_prototypes.insert(
		static_cast<Rva001408C0Target *>(bfmeGoEMEb((void *)name.str()))).second)
	{
		m_changed = true;
	}
	return *this;
}
