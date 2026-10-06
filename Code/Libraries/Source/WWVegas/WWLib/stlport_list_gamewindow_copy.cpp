// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy@PAV?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@PAV12@H@_STL@@YAPAV?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@0@PAV10@00ABUrandom_access_iterator_tag@0@PAH@Z @0x004703B1 47B
// STLport __copy for list<GameWindow*> (4-byte list objects): range-loop
// calling rowed list operator= 0x0046F0C2. Called by copy 0x00474125.
// Evidence: callees rowed; callers 0x00474138; prev/next STL flags.
#include <algorithm>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class GameWindow;
typedef _STL::list<GameWindow *, _STL::allocator<GameWindow *> > GWList;
template GWList *_STL::copy<GWList *, GWList *>(GWList *, GWList *, GWList *);
