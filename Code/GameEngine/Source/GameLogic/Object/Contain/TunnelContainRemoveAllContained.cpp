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

class ContainModuleInterface
{
public:
	virtual void c00();
	virtual void c01();
	virtual void c02();
	virtual void c03();
	virtual void c04();
	virtual void c05();
	virtual void c06();
	virtual void c07();
	virtual void c08();
	virtual void c09();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual void c31();
	virtual void c32();
	virtual void c33();
	virtual void c34();
	virtual void c35();
	virtual void c36();
	virtual void c37();
	virtual void c38();
	virtual void c39();
	virtual void c40();
	virtual void c41();
	virtual void c42();
	virtual void c43();
	virtual void c44();
	virtual void c45();
	virtual void c46();
	virtual void c47();
	virtual void c48();
	virtual void c49();
	virtual void c50();
	virtual void c51();
	virtual void c52();
	virtual void c53();
	virtual void c54();
	virtual void c55();
	virtual void c56();
	virtual void c57();
	virtual void c58();
	virtual void c59();
	virtual void c60();
	virtual void c61();
	virtual void c62();
	virtual void c63();
	virtual void c64();
	virtual void c65();
	virtual void c66();
	virtual void c67();
	virtual void iterateContained( ContainIterateFunc func, void *userData, Bool reverse );
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x115];
	unsigned char m_kindOf115;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x250 - 0x08];
	ContainModuleInterface *m_contain;
};

class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
};

class Player
{
public:
	unsigned char m_pad000[0x2E8];
	Rva00466398 *m_2E8;
};

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
	Rva00466398 *tunnelTracker = owningPlayer->m_2E8;
	ContainmentList objects = tunnelTracker->rva00466398().rva0036AE51();
	ContainmentList::iterator it = objects.begin();
	while (it != objects.end())
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		++it;
		if (obj->m_template->m_kindOf115 & 0x20)
			obj->getContain()->iterateContained( Rva0047DAEARemoveVisit, this, true );
		removeFromContain( obj, exposeStealthUnits );
	}
}
