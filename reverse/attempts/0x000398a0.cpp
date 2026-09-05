// __heap_abort
// partial score=0.9 date=2026-09-05
﻿// __heap_abort
// partial score=0.9 date=2026-09-05
//
// THE SCHEDULING MISS IS FIXED, by one word: the singleton pointer is
// VOLATILE.
//
//     Debug *volatile theDebug;
//
// As a plain `Debug *` the global is an ordinary load and MSVC 7.1 hoists it
// ahead of the volatile store of the captured return address; as a volatile
// access it cannot be reordered past that store, and the sequence falls into
// retail's order. This is the same fix that took the SkipNext bank at
// reverse/attempts/0x00038790.cpp from 13 differing bytes to 6 -- that body IS
// the first half of this one, inlined -- and it is worth trying on any other
// Debug-singleton body showing the same symptom.
//
// 80 bytes against 80, exact prefix 17, and 8 bytes differ.
//
// WHAT IS LEFT is a register phase and nothing else. Retail puts the pushed
// DATA in edx and the VTABLE in eax at the first virtual call; MSVC 7.1 does
// the reverse:
//
//   retail   8b 55 fc  8b 01  6a 01  52  ff 50 5c
//   this     8b 45 fc  8b 11  6a 01  50  ff 52 5c
//
// The phase then ALTERNATES through the four virtual calls, so all eight
// differing bytes come from that single initial choice -- the second call is
// `8b 01 ff 50 60` against `8b 11 ff 52 60`, and the third inverts again to
// `8b 11 ... ff 52 6c` against `8b 01 ... ff 50 6c`. Flip the first vtable load
// into eax and the whole body follows. The last two calls
// (`8b c8 ff 52 38` and `8b c8 ff 52 4c`) already match.
//
// Untried ideas for the phase, in order: give SetCrashAddress a return value
// the caller uses, so eax is committed before the argument temp is created;
// spell the singleton as a reference rather than a pointer; and try /Ob0.
//
// Everything else here was already settled by the 2026-09-03 bank and still
// holds: every call is a virtual on the Debug * at 0x00DE0880, there is not
// one REL32 in the body, and the slots are 0x38 const char * stream operator,
// 0x4C CrashDone, 0x5C the address hand-off, 0x60 SkipNext, 0x6C CrashBegin.
// cl: /Oy- /MD
//
// WWDebug's replacement for the CRT's _heap_abort, the hook the DLL runtime
// calls when the heap is corrupt. The Generals reference spells the body
//
//   DCRASH_RELEASE("Fatal heap error.");
//
// and this engine's expansion of that macro is what the bytes show: capture
// the caller's address, hand it to the Debug singleton, skip the next filter,
// then open a crash, stream the message into it and finish it as fatal.
//
// Every call is a virtual on the Debug * held at 0x00DE0880 - there is not one
// REL32 in the body - so the slots are what had to be right: 0x38 is the
// const char * stream operator, 0x4C CrashDone, 0x5C the address hand-off,
// 0x60 SkipNext and 0x6C CrashBegin. CrashBegin is called with three zeros,
// which is the release form the reference's own comment describes: no file and
// no line, so the crash carries only the message.
//
// The `mov eax, [ebp+4]` at the top is _ReturnAddress(), and it is stored to a
// local before use rather than passed straight through.

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
	virtual Debug &operator<<(const char *text);
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void CrashDone(bool fatal);
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual bool SetCrashAddress(void *address, bool set);
	virtual void SkipNext();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual Debug &CrashBegin(const char *file, int line, const char *group);

	__forceinline static bool SkipNext(bool set);
};

Debug *volatile theDebug;

// Defined here rather than declared: this unit is debug_debug.cpp, where the
// definition lives, so cl inlines it. profile.cpp calls the same function out
// of line at 0x00038790 and that call site is what named it.
bool Debug::SkipNext(bool set)
{
	void *volatile address = _ReturnAddress();

	return theDebug->SetCrashAddress(address, set);
}

extern "C" void __cdecl _heap_abort(void)
{
	Debug::SkipNext(true);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Fatal heap error.").CrashDone(true);
}
