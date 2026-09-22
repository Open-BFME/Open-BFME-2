// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// _heap_abort, retail 0x000398A0 (80 bytes): the debug library's
// replacement for the C runtime's fatal-heap-error hook. Zero Hour's body
// is DCRASH_RELEASE("Fatal heap error."); BFME's release form of that macro
// first hands the caller's return address to the Debug singleton (vtable
// slot 0x5C), then calls SkipNext (0x60), CrashBegin(0, 0, 0) (0x6C), the
// const char * stream operator (0x38) and CrashDone(1) (0x4C) -- every call
// is a virtual through theDebug (0x00DE0880).
//
// The return address is captured with the same two-instruction __asm the
// out-of-line call-site recorder at 0x00038790 uses
// (Debug_recordCallsite.cpp); it is what spills the value to [ebp-4] before
// the first call. _ReturnAddress() keeps it in a register instead.

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;

// Abort process due to fatal heap error
// __heap_abort
extern "C" void __cdecl _heap_abort(void)
{
	unsigned returnAddress;
	__asm
	{
		mov eax, [ebp + 4]
		mov returnAddress, eax
	}
	theDebug->SetCrashAddress(reinterpret_cast<void *>(returnAddress), 1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Fatal heap error.").CrashDone(1);
}
