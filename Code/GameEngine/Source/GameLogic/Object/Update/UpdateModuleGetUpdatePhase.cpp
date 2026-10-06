// cl: /DNDEBUG /MD
//
// ?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ, retail 0x0022C4CB, 4 bytes.
// BFME1/Zero Hour UpdateModule.h: `virtual SleepyUpdatePhase getUpdatePhase() const
// { return PHASE_NORMAL; }` (PHASE_NORMAL = 2), the one virtual UpdateModule adds to
// its primary (BehaviorModule) table. Evidence: ??_7UpdateModule (0x00BF004C) has 13
// slots against BehaviorModule's 12 (0x00BEEA7C), slot 12 holds this body; the
// size-optimised PUSH 2 / POP EAX / RET is shared (ICF) by ~180 module vtable slots.

enum SleepyUpdatePhase
{
	PHASE_INITIAL = 0,
	PHASE_PHYSICS = 1,
	PHASE_NORMAL = 2,
	PHASE_FINAL = 3
};

class UpdateModule
{
protected:
	virtual SleepyUpdatePhase getUpdatePhase() const;
};

SleepyUpdatePhase UpdateModule::getUpdatePhase() const
{
	return PHASE_NORMAL;
}
