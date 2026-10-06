// BFME2 function-level tracer. Zero Hour's call-tracing ProfileFuncLevelTracer
// is gone: its frame entry points survive as gates that call an optional
// __stdcall hook with (1, 0) (FrameStart 0x006C8380, FrameEnd 0x006C83A0).

#ifndef INTERNAL_FUNCLEVEL_H
#define INTERNAL_FUNCLEVEL_H

typedef void (__stdcall *ProfileFuncLevelHook)(int first, int second);

class ProfileFuncLevelTracer
{
public:
	static int FrameStart(void);
	static void FrameEnd(int which, int mixIndex);

	static ProfileFuncLevelHook frameStartHook;   // .bss 0x00E0C768
	static ProfileFuncLevelHook frameEndHook;     // .bss 0x00E0C76C
};

#endif // INTERNAL_FUNCLEVEL_H
