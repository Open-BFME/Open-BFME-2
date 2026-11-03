// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?_M_insert@?$_Rb_tree@IU?$pair@$$CBIPAVImage@@@_STL@@U?$_Select1st@U?$pair@$$CBIPAVImage@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAVImage@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAVImage@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAVImage@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBIPAVImage@@@2@0@Z
// retail 0x004D9C49 136B. _Rb_tree<unsigned Image*>::_M_insert (hinted insert
// worker). Target uses unsigned jb at +0x20 where the signed int-int twin at
// 0x0038341E uses jl; both call the 24B node factory at 0x00382B7F.
// Evidence: called twice by the 294B insert_unique-hint worker at 0x0020673B
// (via 0x002067A5) and by the 134B insert_unique worker at 0x004D795B
// (via 0x004D79BD); that chain feeds the shared ImageSubscriptMap
// operator[] worker at 0x002077D6 through 0x00358211. ImageNameMap is
// map<unsigned Image*> per Code/GameEngine/Source/GameClient/System/ImageCollectionFindImage.cpp.
// The PAVImage _M_create_node spelling is an ICF twin of the rowed HH node at
// 0x00382B7F (34B exact modulo relocs under bfmealloc NO_EXCEPTIONS); pinned
// in the same landing. _Rebalance resolves through its matched row at
// 0x00025490. Flags copy the signed int-int _M_insert TU
// stlport_map_int_int_os.cpp which gives the same 136B/59-insn shape.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>

// The unsigned compares are inlined (retail compares in place); an
// inline-only specialization keeps them so and emits no less<unsigned>
// copy in a shape retail's 0x00758C50 lacks.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Image;
// _M_insert calls the 34-byte node factory retail folds at 0x00382B7F and
// the map's destructor runs the rowed tree destructor
// (stlport_string_pair_cleanup.cpp); declaring both specializations keeps
// this unit from emitting its own differing copies. The node allocator's
// allocate is declared too: the tree's own constructors call it, and the
// shared copy is the bfmealloc one other units of this map emit.
typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, Image *>, _STL::_Select1st<_STL::pair<const unsigned, Image *> >, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > TreeImage;
namespace _STL {
template <> _Rb_tree_node<pair<const unsigned, Image *> > *TreeImage::_M_create_node(const TreeImage::value_type &);
template <> TreeImage::~_Rb_tree();
template <> _Rb_tree_node<pair<const unsigned, Image *> > *allocator<_Rb_tree_node<pair<const unsigned, Image *> > >::allocate(size_t, const void *) const;

// Use the shared constructor without emitting another differing copy.
typedef _Rb_tree_base<pair<const unsigned, Image *>, allocator<pair<const unsigned, Image *> > > ImageTreeBase;
template <> ImageTreeBase::_Rb_tree_base(const allocator_type &);
}

typedef _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > ImageNameMap;

// Instantiate the recovered insert wrapper, rather than every container member.
// The full map instantiation also emits an unused, competing tree-base ctor.
template ImageNameMap::iterator ImageNameMap::insert(ImageNameMap::iterator, const ImageNameMap::value_type &);

// ImageSubscriptMap shared worker (retail 0x002077D6 69B). Declaration-only
// view over ImageNameMap per ImageCollectionFindImage.cpp; retail folds every
// unsigned-key pointer-map operator[] into this worker which drives the rowed
// PAX lower_bound at 0x4FF3B6 (ICF twin of the PAVImage spelling pinned here)
// and the rowed PAVImage hint insert at 0x00358211.
#include "../../../../GameEngine/Include/GameClient/ImageSubscriptMap.h"

// The rowed operator[] lives in HostValidateColorsRva004422DDFarm.cpp,
// whose inline copy has the identical whole body and relocations. Keeping a
// strong copy here conflicts with that required consumer definition.

// This rowed helper used to be emitted through the subscript definition.
// Keep its independent native body when that definition is rehomed.
template TreeImage::iterator TreeImage::lower_bound(const unsigned int &);
