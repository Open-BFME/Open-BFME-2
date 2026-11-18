// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?updateLocalPhantomStructureDisplay@InGameUI@@QAEXXZ, retail 0x002A1158
// (231 bytes, EH frame for one list<int> temporary).
// Name and owner from the WorldBuilder twin 0x00DC4050
// (InGameUI::updateLocalPhantomStructureDisplay, InGameUI.cpp assert 8780
// "InGameUI phantom structure ID missing object!"); retail matches its
// shape. Called directly (not through the vtable) from 0x002A1A67 in the
// 1413-byte InGameUI update body 0x002A1582.
// Body: the phantoms are hidden unless exactly one drawable is selected
// (getSelectCount +0x118 == 1) whose object (Drawable +0xFC) has KindOf bit
// 14 (ThingTemplate byte +0x109 bit 0x40; WB tests KindOf 0xE). For every
// object ID in the list<int> at +0x9C4 (the InGameUICtor/InGameUIDtor
// member) the live object's drawable (rowed Thing::getDrawable 0x005508E2)
// gets setDrawableHidden (0x00271601 pinned name); IDs whose object is gone
// are collected (inlined push_back = rowed list<int>::insert 0x005925E2)
// and removed afterwards (list<int>::remove 0x0047BAF7 pinned name).
// Retail evidence: both loops cache the end node in edi (a local end
// iterator); /EHs keeps the state reset before the rowed _List_base dtor
// 0x004EC395 (ctor 0x004EC36C).
// Facts from retail: slots offsets and callees; names from the WB twin.
#include "../Common/Thing/thing.h"
#include <list>
#include "../Common/GameLogicObjectLookupView.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#include "../../Include/Common/ScalarTypes.h"

class Drawable;

#include "../../Include/Common/ThingTemplate.h"

#include "../../Include/GameClient/Drawable.h"

class Object : public Thing
{
};


extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/InGameUI.h"

void InGameUI::updateLocalPhantomStructureDisplay()
{
	Bool hide = true;
	if (getSelectCount() == 1)
	{
		Object *obj = getFirstSelectedDrawable()->getObject();
		if (obj && ((obj->m_template->m_kindof[0] & (1U << 14)) != 0))
			hide = false;
	}
	_STL::list<int> dead;
	_STL::list<int>::iterator it;
	_STL::list<int>::iterator end = m_9C4.end();
	for (it = m_9C4.begin(); it != end; ++it)
	{
		int id = *it;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
		if (obj)
		{
			Drawable *draw = obj->getDrawable();
			if (draw)
				draw->setDrawableHidden(hide);
		}
		else
			dead.push_back(id);
	}
	end = dead.end();
	for (it = dead.begin(); it != end; ++it)
	{
		int id = *it;
		m_9C4.remove(id);
	}
}
