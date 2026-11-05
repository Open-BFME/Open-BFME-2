// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1StateMachine@@UAE@XZ, retail 0x004D759C (139B, EH frame).
// Zero Hour StateMachine::~StateMachine plus BFME2's reset tail: exit the
// current state with EXIT_RESET (vtable slot 5, argument 1), delete every
// state held in the map, clear the map, then null the current state and set
// the default state id to INVALID_STATE_ID (999999 = 0xF423F). Target
// evidence: the vptr store of vftable 0x00C60740 (the base of the 20
// derived machine vtables, see StateMachineRva004D750F.cpp), the map walk
// via _M_increment 0x00024250 over the +0x08 tree, the clear 0x004D751D and
// tree destructor 0x004D755F of the state map (StateID = unsigned int), and the
// Snapshot vptr 0x00BBB554 restored last. The scalar deleting destructor
// ??_GStateMachine (retail 0x004D7A59, 28B) is emitted here with the vftable.
// Retail's state-map destructor frees the header node through the C++-linkage
// free (0x00030830), which keeps the unwind-state store before the call.
namespace _STL { void __cdecl free(void *); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseStateMapStorage(void *storage)
{
	_STL::free(storage);
}
#include <cstdlib>
#include <map>
class State;
namespace _STL {
template<> inline void allocator<_Rb_tree_node<pair<const unsigned int, State *> > >::deallocate(_Rb_tree_node<pair<const unsigned int, State *> > *__p, size_type) const
{
	if (__p != 0) releaseStateMapStorage((void *)__p);
}
}
#include "Common/Snapshot.h"
#include "../../Include/Common/StateMachine.h"

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

enum
{
	INVALID_STATE_ID = 999999
};

class StateMachine : public Snapshot
{
public:
	virtual ~StateMachine();

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void) = 0;

private:
	State *m_currentState;				// +0x04
	_STL::map<unsigned int, State *> m_stateMap;	// +0x08
	int m_pad14[2];
	unsigned int m_defaultStateID;		// +0x1C
};

StateMachine::~StateMachine()
{
	if (m_currentState)
		m_currentState->onExit(EXIT_RESET);

	for (_STL::map<unsigned int, State *>::iterator i = m_stateMap.begin(); i != m_stateMap.end(); ++i)
	{
		if ((*i).second)
			::delete (*i).second;
	}
	m_stateMap.clear();
	m_currentState = 0;
	m_defaultStateID = INVALID_STATE_ID;
}
