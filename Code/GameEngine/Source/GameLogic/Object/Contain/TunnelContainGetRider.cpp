// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// The inline/noinline view getter is the already rowed 26-byte provider
// at 0x00466398 and its complete bytes also match in this TU. Its visible
// write set restores the target caller register allocation.
// Retail 0x0047DEE1, 99B: a TunnelContain primary-vtable member (only
// reference is a vtable entry; the slot's name is not established, hence the
// address name). It walks the containment list the controlling player's
// tunnel tracker (+0x2E8) returns (0x00466398, as in the matched sibling
// TunnelContain::rva0047DF44 0x0047DF44) and returns the first contained
// object's rider interface (contain module Object+0x250, slot 0x7C) whose
// slot 0x18 test accepts the argument, else null.
#include <list>
#include "Code/GameEngine/Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

class Player;
class ModuleData;

class Rva0047DEE1Rider
{
public:
	virtual void x0();
	virtual void x1();
	virtual void x2();
	virtual void x3();
	virtual void x4();
	virtual void x5();
	virtual bool x6( int arg );
};

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
	virtual Rva0047DEE1Rider *c31();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	unsigned char m_pad00[0x250];
	ContainModuleInterface *m_contain;
};

class Rva00466398
{
public:
	inline __declspec(noinline) Rva0036AE51ListView rva00466398(){Rva0036AE51ListView out;out.a=this?(void*)((char*)this+4):0;out.b=(ContainmentList*)((char*)this+16);return out;}
};

class Player
{
public:
	unsigned char m_pad000[0x2E8];
	Rva00466398 *m_2E8;
};

class TunnelContain
{
public:
	virtual Rva0047DEE1Rider *rva0047DEE1( int arg );
private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

Rva0047DEE1Rider *TunnelContain::rva0047DEE1( int arg )
{
	Player *player = m_object->getControllingPlayer();
	Rva0036AE51ListView out = player->m_2E8->rva00466398();
	ContainmentList *list = out.b;
	for (ContainmentList::iterator it = list->begin(); it._M_node != list->end()._M_node; ++it)
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		ContainModuleInterface *contain = obj->getContain();
		if (contain)
		{
			Rva0047DEE1Rider *rider = contain->c31();
			if (rider && rider->x6(arg))
				return rider;
		}
	}
	return 0;
}
