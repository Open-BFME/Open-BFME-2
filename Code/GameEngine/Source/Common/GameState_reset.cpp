// cl: /O1 /DNDEBUG /MD
//
// ?reset@GameState@@UAEXXZ @0x002DEE9A 41B. GameState's primary table
// 0x00C0402C (installed by the rowed ctor 0x002DE4E6) holds it in slot 9, the
// canonical subsystem reset slot: PlayerList's table 0x00BFD618 has its rowed
// reset in slot 9 and update in slot 10, and GameState's slot 10 is the shared
// empty RET. Body: clears the +0xE0C and +0xE10 lists via the landed list
// clear 0x0023DAA5, runs the rowed 0x002DE311 on this, then zeroes the +0xE18
// byte. Member identities are offsets.

namespace _STL {
template <class T> class allocator;
template <class T, class A> class _List_base
{
public:
	void clear();
};
}

// 0x002DE311 is rowed as Rva002DE311Owner::rva002DE311 (SaveGameInfoCopyBFME2.cpp).
#include "../../Include/Common/Rva002DE311Owner.h"

#include "../../Include/Common/GameState.h"

// ?reset@GameState@@UAEXXZ
void GameState::reset()
{
	((_STL::_List_base<int, _STL::allocator<int> > *)&field0E0C)->clear();
	((_STL::_List_base<int, _STL::allocator<int> > *)&field0E10)->clear();
	((Rva002DE311Owner *)this)->rva002DE311();
	m_isInLoadGame = 0;
}
