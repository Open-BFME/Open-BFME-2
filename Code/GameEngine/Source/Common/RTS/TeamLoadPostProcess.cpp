// cl: /Ireference/shims/bfmelist /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?loadPostProcess@Team@@MAEXXZ, retail 0x003A2339 (107 bytes).
// Identity (target): WorldBuilder's debug Team.cpp:4833..4848 body
// Team::LoadPostProcess sits in the same Team vtable slot (0x0081AF00, after
// ??_GTeam), and retail's callee order agrees: GameLogic::findObjectByID
// over the transfer list, the member-list test
// Object::dlink_isInList_TeamMemberList (0x0028A6C7) against the +0x38 head,
// then the list clear (rowed folded _List_base clear 0x0023DAA5).
// Donor (Zero Hour Team::loadPostProcess): each saved member ID must resolve
// to an object already in the team, else throw SC_INVALID_DATA, which BFME 2
// spells XferException(5, 0) (ctor 0x0060C36E). Layout (target): the
// saved-ID list at +0x12C; ObjectID is held as int, as the folded clear is.
// Shape (inference): retail tests against an end() read once before the loop.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../GameLogicObjectLookupView.h"

class Object
{
public:
	bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;
};


extern GameLogic *TheGameLogic;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

#include "../../../Include/Common/TeamBFME2.h"

void Team::loadPostProcess()
{
	_STL::list<int, _STL::allocator<int> > &xferMemberIDs = *(_STL::list<int, _STL::allocator<int> > *)m_opaque12C;
	_STL::list<int, _STL::allocator<int> >::const_iterator it;
	Object *obj;
	_STL::list<int, _STL::allocator<int> >::const_iterator end = xferMemberIDs.end();
	for (it = xferMemberIDs.begin(); it != end; ++it)
	{
		obj = TheGameLogic->findObjectByID((ObjectID)*it);
		if (obj == 0)
			throw XferException(5, 0);
		if (obj->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList) == false)
			throw XferException(5, 0);
	}
	xferMemberIDs.clear();
}
