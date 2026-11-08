// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc_alloconly
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/MapCache_ctor_Thunk.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// MapCache::MapCache 0x0022E28B (61B). Callee addresses are read off retail's
// call sites (reverse/symbols.csv). Only the placed bodies are carried; the
// donor's other definitions are omitted.
// Open-BFME5: clean C++ lift of the retail MapCache constructor.

#include <map>
#include <set>

#include "ascii_string.h"

// __node_alloc<1,0>::allocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}

// __node_alloc<1,0>::deallocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString,_STL::pair<AsciiString const,bool>,_STL::_Select1st<_STL::pair<AsciiString const,bool> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,bool> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<AsciiString const,bool>,_STL::allocator<_STL::pair<AsciiString const,bool> > >::~_Rb_tree_base(); }
namespace _STL { template <> void _Rb_tree<AsciiString,_STL::pair<AsciiString const,bool>,_STL::_Select1st<_STL::pair<AsciiString const,bool> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,bool> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > *); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > *,_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<AsciiString const,bool> > *,unsigned int) const; }
// bfme link decl-only end

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

#include "unicode_string.h"
#include "../../Include/GameClient/MapMetaData.h"

// Declaration-only: the map<AsciiString, MapMetaData> tree teardown is
// emitted by the cache units that own it; this TU only references it.
namespace _STL {
typedef pair<const AsciiString, MapMetaData> MapCacheValue;
typedef _Rb_tree<AsciiString, MapCacheValue, _Select1st<MapCacheValue>, less<AsciiString>, allocator<MapCacheValue> > MapCacheTree;
template <> _Rb_tree_base<MapCacheValue, allocator<MapCacheValue> >::~_Rb_tree_base();
template <> void MapCacheTree::_M_erase(_Rb_tree_node<MapCacheValue> *);
}

#include "../../Include/GameClient/MapCache.h"

MapCache::MapCache()
{
}
