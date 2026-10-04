// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00423D92@Rva00423D92@@QAEXU?$_List_iterator@PAVGameWindow@@U?$_Const_traits@PAVGameWindow@@@_STL@@@_STL@@0ABU__false_type@3@@Z, retail 0x00423D92, 79 bytes.
// _STL::list<GameWindow*>::_M_assign_dispatch over const_iterator range with
// __false_type tag: copy overlapping nodes then erase tail or insert remainder
// via rowed erase 0x004221B2 and rowed insert 0x00423890. Evidence: STLport
// _list.h source shape; caller 0x004243BE assign wrapper forwards first last
// plus tag; callee types prove GameWindow list.
#include <list>

class GameWindow;
typedef _STL::list<GameWindow *, _STL::allocator<GameWindow *> > GWList;

class Rva00423D92
{
public:
	void rva00423D92(GWList::const_iterator a, GWList::const_iterator b, const _STL::__false_type &c);
};

void Rva00423D92::rva00423D92(GWList::const_iterator first2, GWList::const_iterator last2, const _STL::__false_type &)
{
	GWList *me = (GWList *)this;
	GWList::iterator first1 = me->begin();
	GWList::iterator last1 = me->end();
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		*first1 = *first2;
	if (first2 == last2)
		me->erase(first1, last1);
	else
		me->insert(last1, first2, last2);
}
