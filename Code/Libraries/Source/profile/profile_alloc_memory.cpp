// cl: /MD
//
// profile.cpp ProfileAllocMemory, verbatim from the Generals reference:
//
//   HGLOBAL h = GlobalAlloc(GMEM_FIXED, numBytes);
//   if (!h) DCRASH_RELEASE("Debug mem alloc failed");
//   return (void *)h;
//
// GMEM_FIXED is zero, and GlobalAlloc is the import at 0x00BBA240.
//
// The crash arm is the same macro _heap_abort expands, with one difference
// that is worth having in the ledger: here Debug::SkipNext is CALLED, at
// 0x00038790, where _heap_abort has it inlined. Its body is what identifies
// it - it captures _ReturnAddress() into a local and hands that plus its
// argument to Debug slot 0x5C, which is exactly what the reference's own
// header says SkipNext is for: it records the call site so the crash that
// follows can be associated with it. This engine's takes a bool where the
// reference declares it void.

extern "C" __declspec(dllimport) void *__stdcall GlobalAlloc(unsigned int flags,
		unsigned int bytes);

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

	static bool SkipNext(bool set);
};

Debug *theDebug;

void *ProfileAllocMemory(unsigned int numBytes)
{
	void *h = GlobalAlloc(0, numBytes);
	if (!h)
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Debug mem alloc failed").CrashDone(true);
	}
	return h;
}
