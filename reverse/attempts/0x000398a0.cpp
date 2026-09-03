// __heap_abort
// partial score=0.9 date=2026-09-03
// cl: /MD /Oy-
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
	virtual void SetCrashAddress(void *address, bool set);
	virtual void SkipNext();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual Debug &CrashBegin(const char *file, int line, const char *group);
};

Debug *theDebug;

extern "C" void __cdecl _heap_abort(void)
{
	void *volatile address = _ReturnAddress();

	theDebug->SetCrashAddress(address, true);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Fatal heap error.").CrashDone(true);
}
