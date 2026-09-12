// ?_bfme_updateTimedOps@@YAIXZ
// partial score=0.49 date=2026-09-12
// cl: /MD

// Evidence: retail 0x003FE74B (71 bytes) is the REL32 call target named
// ?_bfme_updateTimedOps@@YAIXZ, referenced (as a forward declaration only)
// by Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp:
//   unsigned int _bfme_updateTimedOps(void);
//   ...
//   unsigned int timedOps = _bfme_updateTimedOps();
// No BFME1 twin exists for this one; the body below is reconstructed
// directly from the retail bytes: a global singly-linked list head
// (VA 0xE02EC0) of polymorphic "timed op" nodes (vtable at +0, m_next at
// +4). Each call services at most the head node: it invokes a non-virtual
// update() (retail 0x3FE6E8, pinned by this call site's thiscall/no-arg/
// eax-return shape) and, if bit 0x2 of the result is set, unlinks and
// tears it down with the exact split retail uses -- a virtual
// op->~TimedOp() call with the deleting-destructor flag forced to 0, then
// a separate call to the global scalar operator delete (0x2FD60) -- rather
// than a bare `delete op;` (which combines both into one flag=1 call and
// does not match). The return value is always masked to bits 0x1/0x4
// (`& 5`); when the list became empty during this call the pre-delete
// flags are first narrowed to just bit 0x4.
//
// Near miss: this reconstruction matches the control flow and the dtor/
// delete split exactly (positional 35/71, prefix 12B) but keeps the old
// list head in a register (esi, pushed/popped) across the update() call
// where retail instead reloads it fresh from the global afterward --
// pure register allocation, not a structural difference.

class TimedOp
{
public:
	virtual ~TimedOp();
	unsigned int update( void );

	TimedOp *m_next; // +0x4
};

extern TimedOp *g_timedOpListHead; // VA 0xE02EC0

unsigned int _bfme_updateTimedOps( void )
{
	unsigned int flags = 0;

	if ( g_timedOpListHead )
	{
		flags = g_timedOpListHead->update();
		if ( flags & 2 )
		{
			TimedOp *op = g_timedOpListHead;
			g_timedOpListHead = op->m_next;
			op->~TimedOp();
			::operator delete( op );
			if ( g_timedOpListHead == 0 )
				flags &= 4;
		}
	}

	return flags & 5;
}
