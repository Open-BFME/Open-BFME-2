// cl: /DNDEBUG /MD
//
// ?getMachineGoalObject@State@@QAEPAVObject@@XZ, retail 0x0033F263, 8 bytes.
//
// State's one-COMDAT inline from Common/StateMachine.h (Zero Hour:
// `inline Object *State::getMachineGoalObject() { return m_machine->getGoalObject(); }`).
// getGoalObject is declared there but not defined, and it takes no stack
// argument, so the compiler emits the inline as a tail call:
//
//     0033F263: 8b 49 18        mov ecx,[ecx+0x18]      ; m_machine
//     0033F266: e9 xx xx xx xx  jmp ?getGoalObject@StateMachine@@QAEPAVObject@@XZ
//
// BFME2's State carries m_machine at +0x18, not the +0x20 the Zero Hour header
// gives it (Win32 State has a single vptr where ZH's header inherits a second
// from Snapshot, and a first/count transition pair where ZH holds a
// std::vector). Two independent retail measurements say so:
//   * the retail State constructor at 0x004D73FC stores its StateMachine*
//     argument with `mov [eax+0x18],ecx` (and the three ids 999999 at
//     +0x04/+0x08/+0x0C, the transition pair at +0x10/+0x14, a byte at +0x1C);
//   * the matched AIDockState::onEnter at 0x00341695 loads `[esi+0x18]` and
//     calls the rowed StateMachine::getGoalObject at 0x004D7726.
// The matched StateMachineDefineState.cpp declares the same +0x18.
//
// That layout difference is why this symbol was previously claimed at
// 0x005E69C8: a TU compiled against the Zero Hour header emits `[ecx+0x20]`,
// and a masked whole-.text search for the four fixed bytes found the one
// `mov ecx,[ecx+0x20]; jmp` site in .text. That site is a different, still
// unclaimed 8-byte function: it jumps to 0x005E68C0, a 120-byte body that
// calls the map/index helpers 0x005F6037, 0x0040CC0E, 0x005E3B1A, 0x005E508F
// and 0x005F62FE, not the rowed StateMachine::getGoalObject. Nothing else in
// Code/ emits this symbol, hence a dedicated TU. 0x0033F263 is the only
// `mov ecx,[ecx+0x18]; jmp` site in .text and sits in the exact 8-byte gap
// between the matched 0x0033F25C+7 and 0x0033F26B, which fixes its boundary.

typedef int StateID;

class Object;

class StateMachine
{
public:
	Object *getGoalObject();
};

class State
{
public:
	virtual void vslot00();
	virtual void vslot04();
	StateID m_id;						// +0x04
	StateID m_successStateID;			// +0x08
	StateID m_failureStateID;			// +0x0C
	const void *m_transitionsFirst;		// +0x10
	int m_transitionsCount;				// +0x14
	StateMachine *m_machine;			// +0x18
	bool m_tail1C;						// +0x1C

	Object *getMachineGoalObject();
};

// ?getMachineGoalObject@State@@QAEPAVObject@@XZ
Object *State::getMachineGoalObject()
{
	return m_machine->getGoalObject();
}
