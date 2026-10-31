// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include <map>
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#define private public
#include "window_video_manager.h"
#undef private
#include "game_window.h"
#include "video_player.h"
// bfme link decl-only begin
namespace _STL { template <> _STL::_Hashtable_node<_STL::pair<GameWindow const * const,WindowVideo *> > * _Hashtable_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::_M_skip_to_next(); }
namespace _STL { template <> _STL::_Ht_iterator<_STL::pair<GameWindow const * const,WindowVideo *>,_STL::_Nonconst_traits<_STL::pair<GameWindow const * const,WindowVideo *> >,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > > hashtable<_STL::pair<GameWindow const * const,WindowVideo *>,GameWindow const *,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<GameWindow const * const,WindowVideo *> >,_STL::equal_to<GameWindow const *>,_STL::allocator<_STL::pair<GameWindow const * const,WindowVideo *> > >::begin(); }
// bfme link decl-only end

// Native [2BF77B,2BF7AC): table at98, mapped receiver at node8,
// virtual slot1C with no arguments. Only the 32-bit key/pointer container
// ABI is borrowed from WindowVideoMap; application types remain unknown.
class Rva002BF77BTarget {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6)
#undef V
 virtual void dispatch();
};
class Rva002BF77B {public:void rva002BF77B();private:char prefix[0x98];WindowVideoManager::WindowVideoMap table;};
void Rva002BF77B::rva002BF77B(){
 WindowVideoManager::WindowVideoMap::iterator it=table.begin();
 for(;it!=table.end();++it)reinterpret_cast<Rva002BF77BTarget*>(it->second)->dispatch();
}

namespace _STL {
template <class _Tp, class _Alloc> class _Vector_base;
template <>
class _Vector_base<GameWindow*, allocator<GameWindow*> >
{
public:
	_Vector_base(const allocator<GameWindow*> &);
};
}

class Rva002BF7AC : public _STL::_Vector_base<GameWindow*, _STL::allocator<GameWindow*> >
{
public:
	Rva002BF7AC(int unused, const _STL::allocator<GameWindow*> &a);
};

Rva002BF7AC::Rva002BF7AC(int unused, const _STL::allocator<GameWindow*> &a)
	: _STL::_Vector_base<GameWindow*, _STL::allocator<GameWindow*> >(a)
{
}

