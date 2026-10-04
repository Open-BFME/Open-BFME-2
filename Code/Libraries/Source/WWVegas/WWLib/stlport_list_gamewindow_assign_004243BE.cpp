// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$assign@U?$_List_iterator@PAVGameWindow@@U?$_Const_traits@PAVGameWindow@@@_STL@@@_STL@@@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAEXU?$_List_iterator@PAVGameWindow@@U?$_Const_traits@PAVGameWindow@@@_STL@@@1@0@Z, retail 0x004243BE, 22 bytes.
// _STL::list<GameWindow*>::assign over const_iterator range: forwards first
// last plus __false_type tag to rowed honest dispatch 0x00423D92.
// Evidence: STLport _list.h assign shape plus rowed honest rva00423D92 plus
// stash 0x004243BE score 0.95 plus callers none plus prev next same flags.
#include <list>

class GameWindow;
typedef _STL::list<GameWindow *, _STL::allocator<GameWindow *> > GWList;
template void GWList::assign<GWList::const_iterator>(GWList::const_iterator, GWList::const_iterator);
