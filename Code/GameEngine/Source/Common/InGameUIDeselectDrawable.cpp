// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /arch:SSE /G7
// stlport
// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z @0x0029F34F 136B
// evidence: InGameUI slot57 deselect via BFME1 donor plus retail offsets plus rowed helpers
#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <algorithm>
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@PAVDrawable@@@_STL@@@_STL@@QBEXPAU?$_List_node@PAVDr:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Drawable;
namespace _STL { template <> void allocator<_List_node<Drawable *> >::deallocate(_List_node<Drawable *> *,unsigned int) const; }
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DBA5E0, head at +0x08; retail 0x0029DFE9).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> list<Drawable *>::iterator list<Drawable *>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool00DBA5E0.m_head;
	g_freelistPool00DBA5E0.m_head = __position._M_node;
	return iterator((_List_node<Drawable *> *)__next_node);
}
}
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../Include/GameClient/Drawable.h"

class ControlBar;
class BfmeWorldRV { public: void rva0031AA4B(int); };

extern ControlBar *TheControlBar;

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;


typedef _STL::list<Drawable *> BfmeDrawableList;

#include "../../Include/GameClient/InGameUI.h"

// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z retail 0x0029F34F 136B
// Slot 57 deselect mirror of slot 56 selectDrawable at 0x002A3805.
// Evidence: Drawable flag +0x43C with out-of-line clear 0x00276B95;
// frame +0x570 count +0x568 list +0x20 via rowed ObjectID find 0x0029B694
// and rowed removeRecycle 0x0029DFE9 with same pushes as list erase;
// evaluateSoloNexus 0x0029B967 with 0; ControlBar 0x0031AA4B;
// reset 0x0029ACC7 with 0. BFME1 donor InGameUIDeselectDrawable.
void InGameUI::deselectDrawable(Drawable *draw)
{
	if (!draw->m_selected)
		return;
	field570 = TheGameLogic->getFrame();
	draw->rva00276B95();
	_STL::list<ObjectID>::iterator findIt = _STL::find(((_STL::list<ObjectID> *)&m_selectedDrawables)->begin(), ((_STL::list<ObjectID> *)&m_selectedDrawables)->end(), *(ObjectID *)&draw);
	m_selectedDrawables.erase(*(BfmeDrawableList::iterator *)&findIt);
	--field568;
	evaluateSoloNexus(0);
	((BfmeWorldRV *)TheControlBar)->rva0031AA4B((int)draw);
	expireAllHints(0);
}
