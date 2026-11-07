// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ??0Rva004134AE@@QAE@XZ, retail 0x0041345B, 55 bytes (RET0).
// The constructor of the class whose nonvirtual dtor 0x004134AE and deleting
// dtor 0x00413492 are rowed (Rva004134AEDtor.cpp). Retail: base ctor
// ??0SubsystemInterface@@QAE@XZ 0x001B4E63 with ecx=this, EH state 0, vtable
// store at +0, then the +0xC member constructed through the rowed map default
// ctor 0x00242F01 (pinned as ?$map@JVLadderPref@@...), returning this. The
// mangled name and the member's original element type are not asserted beyond
// the rowed callee spellings.
#include <map>

// Retail installs the 14-slot SubsystemInterface table 0x008399B8, so this unit needs
// the header's full slot list.
#define BFME_SUBSYSTEM_SLOTS
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../Include/GameNetwork/LadderPref.h"
// Nothing this unit's rows reach calls the map's subtree erase or its node
// destroy; declare them so the unit emits no copies of its own (the kept
// copies serve the link).
namespace _STL {
template <> void _Destroy<pair<const long, LadderPref> >(pair<const long, LadderPref> *);
template <> void _Rb_tree<long, pair<const long, LadderPref>, _Select1st<pair<const long, LadderPref> >,
	less<long>, allocator<pair<const long, LadderPref> > >::_M_erase(_Rb_tree_node<pair<const long, LadderPref> > *);
}

class Rva004134AE : public SubsystemInterface
{
public:
	Rva004134AE();
	// Retail 0x008399B8 slots 1, 9 and 10: empty bodies, folded into the shared ret at
	// 0x000B3FD0 like the base class's empty slots.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	_STL::map<long, LadderPref> m_tree0C;
};

Rva004134AE::Rva004134AE()
{
}
