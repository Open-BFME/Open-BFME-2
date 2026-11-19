// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oy-
// stlport
//
// ?insert@?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001408C0Target@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@PAURva001408C0Target@@U?$_Const_traits@PAURva001408C0Target@@@_STL@@@_STL@@_N@2@ABQAURva001408C0Target@@@Z, retail 0x00080691, 35 bytes.
// STLport 4.5.3 set<Rva001408C0Target*> insert wrapper: hidden-result copy of
// tree insert_unique at pinned 0x00422047. Called from 12 sites including
// 0x004ABEAE (LargeGroupAudio path). Flags from stlport_vector_s_o1.cpp.
#include <set>
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_create_node(Rva001408C0Target *const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }
struct Rva001408C0Target { int x; };
// Bind the shared rowed insert_unique; instantiate the separately rowed
// node insertion below without its per-flag search and iterator copies.
namespace _STL {
typedef _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> > PtrTree001408C0;
template <> pair<PtrTree001408C0::iterator, bool> PtrTree001408C0::insert_unique(Rva001408C0Target *const &);
template PtrTree001408C0::iterator PtrTree001408C0::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, Rva001408C0Target *const &, _Rb_tree_node_base *);
}

typedef _STL::set<Rva001408C0Target*, _STL::less<Rva001408C0Target*>, _STL::allocator<Rva001408C0Target*> > PtrSet001408C0;
template _STL::pair<PtrSet001408C0::iterator, bool> PtrSet001408C0::insert(Rva001408C0Target* const &);
