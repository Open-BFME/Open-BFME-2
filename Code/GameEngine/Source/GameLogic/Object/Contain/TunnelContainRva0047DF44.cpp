// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
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
#include "TunnelContainView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

bool TunnelContain::rva0047DF44(int id)
{
	Player *player = m_object->getControllingPlayer();
	Rva0036AE51ListView out = ((Rva00466398 *)player->m_tunnelSystem)->rva00466398();
	for (ContainmentList::iterator it = out.b->begin(); it._M_node != out.b->end()._M_node; ++it)
	{
		if (containmentFirstWord(*it) == id)
			return true;
	}
	return false;
}
