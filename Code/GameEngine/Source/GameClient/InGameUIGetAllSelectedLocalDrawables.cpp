// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?getAllSelectedLocalDrawables@InGameUI@@UAEPBV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@XZ @0x002A3908 84B: InGameUI virtual slot 64 clears m_selectedLocalDrawables then collects selected drawables whose Object isLocallyControlled. ZH donor InGameUI.cpp getAllSelectedLocalDrawables via BFME1 shape; retail vtables at RVA 0x007C7AB0 and 0x007FD438 both carry this slot; neighbours getMoney and dword getters prove table.
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}

// Compare list nodes with a local overload so this TU emits no iterator-base operator!= copy.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class Drawable;
typedef _STL::list<Drawable *> BfmeDrawableList;

class Rva00239380Holder
{
public:
	void rva00239380();
};

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/GameClient/InGameUI.h"

const BfmeDrawableList *InGameUI::getAllSelectedLocalDrawables()
{
	((Rva00239380Holder *)&m_selectedLocalDrawables)->rva00239380();
	for (BfmeDrawableList::iterator it = m_selectedDrawables.begin(); it != m_selectedDrawables.end(); ++it)
	{
		Drawable *draw = *it;
		if (draw && draw->m_object && draw->m_object->isLocallyControlled())
			m_selectedLocalDrawables.push_back(draw);
	}
	return &m_selectedLocalDrawables;
}
