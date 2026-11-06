// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// Retail 0x0047DAEA (22B) a TunnelContain removal visitor and 0x0047E0CE
// (157B) TunnelContain::removeAllContained.
// Pattern: the matched CaveContain::removeAllContained 0x00466A50 (same
// contain interface at +0x20, removeFromContain in its slot 0xA4): the
// controlling player's tunnel tracker (+0x2E8) list is copied through
// 0x00466398/0x0036AE51 and walked advancing before each removal. BFME 2
// adds: for a contained object whose template has kind-of bit 0x115:0x20,
// its own contain module (Object+0x250) is iterated (slot 0x110, reverse)
// with the 0x0047DAEA visitor and this TunnelContain as user data, so its
// passengers leave through removeFromContain(obj, true) first.
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Object;
class Player;
typedef bool Bool;

typedef void (*ContainIterateFunc)( Object *obj, void *userData );

#include "../../../../Include/GameLogic/Module/ContainModule.h"

#include "../../../../Include/Common/ThingTemplate.h"

#include "../object.h"

class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
};

#include "../../../../Include/Common/Player.h"

class TunnelContainPrimary
{
public:
	virtual void primarySlot00();
protected:
	Object *getObject() const { return m_object; }
private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class TunnelContainInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void removeFromContain( Object *obj, int exposeStealthUnits ) = 0;
	virtual void removeAllContained( int exposeStealthUnits ) = 0;
};

class TunnelContain : public TunnelContainPrimary, public TunnelContainInterface
{
public:
	virtual void removeFromContain( Object *obj, int exposeStealthUnits );
	virtual void removeAllContained( int exposeStealthUnits );
};

template <> void _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::clear();
template <> _STL::_List_base<Rva0036ADF9Element, _STL::allocator<Rva0036ADF9Element> >::~_List_base();

void Rva0047DAEARemoveVisit( Object *obj, void *userData )
{
	((TunnelContain *)userData)->removeFromContain( obj, 1 );
}

void TunnelContain::removeAllContained( int exposeStealthUnits )
{
	Player *owningPlayer = getObject()->getControllingPlayer();
	Rva00466398 *tunnelTracker = (Rva00466398 *)owningPlayer->m_tunnelSystem;
	ContainmentList objects = tunnelTracker->rva00466398().rva0036AE51();
	ContainmentList::iterator it = objects.begin();
	while (it != objects.end())
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		++it;
		if (obj->m_template->m_kindof[3] & (1U << 13))
			obj->getContain()->iterateContained( Rva0047DAEARemoveVisit, this, true );
		removeFromContain( obj, exposeStealthUnits );
	}
}
