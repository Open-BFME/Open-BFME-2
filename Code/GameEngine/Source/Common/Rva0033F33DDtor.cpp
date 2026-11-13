// cl: /MD /EHsc
// ??1AIBackAwayAndCowerState@@UAE@XZ @0x003401E4 75B: AIBackAwayAndCowerState public virtual dtor.
// Native ctor 0x0033F33D uses State, hash 0x6D9C1CB9 and table 0x00810EE0.
// The member at +0x20 is released through slot 0 then global delete.
// The base teardown at 0x0049B47C is the rowed State destructor.
// Both lifecycle units declare native xfer slot 3 at 0x0034027D.
// Unblocks deleting dtor at 0x003428F1.
class StateMachine;
#include "../../Include/Common/StateMachineClass.h"

#include "../../Include/Common/AIBackAwayAndCowerState.h"
#include <new>
AIBackAwayAndCowerState::~AIBackAwayAndCowerState()
{
	if (m_20) {
		::delete m_20;
		m_20 = 0;
	}
}
