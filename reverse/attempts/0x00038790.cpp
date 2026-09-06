// ?SkipNext@Debug@@SA_N_N@Z
// partial score=0.95 date=2026-09-06
// ?SkipNext@Debug@@SA_N_N@Z
// partial score=0.95 date=2026-09-05
﻿// ?SkipNext@Debug@@SA_N_N@Z
// partial score=0.95 date=2026-09-05
//
// THE SCHEDULING MISS IS FIXED. The 2026-09-03 bank recorded it exactly:
// "retail stores the captured return address to its slot immediately and then
// loads the Debug pointer, where cl loads the pointer first". The cause is
// that the singleton pointer is VOLATILE:
//
//     Debug *volatile theDebug;
//
// As a plain `Debug *` the global is an ordinary load and MSVC 7.1 hoists it
// into the gap after `mov eax,[ebp+4]`, ahead of the volatile store. Declaring
// it volatile makes the load a volatile access, which cannot be reordered past
// the volatile store, and the whole instruction sequence falls into retail's
// order. 13 differing bytes of 33 down to 6, exact prefix 11.
//
// The same one-word change fixes the identical miss in the __heap_abort bank
// at reverse/attempts/0x000398a0.cpp -- that body IS this one inlined -- so
// apply it to any other Debug-singleton body that shows the same symptom.
//
// WHAT IS LEFT is a register phase, and it is the only difference:
//
//   retail   8b 55 08  mov edx,[ebp+8]   ...  8b 01  mov eax,[ecx]   ... 52 push edx ... ff 50 5c
//   this     8b 45 08  mov eax,[ebp+8]   ...  8b 11  mov edx,[ecx]   ... 50 push eax ... ff 52 5c
//
// Retail puts the pushed DATA in edx and the VTABLE in eax; MSVC 7.1 does the
// reverse. In __heap_abort the same phase runs through all four virtual calls
// and alternates, so the first vtable load sets it for the whole body -- flip
// that one and the rest follow.
//
// THOSE IDEAS ARE NOW REFUTED, along with 36 others (2026-09-06). The six
// bytes are the allocator wall in its purest form: the instruction sequence,
// the frame, the schedule and the length are all exact, and the ONLY
// difference is that retail assigns edx to the argument temp and eax to the
// vtable load where MSVC 7.1 does the reverse. Nothing reachable from source
// or the command line moves it.
//
// Inert (byte-identical 6-byte miss): /Ob0 /Ob1 /Ob2 /Oa /Ow /Og /Ot /Ox /Gy
// /GX /G5 /G6 /G7 /GB /Oi /Op /Gm /Zp1 /GS /Gf /GF, /MT, /ML,
// #pragma optimize("a",off), #pragma optimize("w",off); and as source shapes,
// hoisting the singleton into a local before the call, copying the bool into a
// local first, and const-qualifying the volatile capture.
//
// Destructive (changes the length, so strictly worse): /Os, /O1,
// #pragma optimize("t",off) -> 29 bytes; #pragma optimize("g",off) and
// #pragma optimize("",off) -> 44; a volatile PARAMETER or a non-volatile copy
// of the capture -> 35; `set ? true : false` -> 38; a volatile local for the
// singleton -> 41. Dropping the volatile from the singleton, spelling it as a
// reference, dereferencing it as (*theDebug), or laundering the capture
// through a volatile-pointer cast all lose the prologue as well: 13 of 33.
//
// The phase is a front-end temp-numbering artifact, not a knob. Retail's
// register assignment is what you get when the OBJECT expression is numbered
// before the arguments; MSVC 7.1 here numbers the arguments first, and no
// spelling of a virtual call through a global singleton reverses that. This
// body needs new information -- a different compiler point release, or a
// second body that pins the numbering order -- not more variants. It is the
// same wall as 0x0000D050, 0x00019260 and 0x0000C000; treat all of them as one
// problem. Only one toolchain is available to build.py (VC71_ROOT), so the
// point-release theory cannot be tested from this host.
// cl: /Oy- /MD
//
// WWDebug Debug::SkipNext. It records the call site for the crash or assert
// that follows: it captures its own return address and hands that, with its
// argument, to slot 0x5C of the Debug singleton at 0x00DE0880.
//
// Identified from ProfileAllocMemory, which calls it out of line here where
// _heap_abort in debug_debug.cpp inlines it - the same body seen from both
// sides. This engine takes a bool where the reference header declares it void.
//
// /Oy- puts the ebp frame back; without it cl reads the return address off esp
// with no frame at all. The captured address is held volatile because retail
// stores it to its slot and reloads it rather than keeping it in a register,
// which is the push ecx in the prologue.

extern "C" void *_ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)

class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual bool SetCrashAddress(void *address, bool set);

	static bool SkipNext(bool set);
};

Debug *volatile theDebug;

bool Debug::SkipNext(bool set)
{
	void *volatile address = _ReturnAddress();

	return theDebug->SetCrashAddress(address, set);
}
