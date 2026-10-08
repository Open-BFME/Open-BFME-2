// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0047DF44@TunnelContain@@UAE_NH@Z @0x0047DF44 61B.
// Target evidence: the only reference to this body is slot 58 of the vtable
// 0x00C475B8 that the matched TunnelContain ctor 0x0047DBF7 and dtor
// 0x0047DB00 install at +0x20 (the OpenContain-family layout); the slot's
// name is not established, hence the address name. cl 7.1 compiles an
// override of a non-primary base's virtual with the base subobject's this
// and folds the adjustment into the member accesses: the Object pointer at
// +8 is read as [ecx-0x18]. Body: asks the controlling player's +0x2E8
// object (rowed 0x00466398) to fill a two-dword record whose second dword is
// a list<int>, and reports whether the argument is in that list (STLport
// list walk: header at [list], first node at [header], value at node +8).
// Structural inference: the Player is held in a local before the call, which
// evaluates the object before pushing &out as retail does.
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

class Thing;
class ModuleData;
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
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
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
class Iface20
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual bool rva0047DF44(int id) = 0;
};
class TunnelContain : public B00, public B0C, public B10, public Iface20
{
public:
	virtual bool rva0047DF44(int id);
};
bool TunnelContain::rva0047DF44(int id)
{
	Player *player = m_object->getControllingPlayer();
	Rva0036AE51ListView out = player->m_2E8->rva00466398();
	for (ContainmentList::iterator it = out.b->begin(); it._M_node != out.b->end()._M_node; ++it)
	{
		if (containmentFirstWord(*it) == id)
			return true;
	}
	return false;
}
