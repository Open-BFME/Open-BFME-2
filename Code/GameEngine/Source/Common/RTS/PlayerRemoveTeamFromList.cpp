// cl: /GX /MD
// stlport
// ?removeTeamFromList@Player@@QAEXPAVTeamPrototype@@@Z, RVA 0x002ABD48, size 75.
// Evidence (target): REL32 call at 0x003A0CDC from TeamPrototype::rva003A0CD1
// on m_owningPlayer with the prototype as argument; the body walks the
// STLport list at Player +0x32C (node next/prev/value), compares the value to
// the argument and erases the first hit through the out-of-line
// list::erase(iterator) at 0x002ABAC0 (hidden iterator return, iterator copied
// by value). Name and purpose carried from Zero Hour's
// Player::removeTeamFromList. Structural inference: the two empty walks
// before and after the search are debug-only list counts whose consumers the
// release build stripped; written here as the empty walks retail keeps.
#include <list>
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@PAVTeamPrototype@@@_STL@@@_STL@@QBEXPAU?$_List_node@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class TeamPrototype;
namespace _STL { template <> void allocator<_List_node<TeamPrototype *> >::deallocate(_List_node<TeamPrototype *> *,unsigned int) const; }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class TeamPrototype;
typedef _STL::list<TeamPrototype *> PlayerTeamList;
// Declared only: the out-of-line erase is retail's rowed body at 0x002ABAC0.
namespace _STL { template <> PlayerTeamList::iterator PlayerTeamList::erase(PlayerTeamList::iterator); }

// The team list's nodes come from a pool: retail's out-of-line erase
// (pinned 0x002ABAC0, ICF twin of rowed Rva002ABAC0Free) unlinks the node and
// pushes it onto the pool's free list at VA 0x00DBBD34 instead of calling
// STLport's node allocator (same pool as PlayerUpdate.cpp's team list).
struct PoolNode002ABAC0;
// The free-list head is the +8 member of the complete pool at VA 0xDBBD2C.
class FreelistPool;
extern FreelistPool g_freelistPool009BBD2C;
#define g_00DBBD34 (*(PoolNode002ABAC0 **)((char *)&g_freelistPool009BBD2C + 8))
namespace _STL {
template <> __declspec(noinline) inline PlayerTeamList::iterator PlayerTeamList::erase(iterator position)
{
	_List_node_base *prev = position._M_node->_M_prev;
	_List_node_base *next = position._M_node->_M_next;
	prev->_M_next = next;
	next->_M_prev = prev;
	*(void **)position._M_node = g_00DBBD34;
	g_00DBBD34 = (PoolNode002ABAC0 *)position._M_node;
	return iterator((_Node *)next);
}
}

class Player
{
public:
	void removeTeamFromList(TeamPrototype *team);

private:
	unsigned char m_pad[0x32C];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
};

void Player::removeTeamFromList(TeamPrototype *team)
{
	PlayerTeamList::iterator it;
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		;
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		if (team == *it) { m_playerTeamPrototypes.erase(it); break; }
	for (it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
		;
}
