// cl: /Ob0 /G7 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS /ICode/GameEngine/Include
// BFME 2 has no DumbProjectileBehavior: game.dat holds no such module name and no row
// is one of its methods. Two shared inlines rest in this file until their addresses get
// an approved unit, sqr<float> (0x00005781) and UpdateModule's getUpdatePhase (0x0022C4CB,
// the ICF-shared PUSH 2/POP EAX/RET slot of retail's UpdateModule table 0x00BF004C).
#include "GameLogic/Module/UpdateModule.h"

template <class NUM> inline NUM sqr(NUM x)
{
	return x * x;
}

template float sqr<float>(float);

inline SleepyUpdatePhase UpdateModule::getUpdatePhase() const
{
	return (SleepyUpdatePhase)2;
}

// A virtual's address is a call thunk, so only a direct call makes this unit emit the
// body, and /Ob0 keeps that call out of line. Nothing here is ever instantiated or run.
class UpdatePhaseCaller;

static SleepyUpdatePhase callUpdatePhase(const UpdatePhaseCaller *caller);

class UpdatePhaseCaller : public UpdateModule
{
	friend SleepyUpdatePhase callUpdatePhase(const UpdatePhaseCaller *caller);
};

static SleepyUpdatePhase callUpdatePhase(const UpdatePhaseCaller *caller)
{
	return caller->UpdateModule::getUpdatePhase();
}

extern const void *const g_updatePhaseAnchor = (const void *)&callUpdatePhase;
