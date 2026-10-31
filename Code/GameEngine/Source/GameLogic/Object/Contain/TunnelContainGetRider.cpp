// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
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
#include "TunnelContainView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

inline __declspec(noinline) Rva0036AE51ListView Rva00466398::rva00466398(){Rva0036AE51ListView out;out.a=this?(void*)((char*)this+4):0;out.b=(ContainmentList*)((char*)this+16);return out;}

Rva0047DEE1Rider *TunnelContain::rva0047DEE1( int arg )
{
	Player *player = m_object->getControllingPlayer();
	Rva0036AE51ListView out = ((Rva00466398 *)player->m_tunnelSystem)->rva00466398();
	ContainmentList *list = out.b;
	for (ContainmentList::iterator it = list->begin(); it._M_node != list->end()._M_node; ++it)
	{
		Object *obj = (Object *)containmentFirstWord(*it);
		ContainModuleInterface *contain = obj->getContain();
		if (contain)
		{
			Rva0047DEE1Rider *rider = (Rva0047DEE1Rider *)contain->c31();
			if (rider && rider->x6(arg))
				return rider;
		}
	}
	return 0;
}
